#ifndef MEMORIA_H
#define MEMORIA_H

#include <sqlite3.h>

typedef enum {
    TYPE_INT,
    TYPE_UCHAR,
    TYPE_STRING,
    TYPE_FLOAT
} ItemType;

int conectar_db(const char *filename);
void cerrar_db();

int crear_db_si_no_existe();

int agregarProducto(const char *nombre);
int quitarProducto(int productoID);
int editarProducto(int productoID, const char *nuevoNombre);

int agregarItemTipo(int productoID, const char *nombre, const char *tipoStr, const void *valor);
int borrarItem(int productoID, const char *nombre);

int getItemProducto(int productoID, const char *nombre, ItemType *tipo, void *resultado);
int escribirItemProducto(int productoID, const char *nombre, ItemType tipo, const void *valor);

#endif
