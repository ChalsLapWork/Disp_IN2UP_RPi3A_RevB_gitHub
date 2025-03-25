#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/select.h>
#include "errorController.h"
#include "system.h"
#include "VFD.h"
#include "serial.h"
#include "VFDmenu.h"
#include "math.h"
#include "queue.h"

#define BUF_SIZE 256
#define BUFFER6_SIZE 400  // Tamaño del nuevo buffer6


// Estructura para compartir datos entre hilos
typedef struct {
    int serial_fd;           // Descriptor de archivo del puerto serial
    char buffer[BUF_SIZE];   // Buffer compartido
    char buffer6[BUFFER6_SIZE]; // Nuevo buffer para concatenar datos
    int data_ready;          // Bandera para indicar que hay datos nuevos
    int sizedata;
    pthread_mutex_t mutex;   // Mutex para proteger el buffer
} thread_data_t;//*********************************************************

pthread_t reader_thread, processor_thread;
thread_data_t data;
extern struct _DISPLAY_VFD_ vfd;

int init_Serial(void){
// Abre el puerto serial
  data.serial_fd = serialOpen("/dev/ttyAMA0", 9600);  // Cambia "/dev/ttyAMA0" y 9600 según tu configuración
  if (data.serial_fd == -1) {
        printf("%s Error al abrir el puerto serial.\n %s",CAMAR,CRESET);
        return 1;}
// Inicializa el mutex
    pthread_mutex_init(&data.mutex, NULL);
    data.data_ready = 0;  // Inicializa la bandera
// Crea el hilo lector
    if (pthread_create(&reader_thread, NULL, serial_reader, &data) != 0) {
        printf("%s Error al crear el hilo lector.\n %s",CAMAR,CRESET);
        return 1;}
// Crea el hilo procesador
    if (pthread_create(&processor_thread, NULL, cons_serial_processor, &data) != 0) {
        printf("%s Error al crear el hilo procesador.\n %s",CAMAR,CRESET);
        return 1;}
return 1;
}//fin de init serial++++++++++++++++++++++++++++++++++++++++++++++++

void cerrar_puerto_serial(void){
      serialClose(data.serial_fd);// Cierra el puerto serial
}//fin de cerrar puerto serial+++++++++++++++++++



// Hilo lector: Lee datos del puerto serial usando select
void *serial_reader(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char temp_buffer[BUF_SIZE];
    ssize_t bytes_read;
    fd_set read_fds;
    struct timeval timeout;
    int ncount;

    while (1) {
        // Configura el conjunto de descriptores de archivo
        FD_ZERO(&read_fds);
        FD_SET(data->serial_fd, &read_fds);
        // Configura el tiempo de espera (1 segundo)
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        int sizedata;
        // Espera a que haya datos disponibles en el puerto serial
        int ret = select(data->serial_fd + 1, &read_fds, NULL, NULL, &timeout);
        if (ret > 0 && FD_ISSET(data->serial_fd, &read_fds)) {
            bytes_read = read(data->serial_fd, temp_buffer, BUF_SIZE - 1);// Lee un bloque de bytes
            if (bytes_read > 0) {
                temp_buffer[bytes_read] = '\0';  // Asegura que el buffer esté terminado con un carácter nulo
                pthread_mutex_lock(&data->mutex);// Bloquea el mutex para proteger el buffer compartido
                strncpy(data->buffer6, temp_buffer,bytes_read);
                data->data_ready = 1;  // Indica que hay datos nuevos
                sizedata=bytes_read;
                data->sizedata=bytes_read;
                pthread_mutex_unlock(&data->mutex);// Desbloquea el mutex
                //printf("%s[LECTOR] Datos leídos:%s %s %s\n",CAZUL,CAMAR, temp_buffer,CRESET);  // Depuración
               printf("%sDatos recibidos (hex):%s%i %s", CVERD,CAMAR,sizedata,CRESET);
               for (int i = 0; i < sizedata; i++) {
                    printf("%s%02X %s ", CROJO, temp_buffer[i], CRESET);}
               for (int i = 0; i < sizedata; i++) {
                    printf("%s%c%s", CAMAR, temp_buffer[i], CRESET);}

                printf("\n");

 
            } else if (bytes_read == -1) {
                printf("%s[LECTOR] Error al leer del puerto serial.%s\n",CROJO,CRESET);
            }
        } else {if (ret == -1) {
                     printf("[LECTOR] Error en select.\n");}
                else{if(ncount++>350){ ncount=0;
                          printf("%sSin datos Seriales... %s",CAMAR,CRESET);}}}
    }//fin while++++++++++++++++++++++
return NULL;
}//fin de serial reader+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Hilo procesador: Procesa los datos del buffer compartido ++++++++++++++++++++++++++++++++++++
void *cons_serial_processor(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char local_buffer[BUFFER6_SIZE];
    int sizedata;
    while (1) {
        pthread_mutex_lock(&data->mutex);// Bloquea el mutex para acceder al buffer compartido
        if (data->data_ready) {// Si hay datos nuevos, los copia y los procesa
            strncpy(local_buffer, data->buffer6, data->sizedata);
            data->data_ready = 0;  // Reinicia la bandera
            data->buffer6[0] = '\0';// Limpia buffer6 después de copiar los datos
            sizedata=data->sizedata;
            if(sizedata==0){
                 mens_Warnning_Debug(" error en consumidor serial");exit(1);}
            local_buffer[sizedata]='\0';//Asegura el caracter nulo al final
            pthread_mutex_unlock(&data->mutex);// Desbloquea el mutex
            printf("%s[Consumdr] a procesar:%s %i %s %s %s",CAQUA,CAMAR,sizedata,CMORA, local_buffer,CAQUA);
            for(int i=0;i<sizedata;i++){
                    printf("%02X  ",local_buffer[i]);}
            printf("\n%s",CRESET);        
            Procesamiento_de_cadena_serProc(&local_buffer[0],sizedata);}// Procesa los datos (en este caso, simplemente los imprime)
        else {
            pthread_mutex_unlock(&data->mutex);}// Desbloquea el mutex si no hay datos nuevos
        usleep(1000);  // Espera 1 ms,// Espera un poco antes de verificar nuevamente
    }//fin while-----------------------------------------------------------
return NULL;
}//fin de consumidor serial protocolo procesador del prootocolo++++++++++++++++++++++++++++++++++++



/* ¨Prpcesamiento de cadena de datos que llega del puerto serial|
 procesa la cadena completa y si se queda el protocolo a medias y se termina la 
   cadena se sale quedando en el estado que estaba para recargar la cadena******************************/
void Procesamiento_de_cadena_serProc(char *c,int size){
static unsigned char estado;
static unsigned char len,cmd,crc,len1;//estado de la cadena
static unsigned short int indice; //el buffer6 es  de 1024 tamaño
static unsigned char param[PARAM_SIZE_COMANDOS],index;
//unsigned char crc_array[PARAM_SIZE_COMANDOS],ret;
static unsigned char nParam,nParam0;//numero de parametros    .
unsigned char dato;

 indice=0;
 do{dato=*(c+indice);                   //  while(indice<size){
   switch(estado){
     default:estado=1;//sin break 
      case 1:if(dato==STX){
                    estado=2;}
              break;
      case 2:len=dato;estado++;break;
      case 3:cmd=dato;
             if(len<2){estado=1;}//error de numeros de comm
             else{if(len==2){estado=5;}//sin parametros el comando
                  else{estado=4;nParam0=0;nParam=len-2;}}//con parametros
             break;
      case 5:crc=dato;
             if(crc_Eval(len,cmd,&param[0],crc))
                 estado=6;//al ETX
             else{estado=1;}//error
             break;
      case 6:if(dato==ETX){
               procesarComando(cmd,&param[0]);}
             estado=1;break;
      case 4:param[nParam0++]=dato;
             if(nParam0==nParam)
                     estado=5;
             break;}//fin switch-++++++++++++++++++++++++
  }while(++indice<size);//fin while ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}//fn de procesamiento de cadena que llega del erial de la procesadora -------------------------------





//Procesamiento de Comando con Parametros
void procesarComando(unsigned char cmd,unsigned char *param){
unsigned char x;
unsigned char mens[]={"COMANDO BARRA ACEPTADO"};
unsigned char mens2[]={"COMANDO SENSE ACEPTADO"};
unsigned char mens3[]={"COMANDO DESCONOCIDO "};

    x=*param;    
    printf(" %d %c",x,x);
    switch(cmd){
        case CMD_DET_ON:printf("%s %s %s",CVERD,mens,CRESET);break; //aumenta el conteo de Rechazo
        case CMD_BARRA://2+8+9+1 cuadritos
                       Serial_Command_Barra_Detection(*param); 
                       printf("%s %s  %i %s:%i",CAMAR,mens,cmd,CRESET,*param);
                       break;  //mueve la barra de deteccion
        case CMD_SENS_PHASE:Serial_Command_Sens_Phase_Det(param);
                            printf("%s %s  %i %s:%i",CAMAR,mens2,cmd,CRESET,*param);
                            break;
        case CMD_DET_PM:printf("%s %s %s",CMORA,mens,CRESET);break; //hace display de los parametros de Portal Inicio
        default:printf("%s %s %s",CAMAR,mens3,CRESET);break;
    }//fin switch ----------------------------------------------------------------------------
}//fin de procesar cmd+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




/*****************************************************************************************+++*/
/*****************************************************************************************+++*/
/*****************************************************************************************+++*/
/*****************************************************************************************+++*/
/*****************************************************************************************+++*/
/*****************************************************************************************+++*/
/*****************************************************************************************+++*/
/****COMANDOS SERIALES         ***********************************************************+++*/

/* CUADRITOS:/2+8+9+1 cuadritos
    2:VACIOS, 8:VACIOS No alcanza deteccion, 9: cuadros llenos Deteccion Alcanzada
    1:Cuadro invisible, no se pinta 
    valores aceptados 15,20,25,30,35...95 de 5 en cinco*/
void Serial_Command_Barra_Detection(unsigned char parametro){
unsigned char var;
    
    switch(parametro){//desntro de los display func se determina si se despleigua o no
        case 15:var=1;break; 
        case 20:var=2;break;
        case 25:var=3;break;
        case 30:var=4;break;
        case 35:var=5;break;
        case 40:var=6;break;
        case 45:var=7;break;
        case 50:var=8;break;
        case 55:var=9;break;
        case 60:var=10;break;
        case 65:var=11;break;
        case 70:var=12;break;
        case 75:var=13;break;
        case 80:var=14;break;
        case 85:var=15;break;
        case 90:var=16;break;
        case 95:var=17;break;
        default:if(parametro>15)
                    var=recalcular_valor_Ser_Barr_det(parametro);
                break;}
    display_Barra_Deteccion(var);
    display_CuentaRechazosProducto(parametro);
}//fin serial comando  barra deteccion+++++++++++++++++++++++++++++++++++++++++++++++++++


/* comando que recibe la sensibilidad y la pase detectada 
   param0: sensibilidad byte0
   param1: sensibilidad byte1, param2: phase-entero param3:phase-frac */
void Serial_Command_Sens_Phase_Det(unsigned char *parametros){
union{
    unsigned short int usint1;
    unsigned char c[2];
}usi;    
     usi.c[1]=*parametros;
     usi.c[0]=*(parametros+1);
     display_Sens_Phase(usi.usint1,*(parametros+2),*(parametros+3));
}//fin de serial comando sensibilidad phase detectada a desplegar