#include "VFDmenu.h"
#include "errorController.h"
#include "system.h"

struct ArbolMenu MenuActualScreen;//la estrucrura del menu actual en pantalla.

unsigned char InitArbolMenu(unsigned char destino){// initializar estructura de datos de los menus
auto unsigned char ret=0;	 
	 switch(destino){
	  /* PANTALLA NIVEL 0************************************************************** */
		 case PORTAL_INICIO: MenuActualScreen.menuNodo=PORTAL_INICIO;
		                     MenuActualScreen.permisos=DESARROLLADOR_PERMISO;//------------------------------------EN-REVISION
		                     //MenuActualScreen.func=0;
		                     //MenuActualScreen.func1=PortalinicioDisplay; // -------------------------------------------------------EN-REVISION    		 
		                     MenuActualScreen.func2=PortalinicioDisplay;
		                    // MenuActualScreen.funcKeyUP=PortaliniciokeyUP;
		                     // MenuActualScreen.funcKeyRT=PortaliniciokeyRT;
		                     // MenuActualScreen.funcKeyLF=PortaliniciokeyLF;
		                    //  MenuActualScreen.funcKeyDN=PortaliniciokeyDN;//Insert the function pointer
		                    //  MenuActualScreen.funcKeyEN=PortaliniciokeyEN;//---poner en los apuntadores apuntar a las funciones--------------4
							 ret=TRUE;
		                     break;		
         default: errorCritico2("error de InitArbol",19);break;                     
        }//fin switch ++EN CONSTRUCCION ++++++++++++++++++++++++++++++++++++
return ret;
}//fin portal inicion++++++++++++++++++++++++++++++++++++++++++++++



//despliega el menu principal, el recurso se solicita y gestiona
//desde el hilo padre del manejo del menu.
//Este metodo Solo se ejecuta una vez sin instancias
unsigned char  PortalinicioDisplay(unsigned char *mem){//Funcion Suprema de Despliegue de la Pantalla0
const unsigned char s[]=VERSION2;
unsigned char *ss;
const unsigned char  a[]="Test Set-up";
const unsigned char  b[]="S                P";
const unsigned char  c[]="Cuenta rechazos ";
const unsigned char  d[]="Cuenta producto ";
const unsigned char x[4]={80,24,24,24};
const unsigned char y[4]={ 2,10,12,14};
unsigned char ret=0;
//unsigned char *inst1,*inst2;//instancias subHilos a ejecutar que se pueden ejecutar en otros lados
unsigned char *estado,*control,*mem_2bytes;

union W16{
   unsigned short int usi;
   unsigned char c[2];
}word_16bits;

    estado=*mem;
   control=*mem+1;
  w16.c[0]=*(mem+4);
  w16.c[1]=*(mem+5);
      aux1=w16.usi;
mem_2bytes=mem+6;//6,7
     



    mensOK("Estoy en portal Inicio",CAMARILLO);   
    NoErrorOK();    
    switch(*estado){ 
       case 1:Deteccion.CuadroMadreReady=FALSE;
              keypad.b.enable=FALSE;
              (*estado)++;break;
       case 2:if(VFDclrscr1(mem_2bytes))estado++;break;
       
    ret=1;
 
return ret;   
}// FIN DESPLIEGUE DEL PORTAL INICIO-------------------------------------------------------------------



