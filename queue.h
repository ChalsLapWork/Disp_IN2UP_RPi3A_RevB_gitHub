#ifndef __QUEUE_H__
  #define __QUEUE_H__  

#include <stdint.h>

#ifndef _PTHREAD_H_
  #define _PTHREAD_H_
  #include <pthread.h>
#endif
#define SIZE_BUF_TFT 5
#define SIZE_IO_TX_BUFFER 85 //ARRAY donde se guarda la direccion de la cabeza del paquete a enviar
#define SIZE_B 60//ARRAY donde se guarda los paquetes que se van a enviar

#define SIZE_FIFO_BOX 10
#define SIZE_FIFO SIZE_FIFO_BOX//30  //array size where the ADC's values are saved

#define SIZE_BARR_NUM 22//size fifo to displat numeros and position where menus has barra detection
#define SIZE_FIFO_CMD_DDS 30 //tamaño de la FIFO para transmitir comando DDS al touch

#define SIZE_BUFFER_TX 90 //BUFER DE TRANSMISION SERIAL ALA O
#define SIZE_BUFFER_DDS_FIFO 50
#define SIZE_TEMP_PIXEL  6//tamaño del buffer para guardar memoria de pixels del display DD
#define SIZE_DDS_PIXEL   40//para pintar el pixel en tiempo real
#define SIZE_DDS_ZOOM   2000
#define SIZE_X  24//array zoom repaint char pantalla 0
#define SIZE_Y  129//array zoom repaint char pantalla0

#define SIZE_SER_KEYPAD 10 //TAMAÑO de la fifo del serial del keypad de entraada
#define SIZE_KEYPAD_IN 10 //buffer de entrada de chars de serial de keypad
#define SIZE_BUFFER1  10U //buffers de rx y tx de serial a IOUP
#define SIZE_BUFFER2  5U//tamaño de rx y tx de i2c fifo memorias
#define SIZE_BUFFER5  20U//kEYPAD FLIP FLOP save keysrokes tamaño de buffer char que entran keypad serial 
#define SIZE_BUFFER6  10//1954U//FIFO de graficos box,char,rayas,puntos,pos,con SO
#define SIZE_BUFFER9  50 //fifo GUARDA LOS pixeles que estan fuera de la pantalla DDS porque se salieton del zoom,estan mas alla del valor desplegable actual al zoom actual
#define SIZE_BUFFER13 10 //FIFO para gestionar recurso VFD de los hilos
#define SIZE_BUFFER14 20//20=No modif streaming-block size transmision a la IOUP  
#define SIZE_BUFFER15 20 //20 no modificar FIFO guarda deteccion, para transmitirla por serial IOUP
#define SIZE_BUFFER16 5  //buffer de recursos de vfd de gestion de
#define SIZE_BOXES    20
#define SIZE_SYS_MONITOR 30
#define SIZE_TBC 15
#define SIZE_CHAR 5
#define SIZE_FEW  3
#define DATOS_SIZE 14U //tamaño del buffer de transmision al VFD
#define SIZE_MAX_FIFO 10//TAMAÑÑO de fifo de transmision a VFD

#define SIZE_MAX_SENDBLOCK 20 //TAMAÑO maximo de envio en bloque de la funcion
#define FIFOc_SIZE 10 //fifo de contexto

#define SIZE_TIPO_MAQ 18 //size tipo maq, longitud nombre de array
#define NOMBRE_PRODUCTO_SIZE  30
#define NAME_INIT             0xE8 //DETERMINA QUE LA cadena de nombre del producto es un producto con nombre real y no solo basura


/*version 310322-1641 add reset genaral */
struct _FIFO_1byte_{//FIFO PARA UNA VARIABLE para un byte
    unsigned char *pop;//primer de la FIFO para salir
    unsigned char *head;//indice 0 del buffer
    unsigned char *tail;//ultimo indice del buffer
    unsigned char *push;//pointer buffer 2
	unsigned char (*popf)(unsigned char *n,struct _FIFO_1byte_ *s);//quitar el prmer elemento de la fifo DDS
	unsigned char (*appendByte)(unsigned char  n,struct _FIFO_1byte_ *s);//agregar byte al buffer de transmision
    void (*vaciarbuff)(unsigned char *p1,unsigned char *p2,unsigned short int size);
    void (*resetFIFO)(struct _FIFO_1byte_ *s,unsigned char *arr,unsigned char size);
    unsigned short int ncount;//cuenta los nodos llenos en la fifo
    unsigned short int size; //size de la fifo
    unsigned char nLibres;//cantidad de nLibres
    unsigned char nOcupados;//cantidad de ocupados
};




 struct _Sync{
	//pthread_cond_t  cond_init_TX_VFD;//condicion de init VFD transmisor
	//pthread_mutex_t mutex_init_VFD;//mutex para init VFD y transmisor
	pthread_mutex_t mutex_free;//mutex para liberar 
	pthread_cond_t  cond_free;//mutex cond para liberar

};//control de sincronia entre los hilos 
 
/*struct _Sync2{
   pthread_cond_t  *cond_free;
   pthread_mutex_t *m_Free;
   pthread_cond_t  *cond_Tx;
   pthread_mutex_t *m_Tx;
   pthread_cond_t  *cond_Mon;
   pthread_mutex_t *m_Mon;
   pthread_mutex_t  VDF_busy;//recurso VFD
   //unsigned char sem;//semaforo para que no se empalme su uso
};*/ //synscronia estructura+++++++++++++++++++++++++++++++++++



struct VFD_DATA{
  unsigned char x;
  unsigned char y;
  unsigned char p;
};


struct Node{
  //unsigned char Xdata[SIZE_MAX_FIFO];
  //unsigned char Ydata[SIZE_MAX_FIFO];
  //unsigned char Pdata[SIZE_MAX_FIFO];
  struct VFD_DATA dato;
  struct Node *next;
};//Nodo para crear las queues+++++++++++++++++++++++++++




struct Queue{
  struct Node *head,*tail;
  int size;  //size of the queue
  #if(SIZE_MAX_FIFO<255)
    unsigned char nLibres;
	unsigned char nOcupados;
	unsigned char Tamano;//tamaño de cantidad de datos a guardar numero fijo
  #endif
  struct _Sync2 s;//apuntador sync de mutex que usar la queue
  unsigned char isPadreAlive;//el proceso que encola esta vivo?, para saber si el transmisor ya tiene que terminar
  unsigned char *p;//pointer char to be send
  unsigned char sizeStream;//size to be send to vfd
};





struct _FIFO_func_{
	  //unsigned char (*append)(unsigned char x,unsigned char y, unsigned char p);
      unsigned char (*append)(struct Queue *q,struct VFD_DATA dato);
	  unsigned char (*pop)(unsigned char *x,unsigned char *y, unsigned char *p);
	  unsigned char (*resetFIFOS)(void);//resetear todas las FIFOs Y arrays y registros
};//fin _FIFO_func_----------------------------------------

struct FIFOc {
    uint8_t buffer[FIFOc_SIZE];  // Almacena números de 1 byte (8 bits)
    int head;  // Índice de inserción
    int tail;  // Índice de extracción
    int count; // Cantidad de elementos almacenados
};//contexto

struct _Contexto{
		unsigned char Actual;  //contexto Actual
		unsigned char Modificado;
		unsigned char destino;//al que quiero ir
		unsigned char control;//el contexto control, controla como llegar al que quiero ir
		unsigned char final;//el contexto al que me mandan si algo sale mal
		unsigned char permisos;//guarda los permisos actuales de cada menu
		unsigned char Anterior0;
		unsigned char Anterior1;
		unsigned char Anterior2;
		unsigned char Anterior3;
		unsigned char Anterior4;
		unsigned char solicitaCambioA;//a donde se ccambiar de contexto
        struct FIFOc fifo;
        int  (*pop)( uint8_t *value);
		void (*push)(uint8_t value);
		unsigned char  (*peek)( int position, uint8_t *value);		
};





struct ZoomControl{//para crear  el zoom y las ecuaciones  polinomicas de acondicionamiento de señal para el DDS
	   signed short int Max;//valor maximo del cuadro central de la pantalla
	   //signed short int Maxn;//valor negativo
	   //float a; //coeficiente del termino grado2
	   //float b;//coeficiente del termino grado 1
	   //float c; //coeficiente del termino grado 0
	   double zFactor;// son los mas menos 32768 entre los 100 zoom's
	   float indiceConversion;//lo que se multiplica para escalar al zoom seleccionado
	   unsigned char Cx; //coordenada x del centro de la pantalla
	   unsigned char Cy;//coordenadas y del centro de la pantalla
	   unsigned char Zoom;//es el zoom se seleccionado actual
	   unsigned short int pixelSizeX;//limite del numero digital despleglable en DDS en funcion del Zoom
	   unsigned short int Maxx;//limite del numero digital desplegable en DDS en funciona del Zoom
	   unsigned short int pixelSizeY;//limite del numero digital despleglable en DDS en funcion del Zoom
	   unsigned short int Maxy;//limite del numero digital desplegable en DDS en funciona del Zoom
	   signed short int lapso;//es el Maximo - Minimo	
	   unsigned short int Ymax;//maximo valor a graficar el zoom en Y, linea de sensibilidad para este zoom
	   unsigned short int Ymin;//minimo valor en la posicion-1 de linea de sesibilidad 
       //zoom.indiceConversion
	  // float factor;//factor de multiplicacion por zoom
	   float (*factor)(unsigned char);//apiunta ala funcion que nos da el factor en funcion del zooom
	   struct Coordusi (*MaxZoom)(unsigned char);//maximo valor para ese zoom en x 
};




/*  FIN DDS ESTRUCURA ********************************************++++*/
/*  FIN DDS ESTRUCURA ********************************************++++*/
/*  FIN DDS ESTRUCURA ********************************************++++*/


void init_queues(void);
unsigned char isFIFO_DDS_Display_Char_empty2(void);
unsigned char *next(unsigned char *inicio,unsigned char *final,unsigned char *pos,unsigned char *pop);
void reset_FIFO_serial_TX(void);
unsigned char is_App(unsigned char(*pop)(void),unsigned char *n);
void reset_FIFO_general_UChar(struct _FIFO_1byte_ *s,unsigned char *arr,unsigned char size);
void init_queues(void);
void Terminar_subProcesos(void);
void* Init_VFD(void* arg);
void init_menu(void);
void *Run_Menu(void *arg);
unsigned char procesar_Paquete(unsigned char cmd,unsigned char *c,unsigned char size);
void iniciar_Run_Menu(void);
void init_fifo_contexto(struct FIFOc *fifo);
int pop_contexto(struct FIFOc *fifo, uint8_t *value);
void push_contexto(struct FIFOc *fifo, uint8_t value);
unsigned char peek_contexto(struct FIFOc *fifo, int position, uint8_t *value);
void push_fifo_contexto(uint8_t dato);
int pop_fifo_contexto(uint8_t *value);
unsigned char peek_fifo_contexto(int position, uint8_t *value);
void configModificado(unsigned char contexto);
#endif 
