#include "Memoria.h"
#include "errorController.h"

unsigned short int getAddPassword(unsigned char level){
unsigned short int add=0;   
	   switch(level){
		   case 1:add=PASSWORD_LEVE1_ADD;break;
		   case 2:add=PASSWORD_LEVE2_ADD;break;
		   case 3:add=PASSWORD_LEVE3_ADD;break;
		   case 4:add=PASSWORD_LEVE4_ADD;break;
		   default:  }//debug error de software   		
return add;
}//fin getAddPassword-------------------------------------------------------------------

void setPasswords(unsigned char level,unsigned char *p){
    //writeEEPROMblock(getAddPassword(level),PASSWORD_SIZE,p);
    mensOK("Falta la funcion de guardar contraseñas",33); 
}//fin setPasswords---------------------------------------------------------------------
