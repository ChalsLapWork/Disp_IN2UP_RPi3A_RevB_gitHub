# Proyecto Display Insight 🚀

No son Bienvenidos al repositorio de mi proyecto secreto. Favor de retirarse.
Proyecto Para visualizar con hilos el VFD 256X128 grafico usando **Rpi ** y la
libreria wiring en la branch **RevD4_tx_VFD_v3**; vamos a deplegar el menu principal
el menu Portal Inicion usando  las funciones sendBlock_VFD esta funcion
escribe en un buffer fifo el array el cual lo va processar otro hilo secundario
y ese hilo secundario saca el cotenido del bufer lo copea en otro fifo y ese ultimo 
fifo descarga y tranmite los datos. para poder manejar varias cadenas vamos a 
manejarlo como un protocolo de comunicacion,

## Características ✨
- **RevD4_tx_VFD_v3** desplegar Menu Portal Usando Hilo especialista ✅
- ** En espera  ** 📚
- **Código limpio** 🧑‍💻
- **COMANDOS SERIALES: hex**
-     BarDet:15%:03.03.11.0F.F9.02
-     BarDet:99%:03.03.11.63.FA.02
-     BarDet:45%:03.03.11.2D.17.02
-     S:25894  P:37.2°  03.06.13.65.26.25.02.09.02
-     S: 2   p:103.9°   03.06.13.00.02.67.09.BA.02
-     S:568  P:2.7°     03.06.13.02.38.02.07.6E.02
-      ENTER:45H        03.03.14.45.49.02
-      RIGHT:52H        03.03.14.52.2C.02
-      LEFT:4CH         03.03.14.4C.76.02
-      DOWN:44H         03.03.14.44.4E.02
-      UP:55H           03.03.14.55.39.02
-     

## Instalación 🔧

1. Comandos utiles:
    ```bash
    git pull
    git fetch
    ```
2. Compilacion:
    ```bash
    gcc -g *.c display_RevD.4 -o  -lwiringPi -v
    ```
3. MakeFile:
   ```bash
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
CFLAGS = -g -Wall -Wextra -O0 -Wno-unused-parameter -Wno-maybe-uninitialized -Wno-unused-variable -Wno-uninitialized -Wno-unused-but-set-variable -v

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


## Uso 🔥
Display Insight !¡¡
```
```python
gdb -/disp_Revxx
```
