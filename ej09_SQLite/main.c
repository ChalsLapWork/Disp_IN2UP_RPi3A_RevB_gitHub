#include <stdio.h>
#include "Memoria.h"

int main() {
    if (conectar_db("productos.db") != SQLITE_OK) {
        printf("No se pudo abrir la base de datos.\n");
        return 1;
    }

    if (!crear_db_si_no_existe()) {
        printf("Error creando base de datos.\n");
        return 1;
    }

    printf("Base de datos inicializada correctamente.\n");

    // Leer item
    char nombre[30];
    ItemType tipo;
    if (getItemProducto(1, "name", &tipo, nombre)) {
        printf("Producto 1, name: %s\n", nombre);
    }

    // Escribir item
    float nuevo = 9.99;
    escribirItemProducto(1, "Fase", TYPE_FLOAT, &nuevo);

    cerrar_db();
    return 0;
}
