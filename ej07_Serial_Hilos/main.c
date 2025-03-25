#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

// Códigos de escape ANSI para colores
#define COLOR_VERDE "\033[32m"
#define COLOR_ROJO  "\033[31m"
#define COLOR_RESET "\033[0m"
#define COLOR_BLANCO "\033[37m"
#define COLOR_AMARILLO "\033[33m"

// Buffer compartido y variables de control
#define BUFFER_SIZE 256
unsigned char buffer[BUFFER_SIZE];
int bytes_received = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
bool new_data_available = false;

// Función del hilo serial_receptor
void* serial_receptor(void* arg) {
    int serial_port = *(int*)arg;

    while (1) {
        if (serialDataAvail(serial_port) > 0) {
            pthread_mutex_lock(&mutex);

            bytes_received = read(serial_port, buffer, sizeof(buffer));  // Leer datos
            if (bytes_received > 0) {
                new_data_available = true;
                pthread_cond_signal(&cond);  // Notificar al consumidor que hay nuevos datos
            }

            pthread_mutex_unlock(&mutex);
        }

        // Pequeña pausa para evitar sobrecargar la CPU
        usleep(1000);  // Esperar 1 ms
    }

    return NULL;
}

// Función del hilo consumidorSerial
void* consumidorSerial(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Esperar hasta que haya nuevos datos disponibles
        while (!new_data_available) {
            pthread_cond_wait(&cond, &mutex);
        }

        // Mostrar los datos recibidos
        printf("%sDatos recibidos (hex):%s ", COLOR_VERDE, COLOR_RESET);

        for (int i = 0; i < bytes_received; i++) {
            printf("%s%02X %s ", COLOR_ROJO, buffer[i], COLOR_RESET);
        }

        for (int i = 0; i < bytes_received; i++) {
            printf("%s%c%s", COLOR_AMARILLO, buffer[i], COLOR_RESET);
        }

        printf("\n");

        new_data_available = false;  // Resetear la bandera de nuevos datos
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    int serial_port;
    pthread_t thread_receptor, thread_consumidor;

    // Inicializar WiringPi
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Error al inicializar WiringPi.\n");
        return 1;
    }

    // Abrir el puerto serial ttyAMA0
    if ((serial_port = serialOpen("/dev/ttyAMA0", 9600)) < 0) {
        fprintf(stderr, "Error al abrir el puerto serial.\n");
        return 1;
    }

    printf("%sConexión serial establecida. Esperando datos...%s\n", COLOR_VERDE, COLOR_RESET);

    // Crear los hilos
    if (pthread_create(&thread_receptor, NULL, serial_receptor, &serial_port) != 0) {
        fprintf(stderr, "Error al crear el hilo serial_receptor.\n");
        return 1;
    }

    if (pthread_create(&thread_consumidor, NULL, consumidorSerial, NULL) != 0) {
        fprintf(stderr, "Error al crear el hilo consumidorSerial.\n");
        return 1;
    }

    // Esperar a que los hilos terminen (nunca ocurrirá en este ejemplo)
    pthread_join(thread_receptor, NULL);
    pthread_join(thread_consumidor, NULL);

    // Cerrar el puerto serial (nunca se alcanzará en este ejemplo)
    serialClose(serial_port);
    return 0;
}