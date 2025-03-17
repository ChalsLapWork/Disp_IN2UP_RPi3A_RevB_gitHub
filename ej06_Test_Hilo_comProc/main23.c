#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>

#define SERIAL_DEVICE "/dev/serial0" // Ajusta según tu configuración
#define BUFFER_SIZE 1024
#define TIMEOUT_SEC 5 // Tiempo en segundos para indicar falta de datos

// Colores para printf
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

char buffer1[BUFFER_SIZE];
char buffer2[BUFFER_SIZE];
int buffer1_lleno = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *hiloProductorSerial(void *arg) {
    int serial_fd = serialOpen(SERIAL_DEVICE, 115200);
    if (serial_fd < 0) {
        fprintf(stderr, RED "Error abriendo el puerto serial\n" RESET);
        return NULL;
    }
    printf(GREEN "Hilo Productor Serial iniciado\n" RESET);

    int index = 0;
    time_t last_data_time = time(NULL);
    while (1) {
        if (serialDataAvail(serial_fd)) {
            char c = serialGetchar(serial_fd);
            putchar(c); // Mostrar datos en la terminal
            fflush(stdout);
            last_data_time = time(NULL); // Reiniciar temporizador

            pthread_mutex_lock(&mutex);
            if (!buffer1_lleno) {
                buffer1[index++] = c;
                if (index >= BUFFER_SIZE - 1 || c == '\n') {
                    buffer1[index] = '\0';
                    buffer1_lleno = 1;
                    index = 0;
                    pthread_cond_signal(&cond);
                }
            }
            pthread_mutex_unlock(&mutex);
        } else {
            if (time(NULL) - last_data_time >= TIMEOUT_SEC) {
                printf(CYAN "\nNo se han recibido datos en %d segundos...\n" RESET, TIMEOUT_SEC);
                last_data_time = time(NULL); // Reiniciar temporizador
            }
            usleep(100000); // Pequeña espera para evitar alto uso de CPU
        }
    }
    return NULL;
}

void *hiloConsumidorSerial(void *arg) {
    printf(YELLOW "Hilo Consumidor Serial iniciado\n" RESET);
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!buffer1_lleno)
            pthread_cond_wait(&cond, &mutex);

        strcpy(buffer2, buffer1); // Copiar buffer1 a buffer2
        printf(YELLOW "\nDatos recibidos: %s\n" RESET, buffer2);
        buffer1_lleno = 0;

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    wiringPiSetup();
    pthread_t th1, th2;

    pthread_create(&th1, NULL, hiloProductorSerial, NULL);
    pthread_create(&th2, NULL, hiloConsumidorSerial, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}
