#include "VFD.h"
#include "system.h"
#include "queue.h"

#include <stdio.h>
#include "errorController.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include "delay.h"
#include "VFDthread.h"

#ifndef  debug_level1 
    #include <wiringPi.h>
#endif



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


//void init_mutex_VFD(void){
//     pthread_mutex_init( &buffer.mutex,NULL);
//     pthread_mutex_init(&buffer2.mutex,NULL);
//     pthread_cond_init(  &buffer.cond ,NULL);
//     pthread_cond_init( &buffer2.cond ,NULL); 
//}// fin de init mutex VFD++++++++++++++++++++++++++

ParallelPort port = { .pins = {0, 1, 2, 3, 4, 5, 6, 7} };
void initParallelPort(ParallelPort *port);
void writeParallelPort(ParallelPort *port, unsigned char value);

// Configurar pines como salidas
void initParallelPort(ParallelPort *port) {
#if ( debug_level1 == 2 )
       usleep(1);
#else        
    for (int i = 0; i < 8; i++) {
        pinMode(port->pins[i], OUTPUT);
        digitalWrite(port->pins[i], LOW); }
#endif
}//fin de init parallel port++++++++++++++++++++++++++++++

void initParallelPort_Global(void){
    initParallelPort(&port);
}//fin init parallel port global++++++++++++++++++++++++++

// Escribir un byte en el puerto paralelo +++++++++++++++++++++++
void writeParallelPort(ParallelPort *port, unsigned char value) {
#if ( debug_level1 == 2 )
       usleep(1);
#else       
    for (int i = 0; i < 8; i++) {
        int bit = (value >> i) & 1;       // Extraer el i-ésimo bit
        digitalWrite(port->pins[i], bit); }// Establecer el valor en el pin correspondiente
#endif
}//fin de write parallelport ++++++++++++++++++++++++++++++++++++


void writePort(unsigned char value){
#if ( debug_level1 == 2 ) 
   usleep(1);
#else     
   digitalWrite(WR_PIN,LOW);//comando de escritura 
   writeParallelPort(&port,value);
   digitalWrite(WR_PIN,HIGH);//comando de escritura OFF
#endif   
}//fin write port++++++++++++++++++++++++++++++++++++++++++


// Simula la función VFD_sendChar (lenta)
void VFD_sendChar(uchar c) {
    printf(" \033[33m0x%02X\033[0m ",c);
    writePort(c);
    usleep(120000);
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
return VFDserial_SendChar(cmd);	    	   
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




/*limpia el VFD de caracteres y todo   */
void VFDclrscr(void){//AUTORIZADO 5:BYTES DE memoria
unsigned char LEN=0x02; //bytes a calcular por CRC
unsigned char buf[]={STX,LEN,COMANDO_CLRSCR,0x00,ETX};

     buf[LEN+1]=getCRC_v2(&buf[1],LEN);
     VFDserial_SendBlock_buf(&buf[0],sizeof(buf));
               
}//fin clear screen VFD-----------------------------------------------------------------------------





unsigned char getCRC_v2(unsigned char *data, unsigned char len) {
unsigned char crc = 0xFF; // Valor inicial de CRC (puede ajustarse según el algoritmo CRC específico)
    for (int i = 0; i < len; i++) {
        crc ^= data[i];  // XOR entre el CRC actual y el byte de datos
        for (unsigned char bit = 8; bit > 0; bit--) {
            if (crc & 0x80) { // Si el bit más significativo es 1
                crc = (crc << 1) ^ 0x07;} // Desplazamiento y XOR con polinomio 0x07 (puedes ajustarlo si usas otro polinomio)
            else {crc <<= 1;}}} // Solo desplazamiento
    // Asegurarse de que el CRC no sea 0x00 o 0xFF
    if (crc == 0x00) {crc = 0x01;} // Cambiar a 0x01 si el CRC es 0x00
    else if (crc == 0xFF) {crc = 0xFE;} // Cambiar a 0xFE si el CRC es 0xFF
    return crc;
}//********************************************************************************************





/** Len= */
unsigned char VFDposicion(unsigned char x,unsigned char y){ //MANDA DEL COMANDO DE POSICION AL vfd
unsigned char LEN=4;          
unsigned char POS_CMD[]={STX,LEN,COMANDO_POS,x,y,0x00,ETX};
     POS_CMD[LEN+1]=getCRC_v2(&POS_CMD[1],LEN);   
   	 VFDserial_SendBlock_buf(&POS_CMD[0],sizeof(POS_CMD));//
return 1;     
}// fin posicionVFD-------------------------------------------------------------


//------------
unsigned char VFDserial_SendChar(unsigned char c){
//struct VFD_DATA dato;
    //dato.p=_CHAR_;dato.x=c;dato.y=0;
	//return vfd.f1.append(&qVFDtx,dato);
unsigned char LEN=3;    
unsigned char a[6]={STX,LEN,COMANDO_CHAR,c,0,ETX};
       a[LEN+1]=getCRC_v2(&a[1],LEN);
return VFDserial_SendBlock_buf(&a,sizeof(a));//Init VFD
}//------------------------------------------------------------------



//REGRESA TRUE si ya se ejecuto todo el comando hasta el final
unsigned char VFDcommand_init(unsigned char cmd){
unsigned char ret=FALSE;
  
    ret+=delay_us_VFD(225);
    ret+=VFDserial_SendChar(cmd);
    ret+=delay_us_VFD(225);
    if(ret==3)ret=TRUE;else ret=FALSE;		    
return ret;	
}//fin vfd command----------------------------------------------------

/* Metodo Multi-Padre pero solo una Estancia ala Vez      */
unsigned char VFDserial_SendBlock1(const void *Ptr,unsigned char size1){
unsigned char array[40];
    
    const unsigned char *data = (const unsigned char *)Ptr;// Convertir los datos a unsigned char y copiarlos al índice 3 del array
    memcpy(&array[3], data, size1);
    array[0] = STX;
    array[1] = size1 + 2; // LEN (longitud total del mensaje)
    array[2] = COMANDO_STRING; // CMD (ejemplo de comando)
    array[size1 + 3-1] = getCRC_v2(array+1,size1+2);
    array[size1 + 4-1] = ETX; // Ejemplo de CRC (ajustar según tu implementación)    
    VFDserial_SendBlock_buf(array, size1 + 5);
    
return 1;// fin de enviar mensaje++++++++++++++++++++++
}//fin insertar en la FIFO un comando para graficar varios carateres.------------------------

/* Metodo Multi-Padre pero solo una Estancia ala Vez     
 valor es el numero que se va adesplegar en el VFD, posx|posy es la posicion en el VFD  
 formatos: 
       RIGHT: se va desplegar de la forma posx:______13
       LEFT:    se va a desplegar de la forma posx:13________
       CENTER se va adesplegar de la forma posx:___13____
       ZEROS se va a desplegar de la forma posx:00013*/
unsigned char VFDserial_Sendusint(unsigned short int valor,unsigned char posx,unsigned char posy,unsigned char formato){
unsigned char array[10];
union{
   unsigned short int usi;
   unsigned char c[2];
}bytes;    
    if(posy>128) return 0;
    switch(formato){//FALTA DE PROBAR LOS DEMAS
         case RIGHT://SOLO SE HA PROBADO EL DE CENTRAL|CENTER
         case LEFT:
         case CENTER:
         case CENTRAL:
         case ZEROS:goto next256;break;
         default:return 0;break;}
next256:         
    array[0] = STX;
    array[1] = 7; // LEN (longitud total del mensaje)
    array[2] = COMANDO_USINT; // CMD (ejemplo de comando)
    bytes.usi=valor;
    array[3]=bytes.c[0];
    array[4]=bytes.c[1];
    array[5] = posx;
    array[6] = posy;
    array[7] = formato;
    array[8] = getCRC_v2(array+1,7);
    array[9] = ETX; // Ejemplo de CRC (ajustar según tu implementación)    
    VFDserial_SendBlock_buf(array, 10);
    
return 1;// fin de enviar mensaje++++++++++++++++++++++
}//fin insertar en la FIFO un comando para graficar varios carateres.------------------------


/** mandar aa dislpay send phase y frac, tres digitos y fraccion un digito */
void VFDserial_SendPhase(unsigned char fase,unsigned char fasefrac,unsigned char posx,unsigned char posy,unsigned char formato){
unsigned char array[10];

    if(posy>128) return 0;
    switch(formato){//FALTA DE PROBAR LOS DEMAS
         case RIGHT://SOLO SE HA PROBADO EL DE CENTRAL|CENTER
         case LEFT:
         case CENTER:
         case CENTRAL:
         case ZEROS:goto next286;break;
         default:return 0;break;}
next286:
    array[0] = STX;
    array[1] = 7; // LEN (longitud total del mensaje)
    array[2] = COMANDO_PHASE; // CMD (ejemplo de comando)
    array[3] = fase;
    array[4] = fasefrac;
    array[5] = posx;
    array[6] = posy;
    array[7] = formato;
    array[8] = getCRC_v2(array+1,7);
    array[9] = ETX; // Ejemplo de CRC (ajustar según tu implementación)    
    VFDserial_SendBlock_buf(array, 10);
}//fin de VFD serial send phase++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//mandamos el valor al cual la barra de deteccion debe de aumentar
//o disminur en un timepo que se vea por el ojo humano
unsigned char VFDserial_SendBarraDet(unsigned char val){ 
unsigned char array[6];
unsigned char len=3; //longitud del calculo crc   
     array[0]=STX;
     array[1]=len;//longitud;
     array[2]=CMD_BARRA;
     array[3]=val;
     array[4]=getCRC_v2(&array[1],len);
     array[5]=ETX;
   VFDserial_SendBlock_buf(array,6);
return 0;   
}//fin de mandar comando de barra de deteccion+++++++++++++++++++++++++++++++++++++++++++++




//init el VFD++++++++++++++++++++++++++++++++++++++++++++++ 
unsigned char inicializar_VFD(void){
const unsigned char LEN=2;//cantidad de bytes a calcular porf CRC    	
//unsigned char init_VFD[]={STX,LEN,CMD_INI,0x1BU,0x40U,0x1FU,0x28U,0x67U,0x01U,FONTSIZE2,0x00,ETX};
unsigned char init_VFD[]={STX,LEN,COMANDO_INIT,0x00,ETX};
//unsigned short int sum=0;     
    init_VFD[3]=getCRC_v2(&init_VFD[1],LEN);
	VFDserial_SendBlock_buf(&init_VFD[0],sizeof(init_VFD));//Init VFD 
return 1;
}//fin de inizializacion de VFD++++++++++++++++++++++++++++++





unsigned char VFDboxLine1(unsigned char pen,unsigned char mode,
                       unsigned char x1,unsigned char y1,
                       unsigned char x2,unsigned char y2){
//coordn16 coordenadas; //             mode  pen   X1   Y1   X2   Y2      //x1LO x1Hi y1Lo y1Hi x2Lo x2Hi y2Lo y2Hi
//unsigned char datos[]={STX,LEN,CMD,0x00,0x00,0x00,0x00,0x00,0x00,CRC,ETX};
     //                   0    1   2   3    4    5    6    7    8    9 10     
unsigned char datos[11],LEN=8;	
    if((mode!=BOX_VACIA)||(mode!=BOX_LLENA)){
              mode=BOX_VACIA;}
    datos[0]=STX;
    datos[1]=LEN;//=longitud, num de bytes
    if(mode==BOX_VACIA){
         datos[2]= COMANDO_BOX;}
    else{datos[2]=COMANDO_BOXF;}
    if(mode==BOX_VACIA)
        {datos[3]= 0x01;}
    else{datos[3]= 0x02;}
    if(pen>0x01){pen=0;}
    datos[4]=pen;
    datos[5] =x1;         
    datos[6]=y1;
    datos[7]=x2;
    datos[8]=y2;
    datos[9]=getCRC_v2(&datos[1],LEN);
    datos[10]=ETX;
    VFDserial_SendBlock_buf(&datos[0],sizeof(datos));
return 1;
}// fin draw line -----------------------------------------------------------------------------------------






