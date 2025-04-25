#include "system.h"
#include "queue.h"
#include "VFDthread.h"
#include "Memoria.h"


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
#include "VFDmenu.h"
#include <semaphore.h>

#ifndef debug_level1
  #include <wiringPi.h>
#endif



extern struct _DISPLAY_VFD_ vfd;
extern struct _PRODUCT1_ producto2;
//extern Seguridad g_seguridad;
Seguridad g_seguridad = {0};  // Inicializada vacía

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
	
    mensOK("Iniciando queueus",CCIAN);	  
	sync1=0xAA;//mutexs ocupados
	NoErrorOK();
	mensOK("Creando Proceso Init VFD",CAZUL1);
	init_VFD_Threads();
	inicializar_VFD();//Init VFD
	mensOK("Fin de Init Queues",CMAGNETA);
	NoErrorOK();
    init_fifo_contexto(&vfd.menu.contexto.fifo);
	vfd.menu.contexto.pop=pop_fifo_contexto;
	vfd.menu.contexto.push=push_fifo_contexto;
	vfd.menu.contexto.peek=peek_fifo_contexto;
    g_seguridad.seguridad_iniciada=0;
    log_mensaje("informacion","[ OK ] System init_Queues ");
	cargar_estado_Contadores();//var contar prod y rechazo from file
}//fin init queue+++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void push_fifo_contexto(uint8_t dato){
push_contexto(&vfd.menu.contexto.fifo,dato);
}//fin e push contexto de fifo ++++++++++++++++++++

int pop_fifo_contexto(uint8_t *value){
return(pop_contexto(&vfd.menu.contexto.fifo,value));
}//fin de pop fifo contexto++++++++++++++++++++++++++++

//regresa 0:el contexto anterior que estabamos 1: anterior 2:anterior al anterior asi 
// *value:0 si algo salio mal,1:todo bien
unsigned char peek_fifo_contexto(int position, uint8_t *value){
return(peek_contexto(&vfd.menu.contexto.fifo,position,value)); 
}//fin de peek fifo de contexto+++++++++++++++++++++ 



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
unsigned char procesar_Paquete(unsigned char cmd,unsigned char *c,unsigned char size){
const unsigned int TIEMPO_CAJAS=12000;//useg tiempo de espera para cambio de cajas
//const unsigned char MAX_BOXES =17;//nmero de boxes Dinamicas
unsigned char *box0,*box1,mode,ibox0,pen;
unsigned char  x1,y1,x2,y2,a[20];						
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
	CMD_BAR= 150,
	CMD_USINT= 160,
	CMD_PHASE= 162 };

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
					 case COMANDO_USINT:estado=CMD_USINT;break;
					 case COMANDO_PHASE:estado=CMD_PHASE;break;     
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
           case CMD_BOX:  vfd.config.bits.recurso_VFD_Ocupado=TRUE;
		                  if(!vfd.config.bits.BOX_enable)
						              {estado=CMD_OK;break;}
		                  writePort(0x1F);  usleep(50);
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
							   //printf("\n 1:box0=%i  box1=%i\n",*box0,*box1);
							   *box1=*c;  //*box0=0;
							   //printf("\n 2:box0=%i  box1=%i\n",*box0,*box1);
							   for(int i=0;i<20;i++){
							              a[i]=0;}
							   a[0]=0x1F;a[1]=0x28;a[2]=0x64;a[3]=0x11;
		                       estado++;}
					      else{estado=CMD_ERR;}
						  break;		  
		   case CMD_BAR+1://printf("\n 3:box0=%i  box1=%i\n",*box0,*box1);
		                  if(*box0>MAX_BOXES)
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
					       if((mode==BOX_VACIA)||(mode==BOX_LLENA)){
						   if((pen==0)||(pen==1)){
		                          		   a[4]=mode;a[5]=pen;		  
						           a[6]=x1;a[8]=y1;a[10]=x2;a[12]=y2;
                                                           estado++;}	 
						   else{estado=CMD_ERR;}}
                                                else{estado=CMD_ERR;}
						  //printf("\n 4:box0=%i  box1=%i\n",*box0,*box1);						
						  break;
		   case CMD_BAR+2://printf("\n 5:box0=%i  box1=%i\n",*box0,*box1);
		   				  for(int i=0;i<14;i++){
		                       writePort(a[i]); usleep(100); }
						  usleep(TIEMPO_CAJAS);//tiempo que tarda la caja en cambiar
						  estado--;
						   break;//regresamos al estado anterior
		   case CMD_USINT:vfd.config.bits.recurso_VFD_Ocupado=TRUE;
		                  union_usi.n[0]=*c;
						  union_usi.n[1]=*(c+1);
						  //union_usi.t <--Guardado aqui el valor a desplegar
						  x1=*(c+2);//posx
						  y1=*(c+3);//posy
						  x2=*(c+4);//formato
					      a[0]=0x1F;a[1]=0x24;a[2]=x1;
						  a[3]=0;a[4]=y1;a[5]=0;
						  for(int i=0;i<6;i++){
			                      	writePort(a[i]); usleep(50);}
						  getCharsFromUINT_var(&a[0],union_usi.t);
						  get_5_Chars_to_ASCII(&a[0]);
						  switch(x2){
							case RIGHT:Formato_USInt(&a[0],&a[5],5,&y2);
							           format_Right(&a[5]);
							           for(int i=5;i<10;i++){
											writePort(a[i]);
											usleep(50);}
										break;	
							case LEFT:Formato_USInt(&a[0],&a[5],5,&y2);
									  format_Left(&a[5]);
							          for(int i=5;i<10;i++){
										  writePort(a[i]);usleep(50);}
									  break;
							case CENTER:Formato_USInt(&a[0],&a[5],5,&y2);
									    format_Center(&a[5]);
							            for(int i=5;i<10;i++){
											  writePort(a[i]);usleep(50);}
							             break;					  
							case ZEROS:for(int i=0;i<5;i++){
											  writePort(a[i]);usleep(50);}
							            break;
							default:break;}
                         estado=CMD_OK;
						 break;
		   case CMD_PHASE:vfd.config.bits.recurso_VFD_Ocupado=TRUE;
		                  x1 =*c;//phase
						  y1 =*(c+1);//phasefrac
						  x2 =*(c+2);//posx
						  y2 =*(c+3);//posy
						  pen=*(c+4);//formato
					      a[0]=0x1F;a[1]=0x24;a[2]=x2;//comando posicion
						  a[3]=0;a[4]=y2;a[5]=0;
						  for(int i=0;i<6;i++){//poner la posicion
			                      	writePort(a[i]); usleep(50);}
                          getASCIIFromUChar1(x1,&a[0]);//sacar los ascii phase entero
						  y2=procesar_Frac_Fase(y1);//get ascii frac
                          Formato_uChar((char *)a,pen);//format phase entero
						  for(int i=0;i<3;i++){
								writePort(a[i]);usleep(50);}
						  writePort('.');usleep(50);
						  writePort(y2); usleep(50);
                          estado=CMD_OK;
						  break;				  
		   case CMD_OK:vfd.config.bits.recurso_VFD_Ocupado=FALSE; 
		               ret=TRUE; estado=0;break;		   
		   case CMD_ERR:vfd.config.bits.recurso_VFD_Ocupado=FALSE;
		                ret=TRUE;estado=0;break;			
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
       //errorCritico2("errorCreacion hilo",175);
        log_mensaje("error","[Error] Executing Run Menu ");
   else{pthread_detach(SubProc_Run_Menu);
        log_mensaje("informacion","[ OK ] Executing Run Menu ");}//hilo independiente	   
}//fin del init Menu+++++++++++++++++++++++++++++++++++++++++++++++++++++

void iniciar_Run_Menu(void){
  if((pthread_create(&SubProc_Run_Menu,NULL,Run_Menu,NULL))!=0)
       errorCritico2("errorCreacion hilo",175);
  else{pthread_detach(SubProc_Run_Menu);}//hilo independiente
}//fin de iniciar run menu+++++++++++++++++++++++++++++++++++++



//Proceso de control de Menus
void *Run_Menu(void *arg){
unsigned char contexto;
unsigned char estado3;
enum{NORMAL1=30,INIT_M=1,TERMINAR1=90};
//unsigned char mem[MEMO_MAX_FUNC_DISPL_MENU];//memoria para los methodos de despliegue

 while(vfd.config.bits.MenuPendiente){ //hilo corriendo  
	switch(estado3){//Maquina de Estados
	  case INIT_M:  estado3++;break;    
	  case INIT_M+1:if(vfd.config.bits.recurso_VFD_Ocupado==0)
	                         estado3++;
					break;		   
	  case INIT_M+2:vfd.config.bits.BOX_enable=0;
	                vfd.config.bits.Menu_Ready=0;
	                estado3++;
					break;
	  case INIT_M+3:estado3++;break;//Mejora de la funcion: recurso.solicitar
	  case INIT_M+4:contexto=find_contexto_Siguiente();estado3++;break;
	  case INIT_M+5:InitArbolMenu(contexto);estado3++;break;
	  case INIT_M+6:vfd.config.bits.Menu_Ready=0;estado3++;break;//menu no esta terminado aun
      case INIT_M+7:MenuActualScreen.func();estado3=TERMINAR1;break;					
	  case TERMINAR1:vfd.config.bits.init_Menu=TRUE;//no esta init el VFD
                    vfd.config.bits.MenuPendiente=FALSE;//hay pendiente un menu por desplegar
                    vfd.menu.contexto.Actual=contexto;
					vfd.menu.contexto.solicitaCambioA=0;
					vfd.menu.contexto.Modificado=0;
					vfd.keypad.enable=1;//habilitado teclado
					break;
	  default:estado3=1;break;}
   }//fin de WHILE bandera de Menu Pendiente--------------------   
return NULL; 
}//fin de prueba de despliegue de datos en el VFD+++++++++++++++++++++++++++++
//fin del control operativo del menu de escape-----------------------------------------
 

// Inicializa la FIFO,
void init_fifo_contexto(struct FIFOc *fifo) {
    fifo->head = 0;
    fifo->tail = 0;
    fifo->count = 0;
}//FIN init fifo+++++++++++++++++++++++++++++

// Inserta un número en la FIFO, eliminando el más antiguo si está llena
void push_contexto(struct FIFOc *fifo, uint8_t value) {
    if (fifo->count == FIFOc_SIZE) {
        // FIFO llena, descartamos el elemento más antiguo
        fifo->tail = (fifo->tail + 1) % FIFOc_SIZE;
        fifo->count--;
    }
    fifo->buffer[fifo->head] = value;
    fifo->head = (fifo->head + 1) % FIFOc_SIZE;
    fifo->count++;
}//fin de push contexto+++++++++++++++++++++++++++++++

// Extrae el número más antiguo de la FIFO
int pop_contexto(struct FIFOc *fifo, uint8_t *value) {
    if (fifo->count == 0) {
        return 0; // FIFO vacía
    }
    *value = fifo->buffer[fifo->tail];
    fifo->tail = (fifo->tail + 1) % FIFOc_SIZE;
    fifo->count--;
    return 1;
}//fin pop contexto+++++++++++++++++++++++++++++

// Lee un elemento sin sacarlo (último, penúltimo... hasta el quinto último)
/*FIFO: A0 
FIFO: A0 A1 
FIFO: A0 A1 A2 
...
FIFO: A2 A3 A4 A5 A6 A7 A8 A9 AA AB 
FIFO: A3 A4 A5 A6 A7 A8 A9 AA AB AC 
FIFO: A4 A5 A6 A7 A8 A9 AA AB AC AD 
Peek(1): AD
Peek(2): AC
Peek(3): AB
Peek(4): AA
Peek(5): A9
Pop: A4
Pop: A5
Pop: A6
FIFO: A7 A8 A9 AA AB AC AD */
unsigned char peek_contexto(struct FIFOc *fifo, int position, uint8_t *value) {
    if (position < 1 || position > 5 || position > fifo->count) {
        *value = 0;    
		return 0; // Posición fuera de rango
    }
    int index = (fifo->head - position + FIFOc_SIZE) % FIFOc_SIZE;
    *value = 1;
    return fifo->buffer[index];
}//fni peek++++++++++++++++++++++++++++++++++++++++



void Terminar_subProcesos(void){
    //pthread_join(Proc_Tx_VFD,NULL);
	//pthread_mutex_destroy(&q->lock);
}//terminar subprocesos+++++++++++++++++++++++++



//se resetea toda la fifo y todo queda cmo de inici
// version 21-oct-24:10:15am
void reset_FIFO_general_UChar(struct _FIFO_1byte_ *s,
       unsigned char *arr,unsigned char  size){
	   s->pop=s->push=s->tail;
	   s->ncount=0;
	   cleanArray(arr,size,0);
	  
}//fin reset_FIFO_serial_TX---fin se resetea toda la fifo


void configModificado(unsigned char contexto){
     //(void)contexto;
	 vfd.menu.contexto.Modificado=contexto;//hay un modificado
}//fin de configmodificado



