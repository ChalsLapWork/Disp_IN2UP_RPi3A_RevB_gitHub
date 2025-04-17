#include "Memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sqlite3 *db = NULL;

int conectar_db(const char *filename) {
    return sqlite3_open(filename, &db);
}

void cerrar_db() {
    if (db) sqlite3_close(db);
}

int crear_db_si_no_existe() {
    char *err = NULL;
    const char *sql_producto =
        "CREATE TABLE IF NOT EXISTS productos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nombre TEXT NOT NULL);";

    const char *sql_items =
        "CREATE TABLE IF NOT EXISTS items ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "producto_id INTEGER,"
        "nombre TEXT,"
        "tipo TEXT,"
        "valor TEXT,"
        "FOREIGN KEY(producto_id) REFERENCES productos(id));";

    if (sqlite3_exec(db, sql_producto, 0, 0, &err) != SQLITE_OK) {
        printf("Error creando tabla productos: %s\n", err);
        return 0;
    }

    if (sqlite3_exec(db, sql_items, 0, 0, &err) != SQLITE_OK) {
        printf("Error creando tabla items: %s\n", err);
        return 0;
    }

    sqlite3_stmt *stmt;
    const char *sql_check = "SELECT COUNT(*) FROM productos WHERE nombre = 'Test Set-up';";
    sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL);
    int existe = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (!existe) {
        agregarProducto("Test Set-up");
        int id = (int)sqlite3_last_insert_rowid(db);

        unsigned char uc = 1;
        float f = 2.5;
        int i = 1234;
        char nombre[20] = "Test Set-up";

        agregarItemTipo(id, "name", "string", nombre);
        agregarItemTipo(id, "GananciaDrive", "uchar", &uc);
        agregarItemTipo(id, "GananciaAnaloga", "uchar", &uc);
        agregarItemTipo(id, "FiltroConfig", "uchar", &uc);
        agregarItemTipo(id, "BorrarContadores", "uchar", &uc);
        agregarItemTipo(id, "Fase", "float", &f);
        agregarItemTipo(id, "phase", "uchar", &uc);
        agregarItemTipo(id, "phasefrac", "uchar", &uc);
        agregarItemTipo(id, "freqselect", "uchar", &uc);
        agregarItemTipo(id, "MarcarAltura", "int", &i);
        agregarItemTipo(id, "GananciaDDS", "uchar", &uc);
        agregarItemTipo(id, "zoom", "uchar", &uc);
        agregarItemTipo(id, "cuadritosDDS", "uchar", &uc);
        agregarItemTipo(id, "Sensibilidad", "int", &i);
        agregarItemTipo(id, "Altura", "int", &i);
        agregarItemTipo(id, "PulsoTiempoRechazo", "int", &i);
        agregarItemTipo(id, "PulsosTiempoEspera", "int", &i);
        agregarItemTipo(id, "Ganancia", "uchar", &uc);
        agregarItemTipo(id, "Frecuencia", "int", &i);
    }

    return 1;
}

int agregarProducto(const char *nombre) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO productos(nombre) VALUES(?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}

int quitarProducto(int productoID) {
    sqlite3_stmt *stmt;
    const char *sql1 = "DELETE FROM items WHERE producto_id=?;";
    const char *sql2 = "DELETE FROM productos WHERE id=?;";
    sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}

int editarProducto(int productoID, const char *nuevoNombre) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE productos SET nombre=? WHERE id=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nuevoNombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, productoID);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}

int agregarItemTipo(int productoID, const char *nombre, const char *tipoStr, const void *valor) {
    char buffer[64] = {0};
    if (strcmp(tipoStr, "int") == 0)
        snprintf(buffer, sizeof(buffer), "%d", *(int *)valor);
    else if (strcmp(tipoStr, "uchar") == 0)
        snprintf(buffer, sizeof(buffer), "%u", *(unsigned char *)valor);
    else if (strcmp(tipoStr, "float") == 0)
        snprintf(buffer, sizeof(buffer), "%f", *(float *)valor);
    else if (strcmp(tipoStr, "string") == 0)
        snprintf(buffer, sizeof(buffer), "%s", (char *)valor);
    else return 0;

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO items(producto_id, nombre, tipo, valor) VALUES(?,?,?,?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, tipoStr, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, buffer, -1, SQLITE_STATIC);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}

int borrarItem(int productoID, const char *nombre) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM items WHERE producto_id=? AND nombre=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_STATIC);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}

int getItemProducto(int productoID, const char *nombre, ItemType *tipo, void *resultado) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT tipo, valor FROM items WHERE producto_id=? AND nombre=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *tipoStr = (const char *)sqlite3_column_text(stmt, 0);
        const char *valorStr = (const char *)sqlite3_column_text(stmt, 1);

        if (strcmp(tipoStr, "int") == 0) {
            *(int *)resultado = atoi(valorStr);
            *tipo = TYPE_INT;
        } else if (strcmp(tipoStr, "uchar") == 0) {
            *(unsigned char *)resultado = (unsigned char)atoi(valorStr);
            *tipo = TYPE_UCHAR;
        } else if (strcmp(tipoStr, "float") == 0) {
            *(float *)resultado = atof(valorStr);
            *tipo = TYPE_FLOAT;
        } else if (strcmp(tipoStr, "string") == 0) {
            strncpy((char *)resultado, valorStr, 30);
            *tipo = TYPE_STRING;
        } else return 0;
    } else return 0;

    sqlite3_finalize(stmt);
    return 1;
}

int escribirItemProducto(int productoID, const char *nombre, ItemType tipo, const void *valor) {
    char buffer[64] = {0};
    const char *tipoStr = "";

    switch (tipo) {
        case TYPE_INT:
            snprintf(buffer, sizeof(buffer), "%d", *(int *)valor);
            tipoStr = "int"; break;
        case TYPE_UCHAR:
            snprintf(buffer, sizeof(buffer), "%u", *(unsigned char *)valor);
            tipoStr = "uchar"; break;
        case TYPE_FLOAT:
            snprintf(buffer, sizeof(buffer), "%f", *(float *)valor);
            tipoStr = "float"; break;
        case TYPE_STRING:
            snprintf(buffer, sizeof(buffer), "%s", (char *)valor);
            tipoStr = "string"; break;
    }

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE items SET valor=?, tipo=? WHERE producto_id=? AND nombre=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, buffer, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tipoStr, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, productoID);
    sqlite3_bind_text(stmt, 4, nombre, -1, SQLITE_STATIC);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}
