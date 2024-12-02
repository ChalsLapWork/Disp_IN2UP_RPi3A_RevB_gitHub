#include "VFD.h"
#include "system.h"
#include "queue.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "errorController.h"
#include <unistd.h>
#ifndef _PTHREAD_H_
  #define _PTHREAD_H_
  #include <pthread.h>
#endif
extern struct _DISPLAY_VFD_ vfd;
extern struct Queue qVFDtx;//queue de transmision vfd 



// Estructura para manejar los pines y datos
typedef struct {
    int pins[8];      // Pines GPIO para datos
} ParallelPort;

ParallelPort port = { .pins = {0, 1, 2, 3, 4, 5, 6, 7} };
void initParallelPort(ParallelPort *port);
void writeParallelPort(ParallelPort *port, unsigned char value);

// Configurar pines como salidas
void initParallelPort(ParallelPort *port) {
    for (int i = 0; i < 8; i++) {
        pinMode(port->pins[i], OUTPUT);
        digitalWrite(port->pins[i], LOW); }
}//fin de init parallel port++++++++++++++++++++++++++++++

void initParallelPort_Global(void){
    initParallelPort(&port);
}//fin init parallel port global++++++++++++++++++++++++++

// Escribir un byte en el puerto paralelo +++++++++++++++++++++++
void writeParallelPort(ParallelPort *port, unsigned char value) {
    for (int i = 0; i < 8; i++) {
        int bit = (value >> i) & 1;       // Extraer el i-ésimo bit
        digitalWrite(port->pins[i], bit); }// Establecer el valor en el pin correspondiente
}//fin de write parallelport ++++++++++++++++++++++++++++++++++++


void writePort(unsigned char value){
   digitalWrite(WR_PIN,LOW);//comando de escritura 
   writeParallelPort(&port,value);
   digitalWrite(WR_PIN,HIGH);//comando de escritura OFF
}//fin write port++++++++++++++++++++++++++++++++++++++++++



//VFD comando en MODO operativo----------------------------------
//REGRESA TRUE si ya se ejecuto todo el comando hasta el final
//instancia 1 y dos 
// funcion mono-Padre || Solo puede tener un padre a la vez
unsigned char VFDcommand(unsigned char cmd){ //unsigned char *p){
	//con 1 ms se le quito el error de FontSize
	//con 100us tiene error de FontSize
	//con 500us se le quito el error de FontSize
	//con 250us se le quito el error de FontSize
	//Se le quito el error con 125us lo dejamos en 125us
return VFDserial_SendChar1(cmd);	    	   
}//fin vfd command----------------------------------------------------


//despliegue de datos en el display
void test_display(void){
unsigned char r[12]=" Hola mundo ";
unsigned char n,j=0;
unsigned char mem[2];
    printf("\n       \033[35mIniciando prueba de Puertos Fisicos.\033[0m\n");
    usleep(90000);
    NoErrorOK();usleep(80000);
    while(1){
        printf(" %d ",j++);usleep(90000);  
        VFDserial_SendBlock1(&r[0],sizeof(r),&n,&mem[0]);
        usleep(80000);

    }//fin while++++++++++++++++++++++++++++++++
}//fin de prueba de despliegue de datos en el VFD



// pusimos estos delay y el tamaño de la Font no obedecia
	//y se ponia chica
//con estos delay ya obedece pero no sabemos si todos o cual
// instancia s1,s2
//METODO  mono-Padre Con-Instancia No almismo Tiempo
unsigned char FontSizeVFD(unsigned char m,unsigned char *mem){
//auto unsigned short int n=10000;
auto unsigned char ret=0,*estado;
  estado=mem;
  switch(*estado){
	case 1:if(VFDcommand(0x1FU))(*estado)++;break;// font size select of a character command
	case 2:if(VFDcommand(0x28U))(*estado)++;break;//  comando 1fh,28h,67h,01h,m
    case 3:if(VFDcommand(0x67U))(*estado)++;break;//m= 01h  6x8 font,   m=02h->8x16 font
	case 4:if(VFDcommand(0x01U))(*estado)++;break;//m=03h-> 12x24   m=04h->16x32 font
	case 5:if(VFDcommand(m))    (*estado)++;break;
	case 6:ret=TRUE;*estado=0;break;
	default:*estado=1;break;}
return ret;
}// fin font size for the VFD----------------------------------------------------


//regresa true cuando se cumpla todo el methodo hasta el final
unsigned char delay_us_VFD(unsigned short int t){
unsigned char ret=0;
/*union W7{//access word: 
	unsigned  short int wordx;   //   	0xaabb        //         aa
	unsigned char byte[2];        //byte[0]=aa,byte[1]=bb
}w16;
DEPRECATED
  w16.wordx=t;
  if(vfd.f1.append(w16.byte[0],w16.byte[1],_DELAY_US))
        ret=TRUE;*/
return ret;    
}//--------------------------------------------------


//void VFDserial_SendChar1(unsigned char c){
//	vfd.f1.append(c,0,_CHAR_);// FIFO_Display_DDS_Char_push(c,0xFE);//0xFE means that is just a char display          
//}//fin VFDserial_SendChar_DDS---------------------------------
unsigned char VFDserial_SendChar1(unsigned char c){
struct VFD_DATA dato;
    dato.p=_CHAR_;dato.x=c;dato.y=0;
	return vfd.f1.append(&qVFDtx,dato);
}//------------------------------------------------------------------



//REGRESA TRUE si ya se ejecuto todo el comando hasta el final
unsigned char VFDcommand_init(unsigned char cmd){
auto unsigned char ret=FALSE;
	//delay1us();
	//con 1 ms se le quito el error de FontSize
	//con 100us tiene error de FontSize
	//con 500us se le quito el error de FontSize
	//con 250us se le quito el error de FontSize
	//Se le quito el error con 125us lo dejamos en 125us
 
  
    ret+=delay_us_VFD(225);
    ret+=VFDserial_SendChar1(cmd);
    ret+=delay_us_VFD(225);
    if(ret==3)ret=TRUE;else ret=FALSE;		    
return ret;	
}//fin vfd command----------------------------------------------------

/* Metodo Multi-Padre pero solo una Estancia ala Vez      */
unsigned char VFDserial_SendBlock1(
    unsigned char *Ptr,//pointer to variable a desplegar
    unsigned char Size,//numero de bytes a desplegar
    unsigned char *Snd,//regreso de estado
    unsigned char *mem)//memoria de manejo de varibles de la func
{//static unsigned char estado5;//111x xxxx
auto unsigned char ret=0; 
unsigned char *estado;
unsigned char *count;
unsigned char debug;
size_t stacksize=1024*1024;

  estado=mem; //estado5&0xE0; //111x xxxx
  count =mem+1;// estado5&0x1F; //xxx1 1111
  switch(*estado){//1110 0000
      case 1:if(!qVFDtx.isPadreAlive)(*estado)++;break; //esta ocuipado el VFD en otro proceso?
	  case 2:if(!vfd.config.bits.Proc_VFD_Tx_running)(*estado)++;break;//todos los hilos Tx a VFD apagados
      case 3:if(!vfd.config.bits.isProc_Free_running)(*estado)++;break;
      case 4:vfd.config.bits.recurso_VFD_Ocupado=TRUE;(*estado)++;break;//recurso ocupado, VFD nadie lo puede usar
      case 5:vfd.mutex.m_Free=&mutex_Free_SendBlock;
             vfd.mutex.cond_free=&cond_Free_SendBlock;(*estado)++;break;
      case 6:pthread_mutex_init(vfd.mutex.m_Free,NULL);
             pthread_cond_init(vfd.mutex.cond_free,NULL);(*estado)++;break; 
      case 7:init_Queue_with_Thread(&vfd.q);(*estado)++;break;
      case 8:vfd.q.sizeStream=Size;vfd.q.p=Ptr;(*estado)++;break;
      case 9:if((debug=pthread_create(&Proc_TX_VFD,NULL,Mon_VFD,&vfd.q))!=0){
                printf("\n\033[31mError Creacion Hilo:174\033[0m");
                exit(EXIT_FAILURE);}(*estado)++;break;
      case 10:if((debug=pthread_create(&Proc_limp_VFD,NULL,Clean_VFD,&vfd.q))!=0){
                printf("\n\033[31mError Creacion Hilo:177\033[0m");
                exit(EXIT_FAILURE);}(*estado)++;break;          
      case 11:pthread_detach(Proc_TX_VFD);
              pthread_detach(Proc_limp_VFD);(*estado)++;break;
      default:*estado=1;break;}
*Snd=0;
return ret;                       /* Return error code */
}//fin insertar en la FIFO un comando para graficar varios carateres.------------------------




//Proceso  unico de Padre unico, PROCESO
void* Mon_VFD(void* arg){  //Proceso Productor<---Proceso/hilo/THread
struct Queue *q=(struct Queue*)arg;//
unsigned char ret=0,estado;
unsigned char i=0,debug,*count;
pthread_attr_t attr;
size_t stacksize=2*1024*1024;// memoria para el hilo

 pthread_attr_init(&attr);
 if(pthread_attr_setstacksize(&attr,stacksize)!=0){
	  fprintf(stderr,"\n\033[31mError config tamaño de pila\033[0m");
	  exit(EXIT_FAILURE);}   	   
 while(!ret){
	switch(estado){
		case 1:printf("\n       Mon VFD starting. . .");estado++;break;
		case 2:pthread_mutex_lock(vfd.mutex.m_Free);
			   vfd.config.bits.Proc_VFD_Tx_running=TRUE;//no se ha iniziado este proceso
			   vfd.config.bits.VDF_busy=TRUE;//Nadie mas puede usar el VFD
               qVFDtx.isPadreAlive=TRUE;
			   estado++;break;
		case 3:NoErrorOK();estado++;break;
		case 4:printf("\n       Creando Hilo Transmisor");
		       if((debug=pthread_create(&Proc_TX_VFD,&attr,SubProceso_Tx_VFD,&q))!=0){//ret==0 :all OK	
				    printf("\n\033[31mError Creacion de Hilo:\033[1;31m%d ",debug);
                   //fprintf(stderr,"\n\033[31mError creando el hilo SubProc TX VFD\033[0m");
				    exit(EXIT_FAILURE);}
			   else{NoErrorOK();}estado++;break;
	    case 5:printf("\n       Init, llenar FIFOs Init para Transmitir");
			   NoErrorOK();*count=0;estado++;break;
		case 6:if(VFDserial_SendChar1(*(q->p+(*count))))estado++;break;
        case 7:if(++(*count)<(q->size+1))estado--;else{estado++;}break;
		case 8:if(++i<(q->sizeStream+1))estado--;else{estado++;}break;
		case 9:pthread_cond_signal(vfd.mutex.cond_free);estado++;break;
        case 10:qVFDtx.isPadreAlive=FALSE;estado++;break;
		case 11:estado=0;ret=TRUE;break;
		default:estado=1;break;}}//fin switch while 
  pthread_join(Proc_TX_VFD,NULL);//esperamos termine de transmitir a display el otro hilo
  pthread_attr_destroy(&attr);
  pthread_mutex_unlock(vfd.mutex.m_Free);
  printf("\n       Init Sub Proceso Init Terminado");
  NoErrorOK();		
return NULL;
}//fin init VFD -------------------------------------------------------------------

//** Proceso Hilo encargado de limpiar el Proceso Init VFD
void *Clean_VFD(void *arg) {
struct Queue *q=(struct Queue*)arg;//
unsigned char estado;	
    printf("\n       Proceso Limpiador de VFD activo");
	pthread_mutex_lock(vfd.mutex.m_Free);
	printf("\n       Limpieza de  recursos de init VFD...");
	switch(estado){
	    case 1:pthread_cond_wait(vfd.mutex.cond_free,vfd.mutex.m_Free);estado++;break;
		case 2:usleep(3);estado++;break;
		case 3:pthread_mutex_destroy(vfd.mutex.m_Free);
			   pthread_cond_destroy(vfd.mutex.cond_free);
			   pthread_mutex_destroy(vfd.mutex.m_Tx);
			   pthread_cond_destroy(vfd.mutex.cond_Tx);
			   estado++;break;
        case 4:vfd.config.bits.Proc_VFD_Tx_running=FALSE;estado++;break;
        case 5:vfd.config.bits.isProc_Free_running=FALSE;estado++;break;
        case 6:vfd.config.bits.recurso_VFD_Ocupado=FALSE;estado++;break;
		case 7:NoErrorOK();printf("\n");usleep(300);
			   estado++;break;
               
		default:estado=1;break;}
    return NULL;
}//fin del proceso hilo limpiador+++++++++++++++++++++++++++++++


