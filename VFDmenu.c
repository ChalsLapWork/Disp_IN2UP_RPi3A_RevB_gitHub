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
#include "VFDisplay.h"

struct ArbolMenu MenuActualScreen;//la estrucrura del menu actual en pantalla.
//extern struct _PRODUCTO1_ producto;
extern struct _DISPLAY_VFD_ vfd;
//extern struct _Detection Deteccion;
extern struct _PRODUCT1_ producto2;
GlobalStruct global = {0};
GlobalStruct *AjParamProd= NULL; // Inicialización
GlobalStruct *MenuInfoUser= NULL;
extern struct _PRODUCT1_ producto2;


unsigned char InitArbolMenu(unsigned char destino){// initializar estructura de datos de los menus
auto unsigned char ret=0;	 
	 switch(destino){
	  /* PANTALLA NIVEL 0************************************************************** */
		 case PORTAL_INICIO: MenuActualScreen.menuNodo=PORTAL_INICIO;
		                     MenuActualScreen.permisos=DESARROLLADOR_PERMISO;//------------------------------------EN-REVISION
		                     MenuActualScreen.func=0;
		                     //MenuActualScreen.func1=PortalinicioDisplay; // -------------------------------------------------------EN-REVISION    		 
		                     MenuActualScreen.func=PortalinicioDisplay;
		                     MenuActualScreen.funcKeyUP=PortaliniciokeyUP;
		                     MenuActualScreen.funcKeyRT=PortaliniciokeyRT;
		                     MenuActualScreen.funcKeyLF=PortaliniciokeyLF;
		                     MenuActualScreen.funcKeyDN=PortaliniciokeyDN;//Insert the function pointer
		                     MenuActualScreen.funcKeyEN=PortaliniciokeyEN;//---poner en los apuntadores apuntar a las funciones--------------4
							 ret=TRUE;
		                     break;	
		 case MENU_INSIGHT:  MenuActualScreen.menuNodo=MENU_INSIGHT;
							 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
							 MenuActualScreen.func=displayMenuInsight;
							 MenuActualScreen.funcKeyUP=MenuInsightkeyUP;
							 MenuActualScreen.funcKeyDN=MenuInsightkeyDN;
							 MenuActualScreen.funcKeyRT=MenuInsightkeyRT;
							 MenuActualScreen.funcKeyLF=MenuInsightkeyLF;
							 MenuActualScreen.funcKeyEN=MenuInsightkeyEN;//MenuInsightkeyEN;
							 ret=TRUE;
							 break;	
/* MENUS NIVEL 2  ******************************************************************/     
		 case AJUSTE_DE_PRODUCTO:MenuActualScreen.menuNodo=AJUSTE_DE_PRODUCTO;
		 	 	 	 	 	 	 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
		 	 	 	 	 	 	 MenuActualScreen.func=displayMenuAjustedeProducto;//no tiene porque es un menu
		 	 	 	 	 	 	 MenuActualScreen.funcKeyUP=AjusteProductokeyUP;
		 	 	 	 	 	     MenuActualScreen.funcKeyRT=AjusteProductokeyRT;	 
		 	 	 	 	 	     MenuActualScreen.funcKeyLF=AjusteProductokeyLF;
		 	 	 	 	 	     MenuActualScreen.funcKeyDN=AjusteProductokeyDN;
		 	 	 	 	 	     MenuActualScreen.funcKeyEN=AjusteProductokeyEN;
		 	 	 	 	 	     ret=TRUE;
		 	 	 	 	 	     break;
		 case AJUSTE_PARAMETRICO_DE_PRODUCTO:
							 MenuActualScreen.menuNodo=AJUSTE_PARAMETRICO_DE_PRODUCTO;
							 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
							 MenuActualScreen.func=DisplayAjusteParamProd;
							 MenuActualScreen.funcKeyUP=AjusteParamProdkeyUP;
							 MenuActualScreen.funcKeyRT=AjusteParamProdkeyRT;	 
							 MenuActualScreen.funcKeyLF=AjusteParamProdkeyLF;
							 MenuActualScreen.funcKeyDN=AjusteParamProdkeyDN;
							 MenuActualScreen.funcKeyEN=AjusteParamProdkeyEN;
							 ret=TRUE;
							 break;
		 case AJUSTE_DE_SISTEMA:
			  	  	  	  	 MenuActualScreen.menuNodo=AJUSTE_DE_SISTEMA;
							 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
							 MenuActualScreen.func=DisplayMenuAjustedeSistema;
							 MenuActualScreen.funcKeyUP=AjustedeSistemakeyUP;
							 MenuActualScreen.funcKeyRT=AjustedeSistemakeyRT;	 
							 MenuActualScreen.funcKeyLF=AjustedeSistemakeyLF;
							 MenuActualScreen.funcKeyDN=AjustedeSistemakeyDN;
							 MenuActualScreen.funcKeyEN=AjustedeSistemakeyEN;
							 ret=TRUE;
							 break;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++-------- PASO-2							 
		 case PANTALLA_DDS://---------------------------------------------------------- PASO 3 IR A VFDkey.h-----
							 MenuActualScreen.menuNodo=PANTALLA_DDS;
							 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
							 //MenuActualScreen.func=DDS_HANDLER;
							/* MenuActualScreen.funcKeyUP=PANTALLA_DDSkeyUP_v2;
							 MenuActualScreen.funcKeyRT=PANTALLA_DDSkeyRT_v2;	 
							 MenuActualScreen.funcKeyLF=PANTALLA_DDSkeyLF_v2;
							 MenuActualScreen.funcKeyDN=PANTALLA_DDSkeyDN_v2;
							 MenuActualScreen.funcKeyEN=PANTALLA_DDSkeyEN_v2;
							 */
							 ret=TRUE;
							 break;
		 case INFORMACION_DE_USUARIO:			 
			 	 	 	 	 MenuActualScreen.menuNodo=INFORMACION_DE_USUARIO;
							 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
							 MenuActualScreen.func=DisplayMenuInformacionUsuario;
							 MenuActualScreen.funcKeyUP=MenuInformacionUsuariokeyUP;
							 MenuActualScreen.funcKeyRT=MenuInformacionUsuariokeyRT;	 
							 MenuActualScreen.funcKeyLF=MenuInformacionUsuariokeyLF;
							 MenuActualScreen.funcKeyDN=MenuInformacionUsuariokeyDN;
							 MenuActualScreen.funcKeyEN=MenuInformacionUsuariokeyEN;
							 ret=TRUE;
							 break;
	



         default: errorCritico2("error de InitArbol,19",19);break;                     
        }//fin switch ++EN CONSTRUCCION ++++++++++++++++++++++++++++++++++++
return ret;
}//fin portal inicion++++++++++++++++++++++++++++++++++++++++++++++



//despliega el menu principal, el recurso se solicita y gestiona
//desde el hilo padre del manejo del menu.
//Este metodo Solo se ejecuta una vez sin instancias
void  PortalinicioDisplay(void){//Funcion Suprema de Despliegue de la Pantalla0
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
      vfd.menu.CuadroMadreReady=FALSE;
      NoErrorOK();			  
      VFDclrscr();
	  delay_ms_VFD(500);
      VFDposicion(65,0);
      VFDserial_SendBlock(&s[0],sizeof(s));//version
	  aux3_char=producto2.name[1];
	  aux1_usi=length(&producto2.name[0],sizeof(producto2.name));  	 
      aux0_uchar=display_centrarNombres((unsigned char)aux1_usi);
      (Status_Prod == MEMO) ? VFDposicion(aux0_uchar, 2) : VFDposicion(x[0], y[0]);

	   VFDserial_SendBlock(&a[0],sizeof(a)); 
	   VFDposicion(x[1],y[1]);
	   VFDserial_SendBlock(&b[0],sizeof(b));
       VFDposicion(x[2],y[2]);
       VFDserial_SendBlock(&c[0],sizeof(c));
       VFDposicion(x[3],y[3]);
       VFDserial_SendBlock(&d[0],sizeof(d));
	   displayCuadroMadre_VFD();
       vfd.menu.CuadroMadreReady=TRUE;
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


void displayMenuInsight(void){// MESPLIEGUE DEL MENU INSGHT----------------------------------------------
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
      VFDserial_SendBlock(&z[0],sizeof(z));
	  VFDposicion(x[1],y[1]);
	  VFDserial_SendBlock(&a[0],sizeof(a));
	  VFDposicion(x[2],y[2]);
      VFDserial_SendBlock(&c[0],sizeof(c));
	  VFDposicion(x[3],y[3]);
	  VFDserial_SendBlock(&w[0],sizeof(w));
	  VFDposicion(x[4],y[4]);
	  VFDserial_SendBlock(&v[0],sizeof(v));
	  VFDposicion(x[5],y[5]);
	  VFDserial_SendBlock(&b[0],sizeof(b));
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




void DisplayAjusteParamProd(void){
unsigned char a[]=" x";
//unsigned char b[]=VERSION_FIRMWARE;
//unsigned char c[]=">Inizializar memoria"; //2
//unsigned char d[]="PSU E/S";              //4
unsigned char e[]=">Sensibilidad"; //6
unsigned char f[]="Fase         ";// 8en revision, debemos leer el valor de la variable si es uno o cero
unsigned char h[]="Borrar contadores"; //10
unsigned char i[]="Pantalla DDS";               //12
unsigned char j[]="Ajustes Avanzados";   //14
unsigned char x[9]={POSXESQ235,0,0,8,0, 8, 8, 8, 8};
unsigned char y[9]={         0,0,2,4,6, 8,10,12,14};
unsigned char *cursorx,*cursory;
//word n;
		cursorx=&vfd.menu.cursorx;
		cursory=&vfd.menu.cursory;
		VFDclrscr();
		VFDposicion(x[0],y[0]);  
		VFDserial_SendBlock(&a[0],sizeof(a));
		VFDposicion(x[4],y[4]);   
	    VFDserial_SendBlock(&e[0],sizeof(e));
		VFDposicion(x[5],y[5]); 
	    VFDserial_SendBlock(&f[0],sizeof(f));
		VFDposicion(x[6],y[6]);   
	    VFDserial_SendBlock(&h[0],sizeof(h));
	    VFDposicion(x[7],y[7]);   
	    VFDserial_SendBlock(&i[0],sizeof(i));
	    VFDposicion(x[8],y[8]);
	    VFDserial_SendBlock(&j[0],sizeof(j));
	    displayUINT_var(POSXAJUSPROD,POSY6,&producto2.Sensibilidad,NONE);
	    displayPhase_var(POSXAJUSPROD,POSY8);
	   // displayFaseVar();
	    displayCuadroMadre_VFD();//despliega el cuadro de barra de deteccion
	    vfd.box.box0=0;//se inicia la barra en 0s. sino empieza ala mitad
	    *cursorx=POSX0;*cursory=POSY6; 
	    //isEnable_Keypad(WAIT);//Desabilita el teclado uno milisegundos.
		AjParamProd=&global;
		AjParamProd->editarSensFase=&AjParamProd->var1;
        *(AjParamProd->editarSensFase)=(unsigned char)0; //variable que indica si se esta editando el numero sensibildad y Fase
        AjParamProd->arg2=&global.var2;
		*(AjParamProd->arg2)=(unsigned char)0;////se borraran los contadores
         vfd.config.bits.Menu_Ready=1;
}//fin display ingenieria2 gracida---------------------------------------------------



void displayMenuAjustedeProducto(void){
unsigned char z[]="Menu de Ajuste de Producto  x";
unsigned char a[]=">Hacer prueba de ejemplo";
unsigned char c[]="Seleccionar producto";
unsigned char w[]="Nuevo producto";
unsigned char v[]="Ajuste de producto";
unsigned char b[]="Borrar Producto";
unsigned char q[]="Copiar Producto"; 
unsigned char x[7]={20,0,8,8, 8, 8, 8};
unsigned char y[7]={0 ,4,6,8,10,12,14};
unsigned char *cursorx,*cursory;
//word n;
			cursorx=&vfd.menu.cursorx;
			cursory=&vfd.menu.cursory;	
		    VFDclrscr();
			VFDposicion(x[0],y[0]); //  delay1us();
		    VFDserial_SendBlock(&z[0],sizeof(z));//delay1us();
			VFDposicion(x[1],y[1]);//   delay1us();
		    VFDserial_SendBlock(&a[0],sizeof(a));//delay1us();
			VFDposicion(x[2],y[2]);   //delay1us();
		    VFDserial_SendBlock(&c[0],sizeof(c));//delay1us();
			VFDposicion(x[3],y[3]); //  delay1us();
			VFDserial_SendBlock(&w[0],sizeof(w));//delay1us();
			VFDposicion(x[4],y[4]); //  delay1us();
		    VFDserial_SendBlock(&v[0],sizeof(v));//delay1us();
			VFDposicion(x[5],y[5]);  // delay1us();
		    VFDserial_SendBlock(&b[0],sizeof(b));//delay1us();
		    VFDposicion(x[6],y[6]);   //delay1us();
		    VFDserial_SendBlock(&q[0],sizeof(q));//delay1us();
		    //VFDposicion(x[7],y[7]);//posiCION del cursor despues de desplegar el menu  
		    *cursorx=POSX0;*cursory=POSY4;
		    //isEnable_Keypad(WAIT);//Desabilita el teclado uno milisegundos.
		    vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.

}//fin display menu del ajuste de producto------------------------------------------------------------------



void DisplayMenuAjustedeSistema(void){//despliega el menu del AJUSTE DE SISTEMA-------------
unsigned char z[]="Menu de Ajuste de Sistema   x";
unsigned char a[]=">Menu Administrativo           ";
unsigned char c[]=" Ajuste de vibracion           ";
unsigned char w[]=" Configurar entradas de sistema";
unsigned char v[]=" Control de frecuencia";
unsigned char b[]=" ID de comunicaciones";
unsigned char q[]=" Ingenieria Gracida"; 
unsigned char x[7]={20,0,0,0,0, 0, 0};
unsigned char y[7]={0 ,4,6,8,10,12,14};
unsigned char *cursorx,*cursory;
//word n;
			  cursorx=&vfd.menu.cursorx;
			  cursory=&vfd.menu.cursory;	
  			  VFDclrscr();
			  VFDposicion(x[0],y[0]); //  delay1us();
		      VFDserial_SendBlock(&z[0],sizeof(z));//delay1us();
		  	  VFDposicion(x[1],y[1]);   //delay1us();
		      VFDserial_SendBlock(&a[0],sizeof(a));//delay1us();
			  VFDposicion(x[2],y[2]);   //delay1us();
		      VFDserial_SendBlock(&c[0],sizeof(c));//delay1us();
			  VFDposicion(x[3],y[3]);   //delay1us();
			  VFDserial_SendBlock(&w[0],sizeof(w));//delay1us();
			  VFDposicion(x[4],y[4]);   //delay1us();
		      VFDserial_SendBlock(&v[0],sizeof(v));//delay1us();
			  VFDposicion(x[5],y[5]);  // delay1us();
		      VFDserial_SendBlock(&b[0],sizeof(b));//delay1us();
		      VFDposicion(x[6],y[6]);  // delay1us();
		      VFDserial_SendBlock(&q[0],sizeof(q));//delay1us();
		      //VFDposicion(x[7],y[7]);//posiCION del cursor despues de desplegar el menu  
		      *cursorx=POSX0;*cursory=POSY4;
			  //isEnable_Keypad(WAIT);//Desabilita el teclado uno milisegundos.
			  vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
}//fin display del menu de AJUSTE DE SISTEMA-----------------------------------------------------------------


void DisplayMenuInformacionUsuario(void){
unsigned char r[]=" x";
unsigned char z[]=">Hacer pruebas de ruido";
unsigned char a[]="Medidas de voltaje";
unsigned char c[]="Ajustes de producto";
unsigned char w[]="Tiempos de Rechazo";
unsigned char v[]="Ajuste sistema de entradas";
unsigned char b[]="ID de maquinas";//en revision--en desarrollo, debemmos leer el valor de la variable en 1 y0
unsigned char q[]="Cuenta producto"; 
unsigned char x[8]={POSXESQUINA,0,8,8,8, 8, 8, 8};
unsigned char y[8]={          0,2,4,6,8,10,12,14};
unsigned char *cursorx,*cursory;
//word n;
			    cursorx=&vfd.menu.cursorx;
			    cursory=&vfd.menu.cursory;	
			    VFDclrscr();
				VFDposicion(x[0],y[0]);   //delay1us();
				VFDserial_SendBlock(&r[0],sizeof(r));//delay1us();
				VFDposicion(x[1],y[1]);   //delay1us();
			    VFDserial_SendBlock(&z[0],sizeof(z));//delay1us();
				VFDposicion(x[2],y[2]);  // delay1us();
			    VFDserial_SendBlock(&a[0],sizeof(a));//delay1us();
				VFDposicion(x[3],y[3]);   //delay1us();
			    VFDserial_SendBlock(&c[0],sizeof(c));//delay1us();
				VFDposicion(x[4],y[4]);   //delay1us();
				VFDserial_SendBlock(&w[0],sizeof(w));//delay1us();
				VFDposicion(x[5],y[5]);   //delay1us();
			    VFDserial_SendBlock(&v[0],sizeof(v));//delay1us();
				VFDposicion(x[6],y[6]);   //delay1us();
			    VFDserial_SendBlock(&b[0],sizeof(b));//delay1us();
			    VFDposicion(x[7],y[7]);   //delay1us();
			    VFDserial_SendBlock(&q[0],sizeof(q));//delay1us();
			    //VFDposicion(x[7],y[7]);//posiCION del cursor despues de desplegar el menu  
			    *cursorx=POSX0;*cursory=POSY2;//POSICION DE LA FLECHA LA DEJAMOS EN 0,2
			    //isEnable_Keypad(WAIT);//Desabilita el teclado uno milisegundos.
			    MenuInfoUser=&global;
				MenuInfoUser->ResetDisplayNum=&global.var1;
		        *(MenuInfoUser->ResetDisplayNum)=(unsigned char)0;		
				vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
}//fin Display Menu INFORMATION  usuarioo-------------------------------------------------------------






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
			   VFDserial_SendBlock(&a[0],sizeof(a)); 
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
}//fin unsigned char display_centrarNombres(unsigned char nchars)------------------------------------


//MANEJADOR  PRINCIPAL DE EJECUCION DEL MENU++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void menus(unsigned char key){//MANEJADOR DEL LAS FUNCIONES COORDINADAS Y SUBORDINADAS DE LOS MENUS
          /* y tambien tiene entradas a SUB-MENUS EL MENUCONTROL SE ejecuta en el enter del case*/
     vfd.keypad.enable=0;//desabilitar teclado
     cursorMenuControl(key);  

//fin de  void menu(unsigned char key)//MANEJADOR DEL LAS FUNCIONES COORDINADAS Y SUBORDINADAS DE LOS MENUS	   
}// fin del Manejador principal de ejecucion del menu+++++++++++++++++++++++++++++++++++++++++++++++++++++


//CONTROL DEL CURSOR EN CADA MENU, keyx, ES LA  TECLA QUE SE PRESIONO
void cursorMenuControl(unsigned char keyx){//control del cursosr por cada menu
 const short int xpos=235,xpos2=239;
 struct ArbolMenu *p=0;  
 
	  p=&MenuActualScreen;        		
      cursorMenuControlService(keyx,p);

}//FIN CURSOR MENU CONTROL-------------------------------------------------------------------------------

unsigned char procSensxDigitoLF(unsigned char posx,unsigned char posy,unsigned short int *Sens){
	 if(*Sens==1)
		return FALSE;  
	 else --(*Sens); 		 
     BarraDet_displayUINT_var(posx,posy,Sens);//displayUINT_var(POSXCFNUM,POSY2,&Sensibilidad,NONE);	
return TRUE;
}//fin ---procSensxDigitoLF--------------------------------------------


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
				default:errorCritico("error de software en cursosr serivces");break;
		         }//fin		           default:break;//fin default de segundo switch de PORTAL INICIO
    //keypad.b.enable=TRUE;
}//fin cursorMenuControlService------------------------------------------------------

