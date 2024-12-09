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
		                     MenuActualScreen.func=0;
		                     MenuActualScreen.func1=PortalinicioDisplay; // -------------------------------------------------------EN-REVISION    		 
		                     //MenuActualScreen.func2=PortalinicioDisplay;
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




//Este metodo Solo se ejecuta una vez sin instancias
unsigned char  PortalinicioDisplay(void){//Funcion Suprema de Despliegue de la Pantalla0
unsigned char ret;
    mensOK("Estoy en portal Inicio",CAMARILLO);   
    ret=1;
 
return ret;   
}// FIN DESPLIEGUE DEL PORTAL INICIO-------------------------------------------------------------------



