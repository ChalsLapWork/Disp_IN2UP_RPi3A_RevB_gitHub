#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define BUF_SIZE 1024
#define FIFO_SIZE 10

// Estructura para la FIFO circular
typedef struct {
    char *buffer[FIFO_SIZE];
    int front;
    int rear;
    pthread_mutex_t lock;
} fifo_t;

// Estructura para pasar datos entre hilos
typedef struct {
    int serial_fd;  // Descriptor del puerto serial usando wiringPi
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
        // FIFO está llena, sobreescribir la más vieja
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

    while (1) {
        char byte = serialGetchar(data->serial_fd);  // Leer un byte del puerto serial
        if (byte != -1) {  // Si se recibió un byte válido
            if (byte == 0x02) {  // STX
                in_stx = 1;
                idx = 0;  // Reiniciar el índice para la nueva cadena
            } else if (byte == 0x03 && in_stx) {  // ETX
                buffer[idx + 1] = '\0';  // Terminar la cadena
                fifo_push(data->fifo, buffer);  // Enviar a la FIFO
                in_stx = 0;
            } else if (in_stx) {
                buffer[idx++] = byte;
                if (idx >= BUF_SIZE - 1) {
                    idx = BUF_SIZE - 2;  // Evitar desbordamiento de búfer
                }
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
            // Procesar el primer dato en la FIFO
            printf("Procesando: %s\n", fifo->buffer[fifo->front]);
            free(fifo->buffer[fifo->front]);
            fifo->front = (fifo->front + 1) % FIFO_SIZE;
        }
        pthread_mutex_unlock(&fifo->lock);
        usleep(100000);  // Esperar un poco antes de comprobar de nuevo
    }
}

int main() {
    const char *serial_device = "/dev/serial0";  // Cambiar al puerto adecuado

    // Inicializar wiringPi
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Error al inicializar wiringPi\n");
        return -1;
    }

    // Inicializar FIFO
    fifo_t fifo;
    fifo_init(&fifo);

    // Abrir el puerto serial
    int serial_fd = serialOpen(serial_device, 9600);  // 9600 baudios
    if (serial_fd == -1) {
        fprintf(stderr, "Error al abrir puerto serial\n");
        return -1;
    }

    // Crear hilos
    pthread_t reader_thread, processor_thread;
    thread_data_t data = {serial_fd, &fifo};

    pthread_create(&reader_thread, NULL, serial_reader, (void *)&data);
    pthread_create(&processor_thread, NULL, fifo_processor, (void *)&fifo);

    // Esperar a que los hilos terminen (en este caso, nunca lo harán)
    pthread_join(reader_thread, NULL);
    pthread_join(processor_thread, NULL);

    serialClose(serial_fd);  // Cerrar el puerto serial
    return 0;
}
