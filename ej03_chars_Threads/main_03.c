#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>
#include <stdint.h>

#define BUFFER_SIZE 10
#define MAX_BLOCK_SIZE 40

typedef uint8_t uchar;

// Estructura para almacenar bloques de datos
typedef struct {
    uchar datos[MAX_BLOCK_SIZE];
    size_t longitud;
} bloque_t;

typedef struct {
    bloque_t buffer[BUFFER_SIZE];
    _Atomic int head;  // Índice de escritura (hilo principal)
    _Atomic int tail;  // Índice de lectura (hilo hijo)
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} circular_buffer_t;

circular_buffer_t buffer = {
    .head = 0,
    .tail = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .cond  = PTHREAD_COND_INITIALIZER
};

// Simula la función VFD_sendChar (lenta)
void VFD_sendChar(uchar c) {
    printf("Enviando char: 0x%02X\n", c);
    usleep(500000);  // Simula una transmisión lenta de 500ms por carácter
}

// Función que envía un bloque de datos
void* hilo_hijo(void* arg) {
    while (1) {
        pthread_mutex_lock(&buffer.mutex);
        while (buffer.head == buffer.tail) {
            pthread_cond_wait(&buffer.cond, &buffer.mutex);
        }

        bloque_t bloque = buffer.buffer[buffer.tail];
        buffer.tail = (buffer.tail + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&buffer.mutex);

        for (size_t i = 0; i < bloque.longitud; i++) {
            VFD_sendChar(bloque.datos[i]);
        }
    }
    return NULL;
}

// Función que el hilo principal llama para enviar un bloque de caracteres
unsigned char VFD_sendBlockChars(const uchar *datos, size_t longitud) {
    unsigned char ret = 0;
    int next_head = (buffer.head + 1) % BUFFER_SIZE;

    pthread_mutex_lock(&buffer.mutex);
    if (next_head != buffer.tail && longitud <= MAX_BLOCK_SIZE) {
        bloque_t *bloque = &buffer.buffer[buffer.head];
        bloque->longitud = longitud;
        memcpy(bloque->datos, datos, longitud);

        buffer.head = next_head;
        pthread_cond_signal(&buffer.cond);
        ret = 1;
    }
    pthread_mutex_unlock(&buffer.mutex);

    return ret;
}

int main() {
    pthread_t hijo;
    pthread_create(&hijo, NULL, hilo_hijo, NULL);

    const uchar v1[] = { 0x34, 0xEA, 0xAB };
    const uchar v2[] = { 0x12, 0x34, 0x56, 0x78, 0x9A };

    // Enviar bloques sin detener el hilo principal
    VFD_sendBlockChars(v1, sizeof(v1));
    printf("Padre: Enviado bloque 1\n");

    usleep(100000);  // Simular otra tarea del hilo principal

    VFD_sendBlockChars(v2, sizeof(v2));
    printf("Padre: Enviado bloque 2\n");

    // Simular tareas continuas
    while (1) {
        printf("Padre: Haciendo otras tareas...\n");
        usleep(2000000);  // Simular tareas en tiempo real (2 segundos)
    }

    pthread_cancel(hijo);
    pthread_join(hijo, NULL);

    return 0;
}
