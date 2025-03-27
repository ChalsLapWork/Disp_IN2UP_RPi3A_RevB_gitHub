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

