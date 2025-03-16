#nombre del ejecutable
TARGET = output

#Archivo  fuente en el directorio actual
SRC = main23.c

#ARCHIVO  fuente en el directorio  superior
SRC_UP = ../errorController.c ../system.h ../VFD.c ../VFDthread.c ../delay.c ../queue.c ../VFDmenu.c ../DSP.c ../Memoria.c ../strings.c ../SistOp.c ../BarraDisplay.c

# Directorio de busqueda  de archivo  de cabecera 
INCLUDE = -I../

# Bibliotecas
LIBS = -lwiringPi

#Opciones del compilador
CFLAGS = -g -Wall -Wextra -O0 -Wno-unused-parameter -Wmaybe-uninitialized -Wno-unused-variable -v

#  Comando de compilacion
CC = gcc

# Regla para compilar el ejecutable 
$(TARGET): $(SRC) $(SRC_UP)
	#elimina el ejecutable anterior si existe
	rm -f $(TARGET)
	#compila programa
	 $(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRC) $(SRC_UP) $(LIBS)
	#asigna permisos de ejecucion al ejecutable
	chmod +x $(TARGET)

#  Regla para limpiar archivos generados
clean:
	rm -f $(TARGET) *.o
