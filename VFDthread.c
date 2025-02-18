#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "VFDthread.h"


#ifndef debug_level1
  #include <wiringPi.h>
#endif

// Estructura para almacenar datos en el buffer circular
typedef struct {
    unsigned char data[MAX_LEN];
    size_t len;
} DatosTransmision;


DatosTransmision buffer_circular[NUM_ENTRADAS];  // Buffer circular
int in = 0, out = 0;

unsigned char buffer2[MAX_BUFFER_LEN];  // Buffer lineal para concatenar datos del buffer circular
size_t buffer2_len = 0;

unsigned char buffer3[MAX_BUFFER_LEN];  // Buffer final para enviar a VFDserial_SendBlock_Tx
size_t buffer3_len = 0;

pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_llenos, sem_vacios;
pthread_mutex_t mutex_buffer2 = PTHREAD_MUTEX_INITIALIZER;

pthread_t hilo_productor, hilo_consumidor;


/*  init los threads de manera mas facil   * */
void init_VFD_Threads(void){//
    // Inicialización de semáforos
    sem_init(&sem_llenos, 0, 0);
    sem_init(&sem_vacios, 0, NUM_ENTRADAS);

    // Crear el hilo productor
    pthread_create(&hilo_productor, NULL, VFDserial_SendBlockProductor, NULL);

    // Crear el hilo consumidor
    pthread_create(&hilo_consumidor, NULL, VFDserial_SendBlockConsumidor, NULL);

    // Hilo principal envía datos continuamente
    unsigned char array1[] = {0x41, 0x42, 0x43, 0x44};  // "ABCD"
    char string1[] = "Hola, soy un string 1";
    unsigned char array2[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    char string2[] = "Este es otro string más largo";

    int iteracion = 0;
    while (1) {
        if (iteracion % 4 == 0) {
            VFDserial_SendBlock_buf(array1, sizeof(array1));
        } else if (iteracion % 4 == 1) {
            VFDserial_SendBlock_buf(string1, strlen(string1) + 1);
        } else if (iteracion % 4 == 2) {
            VFDserial_SendBlock_buf(array2, sizeof(array2));
        } else {
            VFDserial_SendBlock_buf(string2, strlen(string2) + 1);
        }
        iteracion++;
        usleep(500000);  // Espera para simular nuevos datos
    }//fin which+++++++++++++++++++++++++++++++++++++++++++++++++++++++
}//fin de initialized VFD threads++++++++++++++++++++++++++++++++++++++


// Función principal para agregar datos al buffer circular
unsigned char VFDserial_SendBlock_buf(void *ptr, size_t size) {
    if (size > MAX_LEN) {
        fprintf(stderr, "Error: El tamaño de los datos excede el máximo permitido.\n");
        return 0;
    }

    sem_wait(&sem_vacios);
    pthread_mutex_lock(&mutex_buffer);

    buffer_circular[in].len = size;
    memcpy(buffer_circular[in].data, ptr, size);
    printf("Hilo Principal: Datos agregados al buffer (len: %zu)\n", size);
    in = (in + 1) % NUM_ENTRADAS;

    pthread_mutex_unlock(&mutex_buffer);
    sem_post(&sem_llenos);

    return 1;
}//fin VFDserial_SendBlock++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Hilo Productor: vacía todo el buffer circular a buffer2
void *VFDserial_SendBlockProductor(void *arg) {
    while (1) {
        sem_wait(&sem_llenos);
        pthread_mutex_lock(&mutex_buffer);

        pthread_mutex_lock(&mutex_buffer2);

        for (int i = 0; i < NUM_ENTRADAS; i++) {
            size_t len = buffer_circular[out].len;
            if (len > 0 && buffer2_len + len <= MAX_BUFFER_LEN) {
                memcpy(buffer2 + buffer2_len, buffer_circular[out].data, len);
                buffer2_len += len;
                printf("Productor: Copió datos al buffer2 (len: %zu, total en buffer2: %zu)\n", len, buffer2_len);
            }
            out = (out + 1) % NUM_ENTRADAS;
        }

        pthread_mutex_unlock(&mutex_buffer2);
        pthread_mutex_unlock(&mutex_buffer);
        sem_post(&sem_vacios);

        usleep(100000);
    }
    return NULL;
}//fin VFDserial_SendBlockProductor+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Hilo Consumidor: transfiere buffer2 a buffer3 y llama a VFDserial_SendBlock_Tx
void *VFDserial_SendBlockConsumidor(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex_buffer2);

        if (buffer2_len > 0) {
            size_t len = buffer2_len;
            memcpy(buffer3, buffer2, len);
            buffer3_len = len;
            buffer2_len = 0;
            printf("Consumidor: Transferencia de datos de buffer2 a buffer3 (len: %zu)\n", len);

            pthread_mutex_unlock(&mutex_buffer2);

            // Llamar a VFDserial_SendBlock_Tx para procesar buffer3 completo
            VFDserial_SendBlock_Tx(buffer3, buffer3_len);
        } else {
            pthread_mutex_unlock(&mutex_buffer2);
        }

        usleep(100000);  // 100 ms para simular procesamiento continuo
    }
    return NULL;
}///fin VFDserial_SendBlockConsumidor++++++++++++++++++++++++++++++++++++++++++++++++

// Función que procesa buffer3 completo (como un gran array de datos)
void VFDserial_SendBlock_Tx(unsigned char *buffer, size_t len) {
unsigned char estado,cmd,n;
//unsigned char c[MAX_NUM_CHAR_VFD];
unsigned char *crc=NULL;
unsigned char str_len = 0;        // Longitud del string de entrada
char *str;	
size_t i=0;
static int count;

    printf("Consumidor-Tx: Procesando buffer3 completo (len: %zu)\n", len);
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
    return;

}//fin VFDserial_SendBlock_Tx+++++++++++++++++++++++++++++++++++++++++++++++++++




