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

#define BUF_SIZE 256
#define BUFFER6_SIZE 1024  // Tamaño del nuevo buffer6


// Estructura para compartir datos entre hilos
typedef struct {
    int serial_fd;           // Descriptor de archivo del puerto serial
    char buffer[BUF_SIZE];   // Buffer compartido
    char buffer6[BUFFER6_SIZE]; // Nuevo buffer para concatenar datos
    int data_ready;          // Bandera para indicar que hay datos nuevos
    pthread_mutex_t mutex;   // Mutex para proteger el buffer
} thread_data_t;//*********************************************************

pthread_t reader_thread, processor_thread;
thread_data_t data;

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

    while (1) {
        // Configura el conjunto de descriptores de archivo
        FD_ZERO(&read_fds);
        FD_SET(data->serial_fd, &read_fds);
        // Configura el tiempo de espera (1 segundo)
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        // Espera a que haya datos disponibles en el puerto serial
        int ret = select(data->serial_fd + 1, &read_fds, NULL, NULL, &timeout);
        if (ret > 0 && FD_ISSET(data->serial_fd, &read_fds)) {
            bytes_read = read(data->serial_fd, temp_buffer, BUF_SIZE - 1);// Lee un bloque de bytes
            if (bytes_read > 0) {
                temp_buffer[bytes_read] = '\0';  // Asegura que el buffer esté terminado con un carácter nulo
                pthread_mutex_lock(&data->mutex);// Bloquea el mutex para proteger el buffer compartido
                //strncpy(data->buffer, temp_buffer, BUF_SIZE);// Copia los datos al buffer compartido
                strncat(data->buffer6, temp_buffer, BUFFER6_SIZE - strlen(data->buffer6) - 1);
                data->data_ready = 1;  // Indica que hay datos nuevos
                pthread_mutex_unlock(&data->mutex);// Desbloquea el mutex
                printf("%s[LECTOR] Datos leídos:%s %s %s\n",CAZUL,CAMAR, temp_buffer,CRESET);  // Depuración
            } else if (bytes_read == -1) {
                printf("%s[LECTOR] Error al leer del puerto serial.%s\n",CROJO,CRESET);
            }
        } else if (ret == -1) {
            printf("[LECTOR] Error en select.\n");}
    }//fin while++++++++++++++++++++++
return NULL;
}//fin de serial reader+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Hilo procesador: Procesa los datos del buffer compartido ++++++++++++++++++++++++++++++++++++
void *cons_serial_processor(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char local_buffer[BUFFER6_SIZE];

    while (1) {
        pthread_mutex_lock(&data->mutex);// Bloquea el mutex para acceder al buffer compartido
        if (data->data_ready) {// Si hay datos nuevos, los copia y los procesa
            strncpy(local_buffer, data->buffer6, BUFFER6_SIZE);
            data->data_ready = 0;  // Reinicia la bandera
            data->buffer6[0] = '\0';// Limpia buffer6 después de copiar los datos
            local_buffer[BUFFER6_SIZE-1]='\0';//Asegura el caracter nulo al final
            pthread_mutex_unlock(&data->mutex);// Desbloquea el mutex
            printf("%s[PROCESADOR] Datos procesados:%s %s %s\n",CAQUA,CAMAR, local_buffer,CRESET);
            Procesamiento_de_cadena_serProc(&local_buffer[0]);}// Procesa los datos (en este caso, simplemente los imprime)
        else {
            pthread_mutex_unlock(&data->mutex);}// Desbloquea el mutex si no hay datos nuevos
        usleep(1000);  // Espera 1 ms,// Espera un poco antes de verificar nuevamente
    }//fin while-----------------------------------------------------------
return NULL;
}//fin de consumidor serial protocolo procesador del prootocolo++++++++++++++++++++++++++++++++++++



/* ¨Prpcesamiento de cadena de datos que llega del puerto serial|
 procesa la cadena completa y si se queda el protocolo a medias y se termina la 
   cadena se sale quedando en el estado que estaba para recargar la cadena******************************/
void Procesamiento_de_cadena_serProc(char *c){
static unsigned char estado;
static unsigned char len,cmd,crc,len1;//estado de la cadena
static unsigned short int indice; //el buffer6 es  de 1024 tamaño
static unsigned char param[PARAM_SIZE_COMANDOS],index;
unsigned char crc_array[PARAM_SIZE_COMANDOS];
static unsigned char numParam,numParam0;//numero de parametros    .

     indice=0;
 while((*(c+indice)!='\0')&&(indice<BUFFER6_SIZE)){
   unsigned char dato=*(c+indice);
   *(c+indice++)=0xFF;
   switch(estado){
      case 1:if(dato==STX)
                    estado++;
              break;
      case 2:len=dato;
             if(len<2){estado=98;break;}
             estado++;break;
      case 3:cmd=dato;
             if(len==2)estado++;//comandos sin parametros
             else{estado=10;len1=len;index=0;
                  numParam0=numParam=len-2;
                  for(int i=0;i<PARAM_SIZE_COMANDOS;i++){
                          param[i]=0;   }
                  }break;//comandos con parametros
      case 4:crc=dato;estado++;break;    //comandos sin parametros
      case 5:if(dato==ETX){
                procesarComando(len,cmd,crc);}
             estado=98;
             break;
      case 10:if(numParam0==0){
                   crc=dato;
                   crc_array[0]=len;
                   crc_array[1]=cmd;
                   for(int i=0, j=2;i<len-2;i++,j++)
                        crc_array[j]=param[i];
                    int crc1=getCRC_v2(&crc_array[0],len);
                    if(crc1==crc)
                         estado++;
                    else{ 
                        estado=98;}}
              else{
                param[numParam-numParam0--]=dato;}
              break;
      case 11:if(dato==ETX){
                            procesarCmd(cmd,&param[0]);}
              estado=98;break;
      case 98:estado=1;cmd=0;len=0;break;//cadena corrupta
      default:estado=1;break;}//fin switch-++++++++++++++++++++++++
   }//fin while ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}//fn de procesamiento de cadena que llega del erial de la procesadora -------------------------------


void procesarCmd(unsigned char cmd,unsigned char *param){
unsigned char x;
unsigned char mens[]={"COMANDO BARRA ACEPTADO"};
    x=*param;    
    printf(" %d %c",x,x);
    switch(cmd){
        case CMD_DET_ON:printf("%s %s %s",CVERD,mens,CRESET);break; //aumenta el conteo de Rechazo
        case CMD_BARRA://2+8+9+1 cuadritos
                       Serial_Command_Barra_Detection(*param); 
                       printf("%s %s  %i %s:%i",CAMAR,mens,cmd,CRESET,*param);
                       break;  //mueve la barra de deteccion
        case CMD_DET_PM:printf("%s %s %s",CMORA,mens,CRESET);break; //hace display de los parametros de Portal Inicio
        default:break;
    }//fin switch ----------------------------------------------------------------------------
}//fin de procesar cmd+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/* procesamiento de comando sin parametros */
void procesarComando(unsigned char len,unsigned char cmd,unsigned char crc){
unsigned char crc1;
unsigned char buffer[2];
      if(len==2){
         buffer[0]=len;buffer[1]=cmd;
         crc1=getCRC_v2(&buffer[0],len);
         if(crc==crc1){
               switch(cmd){
                  case CMD_DET_ON:mens_Warnning_Debug("Comando En construccion");
                                  break;
                  default:break;}}
         else{mens_Warnning_Debug(" Error -Len- Procesar Cmd Serial Comms");}}
      else{mens_Warnning_Debug(" Error -Len- Procesar Cmd Serial Comms");}
}//fin procesar comando++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


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
    var=parametro;    
    switch(var){
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
       default:if(var>15)
                    var=recalcular_valor_Ser_Barr_det(var);
               break;}
 display_Barra_Deteccion(var);break;
}//fin serial comando  barra deteccion+++++++++++++++++++++++++++++++++++++++++++++++++++