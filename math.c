#include "math.h"

/*  recalcula y ajusta los valores de la barra de deteccion para 
  ponerlos en valores fijos de cinco en cinco */
unsigned char recalcular_valor_Ser_Barr_det(unsigned char val){
unsigned char ret,estado;
       if((val>=15)&&(val<20)){ret=15;goto switch1;}
       if((val>=20)&&(val<30)){ret=20;goto switch1;}
       if((val>=25)&&(val<35)){ret=25;goto switch1;}
       if((val>=30)&&(val<40)){ret=30;goto switch1;}
       if((val>=35)&&(val<45)){ret=35;goto switch1;}
       if((val>=40)&&(val<50)){ret=40;goto switch1;}
       if((val>=45)&&(val<55)){ret=45;goto switch1;}
       if((val>=50)&&(val<60)){ret=50;goto switch1;}
       if((val>=55)&&(val<65)){ret=55;goto switch1;}
       if((val>=60)&&(val<70)){ret=60;goto switch1;}
       if((val>=65)&&(val<75)){ret=65;goto switch1;}
       if((val>=70)&&(val<80)){ret=70;goto switch1;}
       if((val>=75)&&(val<85)){ret=75;goto switch1;}
       if((val>=80)&&(val<90)){ret=80;goto switch1;}
       if((val>=85)&&(val<95)){ret=85;goto switch1;}
       if(val>=90){            ret=90;goto switch1;}      
switch1:
return ret;
}//fin de recalcular valores de serial barra de deteccion