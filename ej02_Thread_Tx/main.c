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
#include <stdbool.h>

#define BUFFER_SIZE 10  // Tamaño del buffer circular
#define MAX_MESSAGE_LEN 40
#ifndef TRUE
  #define TRUE 1
#endif



// Función que simula la transmisión lenta
void transmitir_lento(const char *str) {
    while (*str) {
        printf("\033[35m");
        putchar(*str++);
        printf("\033[0m");
        fflush(stdout);
        usleep(900); } // Simula retardo de 900useg
    printf("\n");
}//transmitir lento++++++++++++++++++++++++++++++++   

// Hilo hijo: Consume mensajes del buffer y los transmite
void* hilo_hijo(void *arg) {
  while(1){  
    pthread_mutex_lock(&buffer.mutex);
    while (buffer.head == buffer.tail) {
      pthread_cond_wait(&buffer.cond, &buffer.mutex);}
    char mensaje[MAX_MESSAGE_LEN];// Extrae el mensaje del buffer
    strncpy(mensaje, buffer.buffer[buffer.tail], MAX_MESSAGE_LEN);
    buffer.tail = (buffer.tail + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&buffer.mutex);
    transmitir_lento(mensaje);  // Transmite lentamente
  }//fin while+++++++++
return NULL;
}//+++++++++++++++++++++++++++++++++++++++++++++++++

// Función del hilo padre: Produce mensajes sin bloquearse
unsigned char enviar_mensaje(const char *mensaje) {
unsigned char ret=0;
    int next_head = (buffer.head + 1) % BUFFER_SIZE;
    pthread_mutex_lock(&buffer.mutex);
    if (next_head != buffer.tail) {  // Solo escribe si hay espacio en el buffer
        strncpy(buffer.buffer[buffer.head], mensaje, MAX_MESSAGE_LEN);
        buffer.head = next_head;
        pthread_cond_signal(&buffer.cond);  // Despierta al hijo
        ret=TRUE;}
     pthread_mutex_unlock(&buffer.mutex);
return ret;}// fin de enviar mensaje++++++++++++++++++++++

int main() {
unsigned char estado;
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
      switch(estado){
         case 1:if(enviar_mensaje("Mensaje en bucle infinito"))estado++;break;
         case 2:printf(" Estoy en main ");
                estado=1;break;
         default:estado=1;break;}
      //usleep(10000);  // Envía mensajes cada 0.001seg
    }

    pthread_cancel(hijo);  // En algún punto deberías cancelar el hijo (opcional)
    pthread_join(hijo, NULL);  // Se uniría solo si decides terminar el programa

return 0;
}//fin de main++++++++++++++++++++++++++++++++++++++++++++++
