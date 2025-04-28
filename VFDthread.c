#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "VFDthread.h"
#include "queue.h"
#include "errorController.h"
#include "VFD.h"
#include <stdint.h>
#include "VFDmenu.h"
#include "Memoria.h"


#ifndef debug_level1
  #include <wiringPi.h>
#endif

    
#define PROBAR_HILOS_CONS_PROD_VFD 0 //1:probar hilos productor consumidor VFD


extern struct _DISPLAY_VFD_ vfd;

// Estructura para almacenar datos en el buffer circular
typedef struct {
    unsigned char data[MAX_LEN];
    size_t len;
} DatosTransmision;


DatosTransmision buffer_circular[NUM_ENTRADAS];  // Buffer circular
int in = 0, out = 0;

unsigned char buffer2[MAX_BUFFER_LEN];  // Buffer lineal para concatenar datos del buffer circular
size_t buffer2_len = 0;

unsigned char buffer3[MAX_BUFFER_LEN];  // Buffer final para enviar a VFDserial_SendBlock_Tx
size_t buffer3_len = 0;

pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_llenos, sem_vacios;
pthread_mutex_t mutex_buffer2 = PTHREAD_MUTEX_INITIALIZER;

pthread_t hilo_productor, hilo_consumidor;

pthread_mutex_t lock_Actualizar = PTHREAD_MUTEX_INITIALIZER;//// Mutex para proteger variables compartidas
volatile int reiniciar_temporizador = 0;//// Variables compartidas
volatile int temporizador_activo = 0;
pthread_t temporizador_thread;


/*  init los threads de manera mas facil   * */
void init_VFD_Threads(void){//
    sem_init(&sem_llenos, 0, 0);// Inicialización de semáforos
    sem_init(&sem_vacios, 0, NUM_ENTRADAS);

    pthread_create(&hilo_productor, NULL, VFDserial_SendBlockProductor, NULL);  // Crear el hilo productor
    pthread_create(&hilo_consumidor, NULL, VFDserial_SendBlockConsumidor, NULL);// Crear el hilo consumidor

  #if ( PROBAR_HILOS_CONS_PROD_VFD == 1 )
    // Hilo principal envía datos continuamente
    unsigned char array1[]={STX,0x05,COMANDO_STRING,0x41, 0x42, 0x43, 0x8E,ETX};  // "ABC"
    unsigned char array2[]={STX,0x0E,COMANDO_STRING,0x20,0x48,0x6F,0x6C,0x61,0x20,0x4D,0x75,0x6E,0x64,0x6F,0x20,0xC8,ETX};//" Hola Mundo "
    unsigned char array3[]={STX,0x11,COMANDO_STRING,0x20,0x50,0x6F,0x72,0x74,0x61,0x6C,0x20,0x49,0x6E,0x69,0x63,0x69,0x6F,0x20,0xD3,ETX};//" Portal Inicio"
    unsigned char array4[]={STX,0x0A,COMANDO_STRING,0x20,0x54,0x65,0x73,0x74,0x2D,0x31,0x20,0x6C,ETX};//" Test-1 "

    int iteracion = 0;
    while (1) {
        if (iteracion % 4 == 0) {
            VFDserial_SendBlock_buf(array1, sizeof(array1));}
        else if (iteracion % 4 == 1) {VFDserial_SendBlock_buf(array2, sizeof(array2));} 
             else if (iteracion % 4 == 2) {VFDserial_SendBlock_buf(array3, sizeof(array3));} 
                  else {VFDserial_SendBlock_buf(array4,sizeof(array4));}
        iteracion++;
        usleep(500000);  // Espera para simular nuevos datos
    }//fin which+++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
    
    


}//fin de initialized VFD threads++++++++++++++++++++++++++++++++++++++


// Función principal para agregar datos al buffer circular
unsigned char VFDserial_SendBlock_buf(void *ptr, size_t size) {
    if (size > MAX_LEN) {
        fprintf(stderr, "Error: El tamaño de los datos excede el máximo permitido.\n");
        mens_Warnning_Debug("VFD fifo no hay");        return 0;}
    sem_wait(&sem_vacios);//si es cero detiene hilo, si no decrementa y continua
    pthread_mutex_lock(&mutex_buffer);
    buffer_circular[in].len = size;
    memcpy(buffer_circular[in].data, ptr, size);
    //printf("\033[32m Hilo Principal: Datos agregados al buffer (len: %zu)\033[0m\n", size);
    in = (in + 1) % NUM_ENTRADAS;
    pthread_mutex_unlock(&mutex_buffer);
    sem_post(&sem_llenos);//incrementa valor lugares llenos
return 1;
}//fin VFDserial_SendBlock++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Hilo Productor: vacía todo el buffer circular a buffer2
void *VFDserial_SendBlockProductor(void *arg) {
unsigned char estado=0,i=0,len=0;
int semaforo;
//const unsigned char 
    while (1) {
        switch(estado){
            case 1:sem_wait(&sem_llenos);//si hay recurso avanza
                   estado++;break;
            case 2:pthread_mutex_lock(&mutex_buffer);
                   pthread_mutex_lock(&mutex_buffer2);
                   estado++;i=0;break;
            case 3:if(i<NUM_ENTRADAS)estado++;
                   else{estado=40;}break;  
            case 4:len = buffer_circular[out].len;estado++;break;
            case 5:if (len > 0 && buffer2_len + len <= MAX_BUFFER_LEN)
                        estado++;else{estado=30;}break;
            case 6:memcpy(buffer2 + buffer2_len, buffer_circular[out].data, len);
                   buffer2_len+=len;
                   sem_post(&sem_vacios);//incrementa vacios,
                   //printf("Productor: Copió datos al buffer2 (len: %i, total en buffer2: %zu)\n", len, buffer2_len);
                   out = (out + 1) % NUM_ENTRADAS;
                   estado++;break;
            case 7:sem_getvalue(&sem_llenos,&semaforo);
                   if(semaforo>0){ i++;estado++;}
                   else{estado=40;}break;
            case 8:sem_wait(&sem_llenos);
                   estado=3;break;
            case 30:if(len>0) mens_Warnning_Debug(" Cadena muy grande, no cabe en buffer"); 
                    estado=7;break;      
            case 40:pthread_mutex_unlock(&mutex_buffer2);
                    pthread_mutex_unlock(&mutex_buffer);
                    usleep(100000);//100milisecond
                    estado=1;break;
           default:estado=40;break;}    
    } //fi nwhile+++++++++++++++++++
return NULL;
}//fin VFDserial_SendBlockProductor+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Hilo Consumidor: transfiere buffer2 a buffer3 y llama a VFDserial_SendBlock_Tx
void *VFDserial_SendBlockConsumidor(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex_buffer2);

        if (buffer2_len > 0) {
            size_t len = buffer2_len;
            memcpy(buffer3, buffer2, len);
            buffer3_len = len;
            buffer2_len = 0;
            //printf("Consumidor: Transferencia de datos de buffer2 a buffer3 (len: %zu)\n", len);
            pthread_mutex_unlock(&mutex_buffer2);
            // Llamar a VFDserial_SendBlock_Tx para procesar buffer3 completo
            VFDserial_SendBlock_Tx(buffer3, buffer3_len); } 
        else {pthread_mutex_unlock(&mutex_buffer2);}
        usleep(100000);  // 100 ms para simular procesamiento continuo
       }//fin while+++++++++++
return NULL;
}///fin VFDserial_SendBlockConsumidor++++++++++++++++++++++++++++++++++++++++++++++++

//activar teclado despues de un tiempo
void activar_Teclado(void){
pthread_t thread;
    pthread_create(&thread, NULL, resetKeypadEnable, NULL);
    pthread_detach(thread);// Desprendemos el hilo para que se ejecute independientemente
}//fin activar teclado+++++++++++++++++++++++++++++++++++++++++++++


// Función que será ejecutada por el hilo
void* resetKeypadEnable(void* arg) {
    usleep(700000);  // Espera 500 milisegundos (500,000 microsegundos)
    vfd.keypad.enable = 1;  // Ponemos la bandera enable a 1
    //printf("vfd.keypad.enable = 1\n");
return NULL;
}//fin reset keypad eneable++++++++++++++++++++++++++++++++++++++++

// Función que procesa buffer3 completo (como un gran array de datos)
void VFDserial_SendBlock_Tx(unsigned char *buffer, size_t len) {
unsigned char estado = 0, cmd=0, crc_calculado, crc_recibido;
unsigned char c[MAX_NUM_CHAR_VFD];
unsigned char *str = buffer;
size_t i = 0, datos_len = 0;
static int count = 0;
unsigned char *array_crc,index=0,new_len;

    //printf("Consumidor-Tx: Procesando buffer completo (len: %zu), cont=%i\n", len, count);
    if (count++ == 19) { printf("Stop here\n");}
    
    while (i < len) {
        switch (estado) {
            case 0://printf("Estado 0: Buscando STX...\n");// Buscar STX
                   if(*str==STX){//printf("Encontrado STX en la posición %zu\n", i);
                                 estado++;}  // Avanzamos al siguiente estad
                   str++;i++;break;
            case 1://printf("Estado 1: Leyendo el byte de longitud (LEN)...\n");  // Leer el byte de longitud (LEN)
                   //if (*str+3>=len-i){// Verificamos que haya suficiente espacio
                     //  mens_Warnning_Debug("Error: La longitud de los datos no coincide con el tamaño del buffer.");
                       //return;}
                   datos_len = *str;  // Descontamos el byte de `len` y el byte `cmd`
                   //printf("Longitud de datos: %d\n", (int)datos_len);
                   str++;i++;estado++;break;
            case 2://printf("Estado 2: Leyendo el byte de comando (CMD)...\n");  // Leer el byte de comando (CMD)
                   cmd=*str++;i++;//printf("Comando (CMD): %d\n", cmd);
                   new_len=datos_len;
                   array_crc=(unsigned char *)malloc(new_len * sizeof(unsigned char));
                   if(array_crc==NULL){mens_Warnning_Debug("Error al asignar memoria");estado=0;}
                   else{array_crc[0]=new_len;array_crc[1]=cmd;index=2;}
                   if(datos_len==2)  estado=4;else estado++;break;
            case 3://printf("Estado 3: Leyendo los datos...\n");// Leer los datos  
                   {unsigned char j;
                   switch(cmd){
                       case 's'://STRING
                                for(j=0;j<datos_len-3;j++) {
                                    c[j] = *str++;i++;  // Almacenamos los datos en el array `c`
                                    array_crc[index++]=c[j];}//Array que se va ha usar para calcular el crc
                                datos_len-=4;//para el procesamiento    
                                break;
                       default:for(j=0;j<datos_len-2;j++){
                                     c[j]=*str++;i++;  
                                     array_crc[index++]=c[j];}
                               break;}             
                   //printf("Dato %i: %02X %i  %c\n", j, c[j],c[j],c[j]);
                   }                
                   estado++;break;
            case 4://printf("Estado 4: Calculando y verificando CRC...\n");  // Calcular y verificar CRC
                   crc_calculado = getCRC_v2(array_crc,new_len);  // Sumar 2 para incluir `len` y `cmd`
                   crc_recibido = *str++;i++;  // Leemos el CRC recibido
                   //printf("CRC: %02X, CRC recibido: %02X\n", crc_calculado, crc_recibido);
                   if (crc_calculado != crc_recibido) {mens_Warnning_Debug("Error: El CRC recibido no coincide con el calculado.");
                                                       estado=7;}  // Reiniciar el ciclo para buscar el siguiente STX
                   else {estado++;}break;
            case 5://printf("Estado 5: Verificando si el paquete termina con ETX...\n");  // Verificar ETX
                   if (*str == ETX) {
                         //printf("Encontrado ETX\n");
                         estado = 6;}  // Avanzamos al siguiente estado si encontramos ETX
                   else {mens_Warnning_Debug("Error: No se encontró ETX al final del paquete.");
                        estado = 7;}  // Reiniciar el ciclo para buscar el siguiente STX
                   break;
            case 6://printf("Estado 6: Procesando el paquete...\n");// Procesar el paquete  
                   procesar_Paquete(cmd, c, datos_len);estado++;break;  // Reiniciar el ciclo para buscar el siguiente STX
            case 7://printf("Estado 7: Reiniciando búsqueda para el siguiente paquete...\n");  // Reiniciar y buscar el siguiente paquete
                   estado=0;break; // Volver al estado inicial para buscar el siguiente STX
            default://printf("Estado desconocido. Reiniciando...\n");
                    estado = 0;  // En caso de un estado inesperado, reiniciamos
                    break;}//fin sitch+++++++++++++++++++++++++++++
       }//fin while  Avanzamos al siguiente byte en el buffer
return;
}//fin VFDserial_SendBlock_Tx+++++++++++++++++++++++++++++++++++++++++++++++++++

void* imprimir_char_con_delay(void* arg) {
    //DatosHilo* datos = (DatosHilo*)arg;
    unsigned char datos=(unsigned char)(uintptr_t)arg;
    usleep(375000);  // 1.5 segundos = 1,500,000 microsegundos
    VFDposicion(datos,POSY2);
    VFDserial_SendChar('*');// Imprimir espacios y luego el carácter
    return NULL;
}//fin imprimir_char_con_delay------------------------------------------------

void VFDserial_SendChar_Asterisco(unsigned char cursorx){
pthread_t hilo_Asterisco;

    if(pthread_create(&hilo_Asterisco,NULL,imprimir_char_con_delay,(void*)(uintptr_t)cursorx)!=0){
         perror("pthrear_create error asterisco");
         return;} // No se hace pthread_join, el hilo se ejecuta en segundo plano
    pthread_detach(hilo_Asterisco);// // Lo marcamos como "detached" para que libere recursos al terminar
}//fin VFDserial_SendChar_Asterisco--------------------------------------------


//se actualizan datos que son cuenta de producto y cuanta de rechazos
void actualizador_datos1(void){ 
    pthread_mutex_lock(&lock_Actualizar);
    if (!temporizador_activo) {temporizador_activo = 1;
        reiniciar_temporizador = 0; // Por si quedó activado
        pthread_create(&temporizador_thread, NULL, temporizador_func, NULL);
        pthread_detach(temporizador_thread);} // No nos interesa esperar que termine
    //else {reiniciar_temporizador = 1;}//
    pthread_mutex_unlock(&lock_Actualizar);
}//fin actualizar datos1+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Se crea hilo para poder escribir cuenta prod y rechazsos
void* temporizador_func(void *arg) {
    int segundos = 300; // 5 minutos
    for (int i = 0; i < segundos; i++) {
        sleep(1);
        pthread_mutex_lock(&lock_Actualizar);
        if (reiniciar_temporizador) {
            reiniciar_temporizador = 0;
            pthread_mutex_unlock(&lock_Actualizar);
            temporizador_activo = 0;  // Permitir lanzar uno nuevo
            return NULL;  }// Cancelar este hilo, se iniciará otro nuevo
        pthread_mutex_unlock(&lock_Actualizar);}
    pthread_mutex_lock(&lock_Actualizar);
    guardar_estado_Contadores();
    sleep(3);//que espere 3 segundos. antes que se vuelva a guardar +5seg
    temporizador_activo = 0;  // Marcamos que ya se puede iniciar otro hilo
    pthread_mutex_unlock(&lock_Actualizar);
return NULL;
}//fin actualizar datos++++++++++++++++++++++++++++++++++++++++++++++++++++++++


