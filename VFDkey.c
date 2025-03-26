#include "VFDkey.h"
#include "VFDmenu.h"
#include "VFDisplay.h"


void PortaliniciokeyUP(void){return;}//fin PortaliniciokeyUP--------PONER LAS FUNCIONES KEY DEL MENU------------------6
void PortaliniciokeyRT(void){return; }//fin PortaliniciokeyRT-------LLENAR LAS FUNCIONES DE LOS KEYS------------------8
void PortaliniciokeyLF(void){return;}//fin PortaliniciokeyLF--------------------------------------
void PortaliniciokeyDN(void){return;}//fin PortaliniciokeyLF--------------------------------------
void PortaliniciokeyEN(void){                             
	                         //VFDcommand_Bold_DDS(FALSE);
	                         cambio_de_contexto(MENU_INSIGHT);/*a donde voy*/
                             return;}//fin PortaliniciokeyDN--------------------------------------------------------------------------------------
