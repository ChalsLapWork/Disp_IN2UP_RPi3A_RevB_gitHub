#include <stdio.h>
#include "system.h"
#include "init.h"
#include "queue.h"
#include "VFDisplay.h"
#include <signal.h>
#include <unistd.h>
#include "errorController.h"
#ifndef _PTHREAD_H_
  #define _PTHREAD_H_
  #include <pthread.h>
#endif
#include "VFD.h"
#include "stdlib.h"
#include <signal.h>
#ifndef  debug_level1 
  #include <wiringPi.h>
#endif
#include "serial.h"

#define DEPURANDO_SIN_DISPLAY_ENCENDIDO 1//1=CIERTO 0=DISPLAY ESTA ENCENDIDO Y FUNCIONANDO

//extern pthread_t SubProc_SendBlock_TX_VFD;
//extern pthread_t SubProc_SendBlock_chars_TX_VFD;
extern pthread_t hilo_productor, hilo_consumidor;
extern pthread_t reader_thread, processor_thread;


void signal_handler(int signalnum){
    #if(debug_level1==1)
       printf(" signal:%d",signalnum);
    #endif
    Terminar_subProcesos();
}//fin manejador de signal

//Si el programa termina debido a una señal como SIGKILL o SIGSEGV, las funciones registradas con atexit no se ejecutarán.
void cleanup1(void) {
  printf("Limpieza 1 ejecutada.\n");
  pthread_cancel(hilo_productor);
  pthread_cancel(hilo_consumidor);
  pthread_join(hilo_consumidor, NULL);
  pthread_join(hilo_productor, NULL);
  //pthread_cancel(SubProc_SendBlock_chars_TX_VFD);
  //pthread_join(SubProc_SendBlock_chars_TX_VFD,NULL);
  // Espera a que los hilos terminen (en este caso, nunca terminarán)
    pthread_join(reader_thread, NULL);
    pthread_join(processor_thread, NULL);
    cerrar_puerto_serial();
  pthread_exit(NULL);
}//*****************************************************



int main(void){
  printf("\nInsight v3");
#ifndef  debug_level1 
  wiringPiSetup();  
#endif 
  signal(SIGINT,signal_handler);//asocia el manejador de salida del programa
  configPuertos();
  init_queues();
  usleep(500);
  init_menu();
  init_Serial();



  pause();//se detiene el hilo principal hasta que llega una señal
  printf("\n       Hilo Principal Terminado");
  NoErrorOK();
  printf("\n ");

  atexit(cleanup1);//se ejecuta cuando algun hilo ejecuta exit()


  //sleep(500);//tiempo para transmitir los printf anteriores antes de matar el proceso
   
  //pthread_exit(NULL);//espera alos hijos en la memoria para  que los hilos hijos terminen para que vivan hasta sus ultimas lineas de codigo
//for(;;){
   //digitalWrite(BIT5_PIN,HIGH);
   //delay(500);
   //digitalWrite(BIT5_PIN,LOW);}//fin for++++++++++++++++++++



}//fin de main+++++++++++++++++++++++++++++++++++++++

