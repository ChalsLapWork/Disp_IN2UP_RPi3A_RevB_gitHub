#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // para sleep()
#include <sys/stat.h>   // para verificar si existe el archivo
#include "Memoria.h"

// Nombre del archivo de configuración
#define CONFIG_FILE "systema.ini"







// Función principal del programa
int main() {
    printf("[MAIN] Iniciando el programa...\n");
    printf(" de prueba para crear el init vars ...\n");
    
    init_vars();// Inicia las variables del sistema (puede crear el archivo si no existe)
    
    sleep(3);
    printf("\033[33m");
    printf("level1: %s\n", g_seguridad.level1);
    printf("level2: %s\n", g_seguridad.level2);
    printf("level3: %s\n", g_seguridad.level3);
    printf("level4: %s\n", g_seguridad.level4);
    printf("level5: %s\n", g_seguridad.level5);
    printf("\033[0m");


    for (int i = 0; i < 5; i++) {// Simular que el programa sigue haciendo cosas
        printf("[MAIN] Haciendo cosas importantes... (%d)\n", i + 1);
        sleep(1);}

    printf("[MAIN] Programa finalizado.\n");
    return 0;
}
