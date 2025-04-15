

#ifndef CONFIG_H
#define CONFIG_H

#define MAX_NOMBRE 128
#define MAX_VALOR 256
#define MAX_SECCIONES 10
#define MAX_CLAVES 10

typedef struct {
    char clave[MAX_NOMBRE];
    char valor[MAX_VALOR];
} Entrada;

typedef struct {
    char nombre[MAX_NOMBRE];
    Entrada entradas[MAX_CLAVES];
    int cantidad_entradas;
} Seccion;

typedef struct {
    Seccion secciones[MAX_SECCIONES];
    int cantidad_secciones;
} Config;

// En config.h
typedef struct {
    char password_level1[MAX_VALOR];
    char modo_debug[MAX_VALOR];
    // Agrega más variables según lo que necesites del archivo .ini
} VariablesSistema;



int cargar_config(const char *archivo, Config *config);
int guardar_config(const char *archivo, const Config *config);
int eliminar_clave(Config *config, const char *seccion, const char *clave);
int eliminar_seccion(Config *config, const char *seccion);
const char* obtener_valor(const Config *config, const char *seccion, const char *clave);

extern void reportar_error_config(const char *mensaje);

#endif
