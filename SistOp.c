
#include "queue.h"
#include "SistOp.h"
#include "VFDmenu.h"


extern struct _DISPLAY_VFD_ vfd;




/* Methodo sin sistema operativo
 *  Regresamos     Tamaño de memoria: 1 */	
unsigned char find_contexto_Siguiente(void){
unsigned char ret,estado9;     
  
if(!vfd.config.bits.init_Menu){
         ret=PORTAL_INICIO;}
else{ 
   switch(menu.contexto.solicitaCambioA){
	   case PORTAL_INICIO:switch(menu.contexto.Anterior){
		   	   	   	   	   	      case PORTAL_INICIO:ret=PORTAL_INICIO;break;
		   	   	   	   	   	      case  MENU_INSIGHT:ret=PORTAL_INICIO;break;
		   	   	   	   	   	      default:break;}
	                     break;       
	   case MENU_INSIGHT:break;
	   default:break;}//Debug EN CONSTRUCCION 
}//---------------------------------------------------------  
}//FIN FIND CONTEXTO siguiente+++++++++++++++++++++++++++++++++++++++++++