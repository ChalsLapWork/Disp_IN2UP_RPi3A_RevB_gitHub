# Nombre del ejecutable
TARGET = output

# Archivos fuente en el directorio actual
SRC = $(wildcard *.c)

# Archivos fuente en el directorio superior
SRC_UP = #$(wildcard ../*.c)

# Directorio de búsqueda de archivos de cabecera
INCLUDE = #-I../

# Bibliotecas
LIBS = -lwiringPi

# Opciones del compilador
CFLAGS = -g -Wall -Wextra -O0 -Wno-unused-parameter -Wno-maybe-uninitialized -Wno-unused-variable -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-function  -v

# Comando de compilación
CC = gcc

# Regla para compilar el ejecutable
$(TARGET): $(SRC) $(SRC_UP)
	# Elimina el ejecutable anterior si existe
	rm -f $(TARGET)
	# Compila programa
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(SRC) $(SRC_UP) $(LIBS)
	# Asigna permisos de ejecución al ejecutable
	chmod +x $(TARGET)

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET) *.o
