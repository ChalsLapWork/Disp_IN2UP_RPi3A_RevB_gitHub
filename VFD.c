#include "VFD.h"
#include "system.h"
#include "queue.h"
#include <wiringPi.h>
#include <stdio.h>
#include "errorController.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>



#ifndef _PTHREAD_H_
  #define _PTHREAD_H_
  #include <pthread.h>
#endif


extern struct _DISPLAY_VFD_ vfd;
extern struct Queue qVFDtx;//queue de transmision vfd 


pthread_cond_t  cond_Tx_SendBlock;//condicional exclusivo para send Block
pthread_mutex_t mutex_Tx_SendBlock;//mutex exclusivo para send block
//pthread_cond_t  cond_Mon_SendBlock;//condicional exclusivo para send Block
//pthread_mutex_t mutex_Mon_SendBlock;//mutex exclusivo para send block
pthread_cond_t  cond_Free_SendBlock;//condicional exclusivo para send Block
pthread_mutex_t mutex_Free_SendBlock;//mutex exclusivo para send block
pthread_t Proc_TX_VFD;//Proceso para inizializar el VFD
pthread_t Proc_limp_VFD;//proceso que limpia recursos del proceso hilo init VFD
//pthread_t Proc_Mon;



// Estructura para manejar los pines y datos
typedef struct {
    int pins[8];      // Pines GPIO para datos
} ParallelPort;


circular_buffer_t buffer = {
    .head = 0,
    .tail = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .cond  = PTHREAD_COND_INITIALIZER
};


circular_buffer_t_byteBlock buffer2 = {
    .head = 0,
    .tail = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .cond  = PTHREAD_COND_INITIALIZER
};

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


// Simula la función VFD_sendChar (lenta)
void VFD_sendChar(uchar c) {
    printf(" \033[33m0x%02X\033[0m ",c);
    writePort(c);
}//fin de VFD_sendChar+++++++++++++++++++++++++++++++++++++



/*void writePort_SendBlock(const char value){
   digitalWrite(WR_PIN,LOW);//comando de escritura 
   writeParallelPort(&port,value);
   digitalWrite(WR_PIN,HIGH);//comando de escritura OFF
}*///fin write port++++++++++++++++++++++++++++++++++++++++++


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
unsigned char VFDserial_SendBlock1(const char *Ptr){
unsigned char ret=0; 
   int next_head = (buffer.head + 1) % BUFFER_SIZE;
   pthread_mutex_lock(&buffer.mutex);
   if (next_head != buffer.tail) {  // Solo escribe si hay espacio en el buffer
        strncpy(buffer.buffer[buffer.head], Ptr, MAX_MESSAGE_LEN);
        buffer.head = next_head;
        pthread_cond_signal(&buffer.cond);  // Despierta al hijo
        ret=TRUE;}
     pthread_mutex_unlock(&buffer.mutex);
return ret;// fin de enviar mensaje++++++++++++++++++++++
}//fin insertar en la FIFO un comando para graficar varios carateres.------------------------

//init el VFD+++++++++++++++++++++++++++++++++++++++++++++++ 
unsigned char inicializar_VFD(const uchar *datos, size_t longitud){	
    pthread_mutex_lock(&vfd.mutex.VDF_busy);  
	VFD_sendBlockChars(datos,longitud);//Init VFD
    pthread_mutex__unlock(&vfd.mutex.VDF_busy);
}//fin de inizializacion de VFD++++++++++++++++++++++++++++++


// Función que el hilo principal llama para enviar un bloque de caracteres
unsigned char VFD_sendBlockChars(const uchar *datos, size_t longitud) {
unsigned char ret = 0;
int next_head = (buffer2.head + 1) % BUFFER_SIZE;

    pthread_mutex_lock(&buffer2.mutex);
    if (next_head != buffer2.tail && longitud <= MAX_BLOCK_CHAR_VDF_SIZE) {
        bloque_t *bloque = &buffer2.buffer[buffer2.head];
        bloque->longitud = longitud;
        memcpy(bloque->datos, datos, longitud);
        buffer2.head = next_head;
        pthread_cond_signal(&buffer2.cond);
        ret = 1;}
    pthread_mutex_unlock(&buffer2.mutex);
return ret;
}//VFD_sendBlockChars++++++++++++++++++++++++++++++++++++++


//Proceso  unico de Padre unico, PROCESO
//Funcion DEPRECATED
void* Mon_VFD(void* arg){  //Proceso Productor<---Proceso/hilo/THread
/*struct Queue *q=(struct Queue*)arg;//
unsigned char ret=0,estado;
unsigned char i=0,debug,count;
pthread_attr_t attr;
size_t stacksize=2*1024*1024;// memoria para el hilo

 pthread_attr_init(&attr);
 mensOK("Asignando Recursos a Tx",CRESET);
 if(pthread_attr_setstacksize(&attr,stacksize)!=0){
	  errorCritico2("Error config tamaño de pila:",217);}
 else{NoErrorOK();}        	   
 while(!ret){
	switch(estado){
		case 1:mensOK("Mon VFD starting. . .",CRESET);estado++;break;
        case 2:if(!vfd.config.bits.Proc_VFD_Tx_running)estado++;break;
		case 3:pthread_mutex_lock(vfd.mutex.m_Free);
               q->isPadreAlive=TRUE;
			   estado++;break;
		case 4:NoErrorOK();estado++;break;
		case 5://mensOK("Creando Hilo Transmisor",CRESET);
		       //if((debug=pthread_create(&Proc_TX_VFD,&attr,SubProceso_Tx_VFD,&q))!=0){//ret==0 :all OK	
			   //	    errorCritico2("Error Creacion de Hilo:",debug);}
			   // else{NoErrorOK();}estado++;break;
	    case 6:mensOK("llenar FIFOs para Transmitir",CRESET);count=0;estado++;break;
		case 7:if(VFDserial_SendChar1(*(q->p+count)))estado++;break;
        case 8:if(++count<(q->size+1))estado--;else{estado++;}break;
		case 9:if(++i<(q->sizeStream+1))estado--;else{estado++;}break;
		case 10:pthread_cond_signal(vfd.mutex.cond_free);estado++;break;
        case 11:q->isPadreAlive=FALSE;estado++;break;//ya puede morir el hijo, si esta vacia la queue
		case 12:estado=0;ret=TRUE;break;
		default:estado=1;break;}}//fin switch while 
  pthread_join(Proc_TX_VFD,NULL);//esperamos termine de transmitir a display el otro hilo
  mensOK("Sub Proceso TX Terminado",CRESET);
  pthread_attr_destroy(&attr);
  pthread_mutex_unlock(vfd.mutex.m_Free);
  NoErrorOK();*/		
return NULL;
}//fin init VFD -------------------------------------------------------------------

//** Proceso Hilo encargado de limpiar el Proceso Init VFD
void *Clean_VFD(void *arg) {//HILO DEPRECATED
/*truct Queue *q=(struct Queue*)arg;//
unsigned char estado;	
    mensOK("Proceso Limpiador de VFD activo",CAMARILLO);
	pthread_mutex_lock(vfd.mutex.m_Free);
	mensOK("Limpieza de  recursos de init VFD...",CRESET);
	switch(estado){
	    case 1:pthread_cond_wait(vfd.mutex.cond_free,vfd.mutex.m_Free);estado++;break;
		case 2:usleep(3);estado++;break;
		case 3:pthread_mutex_destroy(vfd.mutex.m_Free);
			   pthread_cond_destroy(vfd.mutex.cond_free);
			   pthread_mutex_destroy(vfd.mutex.m_Tx);
			   pthread_cond_destroy(vfd.mutex.cond_Tx);
			   estado++;break;
        case 4:vfd.config.bits.isProc_Free_running=FALSE;estado++;break;
        case 5:vfd.config.bits.recurso_VFD_Ocupado=FALSE;estado++;break;
		case 6:NoErrorOK();printf("\n");usleep(300);
			   estado++;break;
               
		default:estado=1;break;}*/
    return NULL;
}//fin del proceso hilo limpiador+++++++++++++++++++++++++++++++


