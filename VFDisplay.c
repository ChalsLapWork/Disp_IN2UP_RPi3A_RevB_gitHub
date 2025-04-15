#include "system.h"
#include "queue.h"
#include "VFD.h"
#include "errorController.h"
#include <stdio.h>
#include "VFDmenu.h"
#include "BarraDisplay.h"
#include <stdint.h>
#include <stdbool.h>
#include "strings.h"
#include "VFDisplay.h"
#include <stdlib.h>
#include <unistd.h>
#include "Memoria.h"

extern struct _DISPLAY_VFD_ vfd;
extern struct _PRODUCT1_ producto2;

/*funcion que nos da las coordenadas de las cajas en  y las cajas con pen=1 con, caja BOX_VACIA hasta 
 *  la 8,  y la caja BOX_LLENA es de la box=9 hasta box=17; */ 
void getBoxPattern(unsigned char box,unsigned char *mode,unsigned char *x1,unsigned char *y1,unsigned char *x2,unsigned char *y2){

 switch(vfd.menu.contexto.Actual){	
   case PORTAL_INICIO:
    	  switch(box){
			 case 1 : *x1=POS_X1_BOX3_PI;*y1=POS_Y1_BOX3_PI;*x2=POS_X2_BOX3_PI;*y2=POS_Y2_BOX3_PI;break;  
			 case 2 : *x1=POS_X1_BOX4_PI;*y1=POS_Y1_BOX4_PI;*x2=POS_X2_BOX4_PI;*y2=POS_Y2_BOX4_PI;break;
			 case 3 : *x1=POS_X1_BOX5_PI;*y1=POS_Y1_BOX5_PI;*x2=POS_X2_BOX5_PI;*y2=POS_Y2_BOX5_PI;break;
			 case 4 : *x1=POS_X1_BOX6_PI;*y1=POS_Y1_BOX6_PI;*x2=POS_X2_BOX6_PI;*y2=POS_Y2_BOX6_PI;break;
			 case 5 : *x1=POS_X1_BOX7_PI;*y1=POS_Y1_BOX7_PI;*x2=POS_X2_BOX7_PI;*y2=POS_Y2_BOX7_PI;break;
			 case 6 : *x1=POS_X1_BOX8_PI;*y1=POS_Y1_BOX8_PI;*x2=POS_X2_BOX8_PI;*y2=POS_Y2_BOX8_PI;break;
			 case 7 : *x1=POS_X1_BOX9_PI;*y1=POS_Y1_BOX9_PI;*x2=POS_X2_BOX9_PI;*y2=POS_Y2_BOX9_PI;break;
			 case 8 : *x1=POS_X1_BOX10_PI;*y1=POS_Y1_BOX10_PI;*x2=POS_X2_BOX10_PI;*y2=POS_Y2_BOX10_PI;break;
	   		 case 9 : *x1=POS_X1_BOX11_PI;*y1=POS_Y1_BOX11_PI;*x2=POS_X2_BOX11_PI;*y2=POS_Y2_BOX11_PI;break;
			 case 10: *x1=POS_X1_BOX12_PI;*y1=POS_Y1_BOX12_PI;*x2=POS_X2_BOX12_PI;*y2=POS_Y2_BOX12_PI;break;
			 case 11: *x1=POS_X1_BOX13_PI;*y1=POS_Y1_BOX13_PI;*x2=POS_X2_BOX13_PI;*y2=POS_Y2_BOX13_PI;break;
			 case 12: *x1=POS_X1_BOX14_PI;*y1=POS_Y1_BOX14_PI;*x2=POS_X2_BOX14_PI;*y2=POS_Y2_BOX14_PI;break;
			 case 13: *x1=POS_X1_BOX15_PI;*y1=POS_Y1_BOX15_PI;*x2=POS_X2_BOX15_PI;*y2=POS_Y2_BOX15_PI;break;
	         case 14: *x1=POS_X1_BOX16_PI;*y1=POS_Y1_BOX16_PI;*x2=POS_X2_BOX16_PI;*y2=POS_Y2_BOX16_PI;break;
			 case 15: *x1=POS_X1_BOX17_PI;*y1=POS_Y1_BOX17_PI;*x2=POS_X2_BOX17_PI;*y2=POS_Y2_BOX17_PI;break;
			 case 16: *x1=POS_X1_BOX18_PI;*y1=POS_Y1_BOX18_PI;*x2=POS_X2_BOX18_PI;*y2=POS_Y2_BOX18_PI;break;
			 case 17: *x1=POS_X1_BOX19_PI;*y1=POS_Y1_BOX19_PI;*x2=POS_X2_BOX19_PI;*y2=POS_Y2_BOX19_PI;break; 
			 default:*x1=POS_X1_BOX3_PI;*y1=POS_Y1_BOX3_PI;*x2=POS_X2_BOX3_PI;*y2=POS_Y2_BOX3_PI;
			         box=1;break;//iniciaiacion del box0
			 }//fin switch
	         if(box<9)
	        	 *mode=BOX_VACIA;
	         else *mode=BOX_LLENA;
	         break;// case PORTAL INICIO   Completado
    case AJUSTE_DE_VIBRACION:
        switch(box){
		 case 1 : *x1=POS_X1_BOX3_AV;*y1=POS_Y1_BOX3_AV;*x2=POS_X2_BOX3_AV;*y2=POS_Y2_BOX3_AV;break;  
		 case 2 : *x1=POS_X1_BOX4_AV;*y1=POS_Y1_BOX4_AV;*x2=POS_X2_BOX4_AV;*y2=POS_Y2_BOX4_AV;break;
		 case 3 : *x1=POS_X1_BOX5_AV;*y1=POS_Y1_BOX5_AV;*x2=POS_X2_BOX5_AV;*y2=POS_Y2_BOX5_AV;break;
		 case 4 : *x1=POS_X1_BOX6_AV;*y1=POS_Y1_BOX6_AV;*x2=POS_X2_BOX6_AV;*y2=POS_Y2_BOX6_AV;break;
		 case 5 : *x1=POS_X1_BOX7_AV;*y1=POS_Y1_BOX7_AV;*x2=POS_X2_BOX7_AV;*y2=POS_Y2_BOX7_AV;break;
		 case 6 : *x1=POS_X1_BOX8_AV;*y1=POS_Y1_BOX8_AV;*x2=POS_X2_BOX8_AV;*y2=POS_Y2_BOX8_AV;break;
		 case 7 : *x1=POS_X1_BOX9_AV;*y1=POS_Y1_BOX9_AV;*x2=POS_X2_BOX9_AV;*y2=POS_Y2_BOX9_AV;break;
		 case 8 : *x1=POS_X1_BOX10_AV;*y1=POS_Y1_BOX10_AV;*x2=POS_X2_BOX10_AV;*y2=POS_Y2_BOX10_AV;break;
   		 case 9 : *x1=POS_X1_BOX11_AV;*y1=POS_Y1_BOX11_AV;*x2=POS_X2_BOX11_AV;*y2=POS_Y2_BOX11_AV;break;
		 case 10: *x1=POS_X1_BOX12_AV;*y1=POS_Y1_BOX12_AV;*x2=POS_X2_BOX12_AV;*y2=POS_Y2_BOX12_AV;break;
		 case 11: *x1=POS_X1_BOX13_AV;*y1=POS_Y1_BOX13_AV;*x2=POS_X2_BOX13_AV;*y2=POS_Y2_BOX13_AV;break;
		 case 12: *x1=POS_X1_BOX14_AV;*y1=POS_Y1_BOX14_AV;*x2=POS_X2_BOX14_AV;*y2=POS_Y2_BOX14_AV;break;
		 case 13: *x1=POS_X1_BOX15_AV;*y1=POS_Y1_BOX15_AV;*x2=POS_X2_BOX15_AV;*y2=POS_Y2_BOX15_AV;break;
         case 14: *x1=POS_X1_BOX16_AV;*y1=POS_Y1_BOX16_AV;*x2=POS_X2_BOX16_AV;*y2=POS_Y2_BOX16_AV;break;
		 case 15: *x1=POS_X1_BOX17_AV;*y1=POS_Y1_BOX17_AV;*x2=POS_X2_BOX17_AV;*y2=POS_Y2_BOX17_AV;break;
		 case 16: *x1=POS_X1_BOX18_AV;*y1=POS_Y1_BOX18_AV;*x2=POS_X2_BOX18_AV;*y2=POS_Y2_BOX18_AV;break;
		 case 17: *x1=POS_X1_BOX19_AV;*y1=POS_Y1_BOX19_AV;*x2=POS_X2_BOX19_AV;*y2=POS_Y2_BOX19_AV;break; 
		 default:*x1=POS_X1_BOX3_AV;*y1=POS_Y1_BOX3_AV;*x2=POS_X2_BOX3_AV;*y2=POS_Y2_BOX3_AV;
		         box=1;break;//iniciaiacion del box0
		 }//fin switch
         if(box<9)
        	 *mode=BOX_VACIA;
         else *mode=BOX_LLENA;
       break;//  //fin AJUSTE DE VIBRACION
   case AJUSTE_PARAMETRICO_DE_PRODUCTO:
    		switch(box){
    				 case 1 : *x1=POS_X1_BOX3_AP;*y1=POS_Y1_BOX3_AP;*x2=POS_X2_BOX3_AP;*y2=POS_Y2_BOX3_AP;break;  
    				 case 2 : *x1=POS_X1_BOX4_AP;*y1=POS_Y1_BOX4_AP;*x2=POS_X2_BOX4_AP;*y2=POS_Y2_BOX4_AP;break;
    				 case 3 : *x1=POS_X1_BOX5_AP;*y1=POS_Y1_BOX5_AP;*x2=POS_X2_BOX5_AP;*y2=POS_Y2_BOX5_AP;break;
    				 case 4 : *x1=POS_X1_BOX6_AP;*y1=POS_Y1_BOX6_AP;*x2=POS_X2_BOX6_AP;*y2=POS_Y2_BOX6_AP;break;
    				 case 5 : *x1=POS_X1_BOX7_AP;*y1=POS_Y1_BOX7_AP;*x2=POS_X2_BOX7_AP;*y2=POS_Y2_BOX7_AP;break;
    				 case 6 : *x1=POS_X1_BOX8_AP;*y1=POS_Y1_BOX8_AP;*x2=POS_X2_BOX8_AP;*y2=POS_Y2_BOX8_AP;break;
    				 case 7 : *x1=POS_X1_BOX9_AP;*y1=POS_Y1_BOX9_AP;*x2=POS_X2_BOX9_AP;*y2=POS_Y2_BOX9_AP;break;
    				 case 8 : *x1=POS_X1_BOX10_AP;*y1=POS_Y1_BOX10_AP;*x2=POS_X2_BOX10_AP;*y2=POS_Y2_BOX10_AP;break;
    		   		 case 9 : *x1=POS_X1_BOX11_AP;*y1=POS_Y1_BOX11_AP;*x2=POS_X2_BOX11_AP;*y2=POS_Y2_BOX11_AP;break;
    				 case 10: *x1=POS_X1_BOX12_AP;*y1=POS_Y1_BOX12_AP;*x2=POS_X2_BOX12_AP;*y2=POS_Y2_BOX12_AP;break;
    				 case 11: *x1=POS_X1_BOX13_AP;*y1=POS_Y1_BOX13_AP;*x2=POS_X2_BOX13_AP;*y2=POS_Y2_BOX13_AP;break;
    				 case 12: *x1=POS_X1_BOX14_AP;*y1=POS_Y1_BOX14_AP;*x2=POS_X2_BOX14_AP;*y2=POS_Y2_BOX14_AP;break;
    				 case 13: *x1=POS_X1_BOX15_AP;*y1=POS_Y1_BOX15_AP;*x2=POS_X2_BOX15_AP;*y2=POS_Y2_BOX15_AP;break;
    		         case 14: *x1=POS_X1_BOX16_AP;*y1=POS_Y1_BOX16_AP;*x2=POS_X2_BOX16_AP;*y2=POS_Y2_BOX16_AP;break;
    				 case 15: *x1=POS_X1_BOX17_AP;*y1=POS_Y1_BOX17_AP;*x2=POS_X2_BOX17_AP;*y2=POS_Y2_BOX17_AP;break;
    				 case 16: *x1=POS_X1_BOX18_AP;*y1=POS_Y1_BOX18_AP;*x2=POS_X2_BOX18_AP;*y2=POS_Y2_BOX18_AP;break;
    				 case 17: *x1=POS_X1_BOX19_AP;*y1=POS_Y1_BOX19_AP;*x2=POS_X2_BOX19_AP;*y2=POS_Y2_BOX19_AP;break; 
    				 default:*x1=POS_X1_BOX3_AP;*y1=POS_Y1_BOX3_AP;*x2=POS_X2_BOX3_AP;*y2=POS_Y2_BOX3_AP;
    				         box=1;break;//iniciaiacion del box0
    				 }//fin switch
    		         if(box<9)
    		        	 *mode=BOX_VACIA;
    		         else *mode=BOX_LLENA;
    	   break;   //FIN ajuste PARAMETRICO DE PRODUCTO
   case PARAMETROS_DE_DETECCION:
      		switch(box){
      				 case 1 : *x1=POS_X1_BOX3_PD;*y1=POS_Y1_BOX3_PD;*x2=POS_X2_BOX3_PD;*y2=POS_Y2_BOX3_PD;break;  
       				 case 2 : *x1=POS_X1_BOX4_PD;*y1=POS_Y1_BOX4_PD;*x2=POS_X2_BOX4_PD;*y2=POS_Y2_BOX4_PD;break;
       				 case 3 : *x1=POS_X1_BOX5_PD;*y1=POS_Y1_BOX5_PD;*x2=POS_X2_BOX5_PD;*y2=POS_Y2_BOX5_PD;break;
       				 case 4 : *x1=POS_X1_BOX6_PD;*y1=POS_Y1_BOX6_PD;*x2=POS_X2_BOX6_PD;*y2=POS_Y2_BOX6_PD;break;
       				 case 5 : *x1=POS_X1_BOX7_PD;*y1=POS_Y1_BOX7_PD;*x2=POS_X2_BOX7_PD;*y2=POS_Y2_BOX7_PD;break;
       				 case 6 : *x1=POS_X1_BOX8_PD;*y1=POS_Y1_BOX8_PD;*x2=POS_X2_BOX8_PD;*y2=POS_Y2_BOX8_PD;break;
       				 case 7 : *x1=POS_X1_BOX9_PD;*y1=POS_Y1_BOX9_PD;*x2=POS_X2_BOX9_PD;*y2=POS_Y2_BOX9_PD;break;
       				 case 8 : *x1=POS_X1_BOX10_PD;*y1=POS_Y1_BOX10_PD;*x2=POS_X2_BOX10_PD;*y2=POS_Y2_BOX10_PD;break;
       		   		 case 9 : *x1=POS_X1_BOX11_PD;*y1=POS_Y1_BOX11_PD;*x2=POS_X2_BOX11_PD;*y2=POS_Y2_BOX11_PD;break;
       				 case 10: *x1=POS_X1_BOX12_PD;*y1=POS_Y1_BOX12_PD;*x2=POS_X2_BOX12_PD;*y2=POS_Y2_BOX12_PD;break;
       				 case 11: *x1=POS_X1_BOX13_PD;*y1=POS_Y1_BOX13_PD;*x2=POS_X2_BOX13_PD;*y2=POS_Y2_BOX13_PD;break;
       				 case 12: *x1=POS_X1_BOX14_PD;*y1=POS_Y1_BOX14_PD;*x2=POS_X2_BOX14_PD;*y2=POS_Y2_BOX14_PD;break;
       				 case 13: *x1=POS_X1_BOX15_PD;*y1=POS_Y1_BOX15_PD;*x2=POS_X2_BOX15_PD;*y2=POS_Y2_BOX15_PD;break;
       		         case 14: *x1=POS_X1_BOX16_PD;*y1=POS_Y1_BOX16_PD;*x2=POS_X2_BOX16_PD;*y2=POS_Y2_BOX16_PD;break;
       				 case 15: *x1=POS_X1_BOX17_PD;*y1=POS_Y1_BOX17_PD;*x2=POS_X2_BOX17_PD;*y2=POS_Y2_BOX17_PD;break;
       				 case 16: *x1=POS_X1_BOX18_PD;*y1=POS_Y1_BOX18_PD;*x2=POS_X2_BOX18_PD;*y2=POS_Y2_BOX18_PD;break;
       				 case 17: *x1=POS_X1_BOX19_PD;*y1=POS_Y1_BOX19_PD;*x2=POS_X2_BOX19_PD;*y2=POS_Y2_BOX19_PD;break; 
       				 default:*x1=POS_X1_BOX3_PD;*y1=POS_Y1_BOX3_PD;*x2=POS_X2_BOX3_PD;*y2=POS_Y2_BOX3_PD;
       				         box=1;break;//iniciaiacion del box0
       				 }//fin switch
       		         if(box<9)
       		        	 *mode=BOX_VACIA;
       		         else *mode=BOX_LLENA;
        	   break;   //FIN ajuste PARAMETRICO DE PRODUCTO
      default:break;
      }//fin PRIMER SWITCH           	   
      		    		     	  
}//fin de get patter of the boxes-------------------------------------------------------------------------------


//cambio de contexto funcion principal
/* detiene cualquier ejecucion en proceso del VFD
   y abre un hilo para pasarnos al contexto que se solicita*/
void cambio_de_contexto(unsigned char contexto){
     vfd.config.bits.MenuPendiente=TRUE;
	 vfd.menu.contexto.solicitaCambioA=contexto;
	 iniciar_Run_Menu();
}//FIN DE FUNCION maestra de cambio de contexto

/* Poner nivel de acceso a la variable*/
void setNivelAcceso(unsigned char level){

  switch(level){
     case '1':vfd.NIVEL_ACCESO=1;break;
	 case '2':vfd.NIVEL_ACCESO=2;break;
	 case '3':vfd.NIVEL_ACCESO=3;break;
	 case '4':vfd.NIVEL_ACCESO=4;break;
	 case '5':vfd.NIVEL_ACCESO=5;break;
	 default:vfd.NIVEL_ACCESO=1;break;}

}//fin poner nivel de acceso++++++++++++++++++++++++++++


/* Methodo sin sistema operativo
 *  Regresamos     Tamaño de memoria: 1 */	
unsigned char find_contexto_Siguiente(void){
unsigned char ret=0;     
bool normal[256]     ={[0 ... 255]=false};//menu sin password ni especial
bool passwd[256]	 ={[0 ... 255]=false};//menu que se necesita password
normal[PORTAL_INICIO]=true;
normal[MENU_INSIGHT]=true;
normal[AJUSTE_DE_SISTEMA]=true;
normal[PANTALLA_DDS]=true;
normal[INFORMACION_DE_USUARIO]=true;

passwd[AJUSTE_DE_PRODUCTO]=true;
passwd[AJUSTE_PARAMETRICO_DE_PRODUCTO]=true;

if(!vfd.config.bits.init_Menu){
	     vfd.menu.contexto.solicitaCambioA=PORTAL_INICIO;
         return PORTAL_INICIO;}
else{ 
   	  
   if(normal[vfd.menu.contexto.solicitaCambioA]){	  
	  vfd.menu.contexto.push(vfd.menu.contexto.Actual);
	  return vfd.menu.contexto.solicitaCambioA;}
   if(passwd[vfd.menu.contexto.solicitaCambioA]){
	    if((vfd.menu.contexto.Actual==TEXT_PROCESSOR)&&
		    (vfd.menu.contexto.control==SUPERVISOR)){
                 vfd.menu.contexto.solicitaCambioA=vfd.menu.contexto.destino;
				 vfd.menu.contexto.destino=0;
				 vfd.menu.contexto.control=0;
				 vfd.menu.contexto.permisos=vfd.NIVEL_ACCESO;
			     return vfd.menu.contexto.solicitaCambioA;}
		else{
             vfd.menu.contexto.push(vfd.menu.contexto.Actual);//de donde venimos
			 vfd.menu.contexto.destino=vfd.menu.contexto.solicitaCambioA;//a donde vamos
             vfd.menu.contexto.solicitaCambioA=TEXT_PROCESSOR;
			 //vfd.menu.contexto.permisos=SUPERVISOR;//contraseña
			 vfd.menu.contexto.control=SUPERVISOR;//como contraseña
			 return TEXT_PROCESSOR;
           }}//fin else menu que pide password-------------------------
     }//fin else ya esta hecho el init							
return ret;	 
}//FIN FIND CONTEXTO siguiente++++++++++++++++++++++++++++++++++++++++++++++

void display_Mov_Cursor_Down(void){
unsigned char *cursorx,*cursory;
 	cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory; 
	VFDposicion(*cursorx,*cursory);
	VFDserial_SendChar(' ');
	++(*cursory);
	VFDposicion(*cursorx,++(*cursory));
	VFDserial_SendChar('>');
}//fin mover el cursor para abajo uno++++++++++++++++++++++++++++


unsigned char validad_Nivel_Acceso(unsigned char level){
	 if(level<6)
	     return TRUE;
     else{log_mensaje("error"," Error de software, nivel de acceso invalido");
		  return FALSE;}		 
}//validar el nivel de acceso++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//Desplega datos usando el sistema operativo cuando hay una barra 
void BarraDet_displayUINT_var(unsigned char posx,unsigned char posy,unsigned short int *usint){
unsigned char a[5],*p,n=0;
//uword3 v;	

		p=&a[0];
		getCharsFromUINT_var(p,*usint);
		VFDposicion(posx,posy);		
		VFDserial_SendChar(*(p+0)+0x30); //decmil+0x30);
		VFDserial_SendChar(*(p+1)+0x30);//mil+0x30);
		VFDserial_SendChar(*(p+2)+0x30);//cent+0x30);
		VFDserial_SendChar(*(p+3)+0x30);//dec+0x30);
		VFDserial_SendChar(*(p+4)+0x30);//unidad+0x30);	  
	   // if(n>0)
	     //  __asm(HALT);//debug alto, error de ingenieria de software
}//fin BarraDet_displayUINT_var-------------------------------------------------------------


void display_pushFIFOcOP_Phase_var(unsigned char posx,unsigned char posy){//despliega la variable de phase en la posicion
unsigned char a[3];
unsigned char *p,phasefrac,phase; //para los valores ascii del numero entero
//uword2 v;

        p=&a[0];
        phase=getCharsFromFloat(&phasefrac,producto2.phase);
	    getUChar2Chars(p,phase,YES);//obtiene los tres char de un numero char unsigned
        if(phasefrac>9)
        	phasefrac=0;
       //if((posx>0)&&(posx<6))
	       // posx=digito2posicion(posx); //convierte numero de orden de digito en coordenadasx del display 
       posx=POSXAJUSPROD;
       VFDposicion(posx,posy);
       VFDserial_SendChar(a[0]);
       VFDserial_SendChar(a[1]);
       VFDserial_SendChar(a[2]);
       VFDserial_SendChar('.');
       VFDserial_SendChar(phasefrac+0x30);	   
       producto2.phase=get_Float_from_Phase(phase,phasefrac);   
}//display phase var---------------------------------------------------------------------------------------

void displayPhase_var(unsigned char posx,unsigned char posy){//despliega la variable de phase en la posicion
unsigned char a[3];
unsigned char *p,phase,phasefrac; //para los valores ascii del numero entero
        p=&a[0];
        phase=getCharsFromFloat(&phasefrac,producto2.phase);
	    getUChar2Chars(p,phase,YES);//obtiene los tres char de un numero char unsigned
        if(phasefrac>9)
        	phasefrac=0;
    	//debug    if(posx==0)
	        //controlador de errores aqui
       if((posx>0)&&(posx<6))
	        posx=digito2posicion(posx); //convierte numero de orden de digito en coordenadasx del display 
       VFDposicion(posx,posy);
       VFDserial_SendChar(a[0]);
       VFDserial_SendChar(a[1]);
       VFDserial_SendChar(a[2]);
	   VFDserial_SendChar('.');
       VFDserial_SendChar(phasefrac+0x30);	    
       producto2.phase=get_Float_from_Phase(phase,phasefrac);
}//display phase var-----------------------------------------------------------------------------
	
//despliega la Sensibilidad y la Altura  en la posicion deseada
void displayUINT_var(unsigned char posx,unsigned char posy,unsigned short int *pn,unsigned char operacion){
	unsigned char a[5],*p;
           p=&a[0];
          if(operacion==RESTAR){
               if(*pn==0)
                    *pn=32000;
               else *pn-=1;}
          if(operacion==SUMAR){
                if(*pn>31999)
  	                   *pn=0;
                else  *pn+=1;}
           getCharsFromUINT_var(p,*pn);
	       display5UChars(posx,posy,p);
}// fin display sensibilidad variable-----------------------------------------------
	
void display5UChars(unsigned char posx,unsigned char posy,unsigned char *p){
	     VFDposicion(posx,posy);  
	     VFDserial_SendChar(*(p+0)+0x30); //decmil+0x30);
	     VFDserial_SendChar(*(p+1)+0x30);//mil+0x30);
	     VFDserial_SendChar(*(p+2)+0x30);//cent+0x30);
	     VFDserial_SendChar(*(p+3)+0x30);//dec+0x30);
	     VFDserial_SendChar(*(p+4)+0x30);//unidad+0x30);
	     
}//fin de despleigue de 5 chars en array que representan un numero UINT de maximo 99999-------------------------
    
		

unsigned char  digito2posicion(unsigned char digito){
    	         switch(digito){
	                       case 1: digito=POSXDSSDIGITO1; break;
   	                       case 2: digito=POSXDSSDIGITO2; break;
	                       case 3: digito=POSXDSSDIGITO3; break;
  	                       case 4: digito=POSXDSSDIGITO4; break;
	                       case 5: digito=POSXDSSDIGITO5; break;
  	                       default:digito=0;break; }//fin switch
return digito;         
}// digito to position converter,,, digito  de pantalla convertido a la posicion real en el VFD



//coordendadas absolutas y convertidas a estado final para ser pintadas en DDS
//Regresa el valor del regstro del 1 al 24 que corresponde  de la
/* ccoordenada x, en la absis de 1 a 192 se divden en registros
 * de 8 bits, y regresa el bit que corresponde a la coordenada 
 * en el registro reg, para guardar coordenadas dds de la pantalla */
unsigned char getRegistro_X_bit(unsigned char *Reg,unsigned char x){
unsigned char b,rx;
     
     switch(x){
			case 192:b=0x01;rx=0;break;
			case 1:b=0x02;rx=0;break;
			case 2:b=0x04;rx=0;break;
			case 3:b=0x08;rx=0;break;
			case 4:b=0x10;rx=0;break;
			case 5:b=0x20;rx=0;break;
			case 6:b=0x40;rx=0;break;
			case 7:b=0x80;rx=0;break;
			case 8:b=0x01;rx=1;break;
			case 9:b=0x02;rx=1;break;
			case 10:b=0x04;rx=1;break;
			case 11:b=0x08;rx=1;break;
			case 12:b=0x10;rx=1;break;
			case 13:b=0x20;rx=1;break;
			case 14:b=0x40;rx=1;break;
			case 15:b=0x80;rx=1;break;
			case 16:b=0x01;rx=2;break;
			case 17:b=0x02;rx=2;break;
			case 18:b=0x04;rx=2;break;
			case 19:b=0x08;rx=2;break;
			case 20:b=0x10;rx=2;break;
			case 21:b=0x20;rx=2;break;
			case 22:b=0x40;rx=2;break;
			case 23:b=0x80;rx=2;break;
			case 24:b=0x01;rx=3;break;
			case 25:b=0x02;rx=3;break;
			case 26:b=0x04;rx=3;break;
			case 27:b=0x08;rx=3;break;
			case 28:b=0x10;rx=3;break;
			case 29:b=0x20;rx=3;break;
			case 30:b=0x40;rx=3;break;
			case 31:b=0x80;rx=3;break;
			case 32:b=0x01;rx=4;break;
			case 33:b=0x02;rx=4;break;
			case 34:b=0x04;rx=4;break;
			case 35:b=0x08;rx=4;break;
			case 36:b=0x10;rx=4;break;
			case 37:b=0x20;rx=4;break;
			case 38:b=0x40;rx=4;break;
			case 39:b=0x80;rx=4;break;
			case 40:b=0x01;rx=5;break;
			case 41:b=0x02;rx=5;break;
			case 42:b=0x04;rx=5;break;
			case 43:b=0x08;rx=5;break;
			case 44:b=0x10;rx=5;break;
			case 45:b=0x20;rx=5;break;
			case 46:b=0x40;rx=5;break;
			case 47:b=0x80;rx=5;break;
			case 48:b=0x01;rx=6;break;
			case 49:b=0x02;rx=6;break;
			case 50:b=0x04;rx=6;break;
			case 51:b=0x08;rx=6;break;
			case 52:b=0x10;rx=6;break;
			case 53:b=0x20;rx=6;break;
			case 54:b=0x40;rx=6;break;
			case 55:b=0x80;rx=6;break;
			case 56:b=0x01;rx=7;break;
			case 57:b=0x02;rx=7;break;
			case 58:b=0x04;rx=7;break;
			case 59:b=0x08;rx=7;break;
			case 60:b=0x10;rx=7;break;
			case 61:b=0x20;rx=7;break;
			case 62:b=0x40;rx=7;break;
			case 63:b=0x80;rx=7;break;
			case 64:b=0x01;rx=8;break;
			case 65:b=0x02;rx=8;break;
			case 66:b=0x04;rx=8;break;
			case 67:b=0x08;rx=8;break;
			case 68:b=0x10;rx=8;break;
			case 69:b=0x20;rx=8;break;
			case 70:b=0x40;rx=8;break;
			case 71:b=0x80;rx=8;break;
			case 72:b=0x01;rx=9;break;
			case 73:b=0x02;rx=9;break;
			case 74:b=0x04;rx=9;break;
			case 75:b=0x08;rx=9;break;
			case 76:b=0x10;rx=9;break;
			case 77:b=0x20;rx=9;break;
			case 78:b=0x40;rx=9;break;
			case 79:b=0x80;rx=9;break;
			case 80:b=0x01;rx=10;break;
			case 81:b=0x02;rx=10;break;
			case 82:b=0x04;rx=10;break;
			case 83:b=0x08;rx=10;break;
			case 84:b=0x10;rx=10;break;
			case 85:b=0x20;rx=10;break;
			case 86:b=0x40;rx=10;break;
			case 87:b=0x80;rx=10;break;
			case 88:b=0x01;rx=11;break;
			case 89:b=0x02;rx=11;break;
			case 90:b=0x04;rx=11;break;
			case 91:b=0x08;rx=11;break;
			case 92:b=0x10;rx=11;break;
			case 93:b=0x20;rx=11;break;
			case 94:b=0x40;rx=11;break;
			case 95:b=0x80;rx=11;break;
			case 96:b=0x01;rx=12;break;
			case 97:b=0x02;rx=12;break;
			case 98:b=0x04;rx=12;break;
			case 99:b=0x08;rx=12;break;
			case 100:b=0x10;rx=12;break;
			case 101:b=0x20;rx=12;break;
			case 102:b=0x40;rx=12;break;
			case 103:b=0x80;rx=12;break;
			case 104:b=0x01;rx=13;break;
			case 105:b=0x02;rx=13;break;
			case 106:b=0x04;rx=13;break;
			case 107:b=0x08;rx=13;break;
			case 108:b=0x10;rx=13;break;
			case 109:b=0x20;rx=13;break;
			case 110:b=0x40;rx=13;break;
			case 111:b=0x80;rx=13;break;
			case 112:b=0x01;rx=14;break;
			case 113:b=0x02;rx=14;break;
			case 114:b=0x04;rx=14;break;
			case 115:b=0x08;rx=14;break;
			case 116:b=0x10;rx=14;break;
			case 117:b=0x20;rx=14;break;
			case 118:b=0x40;rx=14;break;
			case 119:b=0x80;rx=14;break;
			case 120:b=0x01;rx=15;break;
			case 121:b=0x02;rx=15;break;
			case 122:b=0x04;rx=15;break;
			case 123:b=0x08;rx=15;break;
			case 124:b=0x01;rx=15;break;
			case 125:b=0x20;rx=15;break;
			case 126:b=0x40;rx=15;break;
			case 127:b=0x80;rx=15;break;
			case 128:b=0x01;rx=16;break;
			case 129:b=0x02;rx=16;break;
			case 130:b=0x04;rx=16;break;
			case 131:b=0x08;rx=16;break;
			case 132:b=0x10;rx=16;break;
			case 133:b=0x20;rx=16;break;
			case 134:b=0x40;rx=16;break;
			case 135:b=0x80;rx=16;break;
			case 136:b=0x01;rx=17;break;
			case 137:b=0x02;rx=17;break;
			case 138:b=0x04;rx=17;break;
			case 139:b=0x08;rx=17;break;
			case 140:b=0x10;rx=17;break;
			case 141:b=0x20;rx=17;break;
			case 142:b=0x40;rx=17;break;
			case 143:b=0x80;rx=17;break;
			case 144:b=0x01;rx=18;break;
			case 145:b=0x02;rx=18;break;
			case 146:b=0x04;rx=18;break;
			case 147:b=0x08;rx=18;break;
			case 148:b=0x10;rx=18;break;
			case 149:b=0x20;rx=18;break;
			case 150:b=0x40;rx=18;break;
			case 151:b=0x80;rx=18;break;
			case 152:b=0x01;rx=19;break;
			case 153:b=0x02;rx=19;break;
			case 154:b=0x04;rx=19;break;
			case 155:b=0x08;rx=19;break;
			case 156:b=0x10;rx=19;break;
			case 157:b=0x20;rx=19;break;
			case 158:b=0x40;rx=19;break;
			case 159:b=0x80;rx=19;break;
			case 160:b=0x01;rx=20;break;
			case 161:b=0x02;rx=20;break;
			case 162:b=0x04;rx=20;break;
			case 163:b=0x08;rx=20;break;
			case 164:b=0x10;rx=20;break;
			case 165:b=0x20;rx=20;break;
			case 166:b=0x40;rx=20;break;
			case 167:b=0x80;rx=20;break;
			case 168:b=0x01;rx=21;break;
			case 169:b=0x02;rx=21;break;
			case 170:b=0x04;rx=21;break;
			case 171:b=0x08;rx=21;break;
			case 172:b=0x10;rx=21;break;
			case 173:b=0x20;rx=21;break;
			case 174:b=0x40;rx=21;break;
			case 175:b=0x80;rx=21;break;
			case 176:b=0x01;rx=22;break;
			case 177:b=0x02;rx=22;break;
			case 178:b=0x04;rx=22;break;
			case 179:b=0x08;rx=22;break;
			case 180:b=0x10;rx=22;break;
			case 181:b=0x20;rx=22;break;
			case 182:b=0x40;rx=22;break;
			case 183:b=0x80;rx=22;break;
			case 184:b=0x01;rx=23;break;
			case 185:b=0x02;rx=23;break;
			case 186:b=0x04;rx=23;break;
			case 187:b=0x08;rx=23;break;
			case 188:b=0x10;rx=23;break;
			case 189:b=0x20;rx=23;break;
			case 190:b=0x40;rx=23;break;
			case 191:b=0x80;rx=23;break;
			default:b=0;rx=0;break;  }//fin swithc----------------------  
            *Reg=rx;
return b;	
}//fin getRegistro_X_bit---------------------------------------------


void DisplayCuentaProducto(void){//-----------------------------------
unsigned char r[]="Apagar  ";
unsigned char z[]="Permitir";
//word n;
unsigned char *cursorx,*cursory;
    cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory;
	VFDclrscr();
	VFDposicion(POSX192,POSY14);   //delay1us();
	if(producto2.CuentaProducto==APAGAR){ 
		producto2.CuentaProducto=PERMITIR; 
		VFDserial_SendBlock(&z[0],sizeof(r));}
	else {producto2.CuentaProducto=APAGAR;
	    VFDserial_SendBlock(&r[0],sizeof(z));}
	//delay1us();
	*cursorx=POSX0;*cursory=POSY14;
    //isEnable_Keypad(WAIT);//Desabilita el teclado uno milisegundos.
    //menu.b.b.isMenu=1;//se ejecuto este menu.
    vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
}// fin Display Centa de Producto-------------------------------------
	
	
/* Procesador de sensibilidad or digito  cambiamos el numero en menu por digito
 * param1: digito, digito a cambiar de valor
 * param2: posicion donde se pinta el digito * */
void procSensxDigitoEN(unsigned char *digito,unsigned char posx,unsigned char initx){
unsigned char a[5],*p;	
unsigned char *cursorx,*cursory;       
       cursorx=&vfd.menu.cursorx;
	   cursory=&vfd.menu.cursory;
	   switch(*digito){//  5 indica decena de miles y 1 unidad
	    				  case 1:*digito=0;p=&a[0];
	    					     *cursorx=posx;
	    				         getCharsFromUINT_var(p,producto2.Sensibilidad);
	    					     VFDposicion(*cursorx,*cursory);
	    					     VFDserial_SendChar(' ');
	    					     VFDserial_SendChar(a[0]+0x30);
	    					     VFDserial_SendChar(a[1]+0x30);
	    					     VFDserial_SendChar(a[2]+0x30);
	    					     VFDserial_SendChar(a[3]+0x30);
	    					     VFDserial_SendChar(a[4]+0x30);			          
	    					     *cursorx=initx;
	    					     VFDposicion(*cursorx,*cursory);
	    					     VFDserial_SendChar('>');
	    					     VFDserial_SendChar(0x01);
					             //isEnable_Keypad(WAIT);
	    					     break;
	    				  case 0:*digito=5;
	    		                 VFDposicion(*cursorx,*cursory);
			                     VFDserial_SendChar(' ');
			                     *cursorx=posx;
			                     VFDposicion(*cursorx,*cursory);
			                     VFDserial_SendChar('>');
			                     VFDserial_SendChar(0x01);
					             //isEnable_Keypad(WAIT);
			                     break;        
	    				  case 5:*digito=4;p=&a[0];
	    				         *cursorx=posx;
	    				         VFDposicion(*cursorx,*cursory);
	    				         getCharsFromUINT_var(p,producto2.Sensibilidad);
	    				         VFDserial_SendChar(a[0]+0x30); 
								 VFDserial_SendChar('>');
								 VFDserial_SendChar(0x01);
								 //isEnable_Keypad(WAIT);
								 break;
	    				  case 4:*digito=3;p=&a[0];
								 *cursorx=posx;
								 VFDposicion(*cursorx,*cursory);
								 getCharsFromUINT_var(p,producto2.Sensibilidad);
								 VFDserial_SendChar(a[0]+0x30);
								 VFDserial_SendChar(a[1]+0x30);
								 VFDserial_SendChar('>');
								 VFDserial_SendChar(0x01);
								 //isEnable_Keypad(WAIT);
								 break;
	    				  case 3:*digito=2;p=&a[0];
								 *cursorx=posx;
								 VFDposicion(*cursorx,*cursory);
								 getCharsFromUINT_var(p,producto2.Sensibilidad);
								 VFDserial_SendChar(a[0]+0x30);
								 VFDserial_SendChar(a[1]+0x30);
								 VFDserial_SendChar(a[2]+0x30);
								 VFDserial_SendChar('>');
								 VFDserial_SendChar(0x01);
								 //isEnable_Keypad(WAIT);
								 break;	 
	    				  case 2:*digito=1;p=&a[0];
								 *cursorx=posx;
								 VFDposicion(*cursorx,*cursory);
								 getCharsFromUINT_var(p,producto2.Sensibilidad);
								 VFDserial_SendChar(a[0]+0x30);
								 VFDserial_SendChar(a[1]+0x30);
								 VFDserial_SendChar(a[2]+0x30);
								 VFDserial_SendChar(a[3]+0x30);
								 VFDserial_SendChar('>');
								 VFDserial_SendChar(0x01);
								 //isEnable_Keypad(WAIT);
								 break;	 	 		 
								 
	    				  default://__asm(Halt);
						          errorCritico("Error en AjParamProd-Enter");
					  			  exit(1);
	    	                      break;}//debug--------

}//fin de procSensxDigito----------------------------------------------


void procFasexDigitoEN(unsigned char *var,unsigned char posx,unsigned char posy){
unsigned char n;
unsigned char a[5],*p,*cursory,*cursorx;
    
    cursory=&vfd.menu.cursory;
	cursorx=&vfd.menu.cursorx;
    if(*cursory==POSY4)  n=8; else n=0;   
	switch(*var){//5 indica decena de miles y 1 unidad
		case 0: *var=5;
		        VFDposicion(*cursorx,*cursory);
				VFDserial_SendChar(' ');
				if(n==8){VFDposicion(POSXDDSNUMS+8,POSY6);
						 VFDserial_SendChar(' ');VFDserial_SendChar(' ');
						 VFDserial_SendChar(' ');VFDserial_SendChar(' ');
						 VFDserial_SendChar(' ');VFDserial_SendChar(0x01);
						 VFDserial_SendChar(0x02);}
				VFDposicion((posx+(8*(5-*var))+n),posy);
				VFDserial_SendChar('^');
				VFDserial_SendChar(0x01);
				VFDserial_SendChar(0x02);
				//isEnable_Keypad(WAIT);
				break;
		case 1: VFDposicion((posx+(8*(5-*var))+n),posy);
				VFDserial_SendChar(' ');
				VFDposicion(*cursorx,*cursory);
				VFDserial_SendChar('>');
				VFDserial_SendChar(0x01);
				VFDserial_SendChar(0x02);
				if(n==8){p=&a[0];
				     getCharsFromUINT_var(p,producto2.Altura);
				     VFDposicion(POSXDDSNUMS,POSY6);
				     for(n=0;n<5;n++)
				         VFDserial_SendChar(a[n]+0x30);
				     VFDserial_SendChar(0x01);//esto es un delay
				     VFDserial_SendChar(0x02);}
				*var=0; 
				//isEnable_Keypad(WAIT);
				break;
		case 2:  
		case 3:VFDposicion((posx+(8*2)+n),posy);
			   VFDserial_SendChar(' ');
			   VFDserial_SendChar(' ');
			   VFDserial_SendChar('^');
			   VFDserial_SendChar(0x01);
			   VFDserial_SendChar(0x02);
			   //isEnable_Keypad(WAIT);
			   *var=1;
			   break;
		case 4:
		case 5:VFDposicion((posx+(8*(5-(*var)--))+n),posy);
			   VFDserial_SendChar(' ');
			   VFDserial_SendChar('^');
			   VFDserial_SendChar(0x01);
			   VFDserial_SendChar(0x02);
			   //isEnable_Keypad(WAIT);
			   break;
		default:errorCritico("Error f.procFasexDigitoEN");break;
		         }//fin switch
}//FIN procFasexDigitoEN-----------------------------------------


void displayTextoProcessorMayusculas(void){
unsigned char r1[]= "  1  2  3  4  5  6  7  8  9  0";//Y6
unsigned char r2[]= "  Q  W  E  R  T  Y  U  I  O  P";        //Ñ=A5h
unsigned char r3[]= "  A  S  D  F  G  H  J  K  L  ;";
unsigned char r4[]= "  Z  X  C  V  B  N  M  ,  .   ";
unsigned char r5[]= "  Ma Mi S           <  >  +  -";		
unsigned char x[7]={POSX_TEXT_PROCS_OK,0,0,0,0 , 0,  0};//POSX_TEXT_PROCS_OK=205
unsigned char y[7]={  0,0,6,8,10,12, 14};
	
	    VFDposicion(x[2],y[2]);  
	    VFDserial_SendBlock(&r1[0],sizeof(r1));
		VFDposicion(x[3],y[3]);   
		VFDserial_SendBlock(&r2[0],sizeof(r2));
		VFDposicion(x[4],y[4]);   
		VFDserial_SendBlock(&r3[0],sizeof(r3));
		VFDposicion(x[5],y[5]);  
		VFDserial_SendBlock(&r4[0],sizeof(r4));
		VFDposicion(x[6],y[6]);  
		VFDserial_SendBlock(&r5[0],sizeof(r5));  
	    //isEnable_Keypad(WAIT);//Desabilita el teclado uno milisegundos.
	    //vfd.config.bits.Menu_Ready=1;// menu.b.b.isMenu=1;//se ejecuto este menu.
}//fin de depliegue del procesadorr de textos para mayusculas

//despliegue de minusculas del procesador de textos
void displayTextoProcessorMinusculas(void){
unsigned char r1[]= "  1  2  3  4  5  6  7  8  9  0";//Y6
unsigned char r2[]= "  q  w  e  r  t  y  u  i  o  p";        //ñ=A4h
unsigned char r3[]= "  a  s  d  f  g  h  j  k  l  ;";
unsigned char r4[]= "  z  x  c  v  b  n  m  ,  .   ";
unsigned char r5[]= "  Ma Mi S           <  >  +  -";		
unsigned char x[7]={ POSX_TEXT_PROCS,0,0,0,0 , 0,  0};
unsigned char y[7]={   0,0,6,8,10,12, 14};

		    VFDposicion(x[2],y[2]); 
		    VFDserial_SendBlock(&r1[0],sizeof(r1));
			VFDposicion(x[3],y[3]);   
			VFDserial_SendBlock(&r2[0],sizeof(r2));
			VFDposicion(x[4],y[4]);   
			VFDserial_SendBlock(&r3[0],sizeof(r3));
			VFDposicion(x[5],y[5]);   
			VFDserial_SendBlock(&r4[0],sizeof(r4));
			VFDposicion(x[6],y[6]);   
			VFDserial_SendBlock(&r5[0],sizeof(r5));  
		    //isEnable_Keypad(WAIT);//Desabilita el teclado uno milisegundos.
		    //menu.b.b.isMenu=1;//se ejecuto este menu.
}//fin de despliegue de minusculas del menu de proceador de texto

//fin del despleigue de symbolos en el procesador de textos
void displayTextoProcessorSymbol(void){ //ñ=A4h  //Y6
unsigned char r1[]={' ',' ',S1,' ',' ' ,S2,' ',' ' ,S3,' ',' ' ,S4,' ',' ' ,S5,' ',' ' ,S6,' ',' ' ,S7,' ',' ' ,S8,' ',' ' ,S9,' ',' ' ,S10};
unsigned char r2[]={' ',' ',S11,' ',' ',S12,' ',' ',S13,' ',' ',S14,' ',' ',S15,' ',' ',S16,' ',' ',S17,' ',' ',S18,' ',' ',S19,' ',' ',S20};
unsigned char r3[]={' ',' ',S21,' ',' ',S22,' ',' ',S23,' ',' ',S24,' ',' ',S25,' ',' ',S26,' ',' ',S27,' ',' ',S28,' ',' ',S29,' ',' ',S30};
unsigned char r4[]={' ',' ',S31,' ',' ',S32,' ',' ',S33,' ',' ',S34,' ',' ',S35,' ',' ',S36,' ',' ',S37,' ',' ',S38,' ',' ',S39,' ',' ',S40};
unsigned char r5[]={ "  Ma Mi S           <  >  +  -"};		
unsigned char x[7]={ POSX_TEXT_PROCS,0,0,0,0 , 0,  0};
unsigned char y[7]={   0,0,6,8,10,12, 14};
	         
            VFDposicion(x[2],y[2]);   
		    VFDserial_SendBlock(&r1[0],sizeof(r1));
			VFDposicion(x[3],y[3]);   
			VFDserial_SendBlock(&r2[0],sizeof(r2));
			VFDposicion(x[4],y[4]);  
			VFDserial_SendBlock(&r3[0],sizeof(r3));
			VFDposicion(x[5],y[5]);  
			VFDserial_SendBlock(&r4[0],sizeof(r4));
			VFDposicion(x[6],y[6]);   
			VFDserial_SendBlock(&r5[0],sizeof(r5));
		    //isEnable_Keypad(WAIT);//Desabilita el teclado uno milisegundos.
		    //menu.b.b.isMenu=1;//se ejecuto este menu.
}//fin del desiegue de simbolos en el menu de procesador de textos----




//despliegue de la cadena de texto en el menu de TEXTO PROCESSOR
void DisplayNewTextProc(void){
unsigned char i,j;
     j=FALSE;
	 VFDposicion(0,POSY2);//POSICION en el reglon 2 donde se despliega la cadena
	 for(i=0;i<NOMBRE_PRODUCTO_SIZE;i++){
		 if(vfd.Text[i]==0)
			 j=TRUE;
		 if(j==FALSE)
    	    VFDserial_SendChar(vfd.Text[i]);
		 else VFDserial_SendChar(' ');}
	
}//fin de despliegue de la cadena de texto en el menu de TEXTO PROCESSOR

void monitorInvalidPassword(void){//arg0 esta ocupado en CONTROL PASSWORD
if((MenuTextProc->arg1==ERROR_PASS)&&(vfd.menu.contexto.control==SUPERVISOR)){//hubo password invalida????
      MenuTextProc->arg1=0;//arg1=0;	 
	  displayTextoProcessor();}
}//fin monitorInvalidPassword-------------------------------------------------------------


//text processor for name modify	
void TextProcessorSpecial(void){
unsigned char *cursorx,*cursory;
      cursorx=&vfd.menu.cursorx;
	  cursory=&vfd.menu.cursory;	
	  if(*cursory==POSY14){
		  specialFunctions();
		  return;}
      if(MenuTextProc->igxc1>=NOMBRE_PRODUCTO_SIZE){//Escribir algun ascii en pantalla
          return;}
	  MenuTextProc->arg5=CAMBIAR;//se ha modificado el nombre del producto
	  if(MenuTextProc->igxc1>(NOMBRE_PRODUCTO_SIZE-1)){//si escribimos mucho llegara hasta 20 el minimo es 19
		  return;}
	  vfd.Text[MenuTextProc->igxc1]=getAscii(*cursorx,*cursory,MenuTextProc->igxc0);//guardamos el ascii seleccionado
	  DisplayCharTextProc(MenuTextProc->igxc1,vfd.Text[MenuTextProc->igxc1]);
	  DisplayCursorTextProc(MenuTextProc->igxc1+1,MenuTextProc->igxc1);
	  MenuTextProc->igxc1++;
return;	
}//fin TextProcessorSpecial--------------------------------------

//metodo del procesador de textos
void specialFunctions(void){
unsigned char *cursorx,*cursory;
unsigned char c;
      cursorx=&vfd.menu.cursorx;
	  cursory=&vfd.menu.cursory;	
	 if(MenuTextProc->igxc1==0)
		  return;
	  switch(*cursorx){
		  case POSX_COL1:break;
		  case POSX_COL2:break;
		  case POSX_COL3:break;
		  case POSX_COL4:break;
		  case POSX_COL5:break;
		  case POSX_COL6:break;
		  case POSX_COL7:MenuTextProc->igxc1=DisplayRecorrerIndiceIzqTextProc(MenuTextProc->igxc1,LEFT);break;
		  case POSX_COL8:MenuTextProc->igxc1=DisplayRecorrerIndiceIzqTextProc(MenuTextProc->igxc1,RIGHT);break; 
		  case POSX_COL9:MenuTextProc->igxc1=DisplayInsertSpaceTextProc(MenuTextProc->igxc1);break;
		  case POSX_COL10:c=TextBackSpace(MenuTextProc->igxc1);//Revisar esta funcionc: lugar actual, igxm1 lugar anterior
		                  DisplayNewTextProc();//despleiga el texto
		                  DisplayCursorTextProc(c,MenuTextProc->igxc1);//despliega el cursos en posicion actual.
		                  MenuTextProc->igxc1=c;
			             break;
		  default:break;  
	  }//fin switch
	
}//fin specialFunctions-----------------------------.-------------------------------------------------------------


void DisplayCharTextProc(unsigned char pos,unsigned char dato){
	  VFDposicion(((pos-1)*8),POSY2);
      VFDserial_SendChar(dato);	
}//fin DisplayCharTextProc-------------------------------------------------------------------------------------------

unsigned char DisplayInsertSpaceTextProc(unsigned char indice){
	unsigned char  i=0;
	         i=indice;
//	         i=TextInsertSpace2(indice);
             DisplayNewTextProc();//despleiga el texto
             return i;
}// DisplayInsertSpaceTextProc--------------------------------------------------------




//ii es pa posicion actual del cursor
unsigned char DisplayRecorrerIndiceIzqTextProc(unsigned char ii,unsigned char IzqDer){
unsigned char i;
        i=ii;
        if(IzqDer==RIGHT){
			if(i>=(NOMBRE_PRODUCTO_SIZE-1))
				i=NOMBRE_PRODUCTO_SIZE-1;
			else ++i;//the value of pointer is incremented
			if(vfd.Text[i]==0)
				vfd.Text[i]=' ';
			DisplayCursorTextProc(i,ii);
            return i;}
        else{
        	if(i==1)
        		return i;
        	if(i<1){usleep(19);
        		    mens_Warnning_Debug("error en diaplay rec indice 837");// __asm(Halt);
			       exit(1);}
        	i--;
        	if(vfd.Text[i]==0)
				vfd.Text[i]=' ';
        	DisplayCursorTextProc(i,ii);
        	return i;}
}//fin DisplayRecorrerIndiceIzqTextProc--------------------------------------------------

//posicion actual: a la que vamos a mover,
void DisplayCursorTextProc(unsigned char pos_actual, unsigned char pos_anterior){
       if(pos_actual>pos_anterior){
    	   if(pos_actual==NOMBRE_PRODUCTO_SIZE){
    		   return;}}
	   VFDposicion((unsigned char)((pos_anterior-1)*8),POSY4);
       VFDserial_SendChar(' ');	
	   VFDposicion((unsigned char)((pos_actual-1)*8),POSY4);
  	   VFDserial_SendChar('^');
	
}//FIN DisplayCursorTextProc--------------------------------------------------------


void saveTextBuffer(unsigned char *p){
unsigned char i;
       for(i=0;i<NOMBRE_PRODUCTO_SIZE;i++)
	      global.igxc5[i]=*(p)++;
}//fin saveTextBuffer-------------------------------------------------------


//nos da la columna adonde vamos basados en donde estamos
unsigned char getColTextProc(unsigned char dir){
	
	switch(vfd.menu.cursorx){
		case POSX_COL1:if(dir==RIGHT)
			              return  POSX_COL2;
			           else return POSX_COL10;
		               break;
		case POSX_COL2:if(dir==RIGHT)
					              return  POSX_COL3;
					           else return POSX_COL1;
				               break;
		case POSX_COL3:if(dir==RIGHT)
					              return  POSX_COL4;
					           else return POSX_COL2;
				               break;
		case POSX_COL4:if(dir==RIGHT)
					              return  POSX_COL5;
					           else return POSX_COL3;
				               break;
		case POSX_COL5:if(dir==RIGHT)
					              return  POSX_COL6;
					           else return POSX_COL4;
				               break;
		case POSX_COL6:if(dir==RIGHT)
					              return  POSX_COL7;
					           else return POSX_COL5;
				               break;
		case POSX_COL7:if(dir==RIGHT)
					              return  POSX_COL8;
					           else return POSX_COL6;
				               break;
		case POSX_COL8:if(dir==RIGHT)
					              return  POSX_COL9;
					           else return POSX_COL7;
				               break;
		case POSX_COL9:if(dir==RIGHT)
					              return  POSX_COL10;
					           else return POSX_COL8;
				               break;
		case POSX_COL10:if(dir==RIGHT)
					              return  POSX_COL1;
					           else return POSX_COL9;
				               break;
		default: return 0; break;																							               
	}//fin switch	
}//fin de get columna a onde vamos--------------------------------
