#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

void quitar_espacios(char *str) {
    char *inicio = str;
    while (*inicio == ' ' || *inicio == '\t') inicio++;
    memmove(str, inicio, strlen(inicio) + 1);
    char *fin = str + strlen(str) - 1;
    while (fin > str && (*fin == ' ' || *fin == '\t')) fin--;
    *(fin + 1) = '\0';
}

int cargar_config(const char *archivo, Config *config) {
    FILE *f = fopen(archivo, "r");

    if (!f) {
        reportar_error_config("No se pudo abrir el archivo de configuración.");
        return -1;
    }

    char linea[512];
    Seccion *seccion_actual = NULL;
    config->cantidad_secciones = 0;

    while (fgets(linea, sizeof(linea), f)) {
        quitar_espacios(linea);
        if (linea[0] == '\0' || linea[0] == ';' || linea[0] == '#') continue;

        if (linea[0] == '[') {
            char *fin = strchr(linea, ']');
            if (!fin) continue;
            *fin = '\0';
            if (config->cantidad_secciones >= MAX_SECCIONES) continue;
            seccion_actual = &config->secciones[config->cantidad_secciones++];
            strncpy(seccion_actual->nombre, linea + 1, MAX_NOMBRE);
            seccion_actual->cantidad_entradas = 0;
        } else if (seccion_actual) {
            char *igual = strchr(linea, '=');
            if (!igual) continue;
            *igual = '\0';
            char *clave = linea;
            char *valor = igual + 1;
            quitar_espacios(clave);
            quitar_espacios(valor);
            if (*valor == '"' && valor[strlen(valor) - 1] == '"') {
                valor[strlen(valor) - 1] = '\0';
                valor++;
            }
            if (seccion_actual->cantidad_entradas >= MAX_CLAVES) continue;
            Entrada *e = &seccion_actual->entradas[seccion_actual->cantidad_entradas++];
            strncpy(e->clave, clave, MAX_NOMBRE);
            strncpy(e->valor, valor, MAX_VALOR);
        }
    }

    fclose(f);
    return 0;
}

int guardar_config(const char *archivo, const Config *config) {
    FILE *f = fopen(archivo, "w");
    if (!f) return -1;

    for (int i = 0; i < config->cantidad_secciones; i++) {
        fprintf(f, "[%s]\n", config->secciones[i].nombre);
        for (int j = 0; j < config->secciones[i].cantidad_entradas; j++) {
            fprintf(f, "%s=\"%s\"\n", 
                    config->secciones[i].entradas[j].clave,
                    config->secciones[i].entradas[j].valor);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

const char* obtener_valor(const Config *config, const char *seccion, const char *clave) {
    for (int i = 0; i < config->cantidad_secciones; i++) {
        if (strcmp(config->secciones[i].nombre, seccion) == 0) {
            for (int j = 0; j < config->secciones[i].cantidad_entradas; j++) {
                if (strcmp(config->secciones[i].entradas[j].clave, clave) == 0) {
                    return config->secciones[i].entradas[j].valor;
                }
            }
        }
    }
    return NULL;
}

int eliminar_clave(Config *config, const char *seccion, const char *clave) {
    for (int i = 0; i < config->cantidad_secciones; i++) {
        if (strcmp(config->secciones[i].nombre, seccion) == 0) {
            Seccion *s = &config->secciones[i];
            for (int j = 0; j < s->cantidad_entradas; j++) {
                if (strcmp(s->entradas[j].clave, clave) == 0) {
                    for (int k = j; k < s->cantidad_entradas - 1; k++) {
                        s->entradas[k] = s->entradas[k + 1];
                    }
                    s->cantidad_entradas--;
                    return 0;
                }
            }
        }
    }
    return -1;
}

int eliminar_seccion(Config *config, const char *seccion) {
    for (int i = 0; i < config->cantidad_secciones; i++) {
        if (strcmp(config->secciones[i].nombre, seccion) == 0) {
            for (int j = i; j < config->cantidad_secciones - 1; j++) {
                config->secciones[j] = config->secciones[j + 1];
            }
            config->cantidad_secciones--;
            return 0;
        }
    }
    return -1;
}
