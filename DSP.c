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
	         //Offset.Status=0;//debug poner control con EEPROM AQUI FIRST_START;//no estamos listos para evaluar el offset
	         /*if(Deteccion.tipo==NORMAL){
	        			cuadroBase=(Deteccion.Sensibilidad)/8;//7 cuadros base
	        			Deteccion.LIM1=cuadroBase;
	        			Deteccion.LIM2=cuadroBase*2;
	        			Deteccion.LIM3=cuadroBase*3;
	        			Deteccion.LIM4=cuadroBase*4;
	        			Deteccion.LIM5=cuadroBase*5;
	        			Deteccion.LIM6=cuadroBase*6;
	        			Deteccion.LIM7=cuadroBase*7;
	        			Deteccion.LIM8=cuadroBase*8;
	        			Deteccion.LIM9=cuadroBase*9;
	        			Deteccion.LIM10=cuadroBase*10;
	        			Deteccion.LIM11=cuadroBase*11;
	        			Deteccion.LIM12=cuadroBase*12;
	        			Deteccion.LIM13=cuadroBase*13;
	        			Deteccion.LIM14=cuadroBase*14;
	        			Deteccion.LIM15=cuadroBase*15;
	        			Deteccion.LIM16=cuadroBase*16;
	        			Deteccion.LIM17=cuadroBase*17;
	        		 
	        			   }//FIN DETECCION normal
	        			else 
	        				__asm(Halt);//Debug it
	        	    */
	
}//inizializa la sensibilidad ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




//Zoom_init  SE DEBE EJECUTAR CUANDO CAMBIA EL ZOOM  y se esta en el contexto pantalla DDS*/
void Zoom_init(void){          //unsigned short int  x99= (32000,190)(0,95)(-32000,0)
unsigned short int maxx,maxy,ymax,ymin;	
	     if(vfd.menu.dds.zoom.Zoom==0)//el zoom no puede ser cero o crearia un error
	    	 vfd.menu.dds.zoom.Zoom=99;
	     //vfd.menu.dds.zoom.zFactor=32704/98;// Los zooms no son lineales los incrementos
	     //vfd.menu.dds.zoom.Max=(signed short int)(32767-vfd.menu.dds.zoom.zFactor*(unsigned short int)(vfd.menu.dds.zoom.Zoom-1));//Maximo numero graficable en este zoom seleccionado			     vfd.menu.dds.zoom.Max=LIM_Y;//tamaÃ±o del radio del plano cartesiano a dibujar
	     if(vfd.menu.dds.zoom.Max==0)
	    	  vfd.menu.dds.zoom.Max=100;
	     vfd.menu.dds.zoom.indiceConversion= 64/((float)vfd.menu.dds.zoom.Max);
	     
	 vfd.menu.dds.zoom.Cx=CENTRO_X;
	     vfd.menu.dds.zoom.Cy=CENTRO_Y;
	     
	     switch(vfd.menu.dds.zoom.Zoom){
			case 0:errorCritico2("error de parametro de software",59);break; // __asm(Halt);//debug error de software        
			case 1: maxx=ZOOM_MAX_X_01;    maxy=ZOOM_MAX_Y_01;ymax=23919;ymin=369; break;                                 
			case 2: maxx=ZOOM_MAX_X_02;    maxy=ZOOM_MAX_Y_02;ymax=2649;ymin=81; break;                                 
			case 3: maxx=ZOOM_MAX_X_03;    maxy=ZOOM_MAX_Y_03;ymax=1407;ymin=43; break;                                 
			case 4: maxx=ZOOM_MAX_X_04;    maxy=ZOOM_MAX_Y_04;ymax=956;ymin=29;break;                                 
			case 5: maxx=ZOOM_MAX_X_05;    maxy=ZOOM_MAX_Y_05;ymax=724;ymin=22; break;                                 
			case 6: maxx=ZOOM_MAX_X_06;    maxy=ZOOM_MAX_Y_06;ymax=583;ymin=17; break;                                 
			case 7: maxx=ZOOM_MAX_X_07;    maxy=ZOOM_MAX_Y_07;ymax=488;ymin=15; break;                                 
			case 8: maxx=ZOOM_MAX_X_08;    maxy=ZOOM_MAX_Y_08;ymax=419;ymin=12; break;                                 
			case 9: maxx=ZOOM_MAX_X_09;    maxy=ZOOM_MAX_Y_09;ymax=367;ymin=11; break;                                 
			case 10:maxx=ZOOM_MAX_X_10;    maxy=ZOOM_MAX_Y_10;ymax=327;ymin=10; break;                                
			case 11:maxx=ZOOM_MAX_X_11;    maxy=ZOOM_MAX_Y_11;ymax=295;ymin=9; break;                                
			case 12:maxx=ZOOM_MAX_X_12;    maxy=ZOOM_MAX_Y_12;ymax=268;ymin=8; break;                                
			case 13:maxx=ZOOM_MAX_X_13;    maxy=ZOOM_MAX_Y_13;ymax=246;ymin=7; break;                                
			case 14:maxx=ZOOM_MAX_X_14;    maxy=ZOOM_MAX_Y_14;ymax=227;ymin=7; break;                                
			case 15:maxx=ZOOM_MAX_X_15;    maxy=ZOOM_MAX_Y_15;ymax=211;ymin=6; break;                                
			case 16:maxx=ZOOM_MAX_X_16;    maxy=ZOOM_MAX_Y_16;ymax=197;ymin=6; break;                                
			case 17:maxx=ZOOM_MAX_X_17;    maxy=ZOOM_MAX_Y_17;ymax=185;ymin=5; break;                                
			case 18:maxx=ZOOM_MAX_X_18;    maxy=ZOOM_MAX_Y_18;ymax=174;ymin=5; break;                                
			case 19:maxx=ZOOM_MAX_X_19;    maxy=ZOOM_MAX_Y_19;ymax=164;ymin=5; break;                                
			case 20:maxx=ZOOM_MAX_X_20;    maxy=ZOOM_MAX_Y_20;ymax=156;ymin=4; break;                                
			case 21:maxx=ZOOM_MAX_X_21;    maxy=ZOOM_MAX_Y_21;ymax=148;ymin=4; break;                                
			case 22:maxx=ZOOM_MAX_X_22;    maxy=ZOOM_MAX_Y_22;ymax=141;ymin=4; break;                                
			case 23:maxx=ZOOM_MAX_X_23;    maxy=ZOOM_MAX_Y_23;ymax=135;ymin=4; break;                                
			case 24:maxx=ZOOM_MAX_X_24;    maxy=ZOOM_MAX_Y_24;ymax=129;ymin=3; break;                                
			case 25:maxx=ZOOM_MAX_X_25;    maxy=ZOOM_MAX_Y_25;ymax=123;ymin=3; break;                                 
			case 26:maxx=ZOOM_MAX_X_26;    maxy=ZOOM_MAX_Y_26;ymax=119;ymin=3; break; 
			case 27:maxx=ZOOM_MAX_X_27;    maxy=ZOOM_MAX_Y_27;ymax=114;ymin=3; break; 
			case 28:maxx=ZOOM_MAX_X_28;    maxy=ZOOM_MAX_Y_28;ymax=110;ymin=3; break; 
			case 29:maxx=ZOOM_MAX_X_29;    maxy=ZOOM_MAX_Y_29;ymax=106;ymin=3; break; 
			case 30:maxx=ZOOM_MAX_X_30;    maxy=ZOOM_MAX_Y_30;ymax=102;ymin=3; break; 
			case 31:maxx=ZOOM_MAX_X_31;    maxy=ZOOM_MAX_Y_31;ymax=99;ymin=3; break; 
			case 32:maxx=ZOOM_MAX_X_32;    maxy=ZOOM_MAX_Y_32;ymax=96;ymin=2; break; 
			case 33:maxx=ZOOM_MAX_X_33;    maxy=ZOOM_MAX_Y_33;ymax=93;ymin=2; break; 
			case 34:maxx=ZOOM_MAX_X_34;    maxy=ZOOM_MAX_Y_34;ymax=89;ymin=2; break; 
			case 35:maxx=ZOOM_MAX_X_35;    maxy=ZOOM_MAX_Y_35;ymax=87;ymin=2; break; 
			case 36:maxx=ZOOM_MAX_X_36;    maxy=ZOOM_MAX_Y_36;ymax=85;ymin=2; break; 
			case 37:maxx=ZOOM_MAX_X_37;    maxy=ZOOM_MAX_Y_37;ymax=82;ymin=2; break; 
			case 38:maxx=ZOOM_MAX_X_38;    maxy=ZOOM_MAX_Y_38;ymax=80;ymin=2; break; 
			case 39:maxx=ZOOM_MAX_X_39;    maxy=ZOOM_MAX_Y_39;ymax=78;ymin=2; break; 
			case 40:maxx=ZOOM_MAX_X_40;    maxy=ZOOM_MAX_Y_40;ymax=75;ymin=2; break; 
			case 41:maxx=ZOOM_MAX_X_41;    maxy=ZOOM_MAX_Y_41;ymax=74;ymin=2;  break; 
			case 42:maxx=ZOOM_MAX_X_42;    maxy=ZOOM_MAX_Y_42;ymax=72;ymin=2;  break; 
			case 43:maxx=ZOOM_MAX_X_43;    maxy=ZOOM_MAX_Y_43;ymax=70;ymin=2;  break; 
			case 44:maxx=ZOOM_MAX_X_44;    maxy=ZOOM_MAX_Y_44;ymax=69;ymin=2;  break; 
			case 45:maxx=ZOOM_MAX_X_45;    maxy=ZOOM_MAX_Y_45;ymax=67;ymin=2;  break; 
			case 46:maxx=ZOOM_MAX_X_46;    maxy=ZOOM_MAX_Y_46;ymax=66;ymin=2;  break; 
			case 47:maxx=ZOOM_MAX_X_47;    maxy=ZOOM_MAX_Y_47;ymax=64;ymin=1;  break; 
			case 48:maxx=ZOOM_MAX_X_48;    maxy=ZOOM_MAX_Y_48;ymax=63;ymin=1;  break; 
			case 49:maxx=ZOOM_MAX_X_49;    maxy=ZOOM_MAX_Y_49;ymax=61;ymin=1;  break; 
			case 50:maxx=ZOOM_MAX_X_50;    maxy=ZOOM_MAX_Y_50;ymax=60;ymin=1;  break; 
			case 51:maxx=ZOOM_MAX_X_51;    maxy=ZOOM_MAX_Y_51;ymax=59;ymin=1;  break; 
			case 52:maxx=ZOOM_MAX_X_52;    maxy=ZOOM_MAX_Y_52;ymax=58;ymin=1;  break; 
			case 53:maxx=ZOOM_MAX_X_53;    maxy=ZOOM_MAX_Y_53;ymax=57;ymin=1;  break; 
			case 54:maxx=ZOOM_MAX_X_54;    maxy=ZOOM_MAX_Y_54;ymax=56;ymin=1;  break; 
			case 55:maxx=ZOOM_MAX_X_55;    maxy=ZOOM_MAX_Y_55;ymax=55;ymin=1;  break;                                  
			case 56:maxx=ZOOM_MAX_X_56;    maxy=ZOOM_MAX_Y_56;ymax=54;ymin=1;  break;                                  
			case 57:maxx=ZOOM_MAX_X_57;    maxy=ZOOM_MAX_Y_57;ymax=53;ymin=1;  break;                                  
			case 58:maxx=ZOOM_MAX_X_58;    maxy=ZOOM_MAX_Y_58;ymax=52;ymin=1;  break;                                   
			case 59:maxx=ZOOM_MAX_X_59;    maxy=ZOOM_MAX_Y_59;ymax=51;ymin=1;  break;                                   
			case 60:maxx=ZOOM_MAX_X_60;    maxy=ZOOM_MAX_Y_60;ymax=50;ymin=1;  break;                                   
			case 61:maxx=ZOOM_MAX_X_61;    maxy=ZOOM_MAX_Y_61;ymax=49;ymin=1;  break;                                   
			case 62:maxx=ZOOM_MAX_X_62;    maxy=ZOOM_MAX_Y_62;ymax=48;ymin=1; break;                                    
			case 63:maxx=ZOOM_MAX_X_63;    maxy=ZOOM_MAX_Y_63;ymax=48;ymin=1; break;                                   
			case 64:maxx=ZOOM_MAX_X_64;    maxy=ZOOM_MAX_Y_64;ymax=47;ymin=1; break;                                   
			case 65:maxx=ZOOM_MAX_X_65;    maxy=ZOOM_MAX_Y_65;ymax=46;ymin=1; break;                                  
			case 66:maxx=ZOOM_MAX_X_66;    maxy=ZOOM_MAX_Y_66;ymax=45;ymin=1; break;                                   
			case 67:maxx=ZOOM_MAX_X_67;    maxy=ZOOM_MAX_Y_67;ymax=45;ymin=1; break;                                    
			case 68:maxx=ZOOM_MAX_X_68;    maxy=ZOOM_MAX_Y_68;ymax=44;ymin=1; break;                                     
			case 69:maxx=ZOOM_MAX_X_69;    maxy=ZOOM_MAX_Y_69;ymax=43;ymin=1; break;                                     
			case 70:maxx=ZOOM_MAX_X_70;    maxy=ZOOM_MAX_Y_70;ymax=43;ymin=1; break;                                    
			case 71:maxx=ZOOM_MAX_X_71;    maxy=ZOOM_MAX_Y_71;ymax=42;ymin=1; break;                                    
			case 72:maxx=ZOOM_MAX_X_72;    maxy=ZOOM_MAX_Y_72;ymax=42;ymin=1; break;                                    
			case 73:maxx=ZOOM_MAX_X_73;    maxy=ZOOM_MAX_Y_73;ymax=41;ymin=1; break;                                     
			case 74:maxx=ZOOM_MAX_X_74;    maxy=ZOOM_MAX_Y_74;ymax=40;ymin=1; break;                                     
			case 75:maxx=ZOOM_MAX_X_75;    maxy=ZOOM_MAX_Y_75;ymax=40;ymin=1; break;                                    
			case 76:maxx=ZOOM_MAX_X_76;    maxy=ZOOM_MAX_Y_76;ymax=39;ymin=1; break;                                     
			case 77:maxx=ZOOM_MAX_X_77;    maxy=ZOOM_MAX_Y_77;ymax=39;ymin=1; break;                                     
			case 78:maxx=ZOOM_MAX_X_78;    maxy=ZOOM_MAX_Y_78;ymax=38;ymin=1; break;                                    
			case 79:maxx=ZOOM_MAX_X_79;    maxy=ZOOM_MAX_Y_79;ymax=38;ymin=1; break;
			case 80:maxx=ZOOM_MAX_X_80;    maxy=ZOOM_MAX_Y_80;ymax=37;ymin=1; break;                                    
			case 81:maxx=ZOOM_MAX_X_81;    maxy=ZOOM_MAX_Y_81;ymax=37;ymin=1; break;                                    
			case 82:maxx=ZOOM_MAX_X_82;    maxy=ZOOM_MAX_Y_82;ymax=36;ymin=1; break;
			case 83:maxx=ZOOM_MAX_X_83;    maxy=ZOOM_MAX_Y_83;ymax=36;ymin=1; break;                                    
			case 84:maxx=ZOOM_MAX_X_84;    maxy=ZOOM_MAX_Y_84;ymax=35;ymin=1; break;                                    
			case 85:maxx=ZOOM_MAX_X_85;    maxy=ZOOM_MAX_Y_85;ymax=35;ymin=1; break;
			case 86:maxx=ZOOM_MAX_X_86;    maxy=ZOOM_MAX_Y_86;ymax=35;ymin=1; break;                                   			                                  
			case 87:maxx=ZOOM_MAX_X_87;    maxy=ZOOM_MAX_Y_87;ymax=34;ymin=1; break;
			case 88:maxx=ZOOM_MAX_X_88;    maxy=ZOOM_MAX_Y_88;ymax=34;ymin=1; break;
			case 89:maxx=ZOOM_MAX_X_89;    maxy=ZOOM_MAX_Y_89;ymax=33;ymin=2; break;
			case 90:maxx=ZOOM_MAX_X_90;    maxy=ZOOM_MAX_Y_90;ymax=33;ymin=2; break;  			
			case 91:maxx=ZOOM_MAX_X_91;    maxy=ZOOM_MAX_Y_91;ymax=33;ymin=2; break;                                    
			case 92:maxx=ZOOM_MAX_X_92;    maxy=ZOOM_MAX_Y_92;ymax=32;ymin=2;  break;                                     
			case 93:maxx=ZOOM_MAX_X_93;    maxy=ZOOM_MAX_Y_93;ymax=32;ymin=2;  break;
			case 94:maxx=ZOOM_MAX_X_94;    maxy=ZOOM_MAX_Y_94;ymax=32;ymin=2;  break;	
			case 95:maxx=ZOOM_MAX_X_95;    maxy=ZOOM_MAX_Y_95;ymax=31;ymin=2;  break;   
			case 96:maxx=ZOOM_MAX_X_96;    maxy=ZOOM_MAX_Y_96;ymax=31;ymin=2;  break;                                       
			case 97:maxx=ZOOM_MAX_X_97;    maxy=ZOOM_MAX_Y_97;ymax=31;ymin=2;  break;                                        
			case 98:maxx=ZOOM_MAX_X_98;    maxy=ZOOM_MAX_Y_98; break;
			case 99:maxx=ZOOM_MAX_X_99;    maxy=ZOOM_MAX_Y_99; break;
			        
			default:break;	
	      	     }//fin zoom		
      vfd.menu.dds.zoom.Maxx=maxx;//limite del numero digital desplegable en DDS en funciona del Zoom
      vfd.menu.dds.zoom.Maxy=maxy; 
      vfd.menu.dds.zoom.Ymax=ymax;
      vfd.menu.dds.zoom.Ymin=ymin;
	  //generarPixelsAnalogos();//(0,0);//genera una lista de valores analogos que corresponden en una lista a un pixel digital en un zoom dado
      
      
}//fin zoom init -----------------------------------------------------------------------------------------




/*version1:   generar pixel analogos generamos una lista del pixel digital del DDS coordenadas versus el pixel analogo
 * entre que rango y que rango corresponde un pixel digital DDS
 * version2: vamos a rellenar los arrays con los valores corrrespondienes de analogo signed a pixel DDS para
 * la conversion mas facil y rapida corespondiente al zoom seleccionado */
void generarPixelsAnalogos(void){//signed short int Min,signed short int miny){

       
}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   	   
           