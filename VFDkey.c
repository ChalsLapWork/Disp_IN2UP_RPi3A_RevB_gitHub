#include "VFDkey.h"
#include "VFDmenu.h"
#include "VFDisplay.h"
#include "queue.h"
#include "VFD.h"
#include "system.h"
#include "maths.h"
#include "strings.h"
#include <stdlib.h>
#include "errorController.h"
#include <unistd.h>
#include "Memoria.h"
#include "VFDthread.h"

extern struct _DISPLAY_VFD_ vfd;
extern struct _PRODUCT1_ producto2;


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
		   switch(vfd.menu.contexto.control){
			   case OPERADOR:if(*cursory>=POSY6){//NIVEL-1
				                    *cursory=POSY6;
			                        return;}	
							 /* fall through */		//comentario para el compilador no quitar
			   case ADMINISTRADOR:/* fall through */	   //NIVEL-3
			   case SUPERVISOR:	  /* fall through */ //NIVEL-2
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
unsigned char *cursorx,*cursory,anterior;
	cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory;	
	switch(*cursory){
		case POSY4:/*cambio_de_contexto cambio_de_contexto(EN_DESARROLLO;*/break;
		case POSY6: cambio_de_contexto(SELECCIONAR_PRODUCTO); break;
	    case POSY8: cambio_de_contexto(NUEVO_PRODUCTO);
                    break;
		case POSY10:cambio_de_contexto(AJUSTE_PRODUCTO_SEL); break;
		case POSY12:cambio_de_contexto(BORRAR_PRODUCTO); break;//Borrar PRODUCTO
		case POSY14:cambio_de_contexto(COPY_PRODUCTO);break;
		case POSY0:cambio_de_contexto(PORTAL_INICIO);break;
		default:break;}//fin PortaliniciokeyDN--------------------------------------------------------------------------------------
}//fin AjusteProductokeyEN--------------------------------------------------
// FIN  AjusteProducto  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* FIN  AjusteProducto  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */


void AjusteParamProdkeyUP(void){
unsigned char *cursorx,*cursory;
cursorx=&vfd.menu.cursorx;
cursory=&vfd.menu.cursory;

	if(*(AjParamProd->editarSensFase)>0){//->igxc0>0)//esta seleccionado cambiar por numero
	  	 operacionVariable(POSXAJUSPROD-8,*cursory,*(AjParamProd->editarSensFase),SUMAR);
		 configModificado(AJUSTE_PARAMETRICO_DE_PRODUCTO);
		 //isEnable_Keypad(WAIT);
		 return;}
	if(*cursory==POSY6){//MENU con sistema OPERATIVO
		VFDposicion(*cursorx,*cursory);
		VFDserial_SendChar(' ');
		*cursory=POSY0;	  
		VFDposicion(POSXESQ235,*cursory);
		VFDserial_SendChar('>');
		VFDserial_SendChar('X');
		VFDserial_SendChar(0x01);
		return;}
	if(*cursory==POSY0){return;}
	if(*cursory<=POSY14){	
		 VFDposicion(*cursorx,*cursory);
		 VFDserial_SendChar(' ');
		 --(*cursory);
		 VFDposicion(*cursorx,--(*cursory));
		 VFDserial_SendChar('>');
		 VFDserial_SendChar(0x01);
		 return;}
}//fin AjusteParamProdkeyUP++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void AjusteParamProdkeyDN(void){
unsigned char *cursorx,*cursory;
	cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory;		
	if(*(AjParamProd->editarSensFase)>0){//esta seleccionado cambiar por numero
		operacionVariable(POSXAJUSPROD-8,*cursory,*(AjParamProd->editarSensFase),RESTAR);
		return;}
	if(*cursory==POSY0){
	   VFDposicion(POSXESQ235,POSY0); 
	   VFDserial_SendChar(' ');
	   VFDserial_SendChar('x');
	   *cursory=POSY6;
	   VFDposicion(*cursorx,*cursory);
	   VFDserial_SendChar('>');
	   VFDserial_SendChar(0x01);
	   return;}
	if(*cursory<POSY14){	 
	   VFDposicion(*cursorx,*cursory);
	   VFDserial_SendChar(' ');
	   (*cursory)++;
	   VFDposicion(*cursorx,++(*cursory));
	   VFDserial_SendChar('>');
	   VFDserial_SendChar(0x01);
	   return;}
}//--FIN AJUSTE PARAM PROD KEY DOWN-------------------------------------------------------------------------------------
void AjusteParamProdkeyRT(void){
unsigned char *cursorx,*cursory;
unsigned char 	phasefrac,phase;
	cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory;	
	if(*cursory==POSY6){
		procSensxDigitoRT(POSXAJUSPROD,POSY6,&producto2.Sensibilidad);
	    configModificado(AJUSTE_PARAMETRICO_DE_PRODUCTO);
		return;}
	if(*cursory==POSY8){
		phase=getCharsFromFloat(&phasefrac,producto2.fase);
		if(++phasefrac>9){
			phasefrac=0;
			if(++phase>179){
				phase=0;
				phasefrac=0;}}
		display_pushFIFOcOP_Phase_var(POSXAJUSPROD,POSY8);
		configModificado(AJUSTE_PARAMETRICO_DE_PRODUCTO);
		return;}
}//FIN AjusteParamProdkeyRT ---------------------------------------------------------------
void AjusteParamProdkeyLF(void){
unsigned char *cursorx,*cursory;
unsigned char 	phasefrac,phase;

	cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory;	
	if(*cursory==POSY6){	
	   procSensxDigitoLF(POSXAJUSPROD,POSY6,&producto2.Sensibilidad);
	   configModificado(AJUSTE_PARAMETRICO_DE_PRODUCTO);}
    if(*cursory==POSY8){
		   phase=getCharsFromFloat(&phasefrac,producto2.fase);
		   if(phasefrac!=0)
			   phasefrac--;
		   else{phasefrac=9;
				if(phase==0)
					phase=179;
				  else phase--;}
		   display_pushFIFOcOP_Phase_var(POSXAJUSPROD,POSY8);//fin contextobuffer 0
		   configModificado(AJUSTE_PARAMETRICO_DE_PRODUCTO);
	       producto2.fase=get_Float_from_Phase(phase,phasefrac);   
		   return;}
}//FIN  AjusteParamProdkeyLF----------------------------------------------------------------
void AjusteParamProdkeyEN(void){
//unsigned char a[5],*p;
unsigned char *cursory;
        cursory=&vfd.menu.cursory;   
	    switch(*cursory){
	    	case POSY2: /* INIZIAIZAR MEMORIA*/ break;
	    	case POSY4:                         break;
	    	case POSY6: procSensxDigitoEN(AjParamProd->editarSensFase,POSXAJUSPROD-8,0); 
	    	            break;//del case posy6
	    	case POSY8: procFasexDigitoEN(AjParamProd->editarSensFase,POSXAJUSPROD,POSY10);
						break;
			case POSY10: //  _display   pushFIFOcOP  BorrarContadores_var();
				        configModificado(AJUSTE_PARAMETRICO_DE_PRODUCTO);
						cambio_de_contexto(AJUSTE_PARAMETRICO_DE_PRODUCTO);
						AjParamProd->arg2=(unsigned char)RESET;//arg2=RESET;//se borraran los contadores
						break;
			case POSY12:cambio_de_contexto(PANTALLA_DDS); break;
			case POSY14: //Para Pasar a Ajustes Avanzados
//						menu.b.b.semMenuPendiente=TRUE;//HABILITAMOS  funcion en S.O de escape
//						displayBoxDestructor(ACTIVADO);//destruir y parar la barra de deteccion.
						//cambio_de_contexto(configModificacionController(AJUSTES_AVANZADOS,AJUSTE_PARAMETRICO_DE_PRODUCTO));
//						menu.contexto.Anterior=AJUSTE_PARAMETRICO_DE_PRODUCTO;
						cambio_de_contexto(AJUSTES_AVANZADOS);
						break;
			case POSY0:cambio_de_contexto(PORTAL_INICIO);
			        	break;
			default: //__asm(Halt);
			          errorCritico("Error en AjParamProd-Enter");
					  exit(1);
			         }//debug error de diseño se softwre
return;}// FIN  AjusteParamProdto  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* FIN  AjusteParamProd ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


//*************************************************************************************
void AjustedeSistemakeyUP(void){
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
        else 
        	if(*cursory==POSY4){
        		VFDposicion(*cursorx,*cursory); 
                VFDserial_SendChar(' ');
                *cursorx=POSXESQ235;*cursory=POSY0; //xpos=POSXESQ235
                VFDposicion(*cursorx,*cursory);
                VFDserial_SendChar('>');
                VFDserial_SendChar('X');  }
return;}
void AjustedeSistemakeyRT(void){
return;}	 
void AjustedeSistemakeyLF(void){
	return;}
void AjustedeSistemakeyDN(void){
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
	     else{
	 	 		 if(*cursory<POSY14){
	 	 			 switch(vfd.menu.contexto.control){ //Autor=3
	 	 				 case 1: /* fall through */
	 	 				 case 2:return;break;
	 	 				 case 3:/* fall through */
	 	 				 case 4:if(*cursory==POSY12){
	 	 					         return;break;}/* fall through */	
	 	 				 case 5:VFDposicion(*cursorx,*cursory);
		 	 			 	 	VFDserial_SendChar(' ');
		 	 			        ++(*cursory);
		 	 			        VFDposicion(*cursorx,++(*cursory));
		 	 			        VFDserial_SendChar('>');/* fall through */
	 	 				 default: return;break;
	 	 			 }}}//fin switch, if, else
return;}
void AjustedeSistemakeyEN(void){
unsigned char *cursorx,*cursory;
	cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory;
	if(*cursory==POSY2){/*);ret;*/ return;}
	if(*cursory==POSY4){ cambio_de_contexto( MENU_ADMINISTRATIVO); return;}//-------------M8:poner el contexto al que se quiere entrar
	if(*cursory==POSY6){ cambio_de_contexto(AJUSTE_DE_VIBRACION);  return;}
	if(*cursory==POSY8){ cambio_de_contexto(CONFIGURAR_ENTRADAS_DE_SISTEMA);
	
	                           /* *(ConfEntSyst->cursorAnterior)=POSY0;*/ //<<--- PONER ESTE CUANDO SE HAGA EL MENU
							   
							   return;}
	if(*cursory==POSY10){cambio_de_contexto(CONTROL_DE_FRECUENCIA);return;}
	if(*cursory==POSY12){cambio_de_contexto(ID_COMUNICACIONES);    return;}
	if(*cursory==POSY14){cambio_de_contexto(INGENIERIA_GRACIDA);   return;}
	if(*cursory==POSY0){ cambio_de_contexto(PORTAL_INICIO);	      return;}	        
return;  }//fin AjustedeSistemakeyEN
/* fin AjustedeSistemakeyDN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * AjustedeSistemakeyDN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


void MenuInformacionUsuariokeyUP(void){
unsigned char *cursorx,*cursory;
		cursorx=&vfd.menu.cursorx;
		cursory=&vfd.menu.cursory;	
	if(*cursory==POSY2){//PRIMERA POSICION DESPUES DE LA X    
		   VFDposicion(POSX0,POSY2);
		   VFDserial_SendChar(' ');*cursory=POSY0;
		   VFDposicion(POSXESQUINA,*cursory);
		   VFDserial_SendChar('>');VFDserial_SendChar('X');
		   return;}//posicion primera
		 if(*cursory==POSY0) return;
		 if(*cursory<(POSY14+1)){
		   VFDposicion(POSX0,*cursory); 
		   VFDserial_SendChar(' ');--(*cursory);
		   VFDposicion(POSX0,--(*cursory));
		   VFDserial_SendChar('>'); return;}
}//fin MenuInformacionUsuariokeyUP -------------------
void MenuInformacionUsuariokeyRT(void){return;} 
void MenuInformacionUsuariokeyLF(void){return;}
void MenuInformacionUsuariokeyDN(void){
unsigned char *cursorx,*cursory;
		cursorx=&vfd.menu.cursorx;
		cursory=&vfd.menu.cursory;
	if(*cursory==POSY0){//PRIMERA POSICION DESPUES DE LA X
		   VFDposicion(POSXESQUINA,POSY0);
		   VFDserial_SendChar(' ');VFDserial_SendChar('x');
		   *cursorx=POSX0;*cursory=POSY2;
		   VFDposicion(*cursorx,*cursory);
		   VFDserial_SendChar('>'); return;}
		 if(*cursory==POSY14){//PRIMERA POSICION DESPUES DE LA X
		   return;}
		 if(*cursory<POSY14){
			VFDposicion(POSX0,*cursory);
			VFDserial_SendChar(' ');
			*cursorx=POSX0;++(*cursory);
			VFDposicion(*cursorx,++(*cursory));
			VFDserial_SendChar('>'); return;}
}//fin MenuInformacionUsuariokeyDN----------------------------------------
void MenuInformacionUsuariokeyEN(void){
unsigned char *cursorx,*cursory;
unsigned char k;
		cursorx=&vfd.menu.cursorx;
		cursory=&vfd.menu.cursory;	
	if(*cursory==POSY2) {/*cambio_de_contexto(HACER_PRUEBA_DE_RUIDO;*/  return;}
	if(*cursory==POSY4) {*(MenuInfoUser->ResetDisplayNum)=0; //gpoc.igpoc0=0;//resetea las var de despliegue de numeros
		                cambio_de_contexto(MEDIDAS_DE_VOLTAJE);  return;}
	if(*cursory==POSY6) {/*cambio_de_contexto(AJUSTE_DE_PRODUCTOINFO); */ return;}
	if(*cursory==POSY8) {cambio_de_contexto(TIEMPO_DE_RECHAZOINFO);  return;}
	if(*cursory==POSY10){cambio_de_contexto(AJUSTE_SISTEMA_ENTRADAS);  return;}
	if(*cursory==POSY12){cambio_de_contexto(ID_MAQUINA);  return;}
	if(*cursory==POSY14){DisplayCuentaProducto();  return;}
	if(*cursory==POSY0) {switch(vfd.menu.contexto.peek(1,&k)){
							case AJUSTE_DE_SISTEMA:cambio_de_contexto(k);break;
							case MENU_INSIGHT:cambio_de_contexto(k);break;
							default:cambio_de_contexto(PORTAL_INICIO);break;}}
}//fin MenuInformacionUsuariokeyEN---------------------------------
/* FIN  MenuInformacionUsuariokeyEN++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * */



/**  TEXT PROCESSSOR*******************************************************************************++*****/
void TextoProcessorkeyUP(void){
unsigned char *cursorx,*cursory;
unsigned char a[]= ">SI No";

    cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory;    	
	monitorInvalidPassword();
	if(*cursory==POSY0)
		return;//EN ESTE CONTEXTO NO USAMOS arg0 PORQUE guarda el DATOS
	if(*cursory==POSY6){//DEL menu anterior que se va usar en el menu que viene
		VFDposicion(*cursorx,*cursory);
		VFDserial_SendChar(' ');
		*cursorx=POSX_TEXT_PROCS_OK;*cursory=POSY0;
		VFDposicion(*cursorx,*cursory);
		//VFDserial_SendChar('>');
		VFDserial_SendBlock(&a[0],sizeof(a));
		return;}
	if(*cursory>POSY6)
	  if(*cursory<(POSY14+1)){
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendChar(' ');
			*cursory-=2;
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendChar('>');
			return;}
}//FIN TextoProcessorkeyUP-----------------------------------------------------------------------
void TextoProcessorkeyRT(void){
unsigned char *cursorx,*cursory;
cursorx=&vfd.menu.cursorx;
cursory=&vfd.menu.cursory;
unsigned char a[]= "Si >NO";
unsigned char b[]= ">SI No";

	monitorInvalidPassword();
   if(*cursory==POSY0){
		if(*cursorx==POSX_TEXT_PROCS_OK){
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendBlock(&a[0],sizeof(a));//VFDserial_SendChar(' ');
			*cursorx=POSX_TEXT_PROCS_X;
			//VFDposicion(*cursorx,*cursory);
			//VFDserial_SendChar('>');VFDserial_SendChar('X');
			return;}
		if(*cursorx==POSX_TEXT_PROCS_X){
			VFDposicion(POSX_TEXT_PROCS_OK,*cursory);
			VFDserial_SendBlock(&b[0],sizeof(b));//VFDserial_SendChar(' ');VFDserial_SendChar('x');
			*cursorx=POSX_TEXT_PROCS_OK;
			//VFDposicion(*cursorx,*cursory);VFDserial_SendChar('>');
			return;}}
	if(*cursory==POSY14)
		if(*cursorx==POSX_COL3){
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendChar(' ');
			*cursorx=POSX_COL7;
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendChar('>');
			return;}
	 if(*cursory>POSY4){
		   VFDposicion(*cursorx,*cursory);
		   VFDserial_SendChar(' ');
		   *cursorx=getColTextProc(RIGHT);
		   VFDposicion(*cursorx,*cursory);
		   VFDserial_SendChar('>');
		   return;}        
}//FIN TextoProcessorkeyRT------------------------------------------------------
void TextoProcessorkeyLF(void){
unsigned char *cursorx,*cursory;
cursorx=&vfd.menu.cursorx;
cursory=&vfd.menu.cursory;
unsigned char a[]= "Si >NO";
unsigned char b[]= ">SI No";

	monitorInvalidPassword();	
  if(*cursory==POSY0){
	 if(*cursorx==POSX_TEXT_PROCS_OK){
		   VFDposicion(*cursorx,*cursory);
		   VFDserial_SendBlock(&a[0],sizeof(a));
 		   *cursorx=POSX_TEXT_PROCS_X;
			 return;}
	  if(*cursorx==POSX_TEXT_PROCS_X){
	    	VFDposicion(POSX_TEXT_PROCS_OK,*cursory);
			VFDserial_SendBlock(&b[0],sizeof(b));
		    *cursorx=POSX_TEXT_PROCS_OK;
			return;}}
	   if(*cursory==POSY14)
	   if(*cursorx==POSX_COL7){
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendChar(' ');
		    *cursorx=POSX_COL3;
			VFDposicion(*cursorx,*cursory);
			VFDserial_SendChar('>');
		   return;}
		if(*cursory>POSY4){
			VFDposicion(*cursorx,*cursory);
	   	    VFDserial_SendChar(' ');
		    *cursorx=getColTextProc(LEFT);
		    VFDposicion(*cursorx,*cursory);
		    VFDserial_SendChar('>');}
}//FIN TextoProcessorkeyLF -------------------------------------------------------------
void TextoProcessorkeyDN(void){
unsigned char *cursorx,*cursory;
unsigned char a[]= "Si  No";
    cursorx=&vfd.menu.cursorx;
    cursory=&vfd.menu.cursory;
	monitorInvalidPassword();
	if(*cursory==POSY0){
		VFDposicion(POSX_TEXT_PROCS_OK,*cursory);
		VFDserial_SendBlock(&a[0],sizeof(a));
		*cursorx=(unsigned char)POSX_COL1;
		*cursory=(unsigned char)POSY6;
		VFDposicion(*cursorx,*cursory);
		VFDserial_SendChar('>');
		return;}
	if(*cursory==POSY6){
		VFDposicion(*cursorx,*cursory);
		VFDserial_SendChar(' ');
		*cursory+=2;
		VFDposicion(*cursorx,*cursory);
	    VFDserial_SendChar('>');
	    return;}
	if(*cursory==POSY12){
		switch(*cursorx){
			case POSX_COL4:return;
			case POSX_COL5:return;
			case POSX_COL6:return;
			default:break;}}
	if(*cursory>POSY6){if(*cursory==POSY14)
							return;
						VFDposicion(*cursorx,*cursory);
						VFDserial_SendChar(' ');
						*cursory+=2;
						VFDposicion(*cursorx,*cursory);
						VFDserial_SendChar('>');
						return;}
}//fin  TextoProcessorkeyDN----------------------------------------------------
void TextoProcessorkeyEN(void){
unsigned char a[]= "Contrasena invalida",*p=0,c;
unsigned char k,v;
unsigned char *cursorx,*cursory,Level;
    cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory; 
	if(*cursory==POSY0){//cambio_de_contexto(NuevoProducto.menuPadre;
		if(*cursorx==POSX_TEXT_PROCS_OK){//aceptamos el nombre
			switch(vfd.menu.contexto.control){
				case NUEVO_PRODUCTO:
					    MenuTextProc->igxc0=NOMBRE_PRODUCTO_SIZE-1; //->igxc0=NOMBRE_PRODUCTO_SIZE-1;
						for(k=MenuTextProc->igxc0;k>0;k--)//insertamos el NAME_INIT
							vfd.Text[k]=vfd.Text[k-1];
						vfd.Text[0]=NAME_INIT;//insertar la clave de correcto
                        vaciar_A2B(&vfd.Text[0],&producto2.name[0],0,sizeof(vfd.Text)-1);
						cambio_de_contexto(AJUSTE_DE_PRODUCTO_MODE); //pasamos al siguiente screen AJUSTE DE PRODUCTO MODE
						return;
						break;//fin nuevo producto
				case NOMBRE_PRODUCTO:
					 switch(vfd.menu.contexto.peek(1,&v)){
					   case NUEVO_PRODUCTO:swapArrays(&producto2.name[0],&vfd.Text[0],NOMBRE_PRODUCTO_SIZE);//el nuevo nombre a name y el viejo nombre a text para guardarlo en caso de error o cambio de par
						                   cambio_de_contexto(AJUSTES_AVANZADOS);
					                       break;
					   case AJUSTE_DE_PRODUCTO:if(vfd.menu.contexto.Modificado==NOMBRE_PRODUCTO){
													swapArrays(&producto2.name[0],&vfd.Text[0],NOMBRE_PRODUCTO_SIZE);//el nuevo nombre a name y el viejo nombre a text para guardarlo en caso de error o cambio de parecer
													cleanArrayName(&producto2.name[0],sizeof(producto2.name),0,0);
													cleanArrayName(&vfd.Text[0],sizeof(vfd.Text),0,0);
													cambio_de_contexto(AJUSTES_AVANZADOS);}
											   break;
					   case AJUSTE_PARAMETRICO_DE_PRODUCTO://venimos de ajuste parametrico de producto y de ajustes avanzados
											   swapArrays(&producto2.name[0],&vfd.Text[0],NOMBRE_PRODUCTO_SIZE);//el nuevo nombre a name y el viejo nombre a text para guardarlo en caso de error o cambio de parecer
											   cleanArrayName(&producto2.name[0],sizeof(producto2.name),0,0);
											   cleanArrayName(&vfd.Text[0],sizeof(vfd.Text),0,0);
											   cambio_de_contexto(AJUSTES_AVANZADOS);
											   break;
					   default:break;}
			           break;//FIN  nombre producto PROD_VAR_SIZE
				case CONTROL_PASSWORD:
					    if(MenuTextProc->arg2==CONFIRMAR){//es confirmacion de contraseña nueva
					    	MenuTextProc->arg2=0;//arg2 se limpia confirmacion
					    	if(compareString(&vfd.Text[0],&MenuTextProc->igxc5[0],NOMBRE_PRODUCTO_SIZE)){//se confirmo bien
						      		   setPasswords(MenuTextProc->arg0,&vfd.Text[0]);
					    		  vfd.menu.contexto.Actual=AJUSTE_DE_PRODUCTO;//sera el padre
					    	 	  cambio_de_contexto(CONTROL_PASSWORD);}
					    	else{//en la confirmacion se puso mal la contraseña
					    		  MenuTextProc->igxc0=0;//iniciamos desplegando mayuculas
								  MenuTextProc->igxc1=0;//indice del arreglo del Texto. 
								  MenuTextProc->igxc4=0;//no ha habido escritura de ascii
								  //arg0=0;//gurada el level 1 a 4 que quiere modificarse
								  MenuTextProc->arg1=0;//error de  valida password
								  MenuTextProc->arg2=0;//para saber si estamo en confirmcion
								  displayTextoProcessor();}} //se reinicia el text-procesor
					    else{//vamos a poner una nueva password
							if(validatePasswords(p,&vfd.Text[0])){//validamos la password
							      saveTextBuffer(&vfd.Text[0]);//save Text buffer
								  MenuTextProc->arg2=CONFIRMAR; //configurar arg2 para poner confirmar pass
								  displayTextoProcessor();} //se reinicia el text-procesor
							else {//anuncio de que es l password invalida
	        	    		      VFDposicion(0,POSY2);
	        	    		      VFDserial_SendBlock(&a[0],sizeof(a)); 
 		                          MenuTextProc->arg1=ERROR_PASS;}}//arg0 esta ocupado
					    break;//fin CONTROL_PASSWORD
				case SUPERVISOR:vfd.menu.contexto.control=0;
				                if(validatePassword(&Level,&vfd.Text[0])){
                                     cambio_contexto(vfd.menu.contexto.destino);
									 setNivelAcceso(Level);}//ejecuta el cambio de contexto
				                break;
				default:usleep(1);
				  		mensOK("Error:TextoProcessorkeyEN ",32);
				        break;}
            return;}//ACEPTAMOS NOMBRE;fin OK cursorx==POSX_TEXT_PROCS_OK---------
       if(*cursorx==POSX_TEXT_PROCS_X){//NO ACEPTAMOS EL NOMBRE--------------------
		   switch(vfd.menu.contexto.control){
			    case NUEVO_PRODUCTO:   cambio_de_contexto(MENU_INSIGHT);
			                           return;break;
			    case NOMBRE_PRODUCTO:
			    	      switch(vfd.menu.contexto.peek(1,&v)){//contexto padre
							  case AJUSTE_PARAMETRICO_DE_PRODUCTO:
										 MenuTextProc->arg5=0;//NO se ha modificado el nombre del producto
										 cambio_de_contexto(AJUSTES_AVANZADOS);                                                     
										 break;
							  default:break;}					 
						  break;
			    case CONTROL_PASSWORD:MenuTextProc->igxc0=0;//iniciamos desplegando mayuculas
			                          MenuTextProc->igxc1=0;//indice del arreglo del Texto. 
			                          MenuTextProc->igxc4=0;//no ha habido escritura de ascii
 	  	  		                      MenuTextProc->arg0=0;//se usara en la validacion de password mismo contexto
 	  	  		                      MenuTextProc->arg1=0;//error de  valida password
 	  	  		                      MenuTextProc->arg2=0;//importante
			    	                  cambio_de_contexto(CONTROL_PASSWORD);
			                          return;break;
			    case SUPERVISOR:cambio_de_contexto(vfd.menu.contexto.peek(1,&v));
			    	            break;
			   default:return; break;}
   		      return;}//fin cursorx==POSX_TEXT_PROCS_X
	 return;}// fin ==POSY0--------------------------------------------------------------------------
 if(*cursory>POSY0){
	 monitorInvalidPassword();  
     if(vfd.menu.contexto.control==NOMBRE_PRODUCTO){
    	    TextProcessorSpecial();
    	    return;}
	 if(*cursory==POSY14){//------------------------------------------------------------------
		if(*cursorx==POSX_COL1){
			   if(MenuTextProc->igxc0==MAYUSCULAS)
				   return;
			   else{//esta activa alguna otra pantalla que no es mayusculas
					  VFDposicion(*cursorx,*cursory);
					  VFDserial_SendChar(' ');//limpiar el cursor actual
					  displayTextoProcessorMayusculas();
					  *cursorx=POSX_COL1;*cursory=POSY14;
					  VFDposicion(*cursorx,*cursory);
					  VFDserial_SendChar('>');
					  MenuTextProc->igxc0=MAYUSCULAS;
					  return;}return;}//fin col1
		if(*cursorx==POSX_COL2){
			  if(MenuTextProc->igxc0==MINUSCULAS)
				  return;
			  else{
				  VFDposicion(*cursorx,*cursory);
				  VFDserial_SendChar(' ');
				  displayTextoProcessorMinusculas();
			  *cursorx=POSX_COL2;*cursory=POSY14;
			  VFDposicion(*cursorx,*cursory);
			  VFDserial_SendChar('>');
			  MenuTextProc->igxc0=MINUSCULAS;
				  return;} return;}
		if(*cursorx==POSX_COL3){
			  if(MenuTextProc->igxc0==SYMBOL)
				  return;
			  else{
				  VFDposicion(*cursorx,*cursory);
				  VFDserial_SendChar(' ');
				  displayTextoProcessorSymbol();
				  *cursorx=POSX_COL3;*cursory=POSY14;
				  VFDposicion(*cursorx,*cursory);
					  VFDserial_SendChar('>');
					  MenuTextProc->igxc0=SYMBOL;
				 return;}return;}
		if(*cursorx==POSX_COL7){
			  if((MenuTextProc->igxc1)!=0){
				if(MenuTextProc->igxc1==1)
				   return;
				if(MenuTextProc->igxc4==DONE)
				(MenuTextProc->igxc1)-=1;
				VFDposicion((unsigned short)((MenuTextProc->igxc1)*8),POSY4);//mover el cursor uno a la izquierda
				VFDserial_SendChar(' ');//borramos el   ^
				VFDposicion((unsigned short)((--(MenuTextProc->igxc1))*8),POSY4);//mover el cursor uno a la izquierda
				VFDserial_SendChar(FX);//escribimos el ^ uno antes de donde estaba
				MenuTextProc->igxc4=VERDE1;//indica que hubo atraso del cursor
				return;}
	         return;}//fin POSX_COL7
		if(*cursorx==POSX_COL8){//mueve cursor a la derecha
			if(MenuTextProc->igxc1<(NOMBRE_PRODUCTO_SIZE-1)){//indice del array
			   if(MenuTextProc->igxc4==DONE)
					(MenuTextProc->igxc1)-=1;
			   VFDposicion((unsigned short)((MenuTextProc->igxc1)*8),POSY4);
			   VFDserial_SendChar(' ');//borramos el   ^
			   VFDposicion((unsigned short)((++(MenuTextProc->igxc1))*8),POSY4);//mover el cursor uno a la derecha
			   VFDserial_SendChar(FX);//escribimos el ^ uno antes de donde estaba
			   if(isNumLetter(vfd.Text[MenuTextProc->igxc1])==FALSE)
					 vfd.Text[MenuTextProc->igxc1]=' ';
			   MenuTextProc->igxc4=VERDE1;//indica que hubo adelanto de cursor
		   return;}return;}//FIN POSX_COL8
		if(*cursorx==POSX_COL9){//agrega espacio
			if(MenuTextProc->igxc4==DONE)
				 (MenuTextProc->igxc1)-=1;
			if(MenuTextProc->igxc1<=(NOMBRE_PRODUCTO_SIZE-1)){   //indice de l array
			  TextInsertSpace(MenuTextProc->igxc1);
			  DisplayNewTextProc();
			 MenuTextProc->igxc4=VERDE1;//indiCa que hubo un insert Space
		   return;}return;}
		if(*cursorx==POSX_COL10){
			 if(MenuTextProc->igxc1==0)
				 return;
			 if((MenuTextProc->igxc4==DONE)&&(MenuTextProc->igxc1==1))//fix a bug
				 return;
			 if(MenuTextProc->igxc4==DONE)
				 (MenuTextProc->igxc1)-=1;
			 MenuTextProc->arg5=CAMBIAR;//se ha modificado el nombre del producto
			 c=TextBackSpace(MenuTextProc->igxc1);//revisr esta funcion
			 DisplayNewTextProc();
			 if((c>1)&&(c!=MenuTextProc->igxc1)){
				VFDposicion((unsigned short)((MenuTextProc->igxc1)*8),POSY4);
				VFDserial_SendChar(' ');
				MenuTextProc->igxc1=c;
				VFDposicion((unsigned short)((MenuTextProc->igxc1)*8),POSY4);
				VFDserial_SendChar(FX);//escribimos el ^ uno antes de donde estaba
				MenuTextProc->igxc4=VERDE1;//india que hubo un back Space    
				return;}
			 else{return;}}
	 return;} //fin POSY14---------------------------------------------------------------------------------------------------------   
	if(MenuTextProc->igxc1<NOMBRE_PRODUCTO_SIZE){//Escribir algun ascii en pantalla
		MenuTextProc->arg5=CAMBIAR;//se ha modificado el nombre del producto
		vfd.Text[MenuTextProc->igxc1]=getAscii(*cursorx,*cursory,MenuTextProc->igxc0);//guardamos el ascii seleccionado
		//Text[MenuTextProc->igxc1+1]=0;//siguiente es cero como limite
		if(vfd.menu.contexto.final==NOMBRE_PRODUCTO){
			VFDposicion((unsigned short)((MenuTextProc->igxc1-1)*8),POSY2);//posicion del cursor del nombre
			VFDserial_SendChar(vfd.Text[MenuTextProc->igxc1]);
			if(MenuTextProc->igxc1!=(NOMBRE_PRODUCTO_SIZE-1)){
					if(MenuTextProc->igxc1!=0){//ess el indice del Text[]
						VFDposicion((unsigned short)((MenuTextProc->igxc1-1)*8),POSY4);
						VFDserial_SendChar(' ');}
					VFDposicion((unsigned short)((MenuTextProc->igxc1)*8),POSY4);
					VFDserial_SendChar(FX);}}
		else{VFDposicion((unsigned char)((MenuTextProc->igxc1)*8),POSY2);//posicion del cursor del nombre
			if((vfd.menu.contexto.final==CONTROL_PASSWORD)||(vfd.menu.contexto.permisos==SUPERVISOR)){
					VFDserial_SendChar(vfd.Text[MenuTextProc->igxc1]);//VFDserial_SendChar('*');
					VFDserial_SendChar_Asterisco((MenuTextProc->igxc1)*8);}
				else	  
					VFDserial_SendChar(vfd.Text[MenuTextProc->igxc1]);
				if(MenuTextProc->igxc1!=0){//ess el indice del Text[]
					VFDposicion((unsigned short)((MenuTextProc->igxc1-1)*8),POSY4);
					VFDserial_SendChar(' ');}
				VFDposicion((unsigned short)((MenuTextProc->igxc1)*8),POSY4);
				VFDserial_SendChar(FX);}
		MenuTextProc->igxc1++;//lo desplegamos y apuntamos al que sigue indice de Text
		MenuTextProc->igxc4=DONE;}//ha habido una escritua de ascii en pantalla
     return;}//fin Mas alla de POSY0 ------------------------------------------------------------------------------------------
          
 }//FIN DE TextoProcessorkeyEN-------------------------------------------------------------------------------------------------







/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/
/*******************************************************************************************************+*/



/*  resta o suma a un digto a la variable de sensibilidad o phase*/
/* Metodo exclusivo de Ajustes PArametricos de Producto por la vriable global */
void operacionVariable(unsigned char posx,unsigned short int y,unsigned char igxm0,unsigned char op){
unsigned char a[5],*p,i,b[6];
//typedef unsigned short int usint;
unsigned char phase,phasefrac,*cursorx,*cursory;
	 p=&a[0];
	 cursorx=&vfd.menu.cursorx;
	 cursory=&vfd.menu.cursory;
	 switch(y){
	  case POSY6:
	  case POSY2:		 
			  operacionUShortInt(&producto2.Sensibilidad,igxm0,op);//opera en el digito indicado
			  *cursorx=posx;//+(8*(5-igxm0));//  igxm
			  VFDposicion(*cursorx,*cursory);
			  getCharsFromUINT_var(p,producto2.Sensibilidad);
			  switch(igxm0){ //VFDserial_SendChar((*(p+5-igxm0))+'0');
				  case 5:b[0]='>';
						 b[1]=a[0]+0x30;
						 b[2]=a[1]+0x30;
						 b[3]=a[2]+0x30;
						 b[4]=a[3]+0x30;
						 b[5]=a[4]+0x30;
				         break;
				  case 4:b[0]=a[0]+0x30;
				         b[1]='>';
				         b[2]=a[1]+0x30;
				         b[3]=a[2]+0x30;
				         b[4]=a[3]+0x30;
				         b[5]=a[4]+0x30;
				         break;
				  case 3:b[0]=a[0]+0x30;
						 b[1]=a[1]+0x30;
						 b[2]='>';
						 b[3]=a[2]+0x30;
						 b[4]=a[3]+0x30;
						 b[5]=a[4]+0x30;
						 break;
				  case 2:b[0]=a[0]+0x30;
						 b[1]=a[1]+0x30;
						 b[2]=a[2]+0x30;
						 b[3]='>';
						 b[4]=a[3]+0x30;
						 b[5]=a[4]+0x30;
						 break;
				  case 1:b[0]=a[0]+0x30;
						 b[1]=a[1]+0x30;
						 b[2]=a[2]+0x30;
						 b[3]=a[3]+0x30;
						 b[4]='>';
						 b[5]=a[4]+0x30;
						 break; 
				  default:break;}
			for(i=0;i<6;i++)
				VFDserial_SendChar(b[i]);
		    break; //fin de POSY6 POSY2
	 case POSY8:
     case POSY4: 
		      phase=getCharsFromFloat(&phasefrac,producto2.phase);
			  if(phasefrac>9)
				  phasefrac=0;
			  getASCII_from_Fase(&a[0],phase,phasefrac);
			  //Deteccion.Phase=get_Float_Fase(&a[0]);
			  operacion_ASCII_Phase2(igxm0,op,&a[0]);
			  producto2.phase=get_Float_From_ASCII(&a[0]);
			  //configModificado(AJUSTE_PARAMETRICO_DE_PRODUCTO);
//			  display_Phase_DDS(posx+8,y,&a[0]);
			  setASCII_to_Fase(&a[0],&phase,&phasefrac);
			  producto2.phase=get_Float_from_Phase(phase,phasefrac);
			  //__asm(nop);//for debug purpuses
			  break;// FIN POS Y8 posy4
	  default:break;}
}//fin operacionVariable-------------------------------------------------------------

unsigned char procSensxDigitoRT(unsigned char posx,unsigned char posy,unsigned short int *Sens){
	if((*Sens)>=32000)
		 return FALSE;
	else{++(*Sens);} 
	BarraDet_displayUINT_var(posx,posy,Sens);//displayUINT_var(POSXCFNUM,POSY2,&Sensibilidad,NONE);	
return 1;	
}//fin ---procSensxDigitoRT--------------------------------------------
