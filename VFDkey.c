#include "VFDkey.h"
#include "VFDmenu.h"
#include "VFDisplay.h"
#include "queue.h"
#include "VFD.h"
#include "system.h"
#include "maths.h"
#include "strings.h"


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

	if(*(AjParamProd->editarSensFase)>0){//->igxc0>0){//esta seleccionado cambiar por numero
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

//*****************************************************************************************
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
unsigned char K;
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
	if(*cursory==POSY0) {vfd.menu.contexto.peek(1,&k);
	                     switch(k){
							case AJUSTE_DE_SISTEMA:cambio_de_contexto(k);break;
							case MENU_INSIGHT:cambio_de_contexto(k);break;
							default:cambio_de_contexto(PORTAL_INICIO);break;}}
}//fin MenuInformacionUsuariokeyEN---------------------------------
/* FIN  MenuInformacionUsuariokeyEN++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * */







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
	else  ++(*Sens); 
	BarraDet_displayUINT_var(posx,posy,Sens);//displayUINT_var(POSXCFNUM,POSY2,&Sensibilidad,NONE);	
return 1;	
}//fin ---procSensxDigitoRT--------------------------------------------
