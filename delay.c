#include "delay.h"
#include "system.h"
#include "VFD.h"



unsigned char delay_ms_VFD(unsigned short int t){
union{
  unsigned short int t;
  unsigned char n[2];
}union_usi;
unsigned char buffer[7];
unsigned short int suma=0;
     union_usi.t=t;
      buffer[0]=STX;
      suma+=buffer[1]=4;//len
      suma+=buffer[2]=CMD_DELAY_MS;//comando
      suma+=buffer[3]=union_usi.n[0];
      suma+=buffer[4]=union_usi.n[1];
      buffer[5]=getCRC(suma,4);
      buffer[6]=ETX;
      VFD_sendBlockChars(&buffer[0],sizeof(buffer));
return 1;        
}//fin de delay miliseconds VFD+++++++++++++++++++++++++++++++

unsigned char delay_us_VFD(unsigned long int t){ 
union{
  unsigned short int t;
  unsigned char n[2];
}union_usi;
unsigned char buffer[7];
unsigned short int suma=0;
     union_usi.t=t;
      buffer[0]=STX;
      suma+=buffer[1]=4;//len
      suma+=buffer[2]=CMD_DELAY_US;//comando
      suma+=buffer[3]=union_usi.n[0];
      suma+=buffer[4]=union_usi.n[1];
      buffer[5]=getCRC(suma,4);
      buffer[6]=ETX;
      VFD_sendBlockChars(&buffer[0],sizeof(buffer));
return 1;          
}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++