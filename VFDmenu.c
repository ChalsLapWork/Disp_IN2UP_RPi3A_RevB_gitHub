#include "VFDmenu.h"
#include "errorController.h"
#include "system.h"
#include "Memoria.h"
#include "delay.h"
#include "queue.h"
#include "VFD.h"
#include "DSP.h"
#include "BarraDisplay.h"
#include "strings.h"

struct ArbolMenu MenuActualScreen;//la estrucrura del menu actual en pantalla.
extern struct _PRODUCTO1_ producto;
extern struct _DISPLAY_VFD_ vfd;
extern struct _Detection Deteccion;



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
const unsigned char  c[]="Cuenta rechazos_!";
const unsigned char  d[]="Cuenta producto ";
const unsigned char x[4]={80,24,24,24};
const unsigned char y[4]={ 2,10,12,14};
unsigned char ret=0;
//unsigned char *inst1,*inst2;//instancias subHilos a ejecutar que se pueden ejecutar en otros lados
unsigned char *estado,/* *control,*/*mem_15bytes,*aux3_char,*aux0_uchar;
unsigned short int aux1_usi;
const unsigned char DEBUG=0x11,MEMO=0x12;
unsigned char Status_Prod=DEBUG;
union W16{
   unsigned short int usi;
   unsigned char c[2];
}word_16bits;

            estado=mem;
           //control=mem+1;
         aux3_char=mem+2;
  word_16bits.c[0]=*(mem+4);
  word_16bits.c[1]=*(mem+5);
          aux1_usi=word_16bits.usi;
        mem_15bytes=mem+6;//6,7 15 bytes
        aux0_uchar=mem+22;

 while(1){		
    VFDserial_SendBlock1(&c[0],sizeof(c));//if(VFDserial_SendBlock2(&s[0],sizeof(s),&n,inst1)) estado++;break;   //version
	
    }


    switch(*estado){ 
	   case 1:mensOK("Estoy en portal Inicio",CAMARILLO);(*estado)++;break;	
       case 2:Deteccion.CuadroMadreReady=FALSE;
              //keypad.b.enable=FALSE;
              (*estado)++;break;
       case 3:NoErrorOK();(*estado)++;break;			  
       case 4:if(VFDclrscr1(mem_15bytes))(*estado)++;break;
	   case 5:delay_ms_VFD(500);(*estado)++;break;
       case 6:if(VFDposicion(65,0))(*estado)++; break;    //2bytes
       case 7:if(VFDserial_SendBlock1(&s[0],sizeof(s)))(*estado)++;break;//if(VFDserial_SendBlock2(&s[0],sizeof(s),&n,inst1)) estado++;break;   //version
       case 8:*aux3_char=producto.name[1];aux1_usi=length(&producto.name[0],sizeof(producto.name));  	 
    	      *aux0_uchar=display_centrarNombres((unsigned char)aux1_usi);(*estado)++;break;
       case 9:if(Status_Prod==MEMO){if(VFDposicion(*aux0_uchar,2))(*estado)++;}
     	 	  else{if(VFDposicion(x[0],y[0])) (*estado)++;}break;
 	   case 10:if(delay_ms_VFD(2))(*estado)++;break; //Tiempo en pruebas
	   case 11:if(Status_Prod==MEMO){ss=aux3_char;
		            if(VFDserial_SendBlock1(ss,(unsigned char)aux1_usi))(*estado)++;}
	 	 	   else{if(VFDserial_SendBlock1(&a[0],sizeof(a)))(*estado)++;} 
	           break;
	   case 12:if(delay_ms_VFD(1))(*estado)++;break; //Tiempo en pruebas,
	   case 13:if(VFDposicion(x[1],y[1]))(*estado)++;break;
	   case 14:if(VFDserial_SendBlock1(&b[0],sizeof(b)))(*estado)++;break;
	   case 15:if(VFDposicion(x[2],y[2]))(*estado)++;break;
       case 16:if(VFDserial_SendBlock1(&c[0],sizeof(c)))(*estado)++;break;
       case 17:if(delay_us_VFD(100))(*estado)++;break;
       case 18:if(VFDposicion(x[3],y[3]))(*estado)++;break;
       case 19:if(VFDserial_SendBlock1(&d[0],sizeof(d)))(*estado)++;break;
	   case 20:if(displayCuadroMadre_VFD())(*estado)++;break;
       case 21:delay_ms_VFD(2);(*estado)++;break;
	   case 22:Deteccion.CuadroMadreReady=TRUE;
	           vfd.box.box0=0;//se inicia desde el primer cuadro a graficar.         	    
	           init_Sensibilidad();
      	       //keypad.b.enable=1;//Habilitado el teclado
	           vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
	           *estado=0;
	           ret=TRUE;
	           break;
		default:*estado=1;break;}//fin de estructura de +++++++++++++++++++++++
	
 word_16bits.usi=aux1_usi;
        *(mem+4)=word_16bits.c[0];
        *(mem+5)=word_16bits.c[1];
          
 
return ret;   
}// FIN DESPLIEGUE DEL PORTAL INICIO-------------------------------------------------------------------







unsigned char display_centrarNombres(unsigned char nchars){
const unsigned char middle=256/2;
const unsigned char charpixel=8;
	switch(nchars){
		case 0:return(middle);break;
		case 1:return(middle);break;//---*---
		case 2:return(middle-charpixel);break;
		case 3:return(middle-charpixel);break;
		case 4:return(middle-(charpixel*2));break;
		case 5:return(middle-(charpixel*3));break;
		default: return(middle-((nchars/2)*charpixel));break;	}
}//fin unsigned char display_centrarNombres(unsigned char nchars){------------------------------------
