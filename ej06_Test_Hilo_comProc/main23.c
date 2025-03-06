// Programa en C para recibir y procesar datos seriales con FIFO
/*
   ESTE PROGRAMA ESPARA RECONOCER EL PROTOCOLO
         STX,LEN,BYTE1,BYTEn,CRC,ETX
           donde LEN=LOngitud, que cuenta el byte len como 1 y el siguiente byte como 2 hasta antes de _CRC|
           e.g. STX,2,byte1,CRC,ETX
                                        
    cadena de recepcion  basura,etx,len,datos,crc,etx, basura,etx,len,datos,basura<--cadena no valida
                                                              ^----------------------cadena no valida falta ETX u CRC
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>


#define BUF_SIZE 1024
#define FIFO_SIZE 10
#define STX 03
#define ETX 02

// Estructura para la FIFO circular
typedef struct {
    char *buffer[FIFO_SIZE];
    int front;
    int rear;
    pthread_mutex_t lock;
} fifo_t;

// Estructura para pasar datos entre hilos
typedef struct {
    int serial_fd;
    fifo_t *fifo;
} thread_data_t;

// Inicializar FIFO circular
void fifo_init(fifo_t *fifo) {
    fifo->front = 0;
    fifo->rear = 0;
    pthread_mutex_init(&fifo->lock, NULL);
}

// Añadir a FIFO
void fifo_push(fifo_t *fifo, const char *data) {
    pthread_mutex_lock(&fifo->lock);
    if ((fifo->rear + 1) % FIFO_SIZE == fifo->front) {
        free(fifo->buffer[fifo->front]);
        fifo->front = (fifo->front + 1) % FIFO_SIZE;
    }
    fifo->buffer[fifo->rear] = strdup(data);
    fifo->rear = (fifo->rear + 1) % FIFO_SIZE;
    pthread_mutex_unlock(&fifo->lock);
}

// Hilo que lee el puerto serial
void *serial_reader(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char buffer[BUF_SIZE];
    int idx = 0;
    int in_stx = 0;
    int expected_len = -1;
    
    while (1) {
        char byte = serialGetchar(data->serial_fd);
        if (byte != -1) {
            printf("[SERIAL] Byte recibido: 0x%02X\n", byte);
            if (byte == STX) {  // STX
                in_stx = 1;
                idx = 0;
                expected_len = -1;
            } else if (byte == ETX && in_stx && expected_len != -1 && idx == expected_len + 1) {  // ETX
                buffer[idx] = '\0';
                printf("[SERIAL] Cadena válida recibida: %s\n", buffer);
                fifo_push(data->fifo, buffer);
                in_stx = 0;
            } else if (in_stx) {
                if (idx == 0) {
                    expected_len = byte;
                } else if (idx >= BUF_SIZE - 1) {
                    in_stx = 0;
                }
                buffer[idx++] = byte;
            }
        }
    }
    return NULL;
}

// Hilo que procesa las cadenas en la FIFO
void *fifo_processor(void *arg) {
    fifo_t *fifo = (fifo_t *)arg;
    while (1) {
        pthread_mutex_lock(&fifo->lock);
        if (fifo->front != fifo->rear) {
            printf("Procesando: %s\n", fifo->buffer[fifo->front]);
            free(fifo->buffer[fifo->front]);
            fifo->front = (fifo->front + 1) % FIFO_SIZE;
        }
        pthread_mutex_unlock(&fifo->lock);
        usleep(100000);
    }
}

int main() {
    const char *serial_device = "/dev/serial0";
    
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Error al inicializar wiringPi\n");
        return -1;
    }

    fifo_t fifo;
    fifo_init(&fifo);

    int serial_fd = serialOpen(serial_device, 9600);
    if (serial_fd == -1) {
        fprintf(stderr, "Error al abrir puerto serial\n");
        return -1;
    }

    pthread_t reader_thread, processor_thread;
    thread_data_t data = {serial_fd, &fifo};

    pthread_create(&reader_thread, NULL, serial_reader, (void *)&data);
    pthread_create(&processor_thread, NULL, fifo_processor, (void *)&fifo);

    pthread_join(reader_thread, NULL);
    pthread_join(processor_thread, NULL);

    serialClose(serial_fd);
    return 0;
}
