#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "config.h"

static VariablesSistema vars;  // Declaración de la variable global

void* hilo_cargar_variables(void *arg) {
    Config config;
    if (cargar_config("systema.ini", &config) != 0) {
        reportar_error_config("No se pudo cargar el archivo systema.ini");
        pthread_exit(NULL);
    }

    const char *v;

    v = obtener_valor(&config, "seguridad", "level_1");
    if (v) strncpy(vars.password_level1, v, MAX_VALOR);

    v = obtener_valor(&config, "debug", "enabled");
    if (v) strncpy(vars.modo_debug, v, MAX_VALOR);

    pthread_exit(NULL);
}

void init_vars() {
    pthread_t hilo;
    int rc = pthread_create(&hilo, NULL, hilo_cargar_variables, NULL);
    if (rc != 0) {
        printf("No se pudo crear el hilo de configuración\n");
        return;
    }

    pthread_detach(hilo);
}

int main() {
    init_vars();

    for (int i = 0; i < 10; i++) {
        printf("Main haciendo cosas importantes...\n");
        sleep(1);
    }

    return 0;
}
