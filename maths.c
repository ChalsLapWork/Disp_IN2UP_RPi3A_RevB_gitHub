
#include "system.h"
#include "DSP.h"
#include "maths.h"
#include "system.h"
#include "queue.h"
#include "VFDisplay.h"
#include "errorController.h"


extern unsigned char phase,phasefrac;//phase de ajustes de deteccion la variable fraccionaria es de la misma vriable
//extern struct _GLOBAL_CONTEXTO gxc,gxc2,gxc3,gxc4;
//extern struct _Comando_DDS dds;
//extern struct ZoomControl zoom;
//extern struct _Detection Deteccion;
extern struct _PRODUCT1_ producto2;
extern struct _DISPLAY_VFD_ vfd;



/*  recalcula y ajusta los valores de la barra de deteccion para 
  ponerlos en valores fijos de cinco en cinco */
unsigned char recalcular_valor_Ser_Barr_det(unsigned char val){
unsigned char ret,estado;
       if((val>=15)&&(val<20)){ret=1;goto switch1;}
       if((val>=20)&&(val<25)){ret=2;goto switch1;}
       if((val>=25)&&(val<30)){ret=3;goto switch1;}
       if((val>=30)&&(val<35)){ret=4;goto switch1;}
       if((val>=35)&&(val<40)){ret=5;goto switch1;}
       if((val>=40)&&(val<45)){ret=6;goto switch1;}
       if((val>=45)&&(val<50)){ret=7;goto switch1;}
       if((val>=50)&&(val<55)){ret=8;goto switch1;}
       if((val>=55)&&(val<60)){ret=9;goto switch1;}
       if((val>=60)&&(val<65)){ret=10;goto switch1;}
       if((val>=65)&&(val<70)){ret=11;goto switch1;}
       if((val>=70)&&(val<75)){ret=12;goto switch1;}
       if((val>=75)&&(val<80)){ret=13;goto switch1;}
       if((val>=80)&&(val<85)){ret=14;goto switch1;}
       if((val>=85)&&(val<90)){ret=15;goto switch1;}
       if((val>=90)&&(val<95)){ret=16;goto switch1;}
       if(val>95){ret=17;}      
switch1:
return ret;
}//fin de recalcular valores de serial barra de deteccion





/* tenemos el registro de los  un registro de las lineas x del despliegue en pantalla de los pixeles
 *  el registro guarda los pixeles que se encienden o no en valor absoluto para se pintados,
 *  param tro bit indica cuales bits del registro estan encendidos
 *  este metodo converte el numero del registro y el bit en un numero
 *  que representa la coordenada la coordenada absoluta a de 1 a 192 ya convertia a dds absoluto.
 * */
unsigned char get_Coord_Num(unsigned char xn,unsigned char bit){
const unsigned char byte[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

   switch(xn){
	   case 0:switch(byte[bit]){//b
		         case 1:return 192;break;
		         case 2:return 1;break;
		         case 4:return 2;break;
		         case 8:return 3;break;
		         case 16:return 4;break;
		         case 32:return 5;break;
		         case 64:return 6;break;
		         case 128:return 7;break;
		         default:break;}
	          break;//fin de 0
	   case 1:switch(byte[bit]){
		         case 1:return 8;break;
		         case 2:return 9;break;
		         case 4:return 10;break;
		         case 8:return 11;break;
		         case 16:return 12;break;
		         case 32:return 13;break;
		         case 64:return 14;break;
		         case 128:return 15;break;
		         default:break;}
		      break;//fin de 1
       case 2:switch(byte[bit]){
    	         case 1: return 16;break;
    	         case 2: return 17;break;
    	         case 4: return 18;break;
    	         case 8: return 19;break;
    	 		 case 16:return 20;break;
    	 		 case 32:return 21;break;
    	 		 case 64:return 22;break;
    	 		 case 128:return 23;break;
    	 		 default:break;}
    	      break;//fin de 2
    	   case 3:switch(byte[bit]){
    	       	 case 1: return 24;break;
    	       	 case 2:return 25;break;
    	       	 case 4:return 26;break;
    	       	 case 8:return 27;break;
    	       	 case 16:return 28;break;
    	       	 case 32:return 29;break;
    	       	 case 64:return 30;break;
    	       	 case 128:return 31;break;
    	       	 default:break;}
    	       break;// fin de 3
    	  case 4:switch(byte[bit]){
    		     case 1: return 32;break;
    		     case 2:return 33;break;
    		     case 4:return 34;break;
    		     case 8:return 35;break;
    		     case 16:return 36;break;
    		     case 32:return 37;break;
    		     case 64:return 38;break;
    		     case 128:return 39;break;
    		     default:break;}
    		   break;// fin de 4      
    	  case 5:switch(byte[bit]){
    		     case 1: return 40;break;
    		     case 2:return 41;break;
    		     case 4:return 42;break;
    		     case 8:return 43;break;
    		     case 16:return 44;break;
    		     case 32:return 45;break;
    		     case 64:return 46;break;
    		     case 128:return 47;break;
    		     default:break;}
    		     break;// fin de 5
         case 6:switch(byte[bit]){
    		     case 1: return 48;break;
    		     case 2:return 49;break;
    		     case 4:return 50;break;
    		     case 8:return 51;break;
    		     case 16:return 52;break;
    		     case 32:return 53;break;
    		     case 64:return 54;break;
    		     case 128:return 55;break;
    		     default:break;}
    		     break;// fin de 6 		     
         case 7:switch(byte[bit]){
        	     case 1: return 56;break;
        	     case 2:return 57;break;
        	     case 4:return 58;break;
        	     case 8:return 59;break;
        	     case 16:return 60;break;
        	     case 32:return 61;break;
        	     case 64:return 62;break;
        	     case 128:return 63;break;
        	     default:break;}
        	     break;// fin de 7 	
         case 8:switch(byte[bit]){
        	    case 1: return 64;break;
        	    case 2:return 65;break;
        	    case 4:return 66;break;
        	    case 8:return 67;break;
        	    case 16:return 68;break;
        	    case 32:return 69;break;
        	    case 64:return 70;break;
        	    case 128:return 71;break;
        	    default:break;}
        	    break;// fin de 8 		     
        case 9:switch(byte[bit]){
        	    case 1: return 72;break;
        	    case 2:return 73;break;
        	    case 4:return 74;break;
        	    case 8:return 75;break;
        	    case 16:return 76;break;
        	    case 32:return 77;break;
        	    case 64:return 78;break;
        	    case 128:return 79;break;
        	    default:break;}
        	    break;// fin de 9 	
       case 10:switch(byte[bit]){
        	    case 1: return 80;break;
        	    case 2:return 81;break;
        	    case 4:return 82;break;
        	    case 8:return 83;break;
        	    case 16:return 84;break;
        	    case 32:return 85;break;
        	    case 64:return 86;break;
        	    case 128:return 87;break;
        	    default:break;}
        	    break;// fin de 10 		     
       case 11:switch(byte[bit]){
        	    case 1: return 88;break;
        	    case 2:return 89;break;
        	    case 4:return 90;break;
        	    case 8:return 91;break;
        	    case 16:return 92;break;
        	    case 32:return 93;break;
        	    case 64:return 94;break;
        	    case 128:return 95;break;
        	    default:break;}
        	    break;// fin de 11	
       case 12:switch(byte[bit]){
    	        case 1: return 96;break;
    	        case 2:return 97;break;
    	        case 4:return 98;break;
    	        case 8:return 99;break;
    	        case 16:return 100;break;
    	        case 32:return 101;break;
    	        case 64:return 102;break;
    	        case 128:return 103;break;
    	        default:break;}
    	        break;// fin de 12		     
        case 13:switch(byte[bit]){
    	        case 1: return 104;break;
    	        case 2:return 105;break;
    	        case 4:return 106;break;
    	        case 8:return 107;break;
    	        case 16:return 108;break;
    	        case 32:return 109;break;
    	        case 64:return 110;break;
    	        case 128:return 111;break;
    	        default:break;}
    	        break;// fin de 13 	
       case 14:switch(byte[bit]){
    	        case 1: return 112;break;
    	        case 2:return 113;break;
    	        case 4:return 114;break;
    	        case 8:return 115;break;
    	        case 16:return 116;break;
    	        case 32:return 117;break;
    	        case 64:return 118;break;
    	        case 128:return 119;break;
    	        default:break;}
    	        break;// fin de 14 		     
       case 15:switch(byte[bit]){
    	        case 1: return 120;break;
    	        case 2:return 121;break;
    	        case 4:return 122;break;
    	        case 8:return 123;break;
    	        case 16:return 124;break;
    	        case 32:return 125;break;
    	        case 64:return 126;break;
    	        case 128:return 127;break;
    	        default:break;}
    	        break;// fin de 15       	        	        	     	       	        	     		            	     		     
       case 16:switch(byte[bit]){
    	        case 1: return 128;break;
    	        case 2:return 129;break;
    	        case 4:return 130;break;
    	        case 8:return 131;break;
    	        case 16:return 132;break;
    	        case 32:return 133;break;
    	        case 64:return 134;break;
    	        case 128:return 135;break;
    	        default:break;}
    	        break;// fin de 16	
       case 17:switch(byte[bit]){
    	        case 1: return 136;break;
    	       	case 2:return 137;break;
    	       	case 4:return 138;break;
    	       	case 8:return 139;break;
    	        case 16:return 140;break;
    	        case 32:return 141;break;
    	       	case 64:return 142;break;
    	       	case 128:return 143;break;
    	        default:break;}
    	       	break;// fin de 17		     
    	case 18:switch(byte[bit]){
    	       	case 1: return 144;break;
    	       	case 2:return 145;break;
    	       	case 4:return 146;break;
    	       	case 8:return 147;break;
    	        case 16:return 148;break;
    	       	case 32:return 149;break;
    	       	case 64:return 150;break;
    	       	case 128:return 151;break;
    	       	default:break;}
    	        break;// fin de 18 	
       case 19:switch(byte[bit]){
    	        case 1: return 152;break;
    	        case 2:return 153;break;
    	       	case 4:return 154;break;
    	        case 8:return 155;break;
    	       	case 16:return 156;break;
    	       	case 32:return 157;break;
    	       	case 64:return 158;break;
    	       	case 128:return 159;break;
    	       	default:break;}
    	       	break;// fin de 19 		     
       case 20:switch(byte[bit]){
    	        case 1: return 160;break;
    	       	case 2:return 161;break;
    	        case 4:return 162;break;
    	       	case 8:return 163;break;
    	        case 16:return 164;break;
    	       	case 32:return 165;break;
    	        case 64:return 166;break;
    	       	case 128:return 167;break;
    	       	default:break;}
    	       	break;// fin de 20       	        	        	     	       	        	     		            	     		     
       case 21:switch(byte[bit]){
    	        case 1: return 168;break;
    	        case 2:return 169;break;
    	        case 4:return 170;break;
    	        case 8:return 171;break;
    	        case 16:return 172;break;
    	        case 32:return 173;break;
    	        case 64:return 174;break;
    	        case 128:return 175;break;
    	        default:break;}
    	        break;// fin de 21      	     		       		       		     
       case 22:switch(byte[bit]){
    	       	case 1: return 176;break;
    	       	case 2:return 177;break;
    	       	case 4:return 178;break;
    	       	case 8:return 179;break;
    	        case 16:return 180;break;
    	       	case 32:return 181;break;
    	       	case 64:return 182;break;
    	       	case 128:return 183;break;
    	      	default:break;}
       	       	break;// fin de 22       	        	        	     	       	        	     		            	     		     
       case 23:switch(byte[bit]){
    	       	case 1: return 184;break;
    	       	case 2:return 185;break;
    	       	case 4:return 186;break;
    	       	case 8:return 187;break;
    	       	case 16:return 188;break;
    	        case 32:return 189;break;
    	        case 64:return 190;break;
    	       	case 128:return 191;break;
    	       	default:break;}
    	       	break;// fin de 23          		          		     	      
    	   default:break;}    
return 0;
}//fin de get_Coord_Num-----------------------------------


/*saca la parte entera de un float y la pasa a
una variable uchar menor a ffh*/
unsigned char getFloat_uchar(float n){

	 if(n<0)
		 return 0;
	 if(n>255)
		 return 0;
	 return (unsigned char)n;
}//fin getFloat_Entero---------------------------------------



float convert_Phase_to_Float(unsigned char fase,unsigned char frac){
float fr;
      if(frac>9)
    	   frac=9;
      fr=frac*0.1f;
	  return((float)(fase+fr));
}//fin convertir fase to float------------------------------------

/* se recalcula con el buffer que tenemos gurdado todos los puntoos
 * actuales del dds y algunos valores fuera del dds, el nuevo zoom
 * basado en el que hay, se reacomodan los puntos en base el nuevo zoom
 * */
void re_Calcular_Buffers_DDS(unsigned char zoom_wished){
	 
	 if(zoom_wished==vfd.menu.dds.zoom.Zoom)
		 return;
	 if(zoom_wished<vfd.menu.dds.zoom.Zoom){//se vamos a restar?
		 if((vfd.menu.dds.zoom.Zoom-zoom_wished)==1)//solo le sera uno, la resta
			 re_Calcular_Buffers_DDS_Modificar_Uno(vfd.menu.dds.zoom.Zoom-1);}
	 else{//aumentar el zoom ACERCAR
		  if((zoom_wished-vfd.menu.dds.zoom.Zoom)==1)
			  re_Calcular_Buffers_DDS_Modificar_Uno(vfd.menu.dds.zoom.Zoom+1);}

}//fin de recalculr el bufer que esta guardado en el DDS----------
	   
	 

/* obtener la parte fracccional de un float
 *  solo el primer decimal y pasarlo a uchar
 * */
unsigned char getFloat_Frac(float n){
unsigned char entero,frac;
float f;
	entero=getFloat_uchar(n);
	 f=(n-((float)entero))*10;
	 frac=(unsigned char)f;
	 if(frac>10)
		 frac=0;
	 return frac;
}//fin getFloat_Frac------------------------------------------



/*op: SUMAR | RESTAR  operacion de las variables
 * digito es el digito que se le va hacer la operacion   000.0
 * digito 5 es el milenio                                ^^^^^
 *                                              digito-->54321
 * */
void operacionPhase(unsigned char digito,unsigned char op){
unsigned char phase=getFloat_uchar(producto2.phase);
unsigned char phasefrac=getFloat_Frac(producto2.Phasefrac);
	switch(op){
		case RESTAR:if((phase==0)&&(phasefrac==0)){
			            	  phase=179;
			            	  phasefrac=9;
		                      break;}
					if(phase==0){
							  phase=179;
							  phasefrac=9;
							  break;}
		            if(digito==1){
			            if(phasefrac==0){
		                       (phase)--;
			                   phasefrac=9;}
			            else (phasefrac)--;
		                break;}
		            if(digito==3){
		            	 (phase)--;
		            	 break;}
		            if(digito==4){
		                if(phase<10){
		                	phase=179;
		                	phasefrac=9;
		                	break;}	
		                else phase-=10;
		                break;}
			        if(digito==5){
			        	if(phase<100){
			        		phase=179;
			        		phasefrac=9;
			        		break;}
			        	else phase-=100;
			            break;}
			        break;
		case SUMAR:if(digito==1){
			             if(phasefrac==9){
			            	 (phase)++;
			            	 phasefrac=0;
			            	 break;}}
		           if(digito==3){
		        	     if(phase<179){
		        	    	 (phase)++;
		        	         break;}
		        	     else {phase=0;
		        	           phasefrac=0;
		        	           break;}}
		        	if(digito==4){
		        		 if(phase==179){
		        			  phase=0;
		        			  phasefrac=0;
		        			  break;}
		        		 else{(phase)+=10;
		                      break;}}
		            if(digito==5){
		            	 if(phase==179){
		            		  phase=0;
		            		  phasefrac=0;
		            		  break;}
		            	 if(phase>99){
		            		 phase=0;
		            		 phasefrac=0;
		            		 break;}}
			       break;
		default:break;
	}//fin switch
	
	producto2.phase=convert_Phase_to_Float( phase, phasefrac);

}//fin operacion phase--------------------------------------------------




/* apartir de un punto cartesiano  y un angulo obtenemos
 *  la ecuacion de la recta y tambien los dos puntos  que estan
 *  dentro del cuadro display 0-192, 0-127 del display VFD
 *  para hacer las rectas en base a ese angulo y ese punto
 * */
struct Coordsf AgetEcuation(struct Ec_Recta* f, struct Coordf P1, float angulo) {
	float CAdy,t;
	struct Coordf P2, P3, P4;
	struct Coordsf P34b;//punto 3 y 4
	t=(float)tan4(angulo);
	CAdy = absf(P1.y) / t;
	P2.x = P1.x + CAdy; P2.y = 0;
	*f = getEcuation(P1, P2);
	P3.x = 0; P3.y = f->b;
	P4.x = 192;//192 porque ang< 33.69° y rEcta pega en pared derecha del cuadro VFD
	P4.y = frecta(f,'x', 192);//f es la ecuacion y val 127 el valor a evualuar en un punto
	P34b.Pm = P3; P34b.Pn = P4;
	return P34b;
}//fin de obtener la ecuacion y los puntos de la recta-----------------------


/*  *n: numero a ser procesado del tipo short int    
 *  digito: digito que se va ha hacer la operacion   digito-> 12345  <--posicion, 5->unidad
 *  op: operacion SUMAR | RESTAR    
 *  Funcion que resta o suma  en un digito en particular def1 */
void operacionUShortInt(unsigned short int *n,unsigned char digito,unsigned char op){//opera en el digito indicado
unsigned short int i,j;
const unsigned short int num[]={0,0,10,100,1000,10000};
	switch(op){
		case RESTAR:if(*n==1)
			             break;
		             j=num[digito];
		             //if(digito==5)
		            	//  j=32765;
					 switch(digito){
						 case 1: (*n)--; return;
						 case 2:
						 case 3:
						 case 4:
						 case 5: i=*n;
								 if(i<j)
									 *n=1;    	 
								else{i-=num[digito];
									 *n=i;}
							    break;
						default:break;}
				   break;//case restar
		case SUMAR:if(*n<32767){
			    	  if(digito==1){
			    		  (*n)++;
			    		  break;}
			    	  if(digito==2){
			    		  i=*n;
			    		  i+=10;
			    		  if(i>32767)
			    			  i=32767;
			    		  *n=i;
			    	      break;}
			    	  if(digito==3){
			    		  i=*n;
			    		  i+=100;
			    		  if(i>32767)
			    		     i=32767;
			    		  *n=i;
			    		  break;}
			    	  if(digito==4){
			    		  i=*n;
			    		  i+=1000;
			    		  if(i>32767)
			    		  	  i=32767;
			    		  *n=i;
			    		  break;}
			    	  if(digito==4){
						  i=*n;
						  i+=1000;
						  if(i>32767)
							  i=32767;
						  *n=i;
						  break;}
			    	  if(digito==5){
			    		 i=*n;
			    		 i+=10000;
			    		 if(i>32767)
			    			 i=32767;
			    		 *n=i;
			    	     break;}
			       }else break; 
		default:break;}
}//fin operacion de  numero short int -------------------------------------------------------



/*Obtener el check sum del pquete de datos a enviar
 *  cmd es el comando a enviar como cabeza, data es el apuntador a los datos a enviar
 *  len: es el numero de bytes a enviar sin contar comando ni checksum., b
 *  version-1*/
unsigned char getCheckSUM(unsigned char cmd, unsigned char *data, unsigned char len){
unsigned char i,j;
union _ussint_{
	unsigned short int Suma;
	unsigned char bytes[2];
}suma1;
           suma1.Suma=0;
           suma1.Suma=cmd;
           for(i=0;i<len;i++)
	           suma1.Suma+=*(data+i);
           j=suma1.bytes[0]+suma1.bytes[1];
           i=j^0xFF;//nvertir valores;
return(i);                                 //inversor
}//fin de get checksum del paquete de datos que pretendemos enviar----------------------


/*Return FALSE if it finish till the last coord,*/
unsigned char is_get_number_from_pixel(unsigned char *x,unsigned char  *y){
//unsigned char i;
const unsigned char byte[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char xx,b;
static unsigned char bit,num,init,reg,var;
static unsigned char debugx[20],debugy[20],i;
static unsigned char row,col;
          
      row=vfd.menu.dds.rePaint.iy;
      reg=vfd.menu.dds.rePaint.ix;
      b=vfd.menu.dds.rePaint.b;
      if(init!=0xAA){
    	   init=0xAA;
    	   vfd.menu.dds.rePaint.iy=0;
    	   vfd.menu.dds.rePaint.ix=0;
    	   num=0;
    	   bit=0;
    	  b=0x00;
    	   *x=0;*y=0;
    	   i=0;
    	   row=0;
    	   col=0;
    	   reg=0;}
      if(b>7){
    	   b=0;
    	   if((++reg)>(SIZE_X-1)){
    		    reg=0;
    		    if((++row)>(SIZE_Y-1)){
    		    	init=0;
    		    	return FALSE;}}}
     xx=vfd.menu.dds.rePaint.xy[row][reg];
     if(xx==0){*x=0;*y=0;}
     else{if((xx&byte[b])==byte[b]){
    	      *x=get_Coord_Num(reg,b);
    	      *y=row;}
          else{*x=0;*y=0;}}
      
      
	vfd.menu.dds.rePaint.iy=row;
	vfd.menu.dds.rePaint.ix=reg;
	vfd.menu.dds.rePaint.b=b+1;
return TRUE; //SEGUIMOS SACANDO NUMEROS DE LA MATRIZ
}//in is_get_number_from_pixel


/*obtener los bytes rovenientes de un numero
 *   signed short int  
 *    version-1   */
void getBytes_from_SSInt(unsigned char *byteMSB,unsigned char *byteLSB,signed short int ssi){
union gr{
  signed short int ssi;
  unsigned char byte[2];
}number;	
	          number.ssi=ssi;
	          *byteMSB=number.byte[0];
	          *byteLSB=number.byte[1];
}//fin getBytes_from_SSInt-------------------------------------------

void generador_de_signal_Debug(signed short int *x,signed short int *y){
static unsigned char estado,i,ret;	
const unsigned char  SIZE=20;
const signed short int xx[]={-60,-50,-40,-30,-20,-10,0,10,20,30,40,50,60,70,80,90,100,120,130,140};
const signed short int yy[]={-60,-50,-40,-30,-20,-10,0,10,20,30,40,50,60,70,80,90,100,120,130,140};

     switch(estado){
    	 case 0:if(i<SIZE){
    		         *x=xx[i];
    	             *y=yy[i++];}
    	        else {i=0;*x=xx[0];*y=yy[0];}
    	        break;
    	 default:estado=0;i=0;break;}

}//fin 	generador_de_señal_Debug---------------------------------------------




/* Calcula y regresa la ecuacion de la recta en base a un punto
 * y un angulo */
struct Ec_Recta getEcuacion_Recta(struct Coordf P1,float angulo){
struct Ec_Recta ret;

     ret.m=(float)(tan4(angulo));
     ret.b=(-1)*ret.m*P1.x+P1.y;
return(ret);     
}//fin de metodo que calcula y regresa la ecuacion de la recta



/* apartir de un punto cartesiano  y un angulo obtenemos
 *  la ecuacion de la recta y tambien los dos puntos  que estan
 *  dentro del cuadro display 0-192, 0-127 del display VFD
 *  para hacer las rectas en base a ese angulo y ese punto */
struct Coordsf AgetEcuation2(struct Ec_Recta* f, struct Coordf P1, float angulo) {
	float ang2;
	float Cop;//CATETO opuesto
	const float ang_Max = 180-33.69;//grados maximos de la esquina
	struct Coordf P2, P3, P4;
	struct Coordsf P34b;//punto 3 y 4
	unsigned char estado = 0;

	if ((angulo > 90) && (angulo < ang_Max))
		estado = 1;
	else {if ((angulo > ang_Max) && (angulo < 180))
			estado = 2;
		  else estado=3;}
	switch (estado) {
	case 1:ang2 = angulo - 90;
		   Cop = absf(P1.y) * (float)tan4(ang2);
		   if((P1.x<0)||(P1.y<-127)){//para el punto inferior que se sale del cuadro
		   	    	      //__asm(Halt);__asm(nop);
						  mens_Warnning_Debug("Error de Software en AgetEcuation2");}
   		   P2.x = P1.x - Cop; P2.y = 0;
		   *f = getEcuation(P1, P2);
		   P3.y = 0;    P3.x = frecta(f,'y', P3.y);
		   P4.y = -127; P4.x = frecta(f,'y', P4.y);
		   break;
	case 2:		
		if (angulo < ang_Max){// __asm(nop);__asm(Halt);
		                      mens_Warnning_Debug("Error de Software en AgetEcuation2"); }
		ang2 = angulo - 90;//
		Cop = absf(P1.y) * (float)tan4(ang2);//
        f->m=(float)tan4(angulo);
        f->b=(-1)*f->m*P1.x+P1.y;
		if (Cop < 96) {// __asm(nop);__asm(Halt);
						mens_Warnning_Debug("Error de Software en AgetEcuation2");}
		P2.x = Cop - 96; P2.y = 0;
		*f = getEcuation(P1, P2);
		P3.x = 0;   P3.y = frecta(f,'x', P3.x);
		P4.x = 192; P4.y = frecta(f,'x', P4.x);
		break;
	default:break;}
	P34b.Pm = P3; P34b.Pn = P4;
return P34b;
}//fin de obtener la ecuacion y los puntos de la recta-----------------------


//automata
struct Coordsf AgetEcuation3(struct Ec_Recta *g,struct Ec_Recta f, struct Coordf P, float angulo) {
struct Coordsf PP;	
float angMax=180-33.69; //146.31°  recta de P1 al P0,0
unsigned char edo=0; 
	 if(angulo>90){
			 g->m=f.m;
			 g->b=((-1)*f.m*P.x)+P.y;
			 if(angulo==angMax){
				 PP.Pm.x=0;PP.Pm.y=0;
			     PP.Pn.x=192;PP.Pn.y=-127;} 
			 else{PP.Pm.y=0;
				  PP.Pm.x=frecta(g,'y',PP.Pm.y);
				  if(PP.Pm.x<0){//Es negativo
					  PP.Pm.x=0;
					  PP.Pm.y=frecta(g,'x',PP.Pm.x);}
				  PP.Pn.x=192;
				  PP.Pn.y=frecta(g,'x',PP.Pn.x);
                  if(PP.Pn.y>0){mens_Warnning_Debug("Error de Software en AgetEcuation3");
								//__asm(nop);__asm(Halt);
				                }
				  if(PP.Pn.y<-127){
					    PP.Pn.y=-127;
				  	    PP.Pn.x=frecta(g,'y',PP.Pn.y);}	}}
l682:if(PP.Pm.x<0)   edo=1;
     else{if(PP.Pn.x<0)edo=2;
          else{if(PP.Pn.x>192) edo=3;
               else{if(PP.Pm.x>192) edo=4;
                    else{if(PP.Pm.y>0) edo=5;
                         else{if(PP.Pn.y>0) edo=6;
                              else{if(PP.Pm.y<-127) edo=7;
                                   else{if(PP.Pn.y<-127) edo=8;
                                        else{edo=0;}}}}}}}}
	 switch(edo){
		 
		 case 3:PP.Pn.x=192;PP.Pn.y=frecta(g,'x',PP.Pn.x);
		        edo=0;goto l682;break;
		 case 1:
		 case 2:
		 case 4:
		 case 5:
		 case 6:
		 case 7:
		 case 8:edo--;//__asm(Halt);
					  mens_Warnning_Debug("Error de Software en AgetEcuation3");
					  break;
		 default:break;}
      if(edo>0)
	    	 goto l682;
return PP;
}//fin a get Ecuation version 3

			 
			 



/*Le proporcionamos dos puntos en el cartesiano y obetenemos la acuacion
 * de la recta*/
struct Ec_Recta getEcuation(struct Coordf P1, struct Coordf P2) {
struct Ec_Recta fx;
float denom;
	denom=P2.x-P1.x;
	if(denom==0)
		   denom=0.0001;//division entre cero, pendiente de 90°
	fx.m = ((P2.y - P1.y) / denom);
	fx.b = (((P2.y - P1.y) * P2.x * (-1)) / denom) + P2.y;
	return fx;
}//fin ecuacion de la recta en base a dos puntos en el espacio cartesiano


//calculo del angulo de la pendiente inversa de un angulo que representa una pendiente
float calculo_pendiente_inversa(float ang){
double ang2,m,im;
        ang2=(double)ang;
        m=tan4(ang2);
        im=(-1)*(1/m);
return (float)im;        
}//fin calculo pendiente inversa--------------------------------------------

/* obtener la recta apartir de un punto y una pendiente */
struct Ec_Recta getEcuacion_Recta_Punto_Pendiente(struct Coordf P,float m){
struct Ec_Recta ec;

        ec.b=(-1)*m*P.x+P.y;
        ec.m=m;
return ec;        
}//fin get ecuacion de la recta obtenido de punto y pendiente


/* busqueda de los Puntos donde van las rectas perpedicularres que 
 * forman las tapas del sobre y son la altura,
 * FX es la ecuacion directris, y px es la perpendicular a fx y paralelas
 * a las ecuaciones de altura. 
 *  s: sensibilidad */
struct Coordsf busqueda_Puntos_Altura(struct Ec_Recta f,unsigned  short int s){
struct Coordsf ret={{0,0},{0,0}};
struct Coordf P1;
   P1.x=96;P1.y=-64;
   ret.Pm=Buscar_Punto_en_Recta_auna_Distancia(LEFT,f,P1,s);
   ret.Pn=Buscar_Punto_en_Recta_auna_Distancia(RIGHT,f,P1,s);
return ret;
}//fin busqueda de los puntos de Alturas.--------------------------------
   
 

/* Encuentra un Punto en la recta dada, a  una distancia de otro
 * punto dado.
 * Param: dir: si buscamos hacia el lado negativo o positivo
 * f: la ecuacio de la recta en la que vamos a buscar
 * P: es el primer punto del que va a partir la busqueda
 * s: es la distacia a la que deben estar los puntos en la recta
 * regresa el Punto a la distancia s del punto P*/
struct Coordf Buscar_Punto_en_Recta_auna_Distancia(unsigned char dir,
		struct Ec_Recta f,struct Coordf P,unsigned short int s){
float M,x2;//Maximo_izquierdo;/
struct Coordf P2;
     M=Buscar_Maximo_para_Busqueda_Binaria(dir,100,f,P,s);
	 x2=Busqueda_Binaria_de_un_Punto(M,f,P,s,0.8,P.x);
	 P2.x=x2;P2.y=f.m*x2+f.b;
return 	P2; 
}//fin de encontrar un punto en la recta a una distancia de otro punto dado

/*Busca un punto en una recta con busqueda binaria
 * que el punto tenga la distancia s, desde el punto P
 * param: M es el maximo izquierdo que contiene el punto a buscar
 * f: ec de la recta en donde se buscan los puntos, s:distancia
 * entre puntos, e: error aceptable de distancia buscada min: es 
 * el punto min izqquierdo que contiene el valor a buscar*/
float Busqueda_Binaria_de_un_Punto(
	   float xM,struct Ec_Recta f,struct Coordf P1,unsigned short int s,
	   float e, float xmin){
float dxM,dmid,ret=0;//dd: dista maxima, dmed, distancia media
float xmid,ss;

       ss=(float)s;
       if((xM==0)&&(xmin==0)){//__asm(nop);__asm(Halt);
							mens_Warnning_Debug("Error de Software f.Busqueda_Binaria_de_un_Punto");
	                          } 
       dxM =distancia_Entre_Puntos(f,P1,xM);//   Obtener_Mitad_Recta(M,min);
       xmid=Obtener_Mitad_Recta(xM,xmin);
       dmid=distancia_Entre_Puntos(f,P1,xmid); 
       if(absf(ss-dmid)<e){
    	       ret=xmid;}
       else{if((dxM>ss)&&(ss>dmid))
    	       ret=Busqueda_Binaria_de_un_Punto(xM,f,P1,s,e,xmid);
            else{if(dmid>ss) 
            	   ret=Busqueda_Binaria_de_un_Punto(xmid,f,P1,s,e,xmin);
                 else{//__asm(Halt);__asm(nop);
					mens_Warnning_Debug("Error de Software f.Busqueda_Binaria_de_un_Punto");				      
				 }}}
return ret;       
}//fin de busqueda binaria--------------------------------------

//distancia entre dos puntos en la recta Ec f(x)
float distancia_Entre_Puntos(struct Ec_Recta f,struct Coordf P1,float x2){
double m,b,y2,d,x2d;
float ret;
     m=(double)f.m;b=(double)f.b;x2d=(double)x2;
	 y2=m*x2d+b;
	 d=Raizd(pow1d(x2d-P1.x,2)+pow1d(y2-P1.y,2));
	 ret=(float)d;
	 if(ret==0){
		 //__asm(Halt);
		 //__asm(nop);
		mens_Warnning_Debug("Error de Software f.distancia_Entre_Puntos");
		 }
		
return ret;	
}//fin de distancia entre dos puntos------------------------------------------


/*Busca el Maximo izquiero de una recta unidimensional
 * que sobre pase la distancia del punto que queremos encontrar
 * para propositos de que alguien mas haga una busqueda 
 * binaria.
 * parametros:DIR: se va a buscar hacia izq, negativo o der pos
 *  i: valor propuesto izquierdo, f: funcion de la recta
 *  P:punto inicial de la busqueda, s:distancia entre los puntos
 *  deseada que tenga P1 y P2.
 *  regresa el valor maximo hacia izq o der,  donde se puede 
 *  comenzar a buscar  el valor o punto que queremos
 * */
float Buscar_Maximo_para_Busqueda_Binaria(
	  unsigned char Dir,float i,struct Ec_Recta f,
	  struct Coordf P,unsigned short int s){
unsigned char init=1;
struct Coordf P2;
unsigned short int count=0;
float d,ss,ret;
     if(i==0)
    	  i=100;
     switch(Dir){//seguro de cordenadas izquierda y derecha correctas
    	 case RIGHT: if(i<P.x)
    		             i=P.x+i;
    	             break;
    	 case  LEFT: if(P.x<i)//el numero propuesto esta mas a la derecha que el cenrto
    		             i=i-P.x;
    		         break; 
    	 default://__asm(Halt);__asm(nop);
		         mens_Warnning_Debug("Error de software en f.Buscar_Maximo_para_Busqueda_Binaria");
		         }
      P2.x=i; 
      do{count++;
      P2.y=f.m*P2.x+f.b;
      d=(float)(Raizd(pow1d(P2.x-P.x,2)+pow1d(P2.y-P.y,2)));
      ss=(float)s;
      if((ss==d)&&(init==1))
    	   return 0;
      if(ss<d){
    	  ret=P2.x;
    	  break;}
      else{if(Dir==RIGHT)
    	        P2.x=P2.x+P2.x;
           else P2.x=P2.x-P2.x; }  
      }while(count<0xFFF1);
      //__asm(nop);//nunca se resuelve
      //__asm(Halt);//debug, error de software.
return ret;	
}//fin de busqueda maximo de un punto en la recta para buscar en ese rango



/* parametro
 * M: es el valor de la izquierda o mas negativo
 * m: el valor de la derecha o mas positivo
 * regresa el valor de la mitad entre esos dos*/
float Obtener_Mitad_Recta(float M,float m){
float mitad,k,ab;
unsigned char comprobante=0;
	 k=M-m;
	 ab=k/2;
	 mitad=m+ab;
	 //comprobacion
  	if(mitad+ab==M)
  		comprobante++;
  	if(mitad-ab==m)
  		comprobante++;
  	if(comprobante==2)
          return mitad;
  	else{//__asm(nop);
  	     //__asm(Halt);
		mens_Warnning_Debug("Error de software en f.Obtener_Mitad_Recta");
		 }
return 0;  	
}//Fin de obtener la mitad del valor entre dos puntos de una recta de 1 dimension



//ecuacion de la recta  con el valor x obtenemos el valor y de la  get_x2r
//eccuacion de la recta f.
float frecta(struct Ec_Recta* f,char c, float x) {
	switch(c){
		case 'X':
		case 'x':return(f->m * x + f->b);break;//despeja la Y
		case 'Y':
		case 'y':return ((x - f->b) / f->m);break;//despeja la X
		default:break;}
return 0;
}//fin obtener valor x de la ecuacion de la recta f teniendo y




/* obtener el punto inferior a la recta central de 33.69° perpendicular a la master
 * line central */
struct Coordsf get_Puntos_Perpendiculares(float m, struct Coordf P, unsigned short int s) {
	//float mr,br;
	//struct Coordf P5;
	struct Coordsf P58;
	struct Ec_Recta fr;//recta perpendicular a la central
	fr.m = (-1) * (1 / m);
	fr.b = P.y - fr.m * P.x;
	P58 = get_x2r(s, fr, P);
	P58.Pn.y = frecta(&fr,'x', P58.Pn.x);//punto inferior
	P58.Pm.y = frecta(&fr,'x', P58.Pm.x);//punto superior
	//printf("\n r(x)= yr=%fx+%f ", fr.m, fr.b);
	return P58;
}//fin obtener el punto inferior perpbbendicular ala recta central a 33.69°



/* Buscar el punto x del P inferior de la recta, buscar la distancia
 * entre la recta y el punto sea igual a sens, y alli establecer una recta
 * s es la sensinilidad, f es la ecuacion de la recta quee es perpendicular
 * y alli estabecemos y movemos las distancias y P es el punto  donde esta
 * la recta perpendicular original centro VFD para sacar la distancia
 * regresa un punto x donde es la distancia igual a sens en la recta f(r)
 * sacamos los puntos x de la recta perpendicular superior e inferior de la mediatriz*/
struct Coordsf get_x2r(unsigned short int s, struct Ec_Recta f, struct Coordf P) {
float x2 = 0;
float d, e = 0;
unsigned char n = 0, estado = 0,ff=0,i=0;
unsigned char punto = 0, flip = 0;
struct Coordsf P58 = { {0,0},{0,0} };
const float inf1 = 432454221;
float xa=96, xb=inf1,inc=10;

    if(s==0) s=30; //DEBUG error aqui guardar el s en la memoria
	//ang=atan((double)(f.m));
	if((f.m == 0) && (f.b == 0)) {//recta igual al eje de las X
		P58.Pm.x = 0; P58.Pm.y = -64;
		P58.Pn.x = 192; P58.Pn.y = -64;
		return P58;}
    x2=xa;
L1:	if(x2 < xb) goto L2; else {mens_Warnning_Debug("Error de Software f.getx2r");//__asm(nop);__asm(Halt);
                                }
L3:	if(x2 > xb) goto L2; 
    else {mens_Warnning_Debug("Error de Software f.getx2r");}
L2:	    x2 += inc;
		d = Raiz2((pow1((x2 - P.x), 2)) + (pow1(((((f.m * x2)) + f.b - P.y)), 2)));
		e = absf(d - s);
		if(e < 1.1) {
			if (!flip) {P58.Pm.x = x2; flip++;
				        xa = 96; inc = -10; xb = 0; x2 = xa; ff = 0;
				        goto L3;}
			else { P58.Pn.x = x2; return P58; }}
		else{if (d < s) {xa = x2; ff |= 1;
				          if (!flip)  goto L1; else  goto L3;}
			 else {if (d > s) {xb = x2; x2 = xa; ff |= 2;}
				else {mens_Warnning_Debug("Error de Software f.getx2r");}
				if (ff > 1) {ff = 0;inc /= 10;}
				if (!flip)  goto L1; else  goto L3;}}
return P58;
}//fin obtener la distacia y la coordenadda x en el punto inferior





/*convierte el numero WORD  ADCVAL: es un numero del adc que es el voltaje de 0 a 65520 representa
 * 0v a 1.3volts    regresa float el numero miliamper  en float
 * formula es  y=19.834x10^-6(x)+0.03826       y=mx+b*/
double convertir_ADC_word_A_miliVolt(unsigned short int ADCval,unsigned char channel){
double r;
	  
    switch(channel){
    	case _PICKUP_://r=0.000019834*((float)ADCval)+0.03826;//Pickup formula con multimetro y generador
                      r=(0.000015367421067*((float)ADCval))+0.11468063; //con osciloscopio y señal real
    		          break;
    	case _DRIVER_://r=0.000722366*((float)ADCval)+0.177825;//DRiver formula con multimetro y generador
                      r=((0.000692321)*((float)ADCval))+3.880113079; //con osciloscopio y señal real
    		          break;
    	case CANAL_Y:              
    	case CANAL_X://r=m(x-a)+b; ecuacion de la recta (10,0),(17709,2.71)
    	             r=0.00015*((float)ADCval)-0.00153; //voltaje canal X
    	             break;}
        
return r;
}//fin convertir_ADC_word_A_miliVolt-----------------------------------------------



/* convierte de BCD  a uchar  e.g.    99 en BCD es  1001 1001 
 * lo convierte a uchar en binario seria 99 a binario=63h =  0110 0011 */
unsigned char convert_BCD_to_uchar(unsigned char BCD){
unsigned char i,k;	
	    i=BCD&0x0F;
	    if(i<10)
	    	k=i;
	    else k=0;
	    i=BCD&0xF0;
	    if(i<0x91)
	    	k+=i;
return k;
}//fin convertir BCD  a unsigned char---------------------



//evalua si la recta sale por la pared izquierda del cuadro o por
//la parte inferior ó piso.
struct Coordsf get_Evaluar_(struct Coordsf P, struct Ec_Recta f) {
	unsigned char i, n = 0;
	struct Coordf* p;
	//float ang;
L173:for (i = 0, p = &P.Pm; i < 2; i++, p++) {//Error 127
			if (p->x == 0) {
				if ((p->y < -127) || (p->y > 0)) {
					p->y = -127;
					p->x = (p->y - f.b) / f.m; n++;
					if (n > 2) { mens_Warnning_Debug("Error de Software f.get_Evaluar_");//__asm(nop);__asm(Halt); 
					             }
					goto L173;}}//is ok
			if (p->x == 192) {
				if (p->y > 0) { p->y = 0; p->x = ((p->y) - f.b) / f.m; }
				else {
					if (p->y < -127) {
						mens_Warnning_Debug("Error de Software f.get_Evaluar_");//__asm(nop);__asm(Halt);
						 }}}
			if ((p->y < -127) && (p->x == 0)) {
				p->y = -127; p->x = ((p->y) - f.b) / f.m;	}}//fin del for
		
		if ((P.Pm.y > 0) || (P.Pm.y < -127)) {
			mens_Warnning_Debug("Error de Software f.get_Evaluar_");//__asm(nop);__asm(Halt);
			}
		if ((P.Pn.y > 0) || (P.Pn.y < -127)) {
			mens_Warnning_Debug("Error de Software f.get_Evaluar_");//__asm(nop);__asm(Halt);
			 }
		if ((P.Pm.x < 0) || (P.Pm.x > 192)) {
			mens_Warnning_Debug("Error de Software f.get_Evaluar_");//__asm(nop);__asm(Halt);
			}
		if ((P.Pn.x < 0) || (P.Pn.x > 192)) {
			mens_Warnning_Debug("Error de Software f.get_Evaluar_");//__asm(nop);__asm(Halt);
			}
	return P;
}//fin get evaluar -----------------------------------------


struct Coordsf get_Evaluar_3(struct Coordsf P,struct Ec_Recta f){
float y,x;    
unsigned char estado=0;
struct Coordsf ret={0};	 
    (void)P;  // Evita la advertencia de parámetro no usado  
      //Lado izquierdo Pm
	  y=frecta(&f,'x',0);//es y postiva o negativa?
	  if(absf(y)<0.5){estado=1;}//casi esta en cerca del centro origen
	  else{if(y>0){estado=2;}//para arriba es positiva
	       else estado=3;}	  //para abajo es negativa
	  switch(estado){
		  case 1:mens_Warnning_Debug("Error de software: f.GetEvaluar3");
		         break;
		  case 2:y=0;x=frecta(&f,'y',y);P.Pm.x=x;
		         P.Pm.y=y;break;		
		  case 3:P.Pm.x=0;P.Pm.y=y;break;
		  default:mens_Warnning_Debug("Error de software: f.GetEvaluar3");
		          break;}
	  //Lado derecho Pn
	  y=frecta(&f,'x',192);//es y postiva o negativa?
	  if(absf(y)<0.5){estado=1;}//casi esta en cerca del centro origen
	  else{if(y>-127){estado=2;}//para arriba es   -127<y<0
	       else estado=3;}	  //para abajo abajo  y<-127
	  switch(estado){
	  		  case 1:mens_Warnning_Debug("Error de software: f.GetEvaluar3");
			         break;
	  		  case 2:x=192;y=frecta(&f,'x',x);P.Pn.x=x;
	  		         P.Pm.y=y;break;
	  		  case 3:y=-127;x=frecta(&f,'y',y);
	  		         P.Pm.x=x;P.Pm.y=y;break;
	  		  default:mens_Warnning_Debug("Error de software: f.GetEvaluar3");
			          break;}
return ret;	
}//----------------------------------------------------------------




//evalua si la recta sale por la pared izquierda delcuadro o por
//la parte inferior ó piso. 
//indica si es la linea de abajo o arriba, sens: la sensibilidad actual
struct Coordsf get_Puntos(struct Ec_Recta f,float angulo,unsigned char linea,unsigned short int s){
	unsigned char i, n = 0,error=0,estado=0;
	struct Coordf* p;
	struct Coordsf P;
	//vfd.menu.dds.zoom.factor=1;
	float x,y;
	//Revisar en que cuadrate pertence
	if(angulo<0){mens_Warnning_Debug("Error de software: f.get_Puntos");//__asm(nop);__asm(Halt);
	             }//no se procesan angulos negativos
	if(angulo<90) estado=1;//angulo de cero a 90
	else{if(absf(angulo-90)<1.2){estado=2;}//angulo de 90° o casi de 90°
	     else{estado=3;}}//angulo>90°
	//Procesar la coordenada segun el cuadrante
	switch(estado){
		case 1: y=frecta(&f,'x',192);
		        if(y>0){y=0;x=frecta(&f,'y',y);}
		        else{x=192;y=frecta(&f,'x',x);}
		        P.Pm.x=x;P.Pm.y=y;
		        y=frecta(&f,'x',0);
		        if(y<-127){y=-127;x=frecta(&f,'y',y);}
		        else{x=0;y=frecta(&f,'x',x);}
		        P.Pn.x=x;P.Pn.y=y;break;
		case 2:switch(linea){
				 case PARRIBA:P.Pm.x=96-s;P.Pm.y=0;
				              P.Pn.x=P.Pm.x;P.Pn.y=-127;break;
				 case PABAJO: P.Pm.x=96+s;P.Pm.y=0;
	              	  	  	  P.Pn.x=P.Pm.x;P.Pn.y=-127;break;
				 case CENTRAL:P.Pm.x=96;P.Pm.y=0;
			       	   	   	  P.Pn.x=96;P.Pn.y=-127;break;
				 default:break;}//fin switch linea---------------
			    break;//fin case 2,------------------------------
		case 3: y=frecta(&f,'x',0);              //92.1°
				if(y>0){y=0;x=frecta(&f,'y',y);} //y=-27.27x+2827-14
				else{x=0;y=frecta(&f,'x',x);}
				P.Pm.x=x;P.Pm.y=y;
				y=frecta(&f,'x',192);
				if(y>-127){x=192;y=frecta(&f,'x',x);}
				else{y=-127;x=frecta(&f,'y',y);}
				P.Pn.x=x;P.Pn.y=y;break;
		case 0:
		default:mens_Warnning_Debug("Error de software: f.get_Puntos");//__asm(nop);__asm(Halt);
		         
				 break;}//error de software
		
   for (i = 0, p = &P.Pm; i < 2; i++, p++){	
	   if(p->y<-127) error|=0x01;
	   if(p->y>0   ) error|=0x02;//Error
	   if(p->x>192 ) error|=0x04;//       EScalera de Debug/Depuración
	   if(p->x<0   ) error|=0x08;//Error, Debug/Depuracion, error 0000 1010
	   if(error>0){
		   //__asm(nop);
		   mens_Warnning_Debug("Error de software: f.get_Puntos");//__asm(Halt);
		   }}
return P;
}//fin get evaluar -----------------------------------------zoom







//evalua si la recta sale por la pared izquierda delcuadro o por
//la parte inferior ó piso. 
struct Coordsf get_Evaluar_2(struct Coordsf P,struct Ec_Recta f,float angulo){
	unsigned char i, n = 0,error=0,estado=0;
	struct Coordf* p;
	struct Coordsf errorCoords = {0}; // Inicializa en 0 (o valores de error)
	float x,y;
	//Revisar en que cuadrate pertence
	if(angulo<0){//__asm(nop);__asm(Halt);
	              mens_Warnning_Debug("error de Sotware f.get Evaluar2");return errorCoords;
	             }//no se procesan angulos negativos
	if(angulo<90) estado=1;//angulo de cero a 90
	else{if(absf(angulo-90)<1.2){estado=2;}//angulo de 90° o casi de 90°
	     else{estado=3;}}//angulo>90°
	//Procesar la coordenada segun el cuadrante
	switch(estado){
		case 1: y=frecta(&f,'x',192);
		        if(y>0){y=0;x=frecta(&f,'y',y);}
		        else{x=192;y=frecta(&f,'x',x);}
		        P.Pm.x=x;P.Pm.y=y;
		        x=frecta(&f,'y',0);
		        if(y<-127){y=-127;x=frecta(&f,'y',y);}
		        else{x=0;y=frecta(&f,'x',x);}
		        P.Pn.x=x;P.Pn.y=y;break;
		case 2:P.Pm.x=96;P.Pm.y=0;
		       P.Pn.x=96;P.Pn.y=-127;break;
		case 3: y=frecta(&f,'x',0);              //92.1°
				if(y>0){y=0;x=frecta(&f,'y',y);} //y=-27.27x+2827-14
				else{x=0;y=frecta(&f,'x',x);}
				P.Pm.x=x;P.Pm.y=y;
				y=frecta(&f,'x',192);
				if(y>-127){x=192;y=frecta(&f,'x',x);}
				else{y=-127;x=frecta(&f,'y',y);}
				P.Pn.x=x;P.Pn.y=y;break;
		case 0:
		default:mens_Warnning_Debug("error de Sotware f.get Evaluar2");return errorCoords;//__asm(nop);__asm(Halt);
		        break;}//error de software
		
   for (i = 0, p = &P.Pm; i < 2; i++, p++){	
	   if(p->y<-127) error|=0x01;
	   if(p->y>0   ) error|=0x02;//Error
	   if(p->x>192 ) error|=0x04;//       EScalera de Debug/Depuración
	   if(p->x<0   ) error|=0x08;//Error, Debug/Depuracion, error 0000 1010
	   if(error>0){
		   //__asm(nop);
		   mens_Warnning_Debug("error de Sotware f.get Evaluar2");return errorCoords;//__asm(Halt);
		   }}
return P;
}//fin get evaluar -----------------------------------------zoom



void re_Calcular_Buffers_DDS_Modificar_Uno(unsigned char zoom1){
#if(SIZE_X>254)
	unsigned short int i,j;
#else
	unsigned char i,j;
#endif

unsigned char xn,b,xr,yr,cuadrante,bit,reg;
//unsigned char buff[2][SIZE_X];
//unsigned char xy[SIZE_Y][SIZE_X];
const unsigned char bbyte[]={1,2,4,8,16,32,64,0x80};
unsigned char zoomPalanca;//aleja o acerca?
    if(vfd.menu.dds.zoom.Zoom>zoom1) {
    	 zoomPalanca=ALEJAR;
    	 vfd.menu.dds.zoom.Zoom--;}
    else {if(vfd.menu.dds.zoom.Zoom<zoom1){
    	    zoomPalanca=ACERCAR;
            vfd.menu.dds.zoom.Zoom++;}
    	  else{mens_Warnning_Debug("error de Sotware f.recalc buff dss mod uno");return;//__asm(nop);__asm(Halt);__asm(nop);
		      }}
	for(j=0;j<SIZE_Y;j++)
	 for(i=0;i<SIZE_X;i++)
		 vfd.menu.dds.rePaint.xy0[j][i]=0;
	for(j=0;j<SIZE_Y;j++)
	  for(i=0;i<SIZE_X;i++)
		  for(b=0;b<8;b++){//sacar el numero de x uno por uno del regitro x
             if((vfd.menu.dds.rePaint.xy[j][i]&bbyte[b])==bbyte[b]){
			       xn=get_Coord_Num(i,b);	//OBTENER EL numero que corresponde al bit activado que es un pixel de 0 a 192
			       cuadrante=get_cuadrante(xn,j);//a que cuadrante pertenecen esta coordenada
                   reconvertir_coord_reducir_uno(xn,j,cuadrante,&xr,&yr,zoomPalanca);//reconvertir coordenada actual y redcirla a escala uno menor
                   bit=getRegistro_X_bit(&reg,xr);//obtener el registro y el bit de esta nueva coordenada
                   vfd.menu.dds.rePaint.xy0[yr][reg]|= bit;
                   //__asm(nop);
                   }}//Guradar nueva coordenada modificada de zoom buf temporal 
	//para fines de debug se combinan ambos buffers
	for(j=0;j<SIZE_Y;j++) //hacer un OR con los pixeles que tenemos con
		  for(i=0;i<SIZE_X;i++)//los reducidos a otro zoom, Debug solo
		        vfd.menu.dds.rePaint.xy[j][i]=vfd.menu.dds.rePaint.xy0[j][i];
		       
		        	
}//fin re_Calcular_Buffers_DDS_Alejar_Uno--------------


/*//reconvertir coordenada actual y redcirla a escala uno menor 
 * palanca: para saber si REDUCE  o aumenta el zoom a uno */
void reconvertir_coord_reducir_uno(unsigned char xn,unsigned char yn,unsigned char cuadrante,unsigned char *xr,unsigned char *yr,unsigned char palanca){
unsigned char a,b,c,d;
  if(palanca==ALEJAR){
          	 a=xn+1;b=yn+1;
          	 c=xn-1;d=yn-1;}
  else {a=xn-1;b=yn-1;
	    c=xn+1;d=yn+1;}
	switch(cuadrante){
		case 1:if(xn>0)
			       *xr=a;//xn+1;
		       if(yn>0)
		    	   *yr=b;//yn+1;
		       break;
		case 2:if(xn>0)
		        *xr=c;//xn-1;
	          if(yn>0)
	    	    *yr=b;//yn+1;
	           break;
		case 3:if(xn>0)
	              *xr=a;//xn+1;
               if(yn>0)
    	          *yr=d;//yn-1;
               break;
		case 4:if(xn>0)
	             *xr=c;//xn-1;
               if(yn>0)
    	         *yr=d;//yn-1;
              break;
			   //__asm(nop);
			   //__asm(Halt);
			   mens_Warnning_Debug("error de Sotware f.reconvertir coord reducir uno");return;//__asm(nop);
		default:break;}
}//fin reconvertir_coord_reducir_uno



/* obtenemos el cuadrante donde debe estar esta coordenada que va desde
 *  el numero 1 al 4 
 * cuadrante donde se encuentra el numero que va del 0 al 192  ydel 0 al 128 pero viendo el centro en 92,64*/
unsigned char get_cuadrante(unsigned char xi,unsigned char yi){
	
  if(xi<96){
	  if(yi<64)
	       return 1;
	  else return 3;}
  else{if(yi<64)
           return 2;
       else return 4;}
}//fin de la funcion get el cuadrante del dds donde esta esta coordenada


/* m es la pendiente de la directriz perpendicular
 *  y angulo es el angulo de la directriz normal de producto
 * */
float get_angulo_Perpendicular(float m,float angulo){
	 
	if(angulo==0) return 90;
	else{if(angulo==90) return 0;
	     else{if(m>0) return(90-angulo);
	     	  else{if(m<0) return(90+angulo);
	     	       else{//__asm(nop);
	     	            mens_Warnning_Debug("error de Sotware f.get Evaluar2");return 0;//__asm(Halt);
						 }}}}
return -1;	
}//fin de obetener el angulo de la recta perpendicular a la directriz maestra




/* Calcula si las coordenas de P estan dentro de las 
 * cooordenadas que coorrespomtem al zoom actual*/
unsigned char isCoords_inZoom(struct Coordsf P1,unsigned char zoom1){
struct Coorducf P; 
	   P=get_MaxDDSzoom(zoom1);
	   if((absf(P1.Pm.x)<P.uc.x)&&(absf(P1.Pn.x)<P.uc.x))
		if((absf(P1.Pm.y)<P.uc.y)&&(absf(P1.Pn.y)<P.uc.y)){
		   return TRUE;}	
return 0;
}//fin inZoom, dentro del zoom actual esta las coordenadas Coord


struct Coorducf get_MaxDDSzoom(unsigned char zoom){
struct Coorducf p={0};
   		   mens_Warnning_Debug("Error de software: f.get_MaxDDSzoom:sin codigo");
return p;
}//fin get max DDS zoom++++++++++++++++++++++++++++++++++++++++++



/* Traducir la grafica sobre el plano (96,-64) con centro (96,-64)
 * traducimos al centro (96,64)
 * */
struct Coordsuc traducirCoordenadas_to_VFD(struct Coordsf f/*,struct Ec_Recta fx*/){
struct Coordsuc ufx;//dos puntos de la recta		
unsigned char error = 0, i;
float a[4], * p, f1;
unsigned char b[4], * up; 
//struct Coorducf Z;//return    	


    p = &a[0];
	up = &b[0];
	if ((f.Pm.x < 0) || (f.Pn.x < 0))//x es negativo?
		error |= 0x01;
	if ((f.Pm.y > 0) || (f.Pn.y > 0))//error 0x0010 ...                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
		error |= 0x02; 
	if ((f.Pm.y < -127) || (f.Pn.y < -127))
		error |= 0x04;
	if ((f.Pm.x > 192) || (f.Pn.x > 192))
		error |= 0x08;
	if (error > 0) { 
		//__asm(nop);
		mens_Warnning_Debug("error de Sotware f.trad coord 2 vfd");//__asm(Halt);
		}//Debug  
	if (f.Pm.y < 0)
		f.Pm.y *= -1;
	if (f.Pn.y < 0)
		f.Pn.y *= -1;

	*(p + 0) = f.Pm.x;
	*(p + 1) = f.Pm.y;
	*(p + 2) = f.Pn.x;
	*(p + 3) = f.Pn.y;
	for (i = 0; i < 4; i++) {//redondear cantidad hacia arriba o abajo
		if (*(p + i) == 0)
			*(up + i) = 0;
		else {
			*(up + i) = (unsigned char)(*(p + i));
			f1 = (float)(*(up + i));
			if (((*(p + i)) - f1) > 0.5)
				(*(up + i))++;
		}
	}
	ufx.Pa.x = *(up + 0);//(unsigned char)f.Pm.x;
	ufx.Pa.y = *(up + 1);//(unsigned char)f.Pm.y;
	ufx.Pb.x = *(up + 2);//(unsigned char)f.Pn.x;
	ufx.Pb.y = *(up + 3);//(unsigned char)f.Pn.y;
	return ufx;
	  	
	  
	  
 
  
}//fin traducir coordenade para coordenadas VFD-----------------------------------






/*Obtiene el Punto de Interseccion de dos rectas */
struct Coordf  get_Puntos_de_Interseccion(struct Ec_Recta f,struct Ec_Recta g){	
double a=0,b=0,c=0,d=0;
struct Coordf ret;
       a=(double)f.m;
       b=(double)g.m;
	   c=(double)f.b;
	   d=(double)g.b;
	   ret.x=(float)((d-c)/(a-b));
	   ret.y=(float)((a*d-b*c)/(a-b));
return ret;	   
}//-----------------------------------------------------------------------------



float atan1(double a) {
	unsigned char i;
	double sum = 0;
	double ret;
	const double pi = 3.141592653;
	double aa;
	aa = (double)a;
	if (aa == 0)
		return 0;
	if (aa == 1)
		return 45;
	if (absd(aa) < 1) {
		for (i = 0; i < 8; i++) {
			sum += (pow1(-1, i) / (2 * i - 1)) * pow1(aa, 2 * i + 1);}
	     ret= rad_a_deg(sum) * -1;}
	else {ret=rad_a_deg((pi / 2) - deg_a_rad(atan1(1 / aa))); }
return (float)ret;
}//fin de arco tangente---------------------------------------------------




//Tangente para pi/2 valores menor a pi/2, la entrada es en radianes
float tanr(float x) {
	return(x + (pow1(x, 3) / 3) + ((2 * pow1(x, 5)) / 15) + ((17 * pow1(x, 7)) / 315) + ((62 * pow1(x, 9)) / 2835));
}//FIN TANGENTE-------------------------------------



//Tangente en grados, valor de entrada menor a 180°
float tan1(float deg) {
	const float pi = (float)3.141592653;
	float rad;
	rad = (deg / 180) * pi;
	return (tanr(rad));
}//tangente fin en grados normales--------------------------



double sin(double g) {
unsigned char n;
double sum = 0,r; 
r = (g * 3.141592653) / 180;
for (n = 0; n < 5; n++) 
 sum += (pow1(-1, n) * pow1(r,(2 * n + 1))) / factorial(2 * n + 1);
return sum;
}//fin sinus ------------------------------


double cos(double g) {
unsigned char n;
double sum = 0, r;
   r = (g * 3.141592653) / 180;
   for (n = 0; n < 5; n++) 
	    sum += (pow1(-1, n) * pow1(r, (2 * n ))) / factorial(2 * n );
return sum;
}//fin sinus -------------------------------


//tangente version 4--------------------------
double tan4(double angulo){ 
      return(sin(angulo)/cos(angulo));
}// fin tangente version 4--------------------


float rad_a_deg(double rad) {
	const double pi = 3.141592653;
	return ((float)((rad / pi) * 180));
}

float deg_a_rad(double deg) {
	const double pi = 3.141592653;
	return ((float)((deg /180) *pi));
}

/* power    */
float pow1(double num1, unsigned char pot) {
	unsigned char i;
	double f = 1,num;
	num =num1;
	if (pot == 0)
		return 1;
	if (pot == 1)
		return (float)num;
	for (i = 0; i < pot; i++)
		f *= num;
	return (float)f;
}//fin pow-------------------------------------------------------------------

/* power    */
float pow1f(float num1, unsigned char pot) {
	unsigned char i;
	double f = 1,num;
	num =(double)num1;
	if (pot == 0)
		return 1;
	if (pot == 1)
		return num1;
	for (i = 0; i < pot; i++)
		f *= num;
return (float)f;
}//fin pow-------------------------------------------------------------------

double pow1d(double num1, unsigned char pot) {
	unsigned char i;
	double f = 1;
	if (pot == 0)
		return 1;
	if (pot == 1)
		return num1;
	for (i = 0; i < pot; i++)
		f *= num1;
return f;
}//fin pow-------------------------------------------------------------------


double factorial(unsigned char a) {
	unsigned char n;
	double sum=1;
	for (n = 1; n <= a; n++)
		sum *= n;
return sum;
}//fin factorial--------------------------------



double absd(double m) {//get absolute from double
	if (m < 0)
		return(m * (-1));
	else return(m);  //absoluto de la pendiente      
}//fin de obtener el absoluto de un numero float---------------------------------------



float absf(float m) {//get absolute from float
	if (m < 0)
		return(m * (-1));
	else return(m);  //absoluto de la pendiente      
}//fin de obtener el absoluto de un numero float---------------------------------------


unsigned long int absul(long int m){
	if (m < 0)
	      return(m * (-1));
	else return(m);  //absoluto de la pendiente
}//--------------------------------------------------------


signed short int absSSInt(signed short int a) {//get the absolute from signed short int
	if (a < 0)
		return(a * (-1));
	else return (a);
}//fin de signed short int absolute--------------------------------------------------


double raizCuadrada(unsigned short int numero) {
	double margen = 0.000001;
	double estimacion = 1.0;
	// Mientras haya una diferencia notable.
	// Es decir, que el cuadrado de nuestra estimación difiera mucho del número
	while (absd((estimacion * estimacion) - numero) >= margen) {
		double cociente = numero / estimacion;
		double promedio = (cociente + estimacion) / 2.0;
		// Elimina la siguiente línea si no quieres ver el proceso
	   // printf("Estimación: %lf. Cociente: %lf. Promedio: %lf\n", estimacion, cociente, promedio);
		estimacion = promedio;
	}
	return estimacion;
}//fin raiz cuadrada-------------------------------------------------


float Raiz2(float num) {
	const float DIF = 0.0001;
	unsigned short int i;
	float  x, x1, ret;

	if (num <= 0) {
		if (num == 0) return 0; else return -1;
	}
	else
	{
		i = 0; x1 = num; x = num / 2;
		while (i < 25) {
			x1 = x - (x * x - num) / (2 * x);
			if (absf(x - x1) < DIF) {
				ret = x1;
				break;
			}
			else {
				i++;
				x = x1;
			}
		}
	}
	return x1;
}//--------------------------------------------------------


double Raizd(double num) {
	const double DIF = 0.0001;
	unsigned short int i;
	double  x, x1, ret;

	if (num <= 0) {
		if (num == 0) return 0; else return -1;
	}
	else
	{
		i = 0; x1 = num; x = num / 2;
		while (i < 25) {
			x1 = x - (x * x - num) / (2 * x);
			if (absd(x - x1) < DIF) {
				ret = x1;
				break;
			}
			else {
				i++;
				x = x1;
			}
		}
	}
	return x1;
}//--------------------------------------------------------
   
/*centra los valores que estan centrados al centro 0,0 los centra al centro
 * del DDS (96,-64)  */
struct Coordf Centrar_Puntos_en_DDS(struct Coordf P){
struct Coordf r;
unsigned char n;
	 r.x=96+P.x; 
	 n=find_Cuadrante(P);
     switch(n){
    	 case 1:r.y=-64-P.y;break;
    	 case 2:r.y=-64+P.y;break;
    	 case 3:
    	 case 4:r.y=-64+P.y;break;
    	 default:r.y=0;r.x=0;break;}
return r;
}//fin de centrar valores al DDS-------------------------------------------------

unsigned char find_Cuadrante(struct Coordf P){
unsigned char i,j,r=0;	
	if((P.x==0)||(P.y==0))
		return 0;
	if(P.x<0) i=0; else i=0xFF;
	if(P.y<0) j=0; else j=0xFF;
	if(j&i) r=2;
	else if(i&(!j))    r=4;
	else if((!i)&j)    r=1;
	else if((!i)&(!j)) r=3;
	else r=0;
return r;	
}//fin de find cuadrante--------------------------------------


/* Regrasa TRUE|FALSE si la coordenada es desplegable en el DDS con el zoom 
 *  actual los datos que le llegan son ya centrados en 96,-64 es P*/
unsigned char isDisplayable_in_ACtual_Zoom(struct Coordf P,unsigned char zoom1){
struct Coordusi P1;
struct Coordssi C={96,64};
    P1=Maximo_Zoom(zoom1);
    if((P.x==0)&&(P.y==0))
    	return FALSE;
    if((absf(P.x)>(C.x+P1.x))||(absf(P.y)>(C.y+P1.y)))
    	return FALSE;
    else return TRUE;
}//fin de es despleglame con el zoom actual en el DDS----------------------vfd.menu.dds.zoom.Zoom





/* valor maximo en x para el valor del zoom*/
struct Coordusi Maximo_Zoom(unsigned char z){//vfd.menu.dds.zoom.Zoom
struct Coordusi P;	
	switch(z){
		case  1: P.x=35534;/*35878.5;*/P.y=23919;break;
		case  2: P.x=3973;/*3973.5;*/  P.y=2649;break;   
		case  3: P.x=2110;/*2110.5;*/  P.y=1407;break;
		case  4: P.x=1434;   P.y=956;break;
		case  5: P.x=1086;   P.y=724;break;
		case  6: P.x=874;/*874.5;*/  P.y=583;break;
		case  7: P.x=732;    P.y=488;break;
		case  8: P.x=628;/*628.5;*/  P.y=419;break;
		case  9: P.x=550;/*550.5;*/  P.y=367;break; 
		case  10:P.x=490;/*490.5;*/  P.y=327;break;
		case  11:P.x=442;/*442.5;*/  P.y=295;break;
		case  12:P.x=402;    P.y=268;break;   
		case  13:P.x=369;    P.y=246;break;
		case  14:P.x=340;/*340.5;*/  P.y=227;break;
		case  15:P.x=316;/*316.5;*/  P.y=211;break;
		case  16:P.x=295;/*295.5;*/  P.y=197;break;
		case  17:P.x=277;/*277.5;*/  P.y=185;break;
		case  18:P.x=261;    P.y=174;break;
		case  19:P.x=246;    P.y=164;break; 
		case  20:P.x=234;    P.y=156;break;
		case  21:P.x=222;    P.y=148;break;
		case  22:P.x=211;/*211.5;*/  P.y=141;break;   
		case  23:P.x=202;/*202.5;*/  P.y=135;break;
		case  24:P.x=193;/*193.5;*/  P.y=129;break;
		case  25:P.x=184;/*184.5;*/  P.y=123;break;
		case  26:P.x=178;/*178.5;*/  P.y=119;break;
		case  27:P.x=171;    P.y=114;break;
		case  28:P.x=165;    P.y=110;break;
		case  29:P.x=159;    P.y=106;break;
		case  30:P.x=153;    P.y=102;break; 
		case  31:P.x=145;/*148.5;*/  P.y=99; break;
		case  32:P.x=144;    P.y=96; break;
		case  33:P.x=139;/*139.5;*/  P.y=93; break;   
		case  34:P.x=133;/*133.5;*/  P.y=89; break;
		case  35:P.x=130;/*130.5;*/  P.y=87; break;
		case  36:P.x=128;/*127.5; */ P.y=85; break;
		case  37:P.x=123;    P.y=82; break;
		case  38:P.x=120;    P.y=80; break;
		case  39:P.x=117;    P.y=78; break; 
		case  40:P.x=111;    P.y=75; break;
		case  41:P.x=109;/*55.5;*/   P.y=74; break;
		case  42:P.x=108;    P.y=72; break;   
		case  43:P.x=103;/*103.5;*/  P.y=70; break;
		case  44:P.x=102;    P.y=69; break;
		case  45:P.x=101;/*100.5;*/  P.y=67; break;
		case  46:P.x=99;     P.y=66; break;
		case  47:P.x=96;     P.y=64; break;
		case  48:P.x=94;/*94.5;*/   P.y=63; break;
		case  49:P.x=92;/*91.5;*/   P.y=61; break;
		case  50:P.x=90;     P.y=60; break; 
		case  51:P.x=88;/*88.5;*/   P.y=59; break;
		case  52:P.x=87;     P.y=58; break;
		case  53:P.x=85;/*85.5;*/   P.y=57; break;   
		case  54:P.x=84;     P.y=56; break;
		case  55:P.x=82;/*82.5;*/   P.y=55; break;
		case  56:P.x=81;     P.y=54; break;
		case  57:P.x=79;/*79.5;*/   P.y=53; break;
		case  58:P.x=78;     P.y=52; break;
		case  59:P.x=74;/*76.5;*/   P.y=51; break; 
		case  60:P.x=75;     P.y=50; break;
		case  61:P.x=73;/*73.5;*/   P.y=49; break;
		case  62:P.x=72;     P.y=48; break;   
		case  63:P.x=72;     P.y=48; break;
		case  64:P.x=70;/*70.5;*/   P.y=47; break;
		case  65:P.x=69;     P.y=46; break;
		case  66:P.x=68;/*67.5;*/   P.y=45; break;
		case  67:P.x=67;/*67.5;*/  P.y=45; break;
		case  68:P.x=66;     P.y=44; break;
		case  69:P.x=65;/*64.5;*/   P.y=43; break;
		case  70:P.x=64;/*64.5;*/   P.y=43; break; 
		case  71:P.x=63;     P.y=42; break;
		case  72:P.x=63;     P.y=42; break;
		case  73:P.x=61;/*61.5;*/   P.y=41; break;   
		case  74:P.x=60;     P.y=40; break;
		case  75:P.x=60;     P.y=40; break;
		case  76:P.x=58;/*58.5;*/   P.y=39; break;
		case  77:P.x=57;/*58.5;*/   P.y=39; break;
		case  78:P.x=57;     P.y=38; break;
		case  79:P.x=57;     P.y=38; break; 
		case  80:P.x=56;/*55.5;*/   P.y=37; break;
		case  81:P.x=55;/*55.5;*/   P.y=37; break;
		case  82:P.x=54;     P.y=36; break;   
		case  83:P.x=54;     P.y=36; break;
		case  84:P.x=53;/*52.5;*/   P.y=35; break;
		case  85:P.x=53;/*52.5;*/   P.y=35; break;
		case  86:P.x=52;/*52.5;*/   P.y=35; break;
		case  87:P.x=51;     P.y=34; break;
		case  88:P.x=51;     P.y=34; break;
		case  89:P.x=50;/*49.5;*/   P.y=33; break;
		case  90:P.x=50;/*49.5;*/   P.y=33; break; 
		case  91:P.x=49;/*49.5;*/   P.y=33; break;
		case  92:P.x=48;     P.y=32; break;
		case  93:P.x=48;     P.y=32; break;   
		case  94:P.x=48;     P.y=32; break;
		case  95:P.x=47;/*46.5;*/   P.y=31; break;
		case  96:P.x=47;/*46.5;*/   P.y=31; break;
		case  97:P.x=46;/*46.5;*/   P.y=31; break;
		case  98:P.x=45;     P.y=30; break;
		case  99:P.x=45;     P.y=30; break;	
		default:break;}
	    vfd.menu.dds.zoom.Maxx=P.x;vfd.menu.dds.zoom.Maxy=P.y;
return P;
}//fin de maxmo valor para eses zoom en cuestion





