#include "Memoria.h"
#include "errorController.h"
#include "strings.h"
#include "system.h"
#include "VFDmenu.h"


#define NUM_DE_PASSWORD 5 //caNTIDAD DE password que manejamos 

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

/* VAlida Passwords si es correcta en algun nivel devuelve TRUE, y 
 * *Level regresa en que nivel es aceptado
 *  *T la cadena a evualuar */
unsigned char validatePasswords(unsigned char *Level,unsigned char *T){//validamos la password
unsigned char *p;
unsigned char i,nivel;	
const unsigned char pass[NUM_DE_PASSWORD]={0,OPERADOR,SUPERVISOR,ADMINISTRADOR,SERVICIO};
    for(i=1,nivel=1;i<NUM_DE_PASSWORD;i++,nivel++){// cuatro niveles de password
       p=getPasswords(i); 
       if(compareString(T,p,PASSWORD_SIZE)){//
	        *Level=pass[nivel];//el nivel de la password que coincidio,
    	    return TRUE;}} //regresa false, porque hay una igual, eso es malo poreso regresa false
return FALSE; //no hubo ninguna password igual------------    
}//fin validatePassword-----------------------------------------------------------------------------

//regresamos apuntador de una clave solamente seleccionada
unsigned char *getPasswords(unsigned char level){
	//return(readEEPROMblock(getAddPassword(level),PASSWORD_SIZE));
static unsigned char s[]="password";
return &s[0];
}//fin getPasswords---------------------------------------------------------------
