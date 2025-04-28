#include "DSP.h"
#include "errorController.h"
#include "queue.h"

/* MODO DE PROCESAMIENTO PARA GIRAR LOS DATOS A LA VIBRACION DE LAS ORDENADAS*/
#define MODO_DE_VIBRACION   GIRO_DE_PLANO_CARTESIANO// GIRO_DE_COORDENADAS_POLARES //GIRO_DE_PLANO_CARTESIANO, GIRO_DE_COORDENADAS_POLARES
#define DDS_X    192

#define DDS_X_1d8 23  //1/4 de pantalla en las X lado negativo de X
#define DDS_X_2d8 45  // 1/2 de la pantalla de las X lado negativo de X
#define DDS_X_3d8 71  //3/4 de pantalla X lado negativo de X
#define DDS_X_4d8 96
#define DDS_X_CX  DDS_X_4d8 //TAMAÑO DE LA MITAD DE RESOLUCION PUNTOS DE LA PANTALLA EN X 192/2 la mitad del ordenada  poitivo  y negativo
#define DDS_X_5d8 120
#define DDS_X_6d8 144
#define DDS_X_7d8 168
#define DDS_X_8d8 192

#define DDS_Y_1d8 16//128/2  la mitad de la absisa  positivo y negativo
#define DDS_Y_2d8  32
#define DDS_Y_3d8  48
#define DDS_Y_4d8  64
#define DDS_Y_5d8  80
#define DDS_Y_6d8  96  
#define DDS_Y_7d8  112
#define DDS_Y_8d8  128
#define DDS_Y_CY   DDS_Y_4d8 

unsigned short int pixelConversionX[3];//DDS_X_8d8];//convierte el pixel Analogo a pixel del zoom actual
unsigned short int pixelConversionY[3];//DDS_Y_8d8];//convierte el pixel Analogo a pixel del zoom actual

//struct _Detection Deteccion;
//struct ZoomControl zoom;
extern struct _DISPLAY_VFD_ vfd;
extern struct _PRODUCT1_ producto2;

void init_Sensibilidad(void){
//unsigned short int cuadroBase;//conversor de sensilidad para 	
	    
             Zoom_init();  
	         vfd.deteccion.EnCurso=0;//no hay deteccion
	         
	
}//inizializa la sensibilidad ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++







/*version1:   generar pixel analogos generamos una lista del pixel digital del DDS coordenadas versus el pixel analogo
 * entre que rango y que rango corresponde un pixel digital DDS
 * version2: vamos a rellenar los arrays con los valores corrrespondienes de analogo signed a pixel DDS para
 * la conversion mas facil y rapida corespondiente al zoom seleccionado */
void generarPixelsAnalogos(void){//signed short int Min,signed short int miny)

       
}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   	   
           