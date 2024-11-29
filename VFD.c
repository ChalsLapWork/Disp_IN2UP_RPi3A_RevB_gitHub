#include "VFD.h"
#include "system.h"
#include "queue.h"
#include <wiringPi.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
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
unsigned char n;
unsigned char mem[2];
    printf("\n      Iniciando prueba de Puertos Fisicos.\n");
    delay(4);
    while(1){
          
        VFDserial_SendBlock1(&r[0],sizeof(r),&n,&mem[0]);
        delay(1);

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
struct Queue q;
pthread_t Proc_Tx_VFD;
pthread_attr_t attr;
size_t stacksize=1024*1024;
unsigned char debug;

estado=mem; //estado5&0xE0; //111x xxxx
count =mem+1;// estado5&0x1F; //xxx1 1111
  switch(*estado){//1110 0000
      case 1:if(!qVFDtx.isPadreAlive)(*estado)++;break; //esta ocuipado el VFD en otro proceso?
	  case 2:*count=0;pthread_attr_init(&attr);
             (*estado)++;break;
      case 3:if(pthread_attr_setstacksize(&attr,stacksize)){
                fprintf(stderr,"\n error en hilo 163");
                 exit(EXIT_FAILURE);}
             (*estado)++;break;
      case 4:if(!vfd.config.bits.Proc_VFD_Tx_running)
                  (*estado)++;break;
      case 5:vfd.config.bits.Proc_VFD_Tx_running=TRUE;
             (*estado)++;break;
      case 6:vfd.config.bits.VDF_busy=TRUE;
             qVFDtx.isPadreAlive=TRUE;
             (*estado)++;break;
      case 7://if(pthread_create(&Proc_Tx_VFD,&attr,SubProceso_Tx_VFD,&qVFDtx)!=0){
             debug=pthread_create(&Proc_Tx_VFD,&attr,SubProceso_Tx_VFD,&qVFDtx);
             if(debug!=0){
               printf("\n\033[31mError Creacion de Hilo: \033[1;31m%d",debug);
               delay(4);
               exit(EXIT_FAILURE);}     
      case 8:if(VFDserial_SendChar1(*(Ptr+(*count))))(*estado)++;break;
      case 9:if(++(*count)<(Size+1))(*estado)--;else{(*estado)++;}break;
      case 10:qVFDtx.isPadreAlive=FALSE;(*estado)++;break;
      case 11:pthread_join(Proc_Tx_VFD,NULL);
              pthread_attr_destroy(&attr);
              vfd.config.bits.Proc_VFD_Tx_running=FALSE;//se murio hilo transmisor al VFD
              (*estado)++;break;
      case 12:(*estado)=0;ret=TRUE;break;
      default:(*estado)=1;break;}
   
*Snd=0;
return ret;                       /* Return error code */
}//fin insertar en la FIFO un comando para graficar varios carateres.------------------------
