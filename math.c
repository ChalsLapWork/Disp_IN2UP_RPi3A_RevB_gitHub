#include "math.h"
#include "system.h"

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


/*  *n: numero a ser procesado del tipo short int    
 *  digito: digito que se va ha hacer la operacion   digito-> 12345  <--posicion, 5->unidad
 *  op: operacion SUMAR | RESTAR    
 *  Funcion que resta o suma  en un digito en particular  */
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

