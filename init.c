#include "system.h"
#include "init.h"
#include <stdio.h>
#include "errorController.h"
#include "VFD.h"
#include "Memoria.h"
#ifndef  debug_level1 
   #include <wiringPi.h>
#endif
extern struct _PRODUCTO1_ producto;

void configPuertos(void){
  printf("\n       Started Configuracion de Puertos");
#ifndef debug_level1 
  for(int i=0;i<8;i++)
      pinMode(i,OUTPUT);
  pinMode(WR_PIN  ,OUTPUT);
  pinMode(R_BUSY_PIN,INPUT);
#endif
#if (debug_level1==1) 
   //printf("\r\033[0;32m[ ok ]\033[0m");
    NoErrorOK();
#endif  
}//fin init puertos++++++++++++++++++++++++


void init_Display(void){

 
}//fin de init_Display+++++++++++++++++++++