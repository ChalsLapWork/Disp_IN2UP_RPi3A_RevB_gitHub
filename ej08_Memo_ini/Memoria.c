#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include <pthread.h>
#include <unistd.h>     // para sleep()
#include <sys/stat.h>   // para verificar si existe el archivo
#include "Memoria.h"


Seguridad g_seguridad = {0};  // Inicializada vacía

// Función para imprimir texto en color
void mensaje(const char* texto, const char* color) {
    printf("%s%s%s\n", color, texto, RESET);
}//FIN DE MENSAJE+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Inicializa las variables del sistema (en un hilo separado)
void init_vars() {
pthread_t tid;
    if (pthread_create(&tid, NULL, config_thread, NULL) != 0) {
        perror(" init_vars - pthread_create");
        return;}
    pthread_detach(tid);// El hilo es autónomo, no esperamos que termine
}// fin init vars+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// Verifica si el archivo existe
int no_existe_init() {
    struct stat st;
    return stat(CONFIG_FILE, &st) != 0;
}//fin verifica-------------------------------------------------

// Crea el archivo con sección [General]
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
}//FIN leer_seguridad_a_struct++++++++++++++++++++++++++++++++++++++++

// Función que se ejecutará en el hilo
void* config_thread(void* arg) {
//Seguridad *sys = (Seguridad*)arg;

    if(no_existe_init()){
           crear_init();}
    if(no_existe_Seguridad()){ 
           crear_seccion_Seguridad();}
    leer_seguridad_a_struct(&g_seguridad);            
    g_seguridad.seguridad_iniciada=0xAA;
    //printf("[CONFIG] Archivo %s creado exitosamente.\n", CONFIG_FILE);
    pthread_exit(NULL);
}//fin config threads++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++