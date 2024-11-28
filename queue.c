#include "system.h"
#include "queue.h"
#include "string.h"
#include "errorController.h"
#include "VFD.h"
#if(debug_level1==1)
  #include <stdio.h>
#endif
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "VFDisplay.h"




struct _DISPLAY_VFD_ vfd;
struct Queue qVFDtx;//queue de transmision vfd 
//struct _Sync2 s1;//sincronia 
void init_Queue_with_Thread(struct Queue  *q);
struct VFD_DATA dequeue(struct Queue   *q);
void enqueue(struct Queue  *q,struct VFD_DATA dato1);

unsigned char  buffer6[SIZE_BUFFER6];//FIFO graficos con S.O, aqui guarda el dato
unsigned char  buffer7[SIZE_BUFFER6];//FIFO graficos con SO. aqui guarda el parametro=char|box|pos|
unsigned char  buffer8[SIZE_BUFFER6];//FIFO graficos con SO. aqui guarda el parametro numero 3
pthread_cond_t  cond0;//mutex de VFD Tx
pthread_mutex_t mutex0;//mutex de VFD TX
pthread_cond_t  cond1;//de uso general
pthread_mutex_t mutex1;//de uso general
unsigned char sync1;//variable de recursos de los mutex1
pthread_cond_t  *cond_free;//pointer para init 
pthread_mutex_t *mutex_free;//mutex

void init_queues(void){
	pthread_t Proc1_Init_VFD;//Proceso para inizializar el VFD
	pthread_t Proc_limpiador;//proceso que limpia recursos del proceso hilo init VFD
    
	init_FIFO_General_1byte(&vfd.x,&buffer6[0],SIZE_BUFFER6);
    init_FIFO_General_1byte(&vfd.y,&buffer7[0],SIZE_BUFFER6);
    init_FIFO_General_1byte(&vfd.p,&buffer8[0],SIZE_BUFFER6);
    printf("\n       Iniciando queueus");	  
    vfd.config.bytes1=0;//init all parameter into zero
    vfd.f1.append=vfd_FIFO_push;
	vfd.f1.pop=vfd_FIFO_pop;                                                                                                                                                                                                                                                                                                                                                                                                                      
	vfd.f1.resetFIFOS=vfd_FIFOs_RESET;
	//qVFDtx.v=&vfd;//misma estructura en los dos lados,
	mutex_free=&mutex1;cond_free=&cond1;
	pthread_mutex_init(&mutex1,NULL);//
	pthread_cond_init(&cond1,NULL);  
	sync1=0xAA;//mutexs ocupados
	init_Queue_with_Thread(&qVFDtx);//fifos Transmisor data al Display
	vfd.config.bits.recurso_VFD_Ocupado=TRUE;//recurso ocupado, VFD nadie lo puede usar
	NoErrorOK();
	printf("\n       Creando Proceso Init VFD");
	switch(pthread_create(&Proc1_Init_VFD,NULL,Init_VFD,&qVFDtx)){
		case 0:NoErrorOK();
		        printf("\n       Creando Proceso Limpiador de INIT VFD");
		       if(pthread_create(&Proc_limpiador,NULL,Proceso_Limpiador,&qVFDtx)==0){
				   NoErrorOK();}else{errorCritico("Error de Proc Limpiador");}
			   break;
		default:errorCritico("Error desconocido de hilo init VFD");break;}
    pthread_detach(Proc1_Init_VFD);//no espera que terminen este proceso y el hilo continua
	pthread_detach(Proc_limpiador);//este hilo continua no espera que terminen los proc hijos
	printf("\n       Fin de  Init Queues");
	NoErrorOK();
	vfd.config.bits.recurso_VFD_Ocupado=FALSE;
}//fin init queue++++++++++

//** Proceso Hilo encargado de limpiar el Proceso Init VFD
void *Proceso_Limpiador(void *arg) {
struct Queue *q=(struct Queue*)arg;//
unsigned char estado;	
    printf("\n       Proceso Limpiador de VFD activo");
	pthread_mutex_lock(mutex_free);
	printf("\n       Limpieza de  recursos de init VFD...");
	switch(estado){
		case 1:if(vfd.config.bits.init_VFD==1)estado++;break;
		case 2:if(vfd.config.bits.Proc_VFD_Tx_running==0)estado++;break;
	    case 3:pthread_cond_wait(cond_free,mutex_free);
		       estado++;break;
		case 4:usleep(3);estado++;break;
		case 5://pthread_mutex_destroy(&vfd.sync.mutex_init_VFD);
			   //pthread_cond_destroy( &vfd.sync.cond_init_TX_VFD);
			   pthread_mutex_destroy(mutex_free);
			   pthread_cond_destroy(cond_free);sync1=0;//recurso libre
			   pthread_mutex_destroy(q->s.mutex);
			   pthread_cond_destroy(q->s.cond);
			   estado++;break;
		case 6:NoErrorOK();estado++;break;
		default:estado=1;break;}
    return NULL;
}//fin del proceso hilo limpiador+++++++++++++++++++++++++++++++



void init_Queue_with_Thread(struct Queue *q){    
	  q->head=q->tail=NULL;
	  q->size=0;
	  q->nLibres=SIZE_MAX_FIFO;
	  q->Tamano=SIZE_MAX_FIFO;
	  q->nOcupados=0;
	  sync1=0xAA;//mutexs usados,no disponibles
	  q->s.mutex=&mutex0;
	  q->s.cond=&cond0;
	  pthread_mutex_init(q->s.mutex,NULL);
	  pthread_cond_init(q->s.cond,NULL);
}//fin de init FIFO transmit VFD+++++++++++++++++++++++++
  


//encola regresa TRUE: si esta llena , FALSE: si esta vacia
void enqueue(struct Queue *q,struct VFD_DATA dato1){
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->dato=dato1;
	new_node->next=NULL;
    pthread_mutex_lock(q->s.mutex); //&vfd.sync.mutex_init_VFD);
	if(q->tail==NULL){
		  q->head=new_node;
		  q->tail=new_node;}
	else{q->tail->next=new_node;
	     q->tail=new_node;}
	q->size++;	 
	q->nLibres--;q->nOcupados++;
    pthread_cond_signal(q->s.cond);//vfd.sync.cond_init_TX_VFD); // Notifica que la cola no está vacía
    pthread_mutex_unlock(q->s.mutex);//vfd.sync.mutex_init_VFD);
}//fin enqueue++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct VFD_DATA dequeue(struct Queue  *q) {
	pthread_mutex_lock(q->s.mutex);//vfd.sync.mutex_init_VFD);
	while(q->size==0)//aqui sabemos que esta vacia la queue
	    pthread_cond_wait(q->s.cond,q->s.mutex);//vfd.sync.cond_init_TX_VFD,&vfd.sync.mutex_init_VFD);	//espera si la cola esta vacia
    struct Node *temp=q->head;
	struct VFD_DATA data=temp->dato;
	q->head=q->head->next;
    if(q->head==NULL)
	     q->tail=NULL;
    q->size--;q->nLibres++;q->nOcupados--;
	free(temp);		 
    pthread_mutex_unlock(q->s.mutex);//vfd.sync.mutex_init_VFD);

return data;
}//fin de queue+++++++++++++++++++++++++++++++++

/*  Control de Display de VFD de despliegue por thread  */
void* SubProceso_Tx_VFD(void* arg) {//consumidor
	struct Queue *q = (struct Queue *)arg;
	struct VFD_DATA data;
	unsigned char estado124,mem[20];


	printf("\n       Proceso Tx VFD running");
	while(q->isPadreAlive||q->size>0){//funcionan mientras este vivo init o haya datos en queue
	 switch(estado124){
	   case 1:NoErrorOK();estado124++;break;
	   case 2://printf("\n       estoy corriendo  ");break;
       case 3:vfd.config.bits.Proc_VFD_Tx_running=TRUE;estado124++;break;
	   case 4:data=dequeue(q);estado124++;break;     
	   case 5:if(Transmissor_a_VFD(data,&mem[0]))estado124--;break;
	   default:estado124=1;break;}}//fin switch y while
	   vfd.config.bits.Proc_VFD_Tx_running=FALSE;
       printf("\n       Hilo TX VFD Apagado:%d",estado124);
 	   NoErrorOK();
    
return NULL;
}//fin del subproceso de envio de datos al display+++++++++++++

//methodo que se usa en un hilo transmisor VFD+++++++++++++++++++++++
unsigned char Transmissor_a_VFD(struct VFD_DATA v,unsigned char *mem){
unsigned char ret=0,*estado1;
coordn16 coordenadas;
const unsigned char DELAY_TIME=1;
enum{   CHARS_X=20,  PUNTO_X=30,     POS_X=40, DELAY_X=50,  
      DELAYUS_X=60,DELAYMS_X=70, TRANSMTIR=80,SALIR_TX=99};
unsigned char *box1,*box0,*nbytes;
unsigned char *pen,*mode,*ibox0,*x1,*y1,*x2,*y2;
unsigned char *timer,*index,*datos;
static union W7{//access word: 
	unsigned  short int wordx; //0xaabb //aa
	unsigned char byte[2];     //byte[0]=aa,byte[1]=bb
}w16;

   estado1=mem+0;
	  box1=mem+2;
	  box0=mem+3;
	   pen=mem+4;
    nbytes=mem+5;
	 index=mem+6;
	 datos=mem+7;//este debe ser la ultima variable|

      switch(*estado1){//DRIVER DE VIDEO
    	  case 1:*timer=0;*index=0;ret=0;*nbytes=0;(*estado1)++;break;
		  case 2:switch(v.p){
                   case _BOX_:if(vfd.config.bits.BOX_enable){box1=&v.x;(*estado1)++;}
							  else{ *estado1=SALIR_TX;}break;
				   case _CHAR_:     *estado1=CHARS_X;break;
				   case _PUNTO_:    *estado1=PUNTO_X;break;	
				   case _RAYA_:     break;
				   case _BOLD_:     *estado1=SALIR_TX;break;//debug
				   case _POS_:      *estado1=POS_X;break;
				   case _DDS_BORRAR:*estado1=POS_X;break;
				   case _DDS_reZOOM:*estado1=POS_X;break;
				   case _DELAY_:    *estado1=DELAY_X;
				   case _DELAY_US:  *estado1=DELAYUS_X;break;
				   case _DELAY_MS:  *estado1=DELAYMS_X;break;	  
                   default:*estado1=SALIR_TX;break;}//fin-switch selection of operation++++++++++++
		  case CHARS_X:*(datos+0)=v.x;*nbytes=1;*estado1=TRANSMTIR;break;
		  case TRANSMTIR:  if(*nbytes==*index)*estado1=SALIR_TX;else(*estado1)++;break;
		  case TRANSMTIR+1:
#if ( DEPURANDO_SIN_DISPLAY_ENCENDIDO == 1 )
		                   if(digitalRead(R_BUSY_PIN)==1)(*estado1)++;
#else 
                           (*estado1)++;
#endif
						   break;
           case TRANSMTIR+2:printf(" %#X ",*(datos+*index));
		                    writePort(*(datos + (*index)++));//writePort(*(datos+*index));
		                   //*(datos+*index)=0;
						   *estado1=TRANSMTIR;
						   break;
		  case SALIR_TX:cleanArray(datos,DATOS_SIZE,0);*estado1=0;ret=TRUE;break;
		  default:*estado1=1;break;}//fin estado principal-----------------------------------------      
return ret;
}//transmisor de datos a VFD+++++++++++++++++++++++++++++++++++++++++


//Proceso  unico de padre unico  y sin instancias
void* Init_VFD(void* arg){  //Proceso Productor<---Proceso/hilo/THread
struct Queue *q=(struct Queue*)arg;//
pthread_t Proc2_Tx_VFD;//Proceso Transmisor al VFD, para despliegue de pantalla
unsigned char ret=0,estado;
const unsigned char SIZE_CMD=7;//numero de comandos
const unsigned char s[7]={0x1BU,0x40U,0x1FU,0x28U,0x67U,0x01U,FONTSIZE2};
unsigned char i=0;
pthread_attr_t attr;
size_t stacksize=2*1024*1024;// memoria para el hilo
pthread_attr_init(&attr);
if(pthread_attr_setstacksize(&attr,stacksize)!=0){
	 fprintf(stderr,"\n Error config tamaño de pila");
	 exit(EXIT_FAILURE);}


/*
	pthread_mutex_lock(&vfd.sync.mutex_free);
	vfd.config.bits.init_VFD=FALSE;
	vfd.config.bits.Proc_VFD_Tx_running=TRUE;
	vfd.config.bits.VDF_busy=TRUE;
	while(++i<10){
	printf("\n       Init VFD running");
	usleep(12200);}
	vfd.config.bits.init_VFD=TRUE;
	vfd.config.bits.Proc_VFD_Tx_running=FALSE;
	vfd.config.bits.VDF_busy=FALSE;
	pthread_cond_signal(&vfd.sync.cond_free);
	pthread_mutex_unlock(&vfd.sync.mutex_free);
    printf("\n       Proceso Init VFD Terminado");
*/


 if(vfd.config.bits.init_VFD){
	   errorCritico("ya esta inizializado Proceso, Error de duplicacion");}	   	   
 while(!ret){
	switch(estado){
		case 1:printf("\n       Init VFD starting. . .");estado++;break;
		case 2:pthread_mutex_lock(mutex_free);
		       vfd.config.bits.init_VFD=FALSE;//no se ha terminado de init
			   vfd.config.bits.Proc_VFD_Tx_running=TRUE;//no se ha iniziado este proceso
			   vfd.config.bits.VDF_busy=TRUE;//Nadie mas puede usar el VFD
               qVFDtx.isPadreAlive=TRUE;
			   estado++;break;
		case 3:NoErrorOK();estado++;break;
		case 4:printf("\n       Creando Hilo Transmisor");
		       if(pthread_create(&Proc2_Tx_VFD,&attr,SubProceso_Tx_VFD,&qVFDtx)!=0){//ret==0 :all OK	
				  fprintf(stderr," \n Error creando el hilo SubProc TX VFD");
				  exit(EXIT_FAILURE);}
			   else{NoErrorOK();}
			   estado++;
			   break;
	    case 5:printf("\n       Init, llenar FIFOs Init para Transmitir");
			   NoErrorOK();estado++;break;
		case 6:if(VFDcommand(s[i]))estado++;break; // init display  ESC@= 1BH,40H
		case 7:if(++i<(SIZE_CMD+1))estado--;else{estado++;}break;
		case 8:vfd.config.bits.init_VFD=TRUE;estado++;break;//se usa en limpieza esta bandera
		case 9:pthread_cond_signal(cond_free);estado++;break;
        case 10:qVFDtx.isPadreAlive=FALSE;estado++;break;
		case 11:estado=0;ret=TRUE;break;
		default:estado=1;break;}}//fin switch while 
  pthread_join(Proc2_Tx_VFD,NULL);//esperamos termine de transmitir a display el otro hilo
  pthread_attr_destroy(&attr);
  pthread_mutex_unlock(mutex_free);
  vfd.config.bits.Proc_VFD_Tx_running=FALSE;//Ya se Destruyo Proceso VFDtx
  printf("\n       Init Sub Proceso Init Terminado");
  NoErrorOK();		

return NULL;
}//fin init VFD -------------------------------------------------------------------



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
