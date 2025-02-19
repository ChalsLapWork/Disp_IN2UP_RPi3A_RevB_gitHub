#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "system.h"
#include "VFDthread.h"
#include "errorController.h"
#include "VFD.h"
#include "queue.h"


#ifndef debug_level1
  #include <wiringPi.h>
#endif

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


/*  init los threads de manera mas facil   * */
void init_VFD_Threads(void){//
    // Inicialización de semáforos
    sem_init(&sem_llenos, 0, 0);
    sem_init(&sem_vacios, 0, NUM_ENTRADAS);

    // Crear el hilo productor
    pthread_create(&hilo_productor, NULL, VFDserial_SendBlockProductor, NULL);

    // Crear el hilo consumidor
    pthread_create(&hilo_consumidor, NULL, VFDserial_SendBlockConsumidor, NULL);

    // Hilo principal envía datos continuamente
    unsigned char array1[] = {STX,0x05,COMANDO_STRING,0x41, 0x42, 0x43, 79,ETX,'\0'};  // "ABCD"
    char string1[] = "Hola, soy un string 1\0";
    unsigned char array2[] = {STX, 0x06, COMANDO_STRING,'h','o','l','a',0x34, ETX,'\0'};
    char string2[] = "Este es otro string más largo\0";

    int iteracion = 0;
    while (1) {
        if (iteracion % 4 == 0) {
            VFDserial_SendBlock_buf(array1, sizeof(array1));}
        else if (iteracion % 4 == 1) {VFDserial_SendBlock_buf(string1, strlen(string1) + 1);} 
             else if (iteracion % 4 == 2) {VFDserial_SendBlock_buf(array2, sizeof(array2));} 
                  else {VFDserial_SendBlock_buf(string2, strlen(string2) + 1);}
        iteracion++;
        usleep(500000);  // Espera para simular nuevos datos
    }//fin which+++++++++++++++++++++++++++++++++++++++++++++++++++++++
}//fin de initialized VFD threads++++++++++++++++++++++++++++++++++++++


// Función principal para agregar datos al buffer circular
unsigned char VFDserial_SendBlock_buf(void *ptr, size_t size) {
    if (size > MAX_LEN) {
        fprintf(stderr, "Error: El tamaño de los datos excede el máximo permitido.\n");
        return 0;}
    sem_wait(&sem_vacios);
    pthread_mutex_lock(&mutex_buffer);
    buffer_circular[in].len = size;
    memcpy(buffer_circular[in].data, ptr, size);
    printf("Hilo Principal: Datos agregados al buffer (len: %zu)\n", size);
    in = (in + 1) % NUM_ENTRADAS;
    pthread_mutex_unlock(&mutex_buffer);
    sem_post(&sem_llenos);
return 1;
}//fin VFDserial_SendBlock++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Hilo Productor: vacía todo el buffer circular a buffer2
void *VFDserial_SendBlockProductor(void *arg) {
    while (1) {
        sem_wait(&sem_llenos);
        pthread_mutex_lock(&mutex_buffer);
        pthread_mutex_lock(&mutex_buffer2);
        for (int i = 0; i < NUM_ENTRADAS; i++) {
            size_t len = buffer_circular[out].len;
            if (len > 0 && buffer2_len + len <= MAX_BUFFER_LEN) {
                memcpy(buffer2 + buffer2_len, buffer_circular[out].data, len);
                buffer2_len += len;
                printf("Productor: Copió datos al buffer2 (len: %zu, total en buffer2: %zu)\n", len, buffer2_len);}
            out = (out + 1) % NUM_ENTRADAS;}
        pthread_mutex_unlock(&mutex_buffer2);
        pthread_mutex_unlock(&mutex_buffer);
        sem_post(&sem_vacios);
        usleep(100000);
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
            printf("Consumidor: Transferencia de datos de buffer2 a buffer3 (len: %zu)\n", len);
            pthread_mutex_unlock(&mutex_buffer2);
            // Llamar a VFDserial_SendBlock_Tx para procesar buffer3 completo
            VFDserial_SendBlock_Tx(buffer3, buffer3_len); } 
        else {pthread_mutex_unlock(&mutex_buffer2);}
        usleep(100000);  // 100 ms para simular procesamiento continuo
       }//fin while+++++++++++
return NULL;
}///fin VFDserial_SendBlockConsumidor++++++++++++++++++++++++++++++++++++++++++++++++

// Función que procesa buffer3 completo (como un gran array de datos)
void VFDserial_SendBlock_Tx(unsigned char *buffer, size_t len) {
unsigned char estado = 0, cmd, crc_calculado, crc_recibido;
unsigned char c[MAX_NUM_CHAR_VFD];
unsigned char *str = buffer;
size_t i = 0, datos_len = 0;
static int count = 0;

    printf("Consumidor-Tx: Procesando buffer completo (len: %zu), cont=%i\n", len, count);
    if (count++ == 19) { printf("Stop here\n");}

    while (i < len) {
        switch (estado) {
            case 0:printf("Estado 0: Buscando STX...\n");// Buscar STX
                   if(*str==STX){printf("Encontrado STX en la posición %zu\n", i);estado++;}  // Avanzamos al siguiente estad
                   str++;break;
            case 1:printf("Estado 1: Leyendo el byte de longitud (LEN)...\n");  // Leer el byte de longitud (LEN)
                   if (*str+3>len-i){// Verificamos que haya suficiente espacio
                       mens_Warnning_Debug("Error: La longitud de los datos no coincide con el tamaño del buffer.");
                       return;}
                   datos_len = *str - 1;  // Descontamos el byte de `len` y el byte `cmd`
                   printf("Longitud de datos: %d\n", datos_len);
                   str++;estado++;break;
            case 2:printf("Estado 2: Leyendo el byte de comando (CMD)...\n");  // Leer el byte de comando (CMD)
                   cmd=*str++;printf("Comando (CMD): %d\n", cmd);
                   estado++;break;
            case 3:printf("Estado 3: Leyendo los datos...\n");// Leer los datos  
                   for(size_t j=0;j<datos_len;j++) {
                           c[j] = *str++;  // Almacenamos los datos en el array `c`
                           printf("Dato %zu: %02X\n", j, c[j]);}
                   estado++;break;
            case 4:printf("Estado 4: Calculando y verificando CRC...\n");  // Calcular y verificar CRC
                   crc_calculado = getCRC_v2(buffer + 1, datos_len + 1);  // Sumar 2 para incluir `len` y `cmd`
                   crc_recibido = *str++;  // Leemos el CRC recibido
                   printf("CRC: %02X, CRC recibido: %02X\n", crc_calculado, crc_recibido);
                   if (crc_calculado != crc_recibido) {mens_Warnning_Debug("Error: El CRC recibido no coincide con el calculado.");
                                                       estado=7;}  // Reiniciar el ciclo para buscar el siguiente STX
                   else {estado++;}break;
            case 5:printf("Estado 5: Verificando si el paquete termina con ETX...\n");  // Verificar ETX
                   if (*str == ETX) {printf("Encontrado ETX\n");estado = 6;}  // Avanzamos al siguiente estado si encontramos ETX
                   else {mens_Warnning_Debug("Error: No se encontró ETX al final del paquete.");
                        estado = 7;}  // Reiniciar el ciclo para buscar el siguiente STX
                   str++;break;
            case 6:printf("Estado 6: Procesando el paquete...\n");// Procesar el paquete  
                   procesar_Paquete(cmd, c, datos_len);estado++;break;  // Reiniciar el ciclo para buscar el siguiente STX
            case 7:printf("Estado 7: Reiniciando búsqueda para el siguiente paquete...\n");  // Reiniciar y buscar el siguiente paquete
                   estado=0;break; // Volver al estado inicial para buscar el siguiente STX
            default:printf("Estado desconocido. Reiniciando...\n");
                    estado = 0;  // En caso de un estado inesperado, reiniciamos
                    break;}//fin sitch+++++++++++++++++++++++++++++
           i++;}//fin while  Avanzamos al siguiente byte en el buffer
return;
}//fin VFDserial_SendBlock_Tx+++++++++++++++++++++++++++++++++++++++++++++++++++




