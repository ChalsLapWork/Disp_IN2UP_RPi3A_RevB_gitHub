
#include "errorController.h"
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>


void errorCritico(char *c){  
    printf("\n\033[0;031m%s\033[0m\n",c);
    usleep(10000);
    exit(-1);
}//fin error critico+++++++++++++++++++++++++++++++++++


// c es el string del mensaje del error critico y 'n' 
/*  n: es numero de linea donde se encuentra el error */
void errorCritico2(char *c,unsigned char n){  
    printf("\n\033[0;031m%s \033[43mError=%d\033[0m\n",c,n);
    usleep(10000);
    exit(-1);
}//fin error critico+++++++++++++++++++++++++++++++++++

void mens_Warnning_Debug(char *c){
      printf("\n \033[1;033m%s \033[0m\n",c);
      usleep(10000);
}//*****************************************************


void NoErrorOK(void){
     printf("\r\033[0;32m[ ok ]\033[0m");usleep(10000);
}// ok label in verde+++++++++++++++++++++++++++++

void mensOK(const char *s,unsigned char color){  
    switch(color){
      case 0:printf("\n       \033[0m%s",s);break;
      case 30:printf("\n       \033[30m%s\033[0m",s);break;
      case 31:printf("\n       \033[31m%s\033[0m",s);break;
      case 32:printf("\n       \033[32m%s\033[0m",s);break;
      case 33:printf("\n       \033[33m%s\033[0m",s);break;
      case 34:printf("\n       \033[34m%s\033[0m",s);break;
      case 35:printf("\n       \033[35m%s\033[0m",s);break;
      case 36:printf("\n       \033[36m%s\033[0m",s);break;
      case 37:printf("\n       \033[37m%s\033[0m",s);break;
      default:printf("\n       \033[0m%s",s);break;}
    usleep(1000);
}//fin de mensaje
