#include "Memoria.h"
#include "errorController.h"
#include "strings.h"
#include "system.h"
#include "VFDmenu.h"
#include <pthread.h>
#include <sys/stat.h>   // para verificar si existe el archivo
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // para sleep()
#include "errorController.h"
#include <time.h>

#define NUM_DE_PASSWORD 5 //caNTIDAD DE password que manejamos 


typedef struct {// Estructura interna para pasar datos al hilo
    char tipo[32];
    char mensaje[256];
} LogData;

Seguridad g_seguridad = {0};  // Inicializada vacía


// Verifica si el tipo de mensaje es uno válido
static int tipo_valido(const char* tipo) {
    return strcmp(tipo, "Error") == 0 ||
           strcmp(tipo, "Advertencia") == 0 ||
           strcmp(tipo, "Información") == 0 ||
           strcmp(tipo, "Metales") == 0;
}//fin de tipo valido+++++++++++++++++++++++++++++++++

// Función ejecutada por el hilo para escribir en el log
static void* log_thread_func(void* arg) {
    LogData* data = (LogData*)arg;
    char fecha[128];// Obtener fecha y hora
    time_t ahora = time(NULL);
    struct tm* t = localtime(&ahora);
    strftime(fecha, sizeof(fecha), "%a %b %d %H:%M:%S %Y", t);

    FILE* logf = fopen("log.txt", "a");// Abrir archivo log
    if (!logf) {
        perror("Error al abrir log.txt");
        free(data);
        return NULL;}
    // Escribir mensaje
    fprintf(logf, "[%s] [%s] %s\n", fecha, data->tipo, data->mensaje);
    fclose(logf);
    free(data);
    return NULL;
}//fin de log thread fucntion++++++++++++++++++++++++++++++++++++

// Función pública para registrar un mensaje con tipo
void log_mensaje(const char* tipo, const char* mensaje) {
    if (!tipo_valido(tipo)) {
        fprintf(stderr, "Tipo de mensaje inválido: %s\n", tipo);
        return;}
    pthread_t hilo;
    LogData* data = malloc(sizeof(LogData));
    if (!data) {
        perror("malloc hilo log mensaje");
		mensaje("Error de malloc al hacer el log ",AMARILLO);
        return;}
    strncpy(data->tipo, tipo, sizeof(data->tipo) - 1);
    data->tipo[sizeof(data->tipo) - 1] = '\0';
    strncpy(data->mensaje, mensaje, sizeof(data->mensaje) - 1);
    data->mensaje[sizeof(data->mensaje) - 1] = '\0';
    if (pthread_create(&hilo, NULL, log_thread_func, data) != 0) {
        perror("pthread_create");
		mensaje("Error al escribir el LOG",AMARILLO);
        free(data);
        return;}
    pthread_detach(hilo);
}// fin de funcion log mensaje++++++++++++++++++++++++++++++++++
// Función para imprimir texto en color
	void mensaje(const char* texto, const char* color) {
    printf("%s%s%s\n", color, texto, RESET);
}//FIN DE MENSAJE+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned short int getAddPassword(unsigned char level){
unsigned short int add=0;   
	   switch(level){
		   case 1:add=PASSWORD_LEVE1_ADD;break;
		   case 2:add=PASSWORD_LEVE2_ADD;break;
		   case 3:add=PASSWORD_LEVE3_ADD;break;
		   case 4:add=PASSWORD_LEVE4_ADD;break;
		   default:  }//debug error de software   		
return add;
}//fin getAddPassword-------------------------------------------------------------------

void setPasswords(unsigned char level,unsigned char *p){
    //writeEEPROMblock(getAddPassword(level),PASSWORD_SIZE,p);
    mensOK("Falta la funcion de guardar contraseñas",33); 
}//fin setPasswords---------------------------------------------------------------------

/* VAlida Passwords si es correcta en algun nivel devuelve TRUE, y 
 * *Level regresa en que nivel es aceptado
 *  *T la cadena a evualuar */
unsigned char validatePassword(unsigned char *Level,unsigned char *T){//validamos la password
	//OPERADOR=2,SUPERVISOR=3,ADMINISTRADOR=4,SERVICIO=5
const char *niveles[] = {
        g_seguridad.level1,g_seguridad.level2,
        g_seguridad.level3,g_seguridad.level4,
        g_seguridad.level5
		};

 if(g_seguridad.seguridad_iniciada==INIT){
    for (int i = 0; i < 5; i++) {
        if (strcmp((char*)T, niveles[i]) == 0) {
            *Level = '1' + i;  // Devuelve '1', '2', ..., '5'
            return 1;}
       }}//fin for----------------------------------------------------
  else{log_mensaje("error","falta carga variables del passwrd en sistema RAM");}//NO se han descargado las passwords del sistema.ini
}//fin validate password++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



return FALSE; //no hubo ninguna password igual------------    
}//fin validatePassword-----------------------------------------------------------------------------

//regresamos apuntador de una clave solamente seleccionada
unsigned char *getPasswords(unsigned char level){
	//return(readEEPROMblock(getAddPassword(level),PASSWORD_SIZE));
static unsigned char s[]="password";
return &s[0];
}//fin getPasswords---------------------------------------------------------------

/*Saca del sistema de archivos las variables del sistema  */
// Inicializa las variables del sistema (en un hilo separado)
void init_vars(void){
pthread_t tid;
    if (pthread_create(&tid, NULL, config_thread, NULL) != 0) {
        perror(" init_vars - pthread_create");
        return;}
    pthread_detach(tid);// El hilo es autónomo, no esperamos que termine     
}//fin init vars+++++++++++++++++++++++++++++++++++++++++++


// Verifica si el archivo existe
int no_existe_init() {
    struct stat st;
    return stat(CONFIG_FILE, &st) != 0;
}//fin verifica-------------------------------------------------

// Crea el archivo con sección [General]
/**Archivo system.ini con variables del sistema
 *  para que empieze a trabajar */
void crear_init() {
    FILE *f = fopen(CONFIG_FILE, "w");
    if (!f) {perror("crear_init");
             return;}

    fprintf(f,
        "; Archivo de configuración del sistema\n"
        "; Este archivo será leído al inicio del programa\n\n"
        "[Seguridad]\n"
        "level_1=\"1\"\n"
        "level_2=\"2\"\n"
        "level_3=\"3\"\n"
        "level_4=\"4\"\n"
        "level_5=\"5\"\n\n"
        "[Producto]\n"
        "cuenta_Rechazos=\"1\"\n"
        "cuenta_Producto=\"2\"\n"
        "Producto=\"Test Set-Up\""
        "tiempo_espera=5000\n"
        "; tiempo en milisegundos\n"
        );//fin fprintf-----------------------------------------
    fclose(f);
    mensaje("[CONFIG] Archivo creado.",AZULITO);
}//fin crear_init-----------------------------------------------

// Verifica si la sección [Seguridad] está presente
int no_existe_Seguridad() {
    FILE *f = fopen(CONFIG_FILE, "r");
    if (!f) return 1;
    char line[256];
    while(fgets(line, sizeof(line), f)) {
        if(strstr(line, "[Seguridad]")) {
            fclose(f);
            return 0;}}
    fclose(f);
    return 1;
}//FIN no_existe_Seguridad+++++++++++++++++++++++++++++++++++++++

// Agrega la sección [Seguridad] al final
void crear_seccion_Seguridad() {
    FILE *f=fopen(CONFIG_FILE,"a");
    if(!f){perror("crear_seccion_Seguridad");
           return;}
    fprintf(f,
        "\n[Seguridad]\n"
        "level1=\"1\"\n"
        "level2=\"2\"\n"
        "level3=\"3\"\n"
        "level4=\"4\"\n"
        "level5=\"5\"\n"
          );//fin de fprintf+++++++++++
    fclose(f);
    mensaje("[CONFIG] Sección [Seguridad] agregada.",AZULITO);
}//fin crear_seccion_Seguridad-------------------------------------

// Llena la estructura Seguridad desde el archivo
void leer_seguridad_a_struct(Seguridad *sec) {
    FILE *f = fopen(CONFIG_FILE, "r");
    if (!f) {perror("leer_seguridad_a_struct");
             return;}
    char line[256];
    int dentro = 0;
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;
        if (strstr(line, "[Seguridad]")) {
            dentro = 1;
            continue;}
        if (dentro) {     //%[^\"] comando: lee todo hasta encontrar comilla de cierre
            if (line[0] == '[') break; // terminó sección
            sscanf(line, "level_1=\"%[^\"]\"", sec->level1);
            sscanf(line, "level_2=\"%[^\"]\"", sec->level2);
            sscanf(line, "level_3=\"%[^\"]\"", sec->level3);
            sscanf(line, "level_4=\"%[^\"]\"", sec->level4);
            sscanf(line, "level_5=\"%[^\"]\"", sec->level5);}
        }//FIN WHILE-------------------------------------------------
    fclose(f);
       // Verificar campos vacíos y asignar valores por defecto
    if (sec->level1[0] == '\0') strcpy(sec->level1, "1");
    if (sec->level2[0] == '\0') strcpy(sec->level2, "2");
    if (sec->level3[0] == '\0') strcpy(sec->level3, "3");
    if (sec->level4[0] == '\0') strcpy(sec->level4, "4");
    if (sec->level5[0] == '\0') strcpy(sec->level5, "5");
}//FIN leer_seguridad_a_srtruct++++++++++++++++++++++++++++++++++++++++

// Función que se ejecutará en el hilo
void* config_thread(void* arg) {
//Seguridad *sys = (Seguridad*)arg;

    if(no_existe_init()){//archivo init
           crear_init();}//crear archivo init
    if(no_existe_Seguridad()){ //seccion seguridad en archivo init
           crear_seccion_Seguridad();}//crear la seccion
    leer_seguridad_a_struct(&g_seguridad);            
    g_seguridad.seguridad_iniciada=INIT;
    //printf("[CONFIG] Archivo %s creado exitosamente.\n", CONFIG_FILE);
    pthread_exit(NULL);
}//fin config threads++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


