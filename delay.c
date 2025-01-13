#include "delay.h"
#include <unistd.h>


unsigned char delay_ms_VFD(unsigned short int t){
unsigned long int t2;
        if(t>10000)
              t=10000;
        t2=t*1000;
        usleep(t2);
return 1;        
}//fin de delay miliseconds VFD+++++++++++++++++++++++++++++++

unsigned char delay_us_VFD(unsigned long int t){ 
       usleep(t);
return 1;       
}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++