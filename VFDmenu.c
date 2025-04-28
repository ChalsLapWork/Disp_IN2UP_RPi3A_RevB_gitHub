#include "VFDmenu.h"
#include "system.h"


#include "errorController.h"
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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "VFDthread.h"

struct ArbolMenu MenuActualScreen;//la estrucrura del menu actual en pantalla.
extern struct _DISPLAY_VFD_ vfd;

//extern struct _Detection Deteccion;
extern struct _PRODUCT1_ producto2;
GlobalStruct global = {0};
GlobalStruct *AjParamProd= NULL; // Inicialización
GlobalStruct *MenuInfoUser= NULL;
GlobalStruct *MenuTextProc=NULL;//variables para menu texto procesor
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
		case TEXT_PROCESSOR:
							 MenuActualScreen.menuNodo=TEXT_PROCESSOR;
							 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
							 MenuActualScreen.func=displayTextoProcessor;
							 MenuActualScreen.funcKeyUP=TextoProcessorkeyUP;
							 MenuActualScreen.funcKeyRT=TextoProcessorkeyRT;	 
							 MenuActualScreen.funcKeyLF=TextoProcessorkeyLF;
							 MenuActualScreen.funcKeyDN=TextoProcessorkeyDN;
							 MenuActualScreen.funcKeyEN=TextoProcessorkeyEN;
	//						  TextoProcessor.menuPadre=NONE;
							 ret=TRUE;
							 break;    
	case AJUSTES_AVANZADOS:
							 MenuActualScreen.menuNodo=AJUSTES_AVANZADOS;
							 MenuActualScreen.permisos=DESARROLLADOR_PERMISO;
							 MenuActualScreen.func=DisplayAjustesAvanzados;
							 MenuActualScreen.funcKeyUP=AjustesAvanzadoskeyUP;
							 MenuActualScreen.funcKeyRT=AjustesAvanzadoskeyRT;	 
							 MenuActualScreen.funcKeyLF=AjustesAvanzadoskeyLF;
							 MenuActualScreen.funcKeyDN=AjustesAvanzadoskeyDN;
							 MenuActualScreen.funcKeyEN=AjustesAvanzadoskeyEN;
	//						 AjustesAvanzados.menuPadre=AJUSTE_PARAMETRICO_DE_PRODUCTO;
							 ret=TRUE;
							 break;//#if



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
//unsigned char ret=0;
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
	  delay_ms_VFD(500);
      VFDserial_SendBlock(&s[0],sizeof(s));//version
      delay_ms_VFD(500);//aveces se borra   	 
      aux0_uchar = display_centrarNombres((unsigned char)strlen(producto2.name));
      (Status_Prod == MEMO) ? VFDposicion(aux0_uchar, 2) : VFDposicion(x[0], y[0]);
	   VFDserial_SendBlock((const void *)producto2.name, (unsigned char)strlen(producto2.name)+1);  // VFDserial_SendBlock(&a[0],sizeof(a));//NOMBRE PRODUCTO 
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
       vfd.config.bits.BOX_enable=TRUE;//SE AUTORIZA COntruir cajas
}// FIN DESPLIEGUE DEL PORTAL INICIO-------------------------------------------------------------------


void displayMenuInsight(void){// MESPLIEGUE DEL MENU INSGHT----------------------------------------------
//unsigned char ret=0;
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
	  vfd.config.bits.Menu_Ready=1;//se ejecuto este menu
	  vfd.config.bits.BOX_enable=FALSE;//No se autoriza a dibujar cajas

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
        if(!validad_Nivel_Acceso(vfd.NIVEL_ACCESO)){
				   return;}
        if(vfd.NIVEL_ACCESO<2){
			 vfd.config.bits.Menu_Ready=1;
             cambio_de_contexto(PORTAL_INICIO);}
		else{	   
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
	        unsigned char pos= display_centrarNombres((unsigned char)strlen(producto2.name));
            VFDposicion(pos, POSY0);
			VFDserial_SendBlock((const void *)producto2.name, (unsigned char)strlen(producto2.name)+1);   
			displayUINT_var(POSXAJUSPROD,POSY6,&producto2.Sensibilidad,NONE);
			displayPhase_var(POSXAJUSPROD,POSY8);
			displayCuadroMadre_VFD();//despliega el cuadro de barra de deteccion
			display_init_barra_deteccion();
			*cursorx=POSX0;*cursory=POSY6; 
			AjParamProd=&global;
			AjParamProd->editarSensFase=&AjParamProd->igxc1;
			(*AjParamProd->editarSensFase)=(unsigned char)0; //variable que indica si se esta editando el numero sensibildad y Fase
			AjParamProd->arg2=0;////se borraran los contadores
			AjParamProd->arg0=0; //borrar Contadores.
			AjParamProd->usi1=0;//sensibilidad0
			AjParamProd->usi2=0;//Altura0
			AjParamProd->usi3=0;//timepo espera
			AjParamProd->usi4=0;//tiempo Rechazo
			AjParamProd->arg3=0;//tiempo espera,frac
			AjParamProd->arg4=0;//tiempo rechazo frac
	        AjParamProd->igxc4=0;//phase
			AjParamProd->igxc3=0;//phase frac	
			AjParamProd->igxc0=0;//Ganancia0
			vfd.config.bits.BOX_enable=TRUE;// se autoriza a dibujar cajas
			vfd.config.bits.Menu_Ready=1;}
}//fin display ingenieria2 gracida---------------------------------------------------



void displayMenuAjustedeProducto(void){
unsigned char z[]="Menu de Ajuste de Producto  x";
         char *textos[]={">Hacer prueba de ejemplo",
                         "Seleccionar producto",
						 "Nuevo producto",
					  	 "Ajuste de producto",
					   	 "Borrar Producto",
					  	 "Copiar Producto"};
unsigned char x[7]={20,0,8,8, 8, 8, 8};
unsigned char y[7]={0 ,4,6,8,10,12,14};
unsigned char *cursorx,*cursory;
//unsigned char var_ctl;//variable control
unsigned char nmenus;//menus disponibles
            //printf("\033[33m ANTES: vfd.NIVEL_ACCESO = %d\n", vfd.NIVEL_ACCESO);
            if(!validad_Nivel_Acceso(vfd.NIVEL_ACCESO)){
				   return;}
			cursorx=&vfd.menu.cursorx;
			cursory=&vfd.menu.cursory;	
            //printf("DESPUES:  vfd.NIVEL_ACCESO = %d\n\033[0m",  vfd.NIVEL_ACCESO);
            switch(vfd.NIVEL_ACCESO){
			  case 1: nmenus=2;break;//mostrar solo las primeras 2 opciones
			  case 2: case 3:case 4:nmenus=5;break;// mostrar hasta borrar prod
			  case 5: nmenus=6;break;//Mostrar todos
			  default:nmenus=2;break;}//por defecto sin user 	
			VFDclrscr();
			VFDposicion(x[0],y[0]); 
		    VFDserial_SendBlock(&z[0],sizeof(z));
            for (int i = 0; i < nmenus; i++) {
       			 VFDposicion(x[i+1], y[i+1]);
        		 VFDserial_SendBlock(textos[i], strlen(textos[i]) + 1);}
		    *cursorx=POSX0;*cursory=POSY4;
		    vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
}//fin display menu del ajuste de producto------------------------------------------------------------------

void DisplayAjustesAvanzados(void){
unsigned char nmenus,aux,*cursorx,*cursory;
char *textos[]={" x",
                ">Nombre de producto",// 8en revision, debemos leer el valor de la variable si es uno o cero
				"Parametros de deteccion", //10
				"Ajustes tiempo de rechazo",
				"Frecuencia"};//12
unsigned char x[9]={POSXESQ235,0, 8, 8, 8};
unsigned char y[9]={         0,8,10,12,14};

		    if(!validad_Nivel_Acceso(vfd.NIVEL_ACCESO)){
				   return;}
			if(strstr(vfd.tipo_de_Maquina,"Multi")!=NULL)
			    nmenus=5;//contiene la cadena Multi
		    else nmenus=4;//es de una frecuencia, no ponemos string:frecc
		    VFDclrscr();
			cursorx=&vfd.menu.cursorx;
			cursory=&vfd.menu.cursory;	
			for(int i=0;i<nmenus;i++) {
       		   VFDposicion(x[i], y[i]);
        	   VFDserial_SendBlock(textos[i], strlen(textos[i]) + 1);}
            aux=display_centrarNombres((unsigned char)strlen(producto2.name));
            VFDposicion(aux, POSY0); 
   	        VFDserial_SendBlock((const void *)producto2.name, (unsigned char)strlen(producto2.name)+1);  // VFDserial_SendBlock(&a[0],sizeof(a));//NOMBRE PRODUCTO 
		    *cursorx=POSX0;*cursory=POSY8; 
		    vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.    
}// fin display Ajustes Avanzados-----------------------------------------------------





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
				MenuInfoUser->ResetDisplayNum=&global.igxc1;
		        *(MenuInfoUser->ResetDisplayNum)=(unsigned char)0;		
				vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
}//fin Display Menu INFORMATION  usuarioo-------------------------------------------------------------



//El ascii dela   Raiz Cuadrada es el decimal 251d.
void displayTextoProcessor(void){//ascci  251=raiz cuadrada*********************************************
                                 //ascci de x=120  X=88
unsigned char i,*s,j;	
unsigned char tx[]= {"Si  No"};//" x";	 
unsigned char t0[]= "Nombre de Producto";
unsigned char t1[]= "Escribir clave de acceso:";//Contrasena";
unsigned char r1[]= "  1  2  3  4  5  6  7  8  9  0";//Y6
unsigned char r2[]= "  Q  W  E  R  T  Y  U  I  O  P";        //Ñ=A4h
unsigned char r3[]= "  A  S  D  F  G  H  J  K  L  ;";
unsigned char r4[]= "  Z  X  C  V  B  N  M  .  ,   ";
unsigned char r5[]= "  Ma Mi S           <  >  +  -";		
unsigned char x[7]={ 205,0,0,0,0 , 0,  0};
unsigned char y[7]={   0,0,6,8,10,12, 14};
unsigned short int n,m;
unsigned char *cursorx,*cursory;
	
	MenuTextProc=&global;//textProc=&g; 
	cursorx=&vfd.menu.cursorx;
	cursory=&vfd.menu.cursory; 	
	VFDclrscr();	
	VFDposicion(0,0);  
	switch(vfd.menu.contexto.control){
	  case NUEVO_PRODUCTO:VFDserial_SendBlock(&t0[0],sizeof(t0));
	                      for(i=0;i<(NOMBRE_PRODUCTO_SIZE-1);i++)   
	  	                               vfd.Text[i]=0;//limpiamos la var.de texto
	  	                  MenuTextProc->igxc0=MAYUSCULAS; //->igxc0=;//iniciamos desplegando mayuculas
	  	                  MenuTextProc->igxc1=0;//textProc->igxc1=0;//indice del arreglo del Texto. 
	  	                  MenuTextProc->igxc4=0;//textProc->igxc4=0;//no ha habido escritura de ascii  
		                  break;     
	  case NOMBRE_PRODUCTO:VFDserial_SendBlock(&t0[0],sizeof(t0));
	                       VFDposicion(0,POSY2);//Posicion del nombre
	                       VFDserial_SendBlock((void *)&producto2.name[0],sizeof(producto2.name));//nombre de producto display
	                       for(i=0,j=1;j<(NOMBRE_PRODUCTO_SIZE-1);i++,j++)//transferimos el nombre a la variable texto
	                             vfd.Text[i]=producto2.name[j];
	                       MenuTextProc->igxc0=MAYUSCULAS;
	                       s=&vfd.Text[0];//puntamos al 0
	                       MenuTextProc->igxc1=findLastChar(s,NOMBRE_PRODUCTO_SIZE-1);//encontramos el ultimo espacio del ultimo caracter 
	                       MenuTextProc->igxc4=0;//no ha habido una escritura de ascii,puede escribir en el espacio
	                       break;    
	  case SUPERVISOR:    
		                  VFDserial_SendBlock(&t1[0],sizeof(t1));
	  	  	  	  	  	  for(i=0;i<(NOMBRE_PRODUCTO_SIZE-1);i++)   
	  	  	                   vfd.Text[i]=0;//limpiam{os la var.de texto
						  MenuTextProc->igxc0=MAYUSCULAS;//iniciamos desplegando mayuculas
					      MenuTextProc->igxc1=0;//indice del arreglo del Texto. 
				          MenuTextProc->igxc4=0;//no ha habido escritura de ascii  
						  break;     
	  default:  usleep(1);
				errorCritico("Error de software TextProc");//Error de ingeniria de Software
				exit(1);
	          break;
	}//fin switch	
	VFDposicion(x[0],y[0]);  
	VFDserial_SendBlock(&tx[0],sizeof(tx));//display the exit control
	displayTextoProcessorMayusculas();//despliega la pantalla de  mayusculas
	*cursorx=POSX_COL1;*cursory=POSY6;
	VFDposicion(*cursorx,*cursory);
	VFDserial_SendChar('>');
	vfd.config.bits.Menu_Ready=1;//se ejecuto este menu.
}//fin de hoja ejecutiva de despleigue del controlador de texto ************************************************







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
 validos[AJUSTE_PARAMETRICO_DE_PRODUCTO]=true; //poner aqui los menus que contienen la barra de deteccion     
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
unsigned char n=0;

if((deteccion>50)&&(detection0<50))
      producto2.Cuenta_Rechazos++;
if((detection0<25)&&(deteccion>30))
	  producto2.Cuenta_Productos++;

if((vfd.config.bits.MenuPendiente==0)&&
    (vfd.config.bits.Menu_Ready==1)){
		if(vfd.menu.contexto.Actual==PORTAL_INICIO){n=0;
			if(Rechazo0!=producto2.Cuenta_Rechazos){n++;
				VFDserial_Sendusint(producto2.Cuenta_Rechazos,POS_X_CONT_RECHAZ,POS_Y_CONT_RECHAZ,CENTER);}
			if(producto0!=producto2.Cuenta_Productos){n++;		  
				VFDserial_Sendusint(producto2.Cuenta_Productos,POS_X_CONT_PROD,POS_Y_CONT_PROD,CENTER);}
			if(n>0){actualizador_datos1();}}}

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

