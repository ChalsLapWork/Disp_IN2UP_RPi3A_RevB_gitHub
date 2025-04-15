
#define CONFIG_FILE "systema.ini"
#define SIZE_PASSWORD 20 //size max of password 


// Definición de colores (códigos ANSI)
#define RESET   "\033[0m"
#define NEGRO   "\033[30m"
#define ROJO3    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL    "\033[34m"
#define MAGENTA "\033[35m"
#define MORADO   MAGENTA
#define CYAN    "\033[36m"
#define AZULITO  CYAN
#define BLANCO  "\033[37m"

typedef struct {
    char level1[SIZE_PASSWORD];
    char level2[SIZE_PASSWORD];
    char level3[SIZE_PASSWORD];
    char level4[SIZE_PASSWORD];
    char level5[SIZE_PASSWORD];
    unsigned char seguridad_iniciada;
} Seguridad;

extern Seguridad g_seguridad;

void* config_thread(void* arg);// Prototipo de función
//void init_vars(void);
void init_vars();
int no_existe_init();
void crear_init();
int no_existe_Seguridad();
void crear_seccion_Seguridad();
void leer_seguridad_a_struct(Seguridad *sec);
