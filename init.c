//#include "system.h"
#include "init.h"
//#include <stdio.h>
//#include "errorController.h"
#include <wiringPi.h>


void configPuertos(void){
  //printf2("\n       Started Configuracion de Puertos");
   wiringPiSetup();
  for(int i=0;i<8;i++)
      pinMode(i,OUTPUT);
  pinMode(WR_PIN  ,OUTPUT);
  pinMode(R_BUSY_PIN,INPUT);

}//fin init puertos++++++++++++++++++++++++


