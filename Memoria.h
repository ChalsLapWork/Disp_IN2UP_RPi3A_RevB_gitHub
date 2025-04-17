


#ifndef MEMOCONFIG_H_
#define MEMOCONFIG_H_


#include <sqlite3.h>



#define  MULTI_100_286_875    'M'//0x70U//DEFINE EL TIPO DE MAQUINA MULTI(100,286,875)
#define  MULTI_30_100_26      'm'//0x71U
#define  SINGLE_875_286       'S'//0x72U
#define  SINGLE_100_30        's'//0x73U
#define  VF_875_286           'V'//0x74U
#define  VF_100_30            'v'//0x75U
#define  PHARMACEUTICAL       'P'// 0x76U

#define  DRIVER               0x90U//tipo de tarjetas en menu ganacias
#define  ANALOGA              0x91U
#define  PICKUP               'p'
//#define                   0x92U //ganancias
//#define                  0x93U
//#define                   0x94U
#define  AJUSTABLE            'J'

#define NORMAL                0x96U
#define ALTA_VELOCIDAD        0x97U
#define INTERMEDIA            0x98U
#define BAJA_64               0x99U
#define BAJA_128              0x9AU
#define DESPACIO              0x9BU

#define ALTA                  'A' //41h
#define MEDIA                 'M' //4Dh
#define BAJA                  'B' //42h

#define SIZE_ERROR             25//cada bit es un error. 25*8=200 errores NUMERO DE ERRORES ESTA EN BASE AL NUMERO DE BUFFER DE I2C
//#define NOMBRE_PRODUCTO_SIZE   25
//definiciones de los productos select and menus
//#define PRODUCT_SIZE      LASTADDRESS_VARS_EEPROM//55 bytes por producto, por 200 productos
#define START_PRODUCT_ADD EEPROM_ADD_BIOS+16//direccion donde empiezan los productos
//#define PRODUCT_NAME_SIZE 20 SE MOVIO A  VFDmenu.h//bytes de nombre NO CAMBIAR NUMERO SI LO HACES CAMBIAR TAMBIEN INDICE EN READ Y WRITE EEPROM BLOCK


#define STATUS_FACTORY_SIZE   5
#define SYSTEM_VAR_SIZE       44 //ESPACION B, NUMERO de variables del sistema 
#define PROD_VAR_SIZE         44 //ESPACIO  C,numero de bytes para un producto
#define _STATUS_FACTORY_      0xA9 //nos dice si es la primera vez que se enciende con esta funcion, cambiar numero si se agrega otra funcion al sftware que necesite ser iniciaizad por primera vez
#define NAME_INIT             0xE8 //DETERMINA QUE LA cadena de nombre del producto es un producto con nombre real y no solo basura
#define PASSWORD_SIZE         NOMBRE_PRODUCTO_SIZE
#define IGXM_SIZE             PROD_VAR_SIZE
#define AUX1_USERDEFINED_SIZE NOMBRE_PRODUCTO_SIZE//Nombre de user defined de auxiliar input 1
#define AUX2_USERDEFINED_SIZE NOMBRE_PRODUCTO_SIZE//Nombre de user defined de auxiliar input 2


#if (IGXM_SIZE < (PASSWORD_SIZE+1)) //NO PUEDE SER MENOR QUE PASSWORD SIZE
 #error "error de tamaño de constantes IGXM	"
#endif

#define STATUS_FACTORY_ADD    0x03UL    //BLOQUE A, 1-byte
#define PRODUCTO_COUNTING_ADD 0x04UL    //dentro de bloque-A, 1byte //numero de productos guardados por usuario aparte del default
#define SYSTEM_VAR_ADD        STATUS_FACTORY_ADD+STATUS_FACTORY_SIZE    //Bloque B
#define PROD_CACHE_VAR_ADD    SYSTEM_VAR_ADD+SYSTEM_VAR_SIZE  //BLoque  C
#define PROD_VAR0_ADD         PROD_CACHE_VAR_ADD+PROD_VAR_SIZE
#define CACHE_SPACE           PROD_CACHE_VAR_ADD   // w/r la EEPROM espacion CAche
#define TEST_SETUP_SPACE      PROD_VAR0_ADD
#define PRODUCTO1_ADD         PROD_VAR0_ADD+PROD_VAR_SIZE //primer producto de ususrio
#define MAXIMO_NUMERO_PROD    199 //No CAMBIAR DE 199 Maximo numero de prodcuctos igual que lock
#define PRODUCTO_ULTIMO_ADD   PROD_VAR0_ADD+(PROD_VAR_SIZE*(MAXIMO_NUMERO_PROD-1))
//all this below deprecated
#define PASSWORD_LEVE1_ADD    1 //PRODUCTO_ULTIMO_ADD+PROD_VAR_SIZE
#define PASSWORD_LEVE2_ADD    2 //PASSWORD_LEVE1_ADD+PASSWORD_SIZE
#define PASSWORD_LEVE3_ADD    3 //PASSWORD_LEVE2_ADD+PASSWORD_SIZEdeprecated
#define PASSWORD_LEVE4_ADD    4 //PASSWORD_LEVE3_ADD+PASSWORD_SIZE
#define AUX1_USERDEFINED_ADD  5 // PASSWORD_LEVE4_ADD
#define AUX2_USERDEFINED_ADD  6 //AUX1_USERDEFINED_ADD+AUX1_USERDEFINED_SIZE //DIRECCION DONDE SE guarda el nmbre de aux2 userdefined

//espacio de memoria A:factory reset variables,   B:System Variables
// C: Product Vars Selected Cache   D:Test Setup Product  
//P2:Product 1 Vars   P199:last Prod
//Password-level1: PL1
//R:reporte variables
//   A  B  C  D  P2  P3 .. P89 P90  R

/*   A  B  C  D  P2   P3   P4   P5   P6   P7  P8   P9   P10   P11  P12  P13  P14  P15  P16  P17  P18  P19  P20 P21 P22   P23  P24   P25   P26  P27 P28   P29   P30  P31  P32  P33  P34  P35
 *   
 *   3  8  30 74 117  160  203 246  289  332 375  418   461   504  547  590  633  676  719  762  805  848  891 934  977
    
     P119     PL1    PL2   PL3   PL4     x
     8588d   8631d  8651d 8671d 8691d  8711d  
     
     
 */

#define ESPACIO_A_ADD         STATUS_FACTORY_ADD
#define ESPACIO_B_ADD         SYSTEM_VAR_ADD
#define ESPACIO_C_ADD         PROD_CACHE_VAR_ADD
#define ESPACIO_D_ADD         TEST_SETUP_SPACE
#define ESPACIO_P2_ADD        PRODUCTO1_ADD //PRIMER PRODUCTO DESPUES DEL TREST SETUP

#define ESPACIO_A_SIZE        STATUS_FACTORY_SIZE
#define ESPACIO_B_SIZE        SYSTEM_VAR_SIZE
#define ESPACIO_C_SIZE        PROD_VAR_SIZE
#define ESPACIO_D_SIZE        PROD_VAR_SIZE
#define ESPACIO_P2_SIZE       PROD_VAR_SIZE //PRIMER PRODUCTO DESPUES DEL TREST SETUP

// NVRAM SPACE MANAGEMENT------------------------------------------------------
//USER SPACE IN NVRAM IS 08h TO 3Fh Total of  56bytes
#define PRODUCT_COUNT_SIZE   2
#define RECHAZO_COUNT_SIZE   2 

#define ESPACIO_E_ADD        8   //Donde se guarda el contador de producto
#define ESPACIO_F_ADD        ESPACIO_E_ADD+PRODUCT_COUNT_SIZE//contador de rechazos


#define VIDX 100// tamaño de los regitros para gardar la memoria de video del DDS
#define VIDY 100  //Tamao de los registros en Y para guardar la memoria de video del DDS
#define DDSMAPSIZEX 32  //NUMERO DE registros en X para los bits en la pantalla DDS
#define DDSMAPSIZEY 16 //nume de registros en Y para dibujar los pixeles en DDS real time

#define SIZE_MEM 5 // memoria de uso general por contexto
#define SIZE_9   300// variable global por contexto
//un byte manipulado por bit se usa por contexto
//no mas alla del contexto

#define CONFIG_FILE "systema.ini"
#define PROD_FILE "productos.db"
#define SIZE_PASSWORD 20 //size max of password 

// Definición de colores (códigos ANSI)
/*#define RESET2   "\033[0m"
#define NEGRO   "\033[30m"
#define ROJO2    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define MAGENTA "\033[35m"
#define MORADO   MAGENTA
#define CYAN    "\033[36m"
#define AZULITO  CYAN
#define BLANCO  "\033[37m"
*/

typedef struct {
    char level1[SIZE_PASSWORD];
    char level2[SIZE_PASSWORD];
    char level3[SIZE_PASSWORD];
    char level4[SIZE_PASSWORD];
    char level5[SIZE_PASSWORD];
    unsigned char seguridad_iniciada;
} Seguridad;

typedef enum {
    TYPE_INT,
    TYPE_UCHAR,
    TYPE_STRING,
    TYPE_FLOAT
} ItemType;


extern Seguridad g_seguridad;
unsigned short int getAddPassword(unsigned char level);
void setPasswords(unsigned char level,unsigned char *p);
unsigned char *getPasswords(unsigned char level);
unsigned char validatePassword(unsigned char *Level,unsigned char *T);

void* config_thread(void* arg);// Prototipo de función
void init_vars(void);
int no_existe_init(void);
void crear_init(void);
int no_existe_Seguridad(void);
void crear_seccion_Seguridad(void);
void leer_seguridad_a_struct(Seguridad *sec);
void mensPrompt(const char* texto, const char* color);
void log_mensaje(const char* tipo, const char* mensaje);


int conectar_db(const char *filename);
void cerrar_db();
int crear_db_si_no_existe();
int agregarProducto(const char *nombre);
int quitarProducto(int productoID);
int editarProducto(int productoID, const char *nuevoNombre);
int agregarItemTipo(int productoID, const char *nombre, const char *tipoStr, const void *valor);
int borrarItem(int productoID, const char *nombre);
int getItemProducto(int productoID, const char *nombre, ItemType *tipo, void *resultado);
int escribirItemProducto(int productoID, const char *nombre, ItemType tipo, const void *valor);
int getIdProductoPorNombre(const char *nombre);
void init_menu(void);
void init_Product(void);



#endif /* MEMOCONFIG_H_ ***************************************************************************/
