#include <stdio.h>
#include <time.h>

void reportar_error_config(const char *mensaje) {
    time_t ahora = time(NULL);
    struct tm *tm_info = localtime(&ahora);

    char fecha[32];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", tm_info);

    // Imprimir por consola
    fprintf(stderr, "[%s] [CONFIG ERROR] %s\n", fecha, mensaje);

    // Guardar en archivo de log
    FILE *log = fopen("config.log", "a");
    if (log) {
        fprintf(log, "[%s] [CONFIG ERROR] %s\n", fecha, mensaje);
        fclose(log);
    }
}
