#include "system.h"
#include "queue.h"
#include "string.h"
#include "errorController.h"
#include "VFD.h"
#if(debug_level1==1)
  #include <stdio.h>
#endif
#ifndef _PTHREAD_H_
  #define _PTHREAD_H_
  #include <pthread.h>
#endif
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "VFDisplay.h"
#include <string.h>
#include "VFDmenu.h"




struct _DISPLAY_VFD_ vfd;
struct Queue qVFDtx;//queue de transmision vfd 
//struct _Sync2 s1;//sincronia 
struct VFD_DATA dequeue(struct Queue   *q);
void enqueue(struct Queue  *q,struct VFD_DATA dato1);

unsigned char  buffer6[SIZE_BUFFER6];//FIFO graficos con S.O, aqui guarda el dato
unsigned char  buffer7[SIZE_BUFFER6];//FIFO graficos con SO. aqui guarda el parametro=char|box|pos|
unsigned char  buffer8[SIZE_BUFFER6];//FIFO graficos con SO. aqui guarda el parametro numero 3
unsigned char sync1;//variable de recursos de los mutex1
extern pthread_cond_t  cond_Tx_SendBlock;//condicional exclusivo para send Block
extern pthread_mutex_t mutex_Tx_SendBlock;//mutex exclusivo para send block
extern circular_buffer_t buffer;
extern struct ArbolMenu MenuActualScreen;//la estrucrura del menu actual en pantalla.
pthread_t SubProc_SendBlock_TX_VFD;//send strings to VFD 
pthread_t SubProc_SendBlock_chars_TX_VFD;//send bytes 	stream to VFD
pthread_t SubProc_Run_Menu;//proceso que gestiona el cambio de menu

void init_queues(void){
const unsigned char init_VFD[]={0x1BU,0x40U,0x1FU,0x28U,0x67U,0x01U,FONTSIZE2};
unsigned char debug;
	init_FIFO_General_1byte(&vfd.x,&buffer6[0],SIZE_BUFFER6);
    init_FIFO_General_1byte(&vfd.y,&buffer7[0],SIZE_BUFFER6);
    init_FIFO_General_1byte(&vfd.p,&buffer8[0],SIZE_BUFFER6);
    printf("\n       Iniciando queueus");	  
    vfd.config.bytes1=0;//init all parameter into zero
    vfd.f1.append=vfd_FIFO_push;
	vfd.f1.pop=vfd_FIFO_pop;                                                                                                                                                                                                                                                                                                                                                                                                                      
	vfd.f1.resetFIFOS=vfd_FIFOs_RESET; 
	sync1=0xAA;//mutexs ocupados
	pthread_mutex_init(&vfd.mutex.VDF_busy,NULL);
	init_Queue_with_Thread(&qVFDtx);//fifos Transmisor data al Display
	vfd.config.bits.recurso_VFD_Ocupado=TRUE;//recurso ocupado, VFD nadie lo puede usar
	NoErrorOK();
	printf("\n       Creando Proceso Init VFD");
	if((debug=pthread_create(&SubProc_SendBlock_chars_TX_VFD,NULL,Subproceso_sendBlockBytes_Tx_VFD,NULL))!=0){
	    errorCritico2("Error creacion Hilo:",67);}else{NoErrorOK();}
	if((debug=pthread_create(&SubProc_SendBlock_TX_VFD,NULL,SubProceso_SendBlock_Tx_VFD,NULL))!=0){	
	    errorCritico2("Error creacion Hilo:",75);}else{NoErrorOK();}		 
	inicializar_VFD((init_VFD,sizeof(init_VFD));// VFD_sendBlockChars(init_VFD,sizeof(init_VFD));//Init VFD
	printf("\n       Fin de Init Queues");
	vfd.config.bits.recurso_VFD_Ocupado=FALSE;
	NoErrorOK();
}//fin init queue+++++++++++++++++++++++++++++++++++++++++++++++++++++++++




void init_Queue_with_Thread(struct Queue *q){    
	  q->head=q->tail=NULL;
	  q->size=0;
	  q->nLibres=SIZE_MAX_FIFO;
	  q->Tamano=SIZE_MAX_FIFO;
	  q->nOcupados=0;
	  q->s.m_Tx=&mutex_Tx_SendBlock;
	  q->s.cond_Tx=&cond_Tx_SendBlock;
	  pthread_mutex_init(q->s.m_Tx,NULL);
	  pthread_cond_init(q->s.cond_Tx,NULL);
}//fin de init FIFO transmit VFD+++++++++++++++++++++++++
  


//encola regresa TRUE: si esta llena , FALSE: si esta vacia
void enqueue(struct Queue *q,struct VFD_DATA dato1){
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->dato=dato1;
	new_node->next=NULL;
    pthread_mutex_lock(q->s.m_Tx); //&vfd.sync.mutex_init_VFD);
	if(q->tail==NULL){
		  q->head=new_node;
		  q->tail=new_node;}
	else{q->tail->next=new_node;
	     q->tail=new_node;}
	q->size++;	 
	q->nLibres--;q->nOcupados++;
    pthread_cond_signal(q->s.cond_Tx);//vfd.sync.cond_init_TX_VFD); // Notifica que la cola no está vacía
    pthread_mutex_unlock(q->s.m_Tx);//vfd.sync.mutex_init_VFD);
}//fin enqueue++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct VFD_DATA dequeue(struct Queue  *q) {
	pthread_mutex_lock(q->s.m_Tx);//vfd.sync.mutex_init_VFD);
	while(q->size==0)//aqui sabemos que esta vacia la queue
	    pthread_cond_wait(q->s.cond_Tx,q->s.m_Tx);//vfd.sync.cond_init_TX_VFD,&vfd.sync.mutex_init_VFD);	//espera si la cola esta vacia
    struct Node *temp=q->head;
	struct VFD_DATA data=temp->dato;
	q->head=q->head->next;
    if(q->head==NULL)
	     q->tail=NULL;
    q->size--;q->nLibres++;q->nOcupados--;
	free(temp);		 
    pthread_mutex_unlock(q->s.m_Tx);//vfd.sync.mutex_init_VFD);

return data;
}//fin de queue+++++++++++++++++++++++++++++++++

/*  Control de Display de VFD de despliegue por thread  */
void* SubProceso_SendBlock_Tx_VFD(void* arg) {//consumidor
  while(1){  
    pthread_mutex_lock(&buffer.mutex);
    while (buffer.head == buffer.tail) {
      pthread_cond_wait(&buffer.cond, &buffer.mutex);}
    char mensaje[MAX_MESSAGE_LEN];// Extrae el mensaje del buffer
    strncpy(mensaje, buffer.buffer[buffer.tail], MAX_MESSAGE_LEN);
    buffer.tail = (buffer.tail + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&buffer.mutex);
    Transmissor_SendBlock_VFD(mensaje);  // Transmite lentamente
  }//fin while+++++++++
return NULL;}//+++++++++++++++++++++++++++++++++++++
//fin del subproceso de envio de datos al display+++++++++++++

// SubProceso hilo que envía un bloque de datos bytes al VFD 
void* Subproceso_sendBlockBytes_Tx_VFD(void* arg) {
    while (1) {
        pthread_mutex_lock(&buffer2.mutex);
        while (buffer2.head == buffer2.tail) {
            pthread_cond_wait(&buffer2.cond, &buffer2.mutex);}
        bloque_t bloque = buffer2.buffer[buffer2.tail];
        buffer2.tail = (buffer2.tail + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&buffer2.mutex);
        for (size_t i = 0; i < bloque.longitud; i++) {
            VFD_sendChar(bloque.datos[i]);}
    }//fin while++++++++++++++++++++++++++++++++++++++++++++
return NULL;
}//fin de subproceso de send Block Bytes TX VFD++++++++++++



//deprecated:metho	do que se usa en un hilo transmisor VFD+++++++++++++++++++++++
unsigned char Transmissor_SendBlock_VFD(const char *str){
   while(*str){			                    		
        printf("\033[35m");
        putchar(*str);
		writePort((unsigned char)*str++);//writePort(*(datos+*index))
        printf("\033[0m");
        fflush(stdout);//salida inmediata de buffer printf
		usleep(900);}
    printf("\n");				
}//transmisor de datos a VFD+++++++++++++++++++++++++++++++++++++++++


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
   if((debug=pthread_create(&SubProc_Run_Menu,NULL,Run_Menu,NULL))!=0)
       errorCritico("errorCreacion hilo",175);
   else{pthread_detach(SubProc_Run_Menu);}//hilo independiente	   
}//fin del init Menu+++++++++++++++++++++++++++++++++++++++++++++++++++++


//Proceso de control de Menus
void *Run_Menu(void arg){
   xControl_Principal_de_Menus_Operativo();
}//fin de run menu++++++++++++++++++++++++++++++++++++++++++++


//Proceso Thread de control de menus
/*Controla la salida segura de los menu de modo Operativo para que termine de hacer la tarea el
 * menu actual y luego se pase al siguiente menu cuando acabe y se presione el escape "x"
 *   se mete el contexto Actual  */
void xControl_Principal_de_Menus_Operativo(void){
unsigned char contexto;
unsigned char estado3;
const NORMAL=30,INIT_M=1,TERMINAR=90;

 while(vfd.config.bits.MenuPendiente){ //hilo corriendo  
	switch(estado3){//Maquina de Estados
	  case INIT_M:  if(!vfd.config.init_menu)estado3++;else{estado3=30;}break;
	  case INIT_M+1:vfd.config.MenuPendiente=TRUE;estado3++;break;
	  case INIT_M+2:pthread_mutex_lock(&vfd.config.VDF_busy);estado3++;break;//Mejora de la funcion: recurso.solicitar
	  case INIT_M+5:contexto=find_contexto_Siguiente()estado3++;break;
	  case INIT_M+6:InitArbolMenu(contexto);estado3++;break;
	  case INIT_m+7:if(MenuActualScreen.func1())estado3=TERMINAR;//se despliega el MenuÂ¡Â¡
					else{errorCritico2("Error de Despliegue de menu",201);}break;
	  case TERMINAR:vfd.config.bits.init_Menu=TRUE;//no esta init el VFD
                    vfd.config.bits.MenuPendiente=FALSE;//hay pendiente un menu por desplegar
                    vfd.menu.contexto.Actual=contexto;
					pthread_mutex_unlock(&vfd.config.VDF_busy);//liberar recurso
	  default:estado3=1;break;}
   }//fin de WHILE bandera de Menu Pendiente--------------------   
	return;




const char *mens[]={" hola mundo ",
                        "  mensaje No.2 ",
                        "  Tercera line del mensaje",
                        "  cuarta line del mensaje",
                        "  quinta line del mensaje",
                        "  sexta line del mensaje",
                        "   777 line del mensaje",
                        "  888888 line del mensaje",
                        "  999999a line del mensaje",
                        "  1010101 line del mensaje",
                        "  11111111 line del mensaje",
                        "  112121212 line del mensaje"
                        };
unsigned char n;
int j=0;
    mensOK("Iniciando prueba de Puertos Fisicos.",CCIAN);
    NoErrorOK();printf("\n");
    while(1){
        for(int i=0;i<12;i++){  
            VFDserial_SendBlock1(mens[i]);   
        }}//fin while++++++++++++++++++++++++++++++++
    printf(" \n j=%d",j);
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
void init_FIFO_General_1byte(struct _FIFO_1byte_ *s,
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
}//fin init_FIFO_RX_serial_Keypad------------------------------------------


//return FALSE if is empty
/* version 300322-1156*/
unsigned char FIFO_general_1byte_pop(unsigned char *dato,
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
}//FIFO_general_1byte_push------------------------------------------

//regresa TRUE  si TODO bien  vfd.f1.append(14,0,_BOX_);
/* El buffer de la FIFO se satura son mas los que entran que los que salen
 * se satura, vamos a poner un seguro para que vacie la FIFO cuando se sature
 * y los datos que llegan cuando este saturado que se pierdan
 * RegrESA  FALSE si esta llena
 *   version 39.22.5.0
 * */
unsigned char FIFO_general_1byte_push(unsigned char dato,
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
}//FIFO_general_1byte_push---------------------------------------------



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
unsigned char vfd_FIFO_push(struct Queue *q,struct VFD_DATA dato){
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
}//fin vfd_FIFO_push-------------------------------------------


/*   */
unsigned char vfd_FIFO_pop(unsigned char *x,unsigned char *y,unsigned char *p){
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
}//fin vfd_FIFO_pop------------------------------------------------------------

/* para el cambio de contexto todas los registros y FIFOs e
 * resetean*/
unsigned char vfd_FIFOs_RESET(void){
	vfd.config.bits.FIFOonReset=1;//se activa el reset, indica que estan en reseteo
	vfd.x.resetFIFO(&vfd.x,&buffer6[0],SIZE_BUFFER6);
	vfd.y.resetFIFO(&vfd.y,&buffer7[0],SIZE_BUFFER6);
	vfd.p.resetFIFO(&vfd.p,&buffer8[0],SIZE_BUFFER6);
 return TRUE;	
}//fin --------------------------------------------------------
