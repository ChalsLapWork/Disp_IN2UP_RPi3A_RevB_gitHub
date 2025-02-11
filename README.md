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

## Uso 🔥
Display Insight !¡¡

```python
gdb -/disp_Revxx
