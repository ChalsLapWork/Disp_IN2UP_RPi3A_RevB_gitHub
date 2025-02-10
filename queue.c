#include "system.h"
#include "queue.h"
#include "string.h"
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


#ifndef debug_level1
  #include <wiringPi.h>
#endif

#define BUFFER_SIZE 250  // Tamaño máximo de cada array
#define NUM_ENTRADAS 8   // Número máximo de arrays en el buffer circular

typedef struct {// Estructura para datos transmitidos
    unsigned char data[BUFFER_SIZE];
    size_t len;
} DatosTransmision;

typedef struct {// Buffer circular para almacenar múltiples arrays
    unsigned char data[BUFFER_SIZE];
    size_t len;
} EntradaBuffer;

EntradaBuffer buffer_circular[NUM_ENTRADAS];//buFFER  del TX del VFD

struct _DISPLAY_VFD_ vfd;
struct Queue qVFDtx;//queue de transmision vfd 
//struct _Sync2 s1;//sincronia 	
struct VFD_DATA dequeue(struct Queue   *q);
void enqueue(struct Queue  *q,struct VFD_DATA dato1);


// Buffer compartido
//unsigned char buffer[BUFFER_SIZE];
size_t buffer_length = 0;
int in = 0;//control de la FIFO de TX de la VFD
int out = 0;//control dela FIFO de Tx VFD

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
pthread_t SubPrcoc_SendBlock_TX_VFD;//TRAnsmisor de los datos al VFD
pthread_t SubProc_Tx_VFD;
// Mutex y condición
//pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;


sem_t sem_llenos;//semaforos de TX VFD
sem_t sem_vacios;//semaforos de TX de VFD
pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER;



void init_queues(void){
//const unsigned char init_VFD[]={0x1BU,0x40U,0x1FU,0x28U,0x67U,0x01U,FONTSIZE2};
unsigned char array1[] = {0x41, 0x42, 0x43, 0x44};
char string1[] = "Hola, soy un string 1";
unsigned char array2[] = {0x01, 0x02, 0x03, 0x04, 0x05};
char string2[] = "Este es otro string más largo";
int iteracion = 0;
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
	//pthread_mutex_init(&vfd.mutex.VDF_busy,NULL);
	//init_Queue_with_Thread(&qVFDtx);//fifos Transmisor data al Display
	vfd.config.bits.recurso_VFD_Ocupado=TRUE;//recurso ocupado, VFD nadie lo puede usar
	//init_mutex_VFD();//inizialisa los mutex que manejan el VFD, transmision
	NoErrorOK();
	printf("\n       Creando Proceso Init VFD");
	sem_init(&sem_llenos, 0, 0);
    sem_init(&sem_vacios, 0, NUM_ENTRADAS);
	if((debug=pthread_create(&SubPrcoc_SendBlock_TX_VFD,NULL,SubProceso_SendBlock_Tx_VFD,NULL))!=0){	
	    errorCritico2("Error creacion Hilo:",75);}else{NoErrorOK();}
    usleep(1);//solo para debug

while (1) {
        if (iteracion % 4 == 0) {
            SubProceso_SendBlock_Tx_VFD(array1);
        } else if (iteracion % 4 == 1) {
            SubProceso_SendBlock_Tx_VFD(string1);
        } else if (iteracion % 4 == 2) {
            SubProceso_SendBlock_Tx_VFD(array2);
        } else {
            SubProceso_SendBlock_Tx_VFD(string2);
        }
        iteracion++;
    }




	inicializar_VFD();//Init VFD
	printf("\n       Fin de Init Queues");
	vfd.config.bits.recurso_VFD_Ocupado=FALSE;
	NoErrorOK();
}//fin init queue+++++++++++++++++++++++++++++++++++++++++++++++++++++++++




/* //void init_Queue_with_Thread(struct Queue *q){    
	  q->head=q->tail=NULL;
	  q->size=0;
	  q->nLibres=SIZE_MAX_FIFO;
	  q->Tamano=SIZE_MAX_FIFO;
	  q->nOcupados=0;
	  q->s.m_Tx=&mutex_Tx_SendBlock;
	  q->s.cond_Tx=&cond_Tx_SendBlock;
	  pthread_mutex_init(q->s.m_Tx,NULL);
	  pthread_cond_init(q->s.cond_Tx,NULL);
}*///fin de init FIFO transmit VFD+++++++++++++++++++++++++
  


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


// Función que el hilo principal llama para enviar un bloque de caracteres
//*********PRODUCTOR-1****************************+
unsigned char VFD_sendBlockChars(void *datos, size_t len){
//unsigned char ret = 0;

      if (len > BUFFER_SIZE) {
        fprintf(stderr, "Error: El tamaño de los datos excede el BUFFER_SIZE\n");
        return 0;}

    sem_wait(&sem_vacios);
    pthread_mutex_lock(&mutex_buffer);
    buffer_circular[in].len = len;
    memcpy(buffer_circular[in].data, datos, len);
    printf("Productor: Escribió datos en el buffer (len: %zu)\n", len);
    in = (in + 1) % NUM_ENTRADAS;
    pthread_mutex_unlock(&mutex_buffer);
    sem_post(&sem_llenos);
return 1;
}//VFD_sendBlockChars+++++++++++++++++++++++++++++++++++++++++++++++++++++++++



/*  Control de Display de VFD de despliegue por thread 
++++++++++ CONSUMIDOR-1******---------------------------- */
void *SubProceso_SendBlock_Tx_VFD(void* arg) {//consumidor
    while (1) {
        sem_wait(&sem_llenos);
        pthread_mutex_lock(&mutex_buffer);

        DatosTransmision *datos = malloc(sizeof(DatosTransmision));
        datos->len = buffer_circular[out].len;
        memcpy(datos->data, buffer_circular[out].data, datos->len);
        printf("Consumidor: Copió del buffer_circular al buffer2 (len: %zu)\n", datos->len);
        out = (out + 1) % NUM_ENTRADAS;
        pthread_mutex_unlock(&mutex_buffer);
        pthread_t SubProc_Tx_VFD;
        if (pthread_create(&SubProc_Tx_VFD, NULL, Transmissor_SendBlock_VFD, datos) != 0) {
            perror("Error al crear el hilo transmisor");
            free(datos);
            continue;}

        pthread_detach(SubProc_Tx_VFD);
        sem_post(&sem_vacios);
    }//fin while+++++++++++++++++++++++++
return NULL;
}//+++++++++++++++++++++++++++++++++++++
//fin del subproceso de envio de datos al display+++++++++++++



void *Transmissor_SendBlock_VFD(void *arg){
DatosTransmision *datos=(DatosTransmision *)arg;
unsigned char estado,len,cmd,n;
unsigned char c[MAX_NUM_CHAR_VFD];
unsigned char *crc=NULL;
unsigned char str_len = 0;        // Longitud del string de entrada
char *str;
size_t i;

	crc=(unsigned char *)malloc(str_len *sizeof(unsigned char));    // Asignar memoria dinámica para el array crc basado en la longitud de *str
    if (crc == NULL) {// Error al asignar memoria
        printf("Error: No se pudo asignar memoria para crc.\n");
        return 0;}
   while(i<datos->len){
	str=&datos->data[i];
	switch(estado){// Continuar mientras no lleguemos al final de la cadena
      case 1:printf("\033[35m");estado++;break;
	  case 2:putchar(*str);estado++;break;
	  case 3:estado++;break;
	  case 4:if(*str++==STX)estado++;else{estado=99;}break;
	  case 5:*crc=len=*str++;n=1;estado++;break;
	  case 6:*(crc+n++)=cmd=*str++;i=0;estado++;break;
	  case 7:switch(len){
		         case 0:mensOK(" error 174, PROTOCOLO mal bytes ",CROJO);break;
				 case 1:mensOK(" eror 175 protocolo par hecho",CAMARILLO);break;
				 case 2:estado=9;break;
                 default:estado=8;i=0;break;}
	  case 8:if(len==n){n--;c[i]=0;estado++;}
	         *(crc+n++)=c[i++]=*str++;
             break;
	  case 9:if(*str++==getCRC_v2(crc,n))estado++;
	         else{estado=99;}break;
	  case 10: if(*str++==ETX)estado++;else{estado=99;}break;
	  case 11:procesar_Paquete(cmd,&c[0],n-2);break;
	  case 12:printf("\033[0m");
              fflush(stdout);//salida inmediata de buffer printf
              printf("\n");
			  break;
	  case 99:estado=2;ret=TRUE;mens_Warnning_Debug(" error 99 ");break;
	  default:estado=1;break;}
	  }//fin while 
}//transmisor de datos a VFD+++++++++++++++++++++++++++++++++++++++++
 				
/** esta funcion manda los paquetes del 
 *  buffer c en base al comando indicado,*/
unsigned char procesar_Paquete(unsigned char cmd,unsigned char *c,
                      unsigned char size){
union{
  unsigned short int t;
  unsigned char n[2];
}union_usi;
unsigned char ret=0,estado,ret2,i;     
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
    CMD_OK = 140   };

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
						  writePort(0x1F);
						  writePort(0x28);
						  writePort(0x67);
						  writePort(0x01);
					 	  writePort(0x02);
						  estado=CMD_OK;break;
           case CMD_BLD:  writePort(0x1F);  usleep(50);
		                  writePort(0x28);  usleep(50);
						  writePort(0x67);  usleep(50);
						  writePort(0x41);  usleep(50);
						  if(*c==1) writePort(0x01); 
						  else{writePort(0x00);}usleep(50);
						  estado=CMD_OK;break;
		   case CMD_OK: ret=TRUE;ret2=TRUE; estado=0;break;		   
		   case CMD_ERR:ret=TRUE;ret2=FALSE;estado=0;break;			
           default:estado=1;break;}//fin switch+++++++++++++
	}//fin of while ++++++++++++++++++++++++++++++++++++++++++
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
   pthread_mutex_init(&vfd.mutex.VDF_busy,NULL);//init recurso VFD
   if((debug=pthread_create(&SubProc_Run_Menu,NULL,Run_Menu,NULL))!=0)
       errorCritico2("errorCreacion hilo",175);
   else{pthread_detach(SubProc_Run_Menu);}//hilo independiente	   
}//fin del init Menu+++++++++++++++++++++++++++++++++++++++++++++++++++++


//Proceso de control de Menus
void *Run_Menu(void *arg){
   xControl_Principal_de_Menus_Operativo();
}//fin de run menu++++++++++++++++++++++++++++++++++++++++++++


//Proceso Thread de control de menus
/*Controla la salida segura de los menu de modo Operativo para que termine de hacer la tarea el
 * menu actual y luego se pase al siguiente menu cuando acabe y se presione el escape "x"
 *   se mete el contexto Actual  */
void xControl_Principal_de_Menus_Operativo(void){
unsigned char contexto;
unsigned char estado3;
enum{NORMAL=30,INIT_M=1,TERMINAR=90};
unsigned char mem[MEMO_MAX_FUNC_DISPL_MENU];//memoria para los methodos de despliegue

 while(vfd.config.bits.MenuPendiente){ //hilo corriendo  
	switch(estado3){//Maquina de Estados
	  case INIT_M:  if(!vfd.config.bits.init_Menu)estado3++;else{estado3=30;}break;
	  case INIT_M+1:vfd.config.bits.MenuPendiente=TRUE;estado3++;break;
	  case INIT_M+2:pthread_mutex_lock(&vfd.mutex.VDF_busy);estado3++;break;//Mejora de la funcion: recurso.solicitar
	  case INIT_M+3:contexto=find_contexto_Siguiente();estado3++;break;
	  case INIT_M+4:InitArbolMenu(contexto);estado3++;break;
	  case INIT_M+5:vfd.config.bits.Menu_Ready=0;estado3++;break;//menu no esta terminado aun
	  case INIT_M+6:if(MenuActualScreen.func2(&mem[0]))estado3=TERMINAR;break;//se despliega el MenuÂ¡Â¡
					
	  case TERMINAR:vfd.config.bits.init_Menu=TRUE;//no esta init el VFD
                    vfd.config.bits.MenuPendiente=FALSE;//hay pendiente un menu por desplegar
                    vfd.menu.contexto.Actual=contexto;
					pthread_mutex_unlock(&vfd.mutex.VDF_busy);//liberar recurso
	  default:estado3=1;break;}
   }//fin de WHILE bandera de Menu Pendiente--------------------   
	return;



/*
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
*/

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
