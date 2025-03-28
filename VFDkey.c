#include "VFDkey.h"
#include "VFDmenu.h"
#include "VFDisplay.h"
#include "queue.h"
#include "VFD.h"
#include "system.h"

extern struct _DISPLAY_VFD_ vfd;


void PortaliniciokeyUP(void){return;}//fin PortaliniciokeyUP--------PONER LAS FUNCIONES KEY DEL MENU------------------6
void PortaliniciokeyRT(void){return; }//fin PortaliniciokeyRT-------LLENAR LAS FUNCIONES DE LOS KEYS------------------8
void PortaliniciokeyLF(void){return;}//fin PortaliniciokeyLF--------------------------------------
void PortaliniciokeyDN(void){return;}//fin PortaliniciokeyLF--------------------------------------
void PortaliniciokeyEN(void){                             
	                         //VFDcommand_Bold_DDS(FALSE);
	                         cambio_de_contexto(MENU_INSIGHT);/*a donde voy*/
                             return;}//fin PortaliniciokeyDN--------------------------------------------------------------------------------------


void MenuInsightkeyUP(void){
unsigned char *cursorx,*cursory;
       cursorx=&vfd.menu.cursorx;
       cursory=&vfd.menu.cursory;    
                            if(*cursory>POSY4){
                              VFDposicion(*cursorx,*cursory);
                              VFDserial_SendChar(' ');
                              --(*cursory);
                              VFDposicion(*cursorx,--(*cursory));
                              VFDserial_SendChar('>');}
                         else 
                        	 if(*cursory==POSY4){
                        		 VFDposicion(*cursorx,*cursory); 
			                     VFDserial_SendChar(' ');
			                     *cursorx=POSXESQ235;*cursory=POSY0; //xpos=POSXESQ235
			                     VFDposicion(*cursorx,*cursory);
			                     VFDserial_SendChar('>');
			                     VFDserial_SendChar('X');  }    
                          return;}//fin MenuInsightkeyUP--------------------------------------
void MenuInsightkeyRT(void){return;}//fin MenuInsightokeyRT--------------------------------------
void MenuInsightkeyLF(void){return;}//fin MenuInsightokeyLF--------------------------------------
void MenuInsightkeyDN(void){
unsigned char *cursorx,*cursory;
       cursorx=&vfd.menu.cursorx;
       cursory=&vfd.menu.cursory;    
                         if(*cursory==POSY0){
	                        VFDposicion(*cursorx,*cursory);
							VFDserial_SendChar(' ');
							VFDserial_SendChar('x');
							*cursorx=POSX0;*cursory=POSY4;
							VFDposicion(*cursorx,*cursory);
							VFDserial_SendChar('>');
							return;}
				         else{
				        	if(*cursory<POSY12){
							VFDposicion(*cursorx,*cursory);
							VFDserial_SendChar(' ');
							++(*cursory);
							VFDposicion(*cursorx,++(*cursory));
							VFDserial_SendChar('>');
							return;}}
	                     return;}//fin MenuInsightokeyDN--------------------------------------
void MenuInsightkeyEN(void){
unsigned char *cursorx,*cursory;
cursorx=&vfd.menu.cursorx;
cursory=&vfd.menu.cursory;    
	 switch(*cursory){
		case POSY4: cambio_de_contexto(AJUSTE_DE_PRODUCTO);break;
		case POSY6: cambio_de_contexto(AJUSTE_PARAMETRICO_DE_PRODUCTO);break;
		case POSY8: cambio_de_contexto(AJUSTE_DE_SISTEMA);break;
		case POSY10:cambio_de_contexto(PANTALLA_DDS);break;
		case POSY12:cambio_de_contexto(INFORMACION_DE_USUARIO);break;
		case POSY0: cambio_de_contexto(PORTAL_INICIO);break;
		default:break;}//fin MenuInsightokeyEN-------------------------------------
}//fin MenuInsightkeyEN------------------------------------------------------------
/*  fin de MenuInsightkey+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  fin de MenuInsightkey+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



void AjusteProductokeyUP(void){
unsigned char *cursorx,*cursory;
       cursorx=&vfd.menu.cursorx;
       cursory=&vfd.menu.cursory;	
	                      if(*cursory>POSY4){
	   			    	      VFDposicion(*cursorx,*cursory);
	   			    	      VFDserial_SendChar(' ');
	   			    	      --(*cursory);
	   			    	      VFDposicion(*cursorx,--(*cursory));
	   			    	      VFDserial_SendChar('>');
	   			    	      return;}
	   			          else if(*cursory==POSY4){VFDposicion(*cursorx,*cursory); 
	   			                                  VFDserial_SendChar(' ');
	   			                                  *cursorx=POSXESQ235;*cursory=POSY0; //xpos=POSXESQ235
	   			                                  VFDposicion(*cursorx,*cursory);
	   			                                  VFDserial_SendChar('>');
	   			                                  VFDserial_SendChar('X');  }
	                      return;}//fin PortaliniciokeyUP--------PONER LAS FUNCIONES KEY DEL MENU------------------6
void AjusteProductokeyRT(void){return; }//fin PortaliniciokeyRT-------LLENAR LAS FUNCIONES DE LOS KEYS------------------8
void AjusteProductokeyLF(void){return;}//fin PortaliniciokeyLF--------------------------------------
void AjusteProductokeyDN(void){
unsigned char *cursorx,*cursory;
       cursorx=&vfd.menu.cursorx;
       cursory=&vfd.menu.cursory;	
	if(*cursory==POSY0){
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendChar(' ');
			VFDserial_SendChar('x');
			*cursorx=POSX0;*cursory=POSY4;
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendChar('>');return;}
	else{if(*cursory<POSY14){
		   switch(menu.contexto.control){
			   case OPERADOR:if(*cursory>=POSY6){//NIVEL-1
				          *cursory=POSY6;
			              return;}
			   case ADMINISTRADOR:	   //NIVEL-3
			   case SUPERVISOR:	   //NIVEL-2
			   case SERVICIO://NIVEL-4	   
				       VFDposicion(*cursorx,*cursory);
				   	   VFDserial_SendChar(' ');
				  	   ++(*cursory);
				   	   VFDposicion(*cursorx,++(*cursory));
				       VFDserial_SendChar('>');
				   	   return;break;
			   default:return;break; }}}//fin switch ----------------------------------------------
return;}//f----------------------------------------------------------------------------------------
void AjusteProductokeyEN(void){
unsigned char *cursorx,*cursory;
	cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory;	
	switch(*cursory){
		case POSY4:/*cambio_de_contexto cambio_de_contexto(EN_DESARROLLO;*/break;
		case POSY6: cambio_de_contexto(SELECCIONAR_PRODUCTO); break;
	    case POSY8: arg0=0;arg1=0;//sin argumentos para entrar aqui
                  	cambio_de_contexto(NUEVO_PRODUCTO);
                    break;
		case POSY10:menu.contexto.Anterior=AJUSTE_DE_PRODUCTO;//de donde vengo, que eligimos
			        cambio_de_contexto(AJUSTE_PRODUCTO_SEL); break;
		case POSY12:cambio_de_contexto(BORRAR_PRODUCTO); break;//Borrar PRODUCTO
		case POSY14:cambio_de_contexto(COPY_PRODUCTO);break;
		case POSY0:cambio_de_contexto(PORTAL_INICIO);break;
		default:break;}//fin PortaliniciokeyDN--------------------------------------------------------------------------------------
}//fin AjusteProductokeyEN--------------------------------------------------
/* FIN  AjusteProducto  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* FIN  AjusteProducto  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * */
