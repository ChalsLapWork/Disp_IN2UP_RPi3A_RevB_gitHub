
#ifndef SYSTEM_H_
  #define SYSTEM_H_
#include <stdint.h>

//LED PIN WIRINpi 0 is bcm_gpio 17.
#define BIT0_PIN 0
#define BIT1_PIN 1
#define BIT2_PIN 2
#define BIT3_PIN 3
#define BIT4_PIN 4
#define BIT5_PIN 5
#define BIT6_PIN 6
#define BIT7_PIN 7
#define WR_PIN   21
#define R_BUSY_PIN 22 //Ready/Busy
//**************************************************
// debug Nivel del debugeo numero-1
//#define debug_level1 1 //1:esta activado el debugeo
//#define debug_level1 2 //2:simular sin Rpi a linux normal

#define PHARMACEUTICO 0xAB

#ifndef _TIPO_DE_MAQUINA_
  #define _TIPO_DE_MAQUINA_ PHARMACEUTICO //TRIPLE_FRECUENCIA
#endif

/* MAXIMOS */
#define MAX_NUM_CHAR_VFD 30 //maximo numero de char a desplegar por comando a VFD


#define ON   1
#define YES  1

#ifndef FALSE
 #define  FALSE  0
#endif

#ifndef TRUE
  #define  TRUE   1
  #define  YES    1
  #define  SIMON  1
  #define  ON     1   
#endif


#define OFF  0
#define NOP  0
#define OK   0 //PARA EL regreso de una funcion
#define BOX_VACIA   0x01    
#define BOX_LLENA   0x02
#define POSITIVO    0	
#define NEGATIVO    1
#define POS         0xFF
#define NEG         0xAA

#define VERDE1      0xE1
#define HI  0x00
#define LO  0x01

#define POPx  0
#define PUSHx 1
#define HEADx 2
#define TAILx 3
#define POPy  4
#define PUSHy 5
#define HEADy 6
#define TAILy 7


#define WAIT        10	
#define DONE        11
#define FREE        12
#define _BOOT_      14  //estamos en el init antes del main booteando
#define SUBE        16
//#define STOP        17
#define RIGHT        0x41 //'R'
#define CENTRAL      0x42// 19
#define LEFT         0x43 //'L'
#define CENTER       0x44 //'c'
#define ZEROS        0x45 //'0'
#define MAYUSCULAS   0x46 
#define MINUSCULAS   0x47
#define SYMBOL       0x48
#define GET          0x49
#define PABAJO       0x4A
#define PARRIBA      0xAB //'¡'<- problema con este char en compilacion
#define ACTIVADO     0x4C
#define ACERCAR      0x4D
#define ALEJAR       0x4E
#define BUSY         0x4F
#define BUSY_WAIT    0x50
#define EJECUTAR     0x51
#define _DRIVER_     0x52
#define DINAMICO     0x53
#define DESACTIVADO  0x54
#define EMPTY        0x55
#define ESTATICO     0x56
#define ERROR_PASS   0x57
#define FULL         0x58
#define INIT         0x59
#define EJECUTANDOSE 0x5A
#define NUMEROS      0x5B
#define _PICKUP_     0x5C
#define ROJO         0x5D
#define SET          0x5E
#define CANAL_X      0x5F
#define CANAL_Y      0x60
//#define VERDE         'V'//ha sido reasignado a errorController no -Mover
#define libre_1      0x61// lugar libre para usar
#define CMD_POS_CHAR 0x62//COMANDO_FASE  lugar libre para usar  comando display fase de 5 chars
//#define COMANDO_POS   '3'//comando solo posicion se manda la posicion
//#define COMANDO_CHAR  '4'//comando solo un char asi nomas 
#define CMD_POS5CHARS '5'//COMANDO ENVIAR POSICION Y luego 5 chars
#define _DELAY_US     0x66
#define _DELAY_MS     0x67


#define EVENT_DDS_ON   0x80  //axxx xxxx flag event DDS TRUE
#define EVENT_DDS_OFF  0x7E //0111 1111 put off flag event-DDS as FALSE
#define DDS_BORRAR     0x40 //xbxx xxxx flag event borrar, TRUE   
#define DDS_BORRAR_OFF 0xBF //1011 1111 apagar bandera de borrar DDS
#define DDS_TIMER      0x20 //xxcx xxxx flag de timer para desplegar DDS
#define DDS_TIMER_OFF  0xDF //1101 1111 flag apgar el timer de dispaly DDS
#define DDS_RELOAD     0xE0//to reoad dds on zoom change, or rezise product angle
#define BUSY_K         555 //timer veces, que se cicla todo el sistema para hacer delay 


#define FIRST_START  0x80 //1xxx xxxx el '1' indica que ya se prendido|inizializado antes

#define CONFIRMAR    24
#define INCREMENTAR  25
#define RESET        26
#define READ_A_INC   28//read and increase
#define SUMAR         0x80  //No midificar ACcion de sumer en una funcion una variable, es un comando en una funcion 
#define RESTAR        0x40 //No modificar  ES UN comando en la funcion setUINT_varxDigito

#define SIZE_EEPROM 2000


#define GIRO_DE_PLANO_CARTESIANO    0x6B
#define GIRO_DE_COORDENADAS_POLARES 0x5A
//#define BAJA        17 redefined en memoria.h

//Configuracion de Vibracion
#define DISPLAY_FREE      0xF0 //Este valor es para la autoConfiguracion
#define DISPLAY_BUSY_BOX  0xF1//EL display esta ocupado desplegando boxes
#define DISPLAY_BUSY_NUM  0xF2 //El display esta ocupado desplegando numeros

//BOX BAR DISPLAY KOSTANT
#define SUBE_DONE   18
#define BAJA_DONE   19
#define LAST_BOX    20
#define MAX_BOXES   17 //NUMERO DE BOXES DINAMICAS del detector de barra.



//Constantes de control Operativo
#define DISPLAY_EEPROM       0x88 //despliegue la pantalla de contenido de eeprom
#define READ_EEPROM_DISPLAY  0x89

//Constantes Generales de memoria
#define RESTAURAR   0x20
#define SAVE        0x21

#define READ        0x24
#define BORRAR      0x25
#define CAMBIAR     0x26

//Menu MEDIDAS_DE_VOLTAJES
#define RAW_X       0x30 
#define RAW_Y       0x31
#define CENTRADO_X  0x32
#define CENTRADO_Y  0x33
#define ROT_X       0x34
#define ROT_Y       0x35
#define FILTRADO_X  0x36
#define FILTRADO_Y  0x37

//constantes para seleccionar el dispositivo SPI  a comunicar
#define ADC        0x31
#define DDS        0x33 //direct digital synthesis generator chip AD9833
#define ADC_CH0    0x34//cambio al ADC de otro dispositivo
#define ADC__CH0   0x35//para el ADC YA funcionando
#define ADC_CH1    0x36//cambio al ADC de otro device
#define ADC__CH1   0x37//el ADC en marcha constante

#define _A5_  0
#define _A4_  1
#define _A3_  2
#define _A2_  3
#define _A1_  4
#define _DM_  5
#define _M_   6
#define _C_   7
#define _D_   8 
#define _U_   9


//usuarios-----------------------------------------------------------------
#define UserDesarrollador  6  //clave    1974
#define UserIngeniero3     5  //clave    2904 
#define UserIngeniero2     4  //clave 5
#define UserIngeniero      3  //clave 4
#define UserAdministrador  2  //clave 2
#define UserOperador       1  //clave 1


//constantes IGUALES EN LA PROCESADORA Y LA IO
#define ACK   0xAA  //Byte de Acknowlege
#define NACK  0xAB  //Byte de no reconocimiento de paquete

//SEMAFOROS
#define SEM_CONTEXTO_CAMBIO 0xA1//semaforo para el cambio de contexto, 
#define SEM_CONTEXTO_FIN    0xA2//semaforo para esperar que se habilite el teclado y poder reactivar el controlador operativo escape

//-CONTROL DE PASSWORD
#define PASSCNTRL_SIZE  6

#define _ORIGEN_  1 //indice del array que controla la brrera de password
#define _DESTIN_  2	
#define _AUTHOR_  3
//--------------------------------------
#define ADMINISTRADOR  0x41//'A'
#define SERVICIO       0x53//'S'
#define OPERADOR       0x4F//'O'



//display de Sensibilidad en el DDS y deteccion.
//limites de sensibilidad en cada zoom
#define ZOOM_LIM_99 30
#define ZOOM_LIM_98 30
#define ZOOM_LIM_97 31


#define STX 0x03    //comando para despliegue VFD
#define ETX 0x02
#define COMANDO_CLRSCR     'c'
#define CMD_DELAY_MS       'm'
#define CMD_DELAY_US       'e'
#define COMANDO_DELAY_US   'u'
#define COMANDO_STRING     's'
#define COMANDO_CHAR       'X'
#define COMANDO_POS        'p' //70h
#define COMANDO_BOX        'b'
#define COMANDO_LINE       'L'
#define COMANDO_DOT        'd'
#define COMANDO_CLEAR      'c'
#define COMANDO_INIT       'i'//69h
#define COMANDO_BOLD       'B'
#define COMANDO_BOXF       'F'
#define COMANDO_USINT      0x12
#define COMANDO_PHASE      0x23

//CONSTANTES DE COMUNICACION
#define PARAM_SIZE_COMANDOS 10 //numero de parametros por comando 
//COMANDOS DE COMUNICACION SERIAL PROCESADORA
#define CMD_DET_ON 0x10 //Param:N/A Deteccion Activada/detectada
#define CMD_BARRA      0x11 //Param:1byte Hasta donde llego la barra de deteccion.
#define CMD_DET_PM     0x12 //PAram:4bytes parametro de SEnsibilidad y phase.
#define CMD_SENS_PHASE 0x13 //display Sens&phase in Portal inicio, 
#define CMD_TECLADO    0X14 //comando Teclado para mover el cursos del menu


//SIZES-------------------------------------------------------
#define BUFF_X_CONTEXTO_SIZE  MAXIMO_NUMERO_PROD+1 //RELE



//typedef union{//access word: 
//	unsigned  short int wordx;   //   	0xaabb   
//	unsigned char byteH;      //         aa
//	unsigned char byte[2];        //byte[0]=aa,byte[1]=bb
//}uword;
//
//typedef union{//access word: 
//	unsigned  long int Dwordx;   //   	0xffxxaabb    capacidad: 131071 bytes=1FFFFH=
//	//unsigned char byteH;      //         ff
//	unsigned char byte[4];        //byte[0]=ff,byte[1]=xx,byte[2]=aa,byte[3]=bb;
//}Dword;


/* REPORTES  +++++++++++++++++++++++++++++++++++++++++++++*/
//dominios
#define D_ERROR     0x22
#define D_FALLA     0x23
#define D_WARNING   0x24
/* tarjeta de evento  */
#define SUB_EV_UP   0x25
/* subdominios de eventos-.........................*/
#define  IIC_NO_ACK 0x26//I2C error no comm error de no responder ACK 


/*  VFD sistema operativo  KONSTANTES */
#define  _CHAR_     'c' //se despliega un char
#define  _PUNTO_    'p' //se despleiga un punto
#define  _RAYA_     'r'  //se despliega una raya
#define  _POS_      'P' //comando de posicion en la grafica
#define  _BOX_      'B' //se despliega una box de barra de deteccion
#define  _BOLD_     'D' //char bold display
#define  _NORM_     'N' //display char normal
#define  _BLINK_    'L' //display char blinking
#define  _INK_OFF   'F'//puntito apagado
#define _INK_ON     'O' //PUNTITO prendido
#define _DDS_BORRAR 'R'
#define _DDS_reZOOM 'z'
#define _DELAY_     'E'//delay de espera para mandar algo al VFD
//#define _FEM_       0x54 //estado FFlag End MEnu, describe que ya se desplego el menu seleccionado- para poder empezar a trabajar en ese menu
//#define DELAY_TIME 1 //numero de IntERRUPCIONES DE TIMER1 para crear delay

#define XROW        128//buffer para guardar los pixeles  que se estan
#define YCOL         24//desplegando en el DDS para se usados por el zoom despues
#define SIZE_MEMO_DRIVER_DISPLAY  160 //buffer para manejar el despliegue de datos en el VFD
#define SIZE_MEMO_MENUS   100 //memoria para desplegar los menus staticos,lo que no se mueve
/*******ERRORES CONTROL ****************************************/
#define WARNING 'W'
#define ERROR   'E'
#define INFO    'I'
#define BUG     'B'

/**MANEJADOR DE RECURSOS********************************************/
#define _VFD_       0xA1
#define _IO_        0xA2
//PID  DE MANEJADOR DE RECURSOS
#define PID_INIT_VFD            0xB1
#define PID_DISPLAY_RECHAZO_VFD 0xB2
#define PID_DISPLAY_PROD        0xB3
//PARAMETROS
#define SIZE_INST       4

/****************************************************************/
//PID  o Paternidad
#define PID1  0x01 //xinit_VFD
#define PID2  0x02 //VFDcommand
#define PID3  0x03 //FontSizeVFD
#define PID4  0x04//xControl_Principal_de_Menus_Operativo
#define PID5  0x05 //Display_Monitor_de_Phase_VFD
#define PID6  0x06//Display_Monitor_de_Rechazos_VFD
#define PID7  0x07//Display_Monitor_de_Producto_VFD
#define PID8  0x08 //Display_Monitor_de_Sensibilidad_VFD
#define PID9  0x09 //xEmpaquetado_de_datos_Deteccion_Hacia_IOUP
#define PID10 0x0A //xDisplay_Cursores_DDS_VFD
#define PID11 0x0B//xDisplay_Punto_DDS_VFD
#define PID12 0x0C //xDisplay_Sens_DDS_VFD
#define PID13 0x0D//cursorUpDown 
#define PID14 0x0E//digitoUpDown
#define PID15 0x0F//enterCursorDDS
#define PID16 0x10//digitoRtLeft
#define PID17 0x11//VFDdrawLine_v4
#define NOMBRE_PRODUCTO_SIZE  30 //numero de chars en nombre producto2


#define CONFIG_FILE "systema.ini"
#define PROD_FILE "productos.db"
#define SIZE_PASSWORD 20 //size max of password 
#define FIFOc_SIZE 10 //fifo de contexto
#define SIZE_BOXES    20
#define SIZE_TIPO_MAQ 18 //size tipo maq, longitud nombre de array

struct _PRODUCT1_{
   unsigned short int Cuenta_Rechazos;//numer de rechazos de producto
   unsigned short int Cuenta_Productos;//numero de productos que ha pasado por detector
   unsigned char CuentaProducto;//ON|OFF contar producto;
   unsigned short int Sensibilidad;//configurada para este producto
   unsigned char phase;//phase del producto, numero entero
   float fase;//fase del producto numero flotante
   unsigned char Phasefrac;// faccion del numero de fase.
    char name[NOMBRE_PRODUCTO_SIZE]; 
   unsigned short int Altura;   
   int id;//es el id del producto en la base de datos
   unsigned short int timeEspera;//timepo de espera de rechazo
   unsigned short int timeRechazo;
   unsigned char timeEsperaFrac;//timepo de espera fraccion
   unsigned char timeRechazoFrac;
   unsigned char Ganancia;
};


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
struct _Menu1_{
   struct _Contexto contexto;
   unsigned char cursorx;
   unsigned char cursory;
   //struct _Comando_DDS dds;
   unsigned char CuadroMadreReady;//el cuadro madre esta construido y listo?.
};

struct _Deteccion_{
       unsigned char EnCurso;//Hay una deteccion en curso
};

struct _KeyPAd_{
   unsigned char enable;//enable teclado
};

union _Byte5_{
	unsigned short int bytes1;
	struct{
		unsigned short FIFOonReset:1;//Las FIFOS estan reseteadas?? osea que esan en ceros y desbilitadas, esto para cambiar de contexto
		unsigned short DDSon:1;//indica si borramos registro de datos repetidos de DDS
		unsigned short TxBuffOFF:1;//buffer de TX vacio, para saber que ya se transmitio todo
		unsigned short init_VFD:1;//flag init VFD indica si ya se init el VFD comandos de inizializacion
		unsigned short init_Menu:1;//flag init Menu, enciende e inicializa los menus y el primer menu en pantalla
		unsigned short BOX_enable:1;
		//unsigned short VDF_busy:1;//se estan mandando comandos  o posiciones
		unsigned short ADC_DATO:1;
		unsigned short deprecated1:1;//deprecated
		unsigned short recurso_VFD_Ocupado:1;//recurso esta 0:libre o 1:ocupado?
        unsigned short Menu_Ready:1;//menu solicitado ya esta desplegado y listo.
	    unsigned short BorrarDDS:1;//borrar DDS 
        unsigned short MenuPendiente:1;//hay algun menu pendiente de desplegar?

	}bits;
};


struct _DISPLAY_VFD_{
    union  _Byte5_ config;//banderas de configuracion y control para el display y menus
    //struct _Sync2   mutex;//syncronia y control de hilos  
    struct _Menu1_ menu;  
    struct _KeyPAd_ keypad;
    struct _Deteccion_ deteccion;
    unsigned char Text[NOMBRE_PRODUCTO_SIZE];//texto que regresa  del procesador de textos
    unsigned char NIVEL_ACCESO;//nivel de accesso
    char tipo_de_Maquina[SIZE_TIPO_MAQ];
 	struct _box_control{
		 unsigned char boxs[SIZE_BOXES];
		 unsigned char box0;
		 unsigned char box; 
		 unsigned short int timer;//se activa  por timer y resetea el array
	     //unsigned char enable;deprecated //display cajas o lo que sea
	   }box;		
};//fin display VFD----------------------------------------------


typedef struct {
    char level1[SIZE_PASSWORD];
    char level2[SIZE_PASSWORD];
    char level3[SIZE_PASSWORD];
    char level4[SIZE_PASSWORD];
    char level5[SIZE_PASSWORD];
    unsigned char seguridad_iniciada;
} Seguridad;

extern Seguridad g_seguridad;


#endif


//#endif //***************************************************************
//**********************************************************************
