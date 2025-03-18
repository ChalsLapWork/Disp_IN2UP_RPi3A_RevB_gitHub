#include "math.h"

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