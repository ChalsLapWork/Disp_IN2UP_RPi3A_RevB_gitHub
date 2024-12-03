/*  ejemplo para probar el sendBlock desde el hilo padre
   y que trabaje en tiempo real el padre y se manden mas 
   lentamente los bytes al hardware sin tantos hilos
*/

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdatomic.h>

#define BUFFER_SIZE 220  // Tamaño del buffer circular
#define MAX_MESSAGE_LEN 256

typedef struct {
    char buffer[BUFFER_SIZE][MAX_MESSAGE_LEN];
    _Atomic int head;  // Índice de escritura (hilo padre)
    _Atomic int tail;  // Índice de lectura (hilo hijo)
    pthread_mutex_t mutex;
} circular_buffer_t;

circular_buffer_t buffer = {
    .head = 0,
    .tail = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER
};

// Función que simula la transmisión lenta
void transmitir_lento(const char *str) {
    while (*str) {
        printf("\033[36m");
        putchar(*str++);
        printf("\033[0m");
        fflush(stdout);
        usleep(50000);  // Simula retardo de 0.5 segundos
    }
    printf("\n");
}

// Hilo hijo: Consume mensajes del buffer y los transmite
void* hilo_hijo(void *arg) {
    while (1) {
        if (buffer.head != buffer.tail) {  // Verifica si hay mensajes disponibles
            pthread_mutex_lock(&buffer.mutex);

            // Extrae el mensaje del buffer
            char mensaje[MAX_MESSAGE_LEN];
            strncpy(mensaje, buffer.buffer[buffer.tail], MAX_MESSAGE_LEN);
            buffer.tail = (buffer.tail + 1) % BUFFER_SIZE;

            pthread_mutex_unlock(&buffer.mutex);

            transmitir_lento(mensaje);  // Transmite lentamente
        } else {
            usleep(1000);  // Pequeña espera para evitar consumo intensivo de CPU
        }
    }
    return NULL;
}

// Función del hilo padre: Produce mensajes sin bloquearse
void enviar_mensaje(const char *mensaje) {
    int next_head = (buffer.head + 1) % BUFFER_SIZE;

    if (next_head != buffer.tail) {  // Solo escribe si hay espacio en el buffer
        pthread_mutex_lock(&buffer.mutex);
        strncpy(buffer.buffer[buffer.head], mensaje, MAX_MESSAGE_LEN);
        buffer.head = next_head;
        pthread_mutex_unlock(&buffer.mutex);
    } else {
        printf(" Buffer lleno, mens descartado: %s\n", mensaje);  // Manejo del desborde
    }
}

int main() {
    pthread_t hijo;

    // Crear el hilo hijo (sin esperar que termine)
    pthread_create(&hijo, NULL, hilo_hijo, NULL);

    // Simulación del hilo padre en tiempo real
    const char *mensajes[] = {
        "Mensaje 1: Hola mundo",
        "Mensaje 2: Transmisión en progreso",
        "Mensaje 3: Fin de transmisión"
    };

    for (int i = 0; i < 3; i++) {
        enviar_mensaje(mensajes[i]);
        printf("Padre: Enviado \"%s\"\n", mensajes[i]);
        usleep(200000);  // Simula tareas en tiempo real (sin bloquearse)
    }

    // El hilo padre continúa indefinidamente (o hasta que lo detengas manualmente).
    while (1) {
        enviar_mensaje("Mensaje en bucle infinito");
        usleep(1000000);  // Envía mensajes cada segundo
    }

    return 0;
}
