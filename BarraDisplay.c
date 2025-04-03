#include "BarraDisplay.h"
#include "system.h"
#include "VFD.h"
#include "VFDmenu.h"
#include <stdlib.h>

extern struct _DISPLAY_VFD_ vfd;


//despliegua el cuadro Madre de deteccion y los dos cuadros hijos vacios en la coordenada x,y
unsigned char displayCuadroMadre_VFD(void){
unsigned char x1a,x1b,x1c;
unsigned char y1a,y1b,y1c;
unsigned char x2a,x2b,x2c;
unsigned char y2a,y2b,y2c;
unsigned char ret=0;

	switch(vfd.menu.contexto.solicitaCambioA){
		case AJUSTE_DE_VIBRACION:x1a=POS_X1_BOX_AV; y1a=POS_Y1_BOX_AV; x2a=POS_X2_BOX_AV; y2a=POS_Y2_BOX_AV;
		                         x1b=POS_X1_BOX1_AV;y1b=POS_Y1_BOX1_AV;x2b=POS_X2_BOX1_AV;y2b=POS_Y2_BOX1_AV;
		                         x1c=POS_X1_BOX2_AV;y1c=POS_Y1_BOX2_AV;x2c=POS_X2_BOX2_AV;y2c=POS_Y2_BOX2_AV;
		                         break;
		case PORTAL_INICIO:x1a=POS_X1_BOX_PI;  y1a=POS_Y1_BOX_PI; 
		                   x2a=POS_X2_BOX_PI;  y2a=POS_Y2_BOX_PI;//CUADRO MADRE
			    	       x1b=POS_X1_BOX1_PI; y1b=POS_Y1_BOX1_PI;
						   x2b=POS_X2_BOX1_PI; y2b=POS_Y2_BOX1_PI;//CUADRO-1  HIJO VACIO	    
			    	       x1c=POS_X1_BOX2_PI; y1c=POS_Y1_BOX2_PI;
						   x2c=POS_X2_BOX2_PI; y2c=POS_Y2_BOX2_PI;
			    	       break;
		case AJUSTE_PARAMETRICO_DE_PRODUCTO:
              x1a=POS_X1_BOX_AP; y1a=POS_Y1_BOX_AP; x2a=POS_X2_BOX_AP; y2a=POS_Y2_BOX_AP;//CUADRO MADRE
      		  x1b=POS_X1_BOX1_AP;y1b=POS_Y1_BOX1_AP;x2b=POS_X2_BOX1_AP;y2b=POS_Y2_BOX1_AP;//CUADRO-1  HIJO VACIO	    
      		  x1c=POS_X1_BOX2_AP;y1c=POS_Y1_BOX2_AP;x2c=POS_X2_BOX2_AP;y2c=POS_Y2_BOX2_AP;//CUADRO-1  HIJO VACIO  	  
              break;
		case PARAMETROS_DE_DETECCION:
			  x1a=POS_X1_BOX_PD; y1a=POS_Y1_BOX_PD; x2a=POS_X2_BOX_PD; y2a=POS_Y2_BOX_PD;//CUADRO MADRE
		      x1b=POS_X1_BOX1_PD;y1b=POS_Y1_BOX1_PD;x2b=POS_X2_BOX1_PD;y2b=POS_Y2_BOX1_PD;//CUADRO-1  HIJO VACIO	    
		      x1c=POS_X1_BOX2_PD;y1c=POS_Y1_BOX2_PD;y2c=POS_X2_BOX2_PD;y2c=POS_Y2_BOX2_PD;//CUADRO-1  HIJO VACIO  	  
		      break;  	
		default:errorCritico("Error Cuadro-Madre: Contexto -Desconocido-");
			    exit(1);		        
		        break;}	
	VFDboxLine1(ON,BOX_VACIA,x1a,y1a,x2a,y2a);//cuadro madre
	VFDboxLine1(ON,BOX_VACIA,x1b,y1b,x2b,y2b);//cuadrito vacio No.1
    VFDboxLine1(ON,BOX_VACIA,x1c,y1c,x2c,y2c);//cuadrito vacio No.2
    ret=TRUE;
return ret;
}//fin del despliegue del cuadro Madre y los dos hijos en funcion del contexto----------------------------
