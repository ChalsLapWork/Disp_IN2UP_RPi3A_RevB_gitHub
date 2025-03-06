#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/select.h>

#define BUF_SIZE 256

// Estructura para compartir datos entre hilos
typedef struct {
    int serial_fd;           // Descriptor de archivo del puerto serial
    char buffer[BUF_SIZE];   // Buffer compartido
    int data_ready;          // Bandera para indicar que hay datos nuevos
    pthread_mutex_t mutex;   // Mutex para proteger el buffer
} thread_data_t;

// Hilo lector: Lee datos del puerto serial usando select
void *serial_reader(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char temp_buffer[BUF_SIZE];
    ssize_t bytes_read;
    fd_set read_fds;
    struct timeval timeout;

    while (1) {
        // Configura el conjunto de descriptores de archivo
        FD_ZERO(&read_fds);
        FD_SET(data->serial_fd, &read_fds);

        // Configura el tiempo de espera (1 segundo)
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        // Espera a que haya datos disponibles en el puerto serial
        int ret = select(data->serial_fd + 1, &read_fds, NULL, NULL, &timeout);
        if (ret > 0 && FD_ISSET(data->serial_fd, &read_fds)) {
            // Lee un bloque de bytes
            bytes_read = read(data->serial_fd, temp_buffer, BUF_SIZE - 1);
            if (bytes_read > 0) {
                temp_buffer[bytes_read] = '\0';  // Asegura que el buffer esté terminado con un carácter nulo

                // Bloquea el mutex para proteger el buffer compartido
                pthread_mutex_lock(&data->mutex);

                // Copia los datos al buffer compartido
                strncpy(data->buffer, temp_buffer, BUF_SIZE);
                data->data_ready = 1;  // Indica que hay datos nuevos

                // Desbloquea el mutex
                pthread_mutex_unlock(&data->mutex);

                printf("[LECTOR] Datos leídos: %s\n", temp_buffer);  // Depuración
            } else if (bytes_read == -1) {
                printf("[LECTOR] Error al leer del puerto serial.\n");
            }
        } else if (ret == -1) {
            printf("[LECTOR] Error en select.\n");
        }
    }

    return NULL;
}

// Hilo procesador: Procesa los datos del buffer compartido
void *data_processor(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char local_buffer[BUF_SIZE];

    while (1) {
        // Bloquea el mutex para acceder al buffer compartido
        pthread_mutex_lock(&data->mutex);

        // Si hay datos nuevos, los copia y los procesa
        if (data->data_ready) {
            strncpy(local_buffer, data->buffer, BUF_SIZE);
            data->data_ready = 0;  // Reinicia la bandera

            // Desbloquea el mutex
            pthread_mutex_unlock(&data->mutex);

            // Procesa los datos (en este caso, simplemente los imprime)
            printf("[PROCESADOR] Datos procesados: %s\n", local_buffer);
        } else {
            // Desbloquea el mutex si no hay datos nuevos
            pthread_mutex_unlock(&data->mutex);
        }

        // Espera un poco antes de verificar nuevamente
        usleep(1000);  // Espera 1 ms
    }

    return NULL;
}

int main() {
    pthread_t reader_thread, processor_thread;
    thread_data_t data;

    // Inicializa WiringPi
    if (wiringPiSetup() == -1) {
        printf("Error al inicializar WiringPi.\n");
        return 1;
    }

    // Abre el puerto serial
    data.serial_fd = serialOpen("/dev/ttyAMA0", 9600);  // Cambia "/dev/ttyAMA0" y 9600 según tu configuración
    if (data.serial_fd == -1) {
        printf("Error al abrir el puerto serial.\n");
        return 1;
    }

    // Inicializa el mutex
    pthread_mutex_init(&data.mutex, NULL);
    data.data_ready = 0;  // Inicializa la bandera

    // Crea el hilo lector
    if (pthread_create(&reader_thread, NULL, serial_reader, &data) != 0) {
        printf("Error al crear el hilo lector.\n");
        return 1;
    }

    // Crea el hilo procesador
    if (pthread_create(&processor_thread, NULL, data_processor, &data) != 0) {
        printf("Error al crear el hilo procesador.\n");
        return 1;
    }

    // Espera a que los hilos terminen (en este caso, nunca terminarán)
    pthread_join(reader_thread, NULL);
    pthread_join(processor_thread, NULL);

    // Cierra el puerto serial (esto no se ejecutará debido al bucle infinito en los hilos)
    serialClose(data.serial_fd);

    return 0;
}