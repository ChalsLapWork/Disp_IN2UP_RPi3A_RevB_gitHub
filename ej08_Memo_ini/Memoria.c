#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include <pthread.h>
#include <unistd.h>     // para sleep()
#include <sys/stat.h>   // para verificar si existe el archivo

#define CONFIG_FILE "systema.ini"

void* config_thread(void* arg);// Prototipo de función
void init_vars(void);



// Inicializa las variables del sistema (en un hilo separado)
void init_vars(void) {
pthread_t tid;
int err;
    err = pthread_create(&tid, NULL, config_thread, NULL);// Crear el hilo
    if (err != 0) {
        fprintf(stderr,"[INIT] No se pudo crear el hilo: %s\n", strerror(err));
        return;}
    pthread_detach(tid);// El hilo es autónomo, no esperamos que termine
}// fin init vars+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Función que se ejecutará en el hilo
void* config_thread(void* arg) {
struct stat st;

    if (stat(CONFIG_FILE, &st) == 0) {// Verificar si el archivo ya existe
        printf("[CONFIG] El archivo ya existe, no se necesita crear.\n");
        pthread_exit(NULL);}
    FILE *f = fopen(CONFIG_FILE, "w");    // Crear el archivo con contenido por defecto
    if (!f) {perror("[CONFIG] Error al crear el archivo");
             pthread_exit(NULL);}
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
        "; tiempo en milisegundos\n");

    fclose(f);
    printf("[CONFIG] Archivo %s creado exitosamente.\n", CONFIG_FILE);
    pthread_exit(NULL);
}//fin config threads++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++