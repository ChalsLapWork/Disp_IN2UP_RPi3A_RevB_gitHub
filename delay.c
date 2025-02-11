#include "delay.h"
#include "system.h"
#include "VFD.h"
#include "queue.h"



unsigned char delay_ms_VFD(unsigned short int t){
union{
  unsigned short int t;
  unsigned char n[2];
}union_usi;                    //0   1   2   3  4   5   6
unsigned char buffer[7],LEN=4;//STX,LEN,CMD,lo, Hi,CRC,ETX

     union_usi.t=t;
      buffer[0]=STX;
      buffer[1]=LEN; //len
      buffer[2]=CMD_DELAY_MS;//comando
      buffer[3]=union_usi.n[0];
      buffer[4]=union_usi.n[1];
      buffer[5]=getCRC_v2(&buffer[1],LEN);
      buffer[6]=ETX;
      VFD_sendBlockChars(&buffer[0],sizeof(buffer));
return 1;        
}//fin de delay miliseconds VFD+++++++++++++++++++++++++++++++

unsigned char delay_us_VFD(unsigned long int t){ 
union{
  unsigned short int t;
  unsigned char n[2];
}union_usi;
unsigned char buffer[7],LEN=4;
     union_usi.t=t;
      buffer[0]=STX;
      buffer[1]=LEN;//len
      buffer[2]=CMD_DELAY_US;//comando
      buffer[3]=union_usi.n[0];
      buffer[4]=union_usi.n[1];
      buffer[5]=getCRC_v2(&buffer[1],LEN);
      buffer[6]=ETX;
      VFD_sendBlockChars(&buffer[0],sizeof(buffer));
return 1;          
}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++