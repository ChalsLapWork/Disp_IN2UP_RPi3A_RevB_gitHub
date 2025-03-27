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
#include "VFDkey.h"
#include <unistd.h>

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
		                     MenuActualScreen.func1=PortalinicioDisplay;
		                     MenuActualScreen.funcKeyUP=PortaliniciokeyUP;
		                     MenuActualScreen.funcKeyRT=PortaliniciokeyRT;
		                     MenuActualScreen.funcKeyLF=PortaliniciokeyLF;
		                     MenuActualScreen.funcKeyDN=PortaliniciokeyDN;//Insert the function pointer
		                     MenuActualScreen.funcKeyEN=PortaliniciokeyEN;//---poner en los apuntadores apuntar a las funciones--------------4
							 ret=TRUE;
		                     break;	
		 case MENU_INSIGHT:  MenuActualScreen.menuNodo=MENU_INSIGHT;
							 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
							 //MenuActualScreen.func=0;
							 MenuActualScreen.func1=displayMenuInsight;
							 MenuActualScreen.funcKeyUP=MenuInsightkeyUP;
							 MenuActualScreen.funcKeyDN=MenuInsightkeyDN;
							 MenuActualScreen.funcKeyRT=MenuInsightkeyRT;
							 MenuActualScreen.funcKeyLF=MenuInsightkeyLF;
							 MenuActualScreen.funcKeyEN=MenuInsightkeyEN;//MenuInsightkeyEN;
							 ret=TRUE;
							 break;	
         default: errorCritico2("error de InitArbol",19);break;                     
        }//fin switch ++EN CONSTRUCCION ++++++++++++++++++++++++++++++++++++
return ret;
}//fin portal inicion++++++++++++++++++++++++++++++++++++++++++++++



//despliega el menu principal, el recurso se solicita y gestiona
//desde el hilo padre del manejo del menu.
//Este metodo Solo se ejecuta una vez sin instancias
unsigned char  PortalinicioDisplay(void){//Funcion Suprema de Despliegue de la Pantalla0
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
	   //usleep(100);//espera que se envien los datos del menu al VFD
       vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
	   vfd.box.enable=1;
       ret=TRUE;
return ret;   
}// FIN DESPLIEGUE DEL PORTAL INICIO-------------------------------------------------------------------


unsigned char displayMenuInsight(void){// MESPLIEGUE DEL MENU INSGHT----------------------------------------------
unsigned char ret=0;
unsigned char z[]="Menu de Insight       x";
unsigned char a[]=">Ajuste de Producto";
unsigned char c[]="Ajuste Parametrico de Producto";
unsigned char w[]="Ajuste de sistema";
unsigned char v[]="Pantalla DDS";
unsigned char b[]="Informacion del usuario";
unsigned char x[7]={65,0,8,8, 8, 8,8};
unsigned char y[7]={0 ,4,6,8,10,12,4};
//word n;
	
      VFDclrscr();
      VFDposicion(x[0],y[0]);
      VFDserial_SendBlock1(&z[0],sizeof(z));
	  VFDposicion(x[1],y[1]);
	  VFDserial_SendBlock1(&a[0],sizeof(a));
	  VFDposicion(x[2],y[2]);
      VFDserial_SendBlock1(&c[0],sizeof(c));
	  VFDposicion(x[3],y[3]);
	  VFDserial_SendBlock1(&w[0],sizeof(w));
	  VFDposicion(x[4],y[4]);
	  VFDserial_SendBlock1(&v[0],sizeof(v));
	  VFDposicion(x[5],y[5]);
	  VFDserial_SendBlock1(&b[0],sizeof(b));
	  VFDposicion(x[6],y[6]);
	  vfd.menu.cursorx=POSX0;
	  vfd.menu.cursory=POSY4;
	  vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
	  //keypad.b.enable=1;//Habilitado el teclado	
	  vfd.box.enable=0;//disable pintar cajas barra detector
	  vfd.config.bits.BOX_enable=TRUE;//se autoriza a dibujar cajas
	  ret=TRUE;

return ret;
}//fin display menu inicio display----------------------------------------------------------------------------




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


/* se despliega en portal inicio la sensibilidad y la phase detectada que llega por 
  comando serial */
void display_Sens_Phase(unsigned short int sens,unsigned char phase,unsigned char phasefrac){	
const unsigned char  a[]="     ";
if((vfd.config.bits.MenuPendiente==0)&&
    (vfd.config.bits.Menu_Ready==1)){
		if(vfd.menu.contexto.Actual==PORTAL_INICIO){
		       VFDposicion(POS_X_SENS,POSY10);	
			   VFDserial_SendBlock1(&a[0],sizeof(a)); 
               usleep(1000);//500mseg 
			   VFDserial_Sendusint(sens,POS_X_SENS,POSY10,CENTER);
			   VFDserial_SendPhase(phase,phasefrac,POS_X_PHASE,POSY10,RIGHT);//no mover el formato de RIGHT porque left y centrado dara "3  .5"  
				 }}            
 
}//fin de desplegar en portal inicio la sensibildiad y la phase detectada++++++++++++++++++++++++++



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


//MANEJADOR  PRINCIPAL DE EJECUCION DEL MENU++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void menus(unsigned char key){//MANEJADOR DEL LAS FUNCIONES COORDINADAS Y SUBORDINADAS DE LOS MENUS
          /* y tambien tiene entradas a SUB-MENUS EL MENUCONTROL SE ejecuta en el enter del case*/
     vfd.keypad.enable=0;//desabilitar teclado
     cursorMenuControl(key);  

//fin de  void menu(unsigned char key){//MANEJADOR DEL LAS FUNCIONES COORDINADAS Y SUBORDINADAS DE LOS MENUS	   
}// fin del Manejador principal de ejecucion del menu+++++++++++++++++++++++++++++++++++++++++++++++++++++


//CONTROL DEL CURSOR EN CADA MENU, keyx, ES LA  TECLA QUE SE PRESIONO
void cursorMenuControl(unsigned char keyx){//control del cursosr por cada menu
 const short int xpos=235,xpos2=239;
 struct ArbolMenu *p=0;  
 
	  p=&MenuActualScreen;        		
      cursorMenuControlService(keyx,p);

}//FIN CURSOR MENU CONTROL-------------------------------------------------------------------------------


/* this method is filted to be executed w/o error of context failure, 'cos
 * the filter it has been pass through, it control the execution concequence of every key */
void cursorMenuControlService(unsigned char key,struct ArbolMenu *Pantalla){//(key,void (*a)())
unsigned char i;
   // keypad.b.enable=FALSE;
	switch(key){case keyUP:Pantalla->funcKeyUP();break;
		        case keyDN:Pantalla->funcKeyDN();break;
		        case keyRT:Pantalla->funcKeyRT();break;
		        case keyLF:Pantalla->funcKeyLF();break;
		        case keyEN:Pantalla->funcKeyEN();break;
		         }//fin		           default:break;//fin default de segundo switch de PORTAL INICIO
    //keypad.b.enable=TRUE;
}//fin cursorMenuControlService------------------------------------------------------

