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
#include "stdbool.h"

struct ArbolMenu MenuActualScreen;//la estrucrura del menu actual en pantalla.
extern struct _PRODUCTO1_ producto;
extern struct _DISPLAY_VFD_ vfd;
extern struct _Detection Deteccion;
extern struct _PRODUCT1_ producto2;



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
unsigned char ss;
const unsigned char  a[]="Test Set-up";
const unsigned char  b[]="S                P";
const unsigned char  c[]="Cuenta rechazos_!";
const unsigned char  d[]="Cuenta producto ";
const unsigned char x[4]={80,24,24,24};
const unsigned char y[4]={ 2,10,12,14};
unsigned char ret=0;
//unsigned char *inst1,*inst2;//instancias subHilos a ejecutar que se pueden ejecutar en otros lados
unsigned char aux3_char,aux0_uchar;
unsigned short int aux1_usi;
const unsigned char DEBUG=0x11,MEMO=0x12;
unsigned char Status_Prod=DEBUG,x1,y1;
union W16{
   unsigned short int usi;
   unsigned char c[2];
}word_16bits;


 /*while(1){		
    VFDserial_SendBlock1(&a[0],sizeof(a));//if(VFDserial_SendBlock2(&s[0],sizeof(s),&n,inst1)) estado++;break;   //version
	VFDserial_SendBlock1(&b[0],sizeof(b));//if(VFDserial_SendBlock2(&s[0],sizeof(s),&n,inst1)) estado++;break;   //version
	VFDserial_SendBlock1(&c[0],sizeof(c));//if(VFDserial_SendBlock2(&s[0],sizeof(s),&n,inst1)) estado++;break;   //version
	VFDserial_SendBlock1(&d[0],sizeof(d));//if(VFDserial_SendBlock2(&s[0],sizeof(s),&n,inst1)) estado++;break;   //version
	VFDposicion(x1,y1);
	if(x1++>40) x1=1;
	if(y1>14) y1=0;else{y1+=2;}}*/

	  mensOK("Estoy en portal Inicio",CAMARILLO);
      Deteccion.CuadroMadreReady=FALSE;
      NoErrorOK();			  
      VFDclrscr();
	  delay_ms_VFD(500);
      VFDposicion(65,0);
      VFDserial_SendBlock1(&s[0],sizeof(s));//version
	  aux3_char=producto.name[1];
	  aux1_usi=length(&producto.name[0],sizeof(producto.name));  	 
      aux0_uchar=display_centrarNombres((unsigned char)aux1_usi);
      (Status_Prod == MEMO) ? VFDposicion(aux0_uchar, 2) : VFDposicion(x[0], y[0]);

	   VFDserial_SendBlock1(&a[0],sizeof(a)); 
	   VFDposicion(x[1],y[1]);
	   VFDserial_SendBlock1(&b[0],sizeof(b));
       VFDposicion(x[2],y[2]);
       VFDserial_SendBlock1(&c[0],sizeof(c));
       VFDposicion(x[3],y[3]);
       VFDserial_SendBlock1(&d[0],sizeof(d));
	   displayCuadroMadre_VFD();
       Deteccion.CuadroMadreReady=TRUE;
	   vfd.box.box0=0;//se inicia desde el primer cuadro a graficar. 
	   vfd.box.box=0;//se inicializa la barra de deteccion.
	   vfd.box.timer=0;
	   for(int i=0;i<SIZE_BOXES;i++)
	         vfd.box.boxs[i]=0;//init boxees variables 
       vfd.config.bits.BOX_enable=TRUE;//se autoriza a dibujar cajas
	   //init_Sensibilidad();
	   usleep(100);//espera que se envien los datos del menu al VFD
       vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
	   
       ret=TRUE;
return ret;   
}// FIN DESPLIEGUE DEL PORTAL INICIO-------------------------------------------------------------------





/**************HOJAS EJECUTIVAS ******************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/********* HOJAS DE LOS MENUS *******************************************************/


/*  Gestiona la ejecucion del despliegue de cambio de cuadritos de la barra de deteccion
    los valores son de apartir de 15 de 5 en 5 */
void display_Barra_Deteccion(unsigned char barra){
 bool validos[256]={[0 ... 255]=false};//se ponen todos los valores en falso
 validos[PORTAL_INICIO]=true; //poner aqui los menus que contienen la barra de deteccion    
    if(vfd.menu.contexto.solicitaCambioA>0) return; //hay un cambio de menu
	if(validos[vfd.menu.contexto.Actual]){
		     VFDserial_SendBarraDet(barra);}     
}//FIN DE display de barra de deteccion++++++++++++++++++++++++++++++++++++++++++++


void display_CuentaRechazosProducto(unsigned char deteccion){
unsigned char sel=0;	
const unsigned char POS_X_CONT_RECHAZ=185;
const unsigned char POS_X_CONT_PROD=185;
const unsigned char POS_Y_CONT_RECHAZ=POSY12;
const unsigned char POS_Y_CONT_PROD=POSY14;
static unsigned char detection0,Rechazo0,producto0;//estado anterior de la deteccion


if((deteccion>50)&&(detection0<50))
      producto2.Cuenta_Rechazos++;
if((detection0<25)&&(deteccion>30))
	  producto2.Cuenta_Productos++;

if((vfd.config.bits.MenuPendiente==0)&&
    (vfd.config.bits.Menu_Ready==1)){
		if(vfd.menu.contexto.Actual==PORTAL_INICIO){
			if(Rechazo0!=producto2.Cuenta_Rechazos)
				VFDserial_Sendusint(producto2.Cuenta_Rechazos,POS_X_CONT_RECHAZ,POS_Y_CONT_RECHAZ,CENTER);
			if(producto0!=producto2.Cuenta_Productos)		  
				VFDserial_Sendusint(producto2.Cuenta_Productos,POS_X_CONT_PROD,POS_Y_CONT_PROD,CENTER);}}

  detection0=deteccion;//se guarda estado anterior		  
  Rechazo0=producto2.Cuenta_Rechazos;
  producto0=producto2.Cuenta_Productos;
}//fin de desplaiegue de conteo de rechazos y producto++++++++++++++++++++++++++



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
