#include "system.h"
#include "queue.h"
#include "strings.h"
#include "errorController.h"
#include "VFD.h"
#include <stdio.h>
#ifndef _PTHREAD_H_
  #define _PTHREAD_H_
  #include <pthread.h>
#endif
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "VFDisplay.h"
#include <string.h>
#include "VFDmenu.h"
#include "SistOp.h"
#include <semaphore.h>
#include "VFDthread.h"

#ifndef debug_level1
  #include <wiringPi.h>
#endif




struct _DISPLAY_VFD_ vfd;
//struct Queue qVFDtx;//queue de transmision vfd 
//struct _Sync2 s1;//sincronia 	


// Buffer compartido
//unsigned char buffer[BUFFER_SIZE];
size_t buffer_length = 0;
//int in = 0;//control de la FIFO de TX de la VFD
//int out = 0;//control dela FIFO de Tx VFD

unsigned char  buffer6[SIZE_BUFFER6];//FIFO graficos con S.O, aqui guarda el dato
unsigned char  buffer7[SIZE_BUFFER6];//FIFO graficos con SO. aqui guarda el parametro=char|box|pos|
unsigned char  buffer8[SIZE_BUFFER6];//FIFO graficos con SO. aqui guarda el parametro numero 3
unsigned char sync1;//variable de recursos de los mutex1
//extern pthread_cond_t  cond_Tx_SendBlock;//condicional exclusivo para send Block
//extern pthread_mutex_t mutex_Tx_SendBlock;//mutex exclusivo para send block
//extern circular_buffer_t buffer;
extern struct ArbolMenu MenuActualScreen;//la estrucrura del menu actual en pantalla.
//pthread_t SubProc_SendBlock_TX_VFD;//send strings to VFD 
//pthread_t SubProc_SendBlock_chars_TX_VFD;//send bytes 	stream to VFD
pthread_t SubProc_Run_Menu;//proceso que gestiona el cambio de menu





void init_queues(void){
//const unsigned char init_VFD[]={0x1BU,0x40U,0x1FU,0x28U,0x67U,0x01U,FONTSIZE2};
unsigned char array1[] = {0x41, 0x42, 0x43, 0x44};
unsigned char debug;
	//init_FIFO_General_1byte(&vfd.x,&buffer6[0],SIZE_BUFFER6);
    //init_FIFO_General_1byte(&vfd.y,&buffer7[0],SIZE_BUFFER6);
    //init_FIFO_General_1byte(&vfd.p,&buffer8[0],SIZE_BUFFER6);
    mensOK("Iniciando queueus",CCIAN);	  
	sync1=0xAA;//mutexs ocupados
	NoErrorOK();
	mensOK("Creando Proceso Init VFD",CAZUL1);
	init_VFD_Threads();
	inicializar_VFD();//Init VFD
	mensOK("Fin de Init Queues",CMAGNETA);
	NoErrorOK();
}//fin init queue+++++++++++++++++++++++++++++++++++++++++++++++++++++++++







/*
void VFDserial_SendBlock_Tx1(unsigned char *buffer, size_t len) {
unsigned char estado,cmd,n;
unsigned char c[MAX_NUM_CHAR_VFD];
unsigned char *crc=NULL;
unsigned char str_len = 0;        // Longitud del string de entrada
char *str;	
size_t i=0;
static int count;

    printf("Consumidor-Tx: Procesando buffer3 completo (len: %zu), cont=%i\n", len,count);
    if(count++==19)
	        printf(" Stop here ");

	crc=(unsigned char *)malloc(str_len *sizeof(unsigned char));    // Asignar memoria dinámica para el array crc basado en la longitud de *str
    if (crc == NULL) {// Error al asignar memoria
        printf("Error: No se pudo asignar memoria para crc.\n");
        return;}
   while(i<len){ 
	//str=(char *)&datos->data[i];
	switch(estado){// Continuar mientras no lleguemos al final de la cadena
      case 1:printf("\033[35m");estado++;break;
	  case 2:putchar(*str);estado++;break;
	  case 3:estado++;break;
	  case 4:if(*str++==STX)estado++;else{estado=99;}break;
	  case 5:*crc=len=*str++;n=1;estado++;break;
	  case 6:*(crc+n++)=cmd=*str++;i=0;estado++;break;
	  case 7:switch(len){
		         case 0:mensOK(" error 174, PROTOCOLO mal bytes ",CROJO1);break;
				 case 1:mensOK(" eror 175 protocolo par hecho",CAMARILLO);break;
				 case 2:estado=9;break;
                 default:estado=8;i=0;break;}
		      break;		 
	  case 8:if(len==n){n--;c[i]=0;estado++;}
	         *(crc+n++)=c[i++]=*str++;
             break;
	  case 9:if(*str++==getCRC_v2(crc,n))estado++;
	         else{estado=99;}break;
	  case 10: if(*str++==ETX)estado++;else{estado=99;}break;
	  case 11://procesar_Paquete(cmd,&c[0],n-2);break;
	  case 12:printf("\033[0m");
              fflush(stdout);//salida inmediata de buffer printf
              printf("\n");
			  break;
	  case 99:estado=2;mens_Warnning_Debug(" error 99 ");break;
	  default:estado=1;break;}
	  i++;}//fin while 
return;
}//transmisor de datos a VFD+++++++++++++++++++++++++++++++++++++++++
 	*/

	
				
/** esta funcion manda los paquetes del 
 *  buffer c en base al comando indicado,*/
unsigned char procesar_Paquete(unsigned char cmd,unsigned char *c,
                      unsigned char size){
//const unsigned char HI  0x00
//const unsigned char LO  0x01
typedef union{//access word: 
unsigned  short int coord16;   //   	0xaabb   
unsigned char byte[2];        //byte[0]=aa,byte[1]=bb
}coordn16; //coordenadas de 2 bytes 

coordn16 coordenadas;
const unsigned int TIEMPO_CAJAS=500000;//useg tiempo de espera para cambio de cajas
//const unsigned char MAX_BOXES =17;//nmero de boxes Dinamicas
unsigned char *box0,*box1,mode,ibox0,pen;
unsigned short int x1,y1,x2,y2;						
union{
  unsigned short int t;
  unsigned char n[2];
}union_usi;
unsigned char ret=0,estado,/*ret2,*/i;     
enum {
    CMD_STR = 10,
    CMD_CHR = 20,
    CMD_POS = 30,
    CMD_BOX = 40,
    CMD_LIN = 50,
    CMD_DOT = 60,
    CMD_CLR = 70,
    CMD_INI = 80,
    CMD_BXF = 90,
    CMD_BLD = 100,
    CMD_DMS = 110,
    CMD_DUS = 120,
    CMD_ERR = 130,
    CMD_OK = 140,  
	CMD_BAR= 150 };

    while(!ret){
       switch(estado){
           case 1:i=0;
		          switch(cmd){
                     case COMANDO_STRING:estado=CMD_STR;break;
		             case COMANDO_CHAR: estado=CMD_CHR;break;
					 case COMANDO_POS:  estado=CMD_POS;break;
					 case COMANDO_BOX:  estado=CMD_BOX;break;
					 case COMANDO_BOXF: estado=CMD_BXF;break;
					 case COMANDO_LINE: estado=CMD_LIN;break;
					 case COMANDO_DOT:  estado=CMD_DOT;break;
					 case COMANDO_CLEAR:estado=CMD_CLR;break;
					 case COMANDO_INIT: estado=CMD_INI;break;
					 case COMANDO_BOLD: estado=CMD_BLD;break;
					 case CMD_DELAY_MS: estado=CMD_DMS;break;
					 case CMD_DELAY_US: estado=CMD_DUS;break;
					 case CMD_BARRA:    estado=CMD_BAR;break;//BARRA DE DETECCION
					 default:estado=CMD_ERR;break;}
				   break;
		   case   CMD_DMS:union_usi.n[0]=*c;
                          union_usi.n[1]=*(c+1);
		                  usleep((union_usi.t)*1000); //delay milisegundos
		   				  estado=CMD_OK;break;
		   case   CMD_DUS:union_usi.n[0]=*c;
                          union_usi.n[1]=*(c+1);
		                  usleep(union_usi.t); //delay milisegundos
		   				  estado=CMD_OK;break;	  		  
		   case   CMD_CLR:usleep(1000);//1mseg
		    			  writePort(0x0CU);//Clean screen
						  usleep(15000);//15mseg	
						  estado=CMD_OK;break;
		   case   CMD_STR:writePort(*(c+i));
		                  usleep(50);
		                  if(i==size)estado++;
	 					  else{i++;}break;
		   case CMD_STR+1:usleep(200);estado=CMD_OK;break;
           case CMD_CHR:  writePort(*c);
		                  usleep(50);estado=CMD_OK;break;
		   case CMD_POS:  writePort(0x1F);  usleep(50);
		                  writePort(0x24);  usleep(50);
						  writePort(*c);    usleep(50);
						  writePort(0x00);  usleep(50);
						  writePort(*(c+1));usleep(50);
						  writePort(0x00);  usleep(50);
						  usleep(150);
						  estado=CMD_OK;break;
	       case CMD_BXF:
		   case CMD_LIN:					  
           case CMD_BOX:  writePort(0x1F);  usleep(50);
						  writePort(0x28);  usleep(50);
						  writePort(0x64);  usleep(50);
						  writePort(0x11);  usleep(50);
						  if(*c>0x02)writePort(0x02);
						  else{writePort(*c);}     usleep(50);//mode:00Line,01Box,02BoxFill
						  if(*(c+1)>1)writePort(0x01);
						  else{writePort(*(c+1));} usleep(50);//1|0:pen
						  writePort(*(c+2));  usleep(50);//x1L						  writePort(0x00);    usleep(50);
						  writePort(0x00);    usleep(50);//x1H
						  writePort(*(c+3));  usleep(50);//y1L
						  writePort(0x00);    usleep(50);//y1H
						  writePort(*(c+4));  usleep(50);//x2L
						  writePort(0x00);    usleep(50);//x2H
  					      writePort(*(c+5));  usleep(50);//y2L
						  writePort(0x00);    usleep(50);//y2H
						  estado=CMD_OK;break;

		   case CMD_DOT:  writePort(0x1F);  usleep(50);
						  writePort(0x28);  usleep(50);
						  writePort(0x64);  usleep(50);
						  writePort(0x10);  usleep(50);
						  writePort(0x01);  usleep(50);
						  writePort(*c);    usleep(50);
						  writePort(0x00);  usleep(50);
						  writePort(*(c+1));usleep(50);
						  writePort(0x00);  usleep(50);
						  estado=CMD_OK;break;
		   case CMD_INI:  writePort(0x1B);  usleep(50);
		                  writePort(0x40);  usleep(50);
						  writePort(0x1F);  usleep(50);
						  writePort(0x28);  usleep(50);
						  writePort(0x67);  usleep(50);
						  writePort(0x01);  usleep(50);
					 	  writePort(0x02);  usleep(50);
						  estado=CMD_OK;break;
           case CMD_BLD:  writePort(0x1F);  usleep(50);
		                  writePort(0x28);  usleep(50);
						  writePort(0x67);  usleep(50);
						  writePort(0x41);  usleep(50);
						  if(*c==1) writePort(0x01); 
						  else{writePort(0x00);}usleep(50);
						  estado=CMD_OK;break;
		   case CMD_BAR:  if(vfd.config.bits.BOX_enable){
                               box0=&vfd.box.box0;     
		                       box1=&vfd.box.box;
							   *box1=*c;		 
		                       estado++;}
					      else{estado=CMD_ERR;}
						  break;		  
		   case CMD_BAR+1:if(*box0>MAX_BOXES)
						                *box0=0;
		                  if(*box0==*box1){
							     estado=CMD_OK;break;}
						  else{if(*box0>*box1){
							      pen=0;ibox0=*box0;
								  getBoxPattern(ibox0,&mode,&x1,&y1,&x2,&y2);//box0 se tiene que decrementar despues no antes
                                  if(*box0>0)
								      ibox0--;
							      *box0=ibox0;}		  
							   else{if(*box1>*box0){
									    pen=1;ibox0=*box0;ibox0++;//increment value box0, to reach box1
										getBoxPattern(ibox0,&mode,&x1,&y1,&x2,&y2);
										*box0=ibox0;}}}
						  estado++;break;
		   case CMD_BAR+2: writePort(0x1F);  usleep(50);
		                   writePort(0x28);  usleep(50);
		                   writePort(0x64);  usleep(50);
		                   writePort(0x11);  usleep(50);
		                   writePort(mode);  usleep(50);
		                   writePort(pen);   usleep(50);
						   coordenadas.coord16=x1;		
						   writePort(coordenadas.byte[LO]);usleep(50);		
						   writePort(coordenadas.byte[HI]);usleep(50);
						   coordenadas.coord16=y1;		
						   writePort(coordenadas.byte[LO]);usleep(50);
						   writePort(coordenadas.byte[HI]);usleep(50);
						   coordenadas.coord16=x2;		
						   writePort(coordenadas.byte[LO]);usleep(50);
						   writePort(coordenadas.byte[HI]);usleep(50);
						   coordenadas.coord16=y2;		
						   writePort(coordenadas.byte[LO]);usleep(50);
						   writePort(coordenadas.byte[HI]);usleep(50);
						   usleep(TIEMPO_CAJAS);//tiempo que tarda la caja en cambiar
						   estado--;break;//regresamos al estado anterior
		                   
								  



		   case CMD_OK: ret=TRUE;/*ret2=TRUE;*/ estado=0;break;		   
		   case CMD_ERR:ret=TRUE;/*ret2=FALSE;*/estado=0;break;			
           default:estado=1;break;}//fin switch+++++++++++++
	}//fin of while ++++++++++++++++++++++++++++++++++++++++++
return ret;
}//fin de procesar paquetes+++++++++++++++++++++++++++++++++++



//Proceso  unico de padre unico  y sin instancias
void* Init_VFD(void* arg){  //Proceso Productor<---Proceso/hilo/THread
return NULL;
}//fin init VFD -------------------------------------------------------------------


//despliegue de datos en el display
void init_menu(void){
unsigned char debug;
   vfd.config.bits.init_Menu=0;//no esta init el VFD
   vfd.config.bits.MenuPendiente=TRUE;//hay pendiente un menu por desplegar
   vfd.config.bits.Menu_Ready=FALSE;//no se a desplegado menu solicitado
   vfd.config.bits.BOX_enable=FALSE;//NO SE pueden dibujar cajas
   pthread_mutex_init(&vfd.mutex.VDF_busy,NULL);//init recurso VFD
   vfd.menu.contexto.Actual=PORTAL_INICIO;
   if((debug=pthread_create(&SubProc_Run_Menu,NULL,Run_Menu,NULL))!=0)
       errorCritico2("errorCreacion hilo",175);
   else{pthread_detach(SubProc_Run_Menu);}//hilo independiente	   
}//fin del init Menu+++++++++++++++++++++++++++++++++++++++++++++++++++++


//Proceso de control de Menus
void *Run_Menu(void *arg){
unsigned char contexto;
unsigned char estado3;
enum{NORMAL=30,INIT_M=1,TERMINAR=90};
unsigned char mem[MEMO_MAX_FUNC_DISPL_MENU];//memoria para los methodos de despliegue

 while(vfd.config.bits.MenuPendiente){ //hilo corriendo  
	switch(estado3){//Maquina de Estados
	  case INIT_M:  if(!vfd.config.bits.init_Menu)estado3++;else{estado3=30;}break;
	  case INIT_M+1:vfd.config.bits.MenuPendiente=TRUE;estado3++;break;
	  case INIT_M+2:estado3++;break;//Mejora de la funcion: recurso.solicitar
	  case INIT_M+3:contexto=find_contexto_Siguiente();estado3++;break;
	  case INIT_M+4:InitArbolMenu(contexto);estado3++;break;
	  case INIT_M+5:vfd.config.bits.Menu_Ready=0;estado3++;break;//menu no esta terminado aun
	  case INIT_M+6:if(MenuActualScreen.func2(&mem[0]))estado3=TERMINAR;break;//se despliega el MenuÂ¡Â¡
					
	  case TERMINAR:vfd.config.bits.init_Menu=TRUE;//no esta init el VFD
                    vfd.config.bits.MenuPendiente=FALSE;//hay pendiente un menu por desplegar
                    vfd.menu.contexto.Actual=contexto;
					break;
	  default:estado3=1;break;}
   }//fin de WHILE bandera de Menu Pendiente--------------------   
return NULL; 
}//fin de prueba de despliegue de datos en el VFD+++++++++++++++++++++++++++++
//fin del control operativo del menu de escape-----------------------------------------
 




void Terminar_subProcesos(void){
    //pthread_join(Proc_Tx_VFD,NULL);
	//pthread_mutex_destroy(&q->lock);
}//terminar subprocesos+++++++++++++++++++++++++


/*parametro 
 * 1: La fifo a inizializar
 * 2: pointer to first element array of fifo
 * 3:pointer to last element array of fifo
 * 4: size of fifo 
 * version 300322-1205
 * version 310322-1637 add reset as general */
/*void init_FIFO_General_1byte(struct _FIFO_1byte_ *s,
     unsigned char *h,unsigned char size){//FIFO_SER_KEYPAD[SIZE_SER_KEYPAD];
	s->head=h;
	s->tail=h+size-1;
	s->pop=s->tail;
	s->push=s->tail;
	s->ncount=s->nOcupados=0;s->nLibres=size;
	s->popf=FIFO_general_1byte_pop;
	s->appendByte=FIFO_general_1byte_push;
	s->size=size;
	s->resetFIFO=reset_FIFO_general_UChar;
}*/ //fin init_FIFO_RX_serial_Keypad------------------------------------------


//return FALSE if is empty
/* version 300322-1156*/
/*unsigned char FIFO_general_1byte_pop(unsigned char *dato,
                   struct _FIFO_1byte_ *s){	
	if(s->ncount==0){
        #if(debug_level1==1)
		    printf("\nFIFO LLENA");
	    #endif
		return FALSE;}
	if(s->ncount==1){
		*dato=*(s->pop);//solo hay un dato en la FIFO
		*(s->pop)=0;//vaciamos nodo
		s->pop=s->push=s->tail;//reajustamos todo de inicio
		s->ncount=0;s->nLibres++;s->nOcupados=0;}
	else{*dato=*(s->pop);
	     *(s->pop)=0;//vaciamos nodo
	     if(s->ncount>0){
	    	  s->ncount--;s->nLibres++;s->nOcupados++;}
		 if(s->pop==s->head)
			    s->pop=s->tail;
		 else s->pop--;}
return TRUE;
}*/ //FIFO_general_1byte_push------------------------------------------

//regresa TRUE  si TODO bien  vfd.f1.append(14,0,_BOX_);
/* El buffer de la FIFO se satura son mas los que entran que los que salen
 * se satura, vamos a poner un seguro para que vacie la FIFO cuando se sature
 * y los datos que llegan cuando este saturado que se pierdan
 * RegrESA  FALSE si esta llena
 *   version 39.22.5.0
 * */
/*unsigned char FIFO_general_1byte_push(unsigned char dato,
                                  struct _FIFO_1byte_ *s){
auto unsigned char ret=0;
	  if(s->nLibres==0) 
		   return FALSE;//FIFO llena
	  if(s->ncount==0){
		   s->pop=s->push=s->tail;//emparejamos pointers
		   *(s->push)=dato;
		   s->push--;s->ncount++;s->nLibres--;s->nOcupados++;
           ret=TRUE;}
	  else{if(s->push==s->head){
		      if(s->tail==s->pop){
		    	  *(s->push)=dato;
		    	  s->push=s->pop;//esta llena
		    	  s->ncount++;s->nLibres--;s->nOcupados++;}
		      else{*(s->push)=dato;s->push=s->tail;
		           s->ncount++;s->nLibres--;s->nOcupados++;
                   ret=TRUE;}}
	       else{if(s->push-1==s->pop){//nos recorreremos para atras y no topamos con pop
		           *(s->push)=dato;
		           s->push=s->pop;
		           s->ncount++;s->nLibres--;s->nOcupados++;
                   if(s->nLibres>0){errorCritico("error de algoritmo de fifo");}
		           ret=TRUE;}
	             else{*(s->push)=dato;s->push--;
                          s->nLibres--;s->nOcupados++;
	                    s->ncount++;ret=TRUE;}}}
return ret;
}*/ //FIFO_general_1byte_push---------------------------------------------



//se resetea toda la fifo y todo queda cmo de inici
// version 21-oct-24:10:15am
void reset_FIFO_general_UChar(struct _FIFO_1byte_ *s,
       unsigned char *arr,unsigned char  size){
	   s->pop=s->push=s->tail;
	   s->ncount=0;
	   cleanArray(arr,size,0);
	  
}//fin reset_FIFO_serial_TX---fin se resetea toda la fifo


//FIFO para ingresar un dato a desplegar vfd.f1.append(14,0,_BOX_);
//Return false|true   TRUE: si se agrego sin problemas
/*unsigned char vfd_FIFO_push(struct Queue *q,struct VFD_DATA dato){
const unsigned char BYTES_BOX=250; //numero de ciclos, mas que bytes por comando de una box cdraw 
unsigned char x,y,p;
const unsigned char DELAY_TIME=1; 
    x=dato.x;y=dato.y;p=dato.p;
    switch(p){//1100 0000 los dos MSB indican que proqrametro es
    	case _BOX_:if(x==0)
    		            return FALSE; 
    	           if(vfd.box.timer==0){
    	        	    vfd.box.timer=DELAY_TIME*BYTES_BOX;
    	        	    cleanArray(&vfd.box.boxs[0],SIZE_BOXES,0);
    	                return TRUE;}
    		       if(vfd.box.boxs[x]==0)
    		    	   vfd.box.boxs[x]++;        
    		       else{if(vfd.box.boxs[x]<250){
    		    	          vfd.box.boxs[x]++;
    		                  return TRUE;}
    		              else return TRUE;}
    	           break;              
    	case _CHAR_ :y='c';break;
    	case _PUNTO_:if((x==0)&&(y==0)){return(TRUE);}
    	             break;
    	case _RAYA_ : 
    	case _POS_  :break;
    	case _BOLD_ :break;
    	default:break;}
     enqueue(q,dato);
return TRUE;//ret;
}*/ //fin vfd_FIFO_push-------------------------------------------


/*   */
/*unsigned char vfd_FIFO_pop(unsigned char *x,unsigned char *y,unsigned char *p){
unsigned char  r;	 
	   if(vfd.x.ncount==0){
		   if((vfd.y.ncount!=0)&&(vfd.p.ncount!=0)){
			       //__asm(Halt);//Debug error de software
		           errorCritico("\n error de Software de FIFO pop");}
	       return 0;}//FIFO vacia
	   else r=1;//FIFO regresa un valor
       vfd.x.popf(x,&vfd.x);
       vfd.y.popf(y,&vfd.y);
       vfd.p.popf(p,&vfd.p);
return r;	   
}*///fin vfd_FIFO_pop------------------------------------------------------------

/* para el cambio de contexto todas los registros y FIFOs e
 * resetean*/
/*unsigned char vfd_FIFOs_RESET(void){
	vfd.config.bits.FIFOonReset=1;//se activa el reset, indica que estan en reseteo
	vfd.x.resetFIFO(&vfd.x,&buffer6[0],SIZE_BUFFER6);
	vfd.y.resetFIFO(&vfd.y,&buffer7[0],SIZE_BUFFER6);
	vfd.p.resetFIFO(&vfd.p,&buffer8[0],SIZE_BUFFER6);
 return TRUE;	
}*/ //fin --------------------------------------------------------
