#include "strings.h"
#include "system.h"



//* Logitud de la cadena si es numero o letra*/
unsigned short int length(unsigned char *c,unsigned char size){
unsigned short int count=0;                            
unsigned char i=1,estado=0;

  for(i=0;i<size;i++)
    switch(estado){
	   case 0:if(*c!=NAME_INIT) //primer char es ame init?
		          insertChar(c,size,0,NAME_INIT); 
	          estado++;
	          break;
	   case 1:if(*(c+1)==0)
		         return 0;
	          if(isNumLetter(*(c+1)))
	        	   estado++;
	          else{ *(c+1)=0;return 0;}
	          break;
	   case 2:if(isNumLetter(*(c+i)))
		            break;
	          else return ((unsigned short)(i-1));
              break;
	   default:break;}       
return size;  
}//ends the char chain lenght assess .---------------------------------------------------------------

/* insertar el char en el indice indicado en index, 
 * pero se recorre todo los char a la izquierda */
void insertChar(unsigned char *s,unsigned char size,unsigned char index,unsigned char c){
unsigned char i,b,a;
    b=c;
	for(i=index;i<size;i++){
	     a=*(s+i);
	     *(s+i)=b; 
		 b=a;}
}//fin insertchar----------------------------------------


unsigned char isNumLetter(char a){   
	 if(a==0x20)
		  return TRUE;
	 if(a==0)
		 return FALSE;
	 if((a<0x5B)&&(a>0x40))  //A=65h, Z=5Ah
		 return TRUE;
	 if((a<0x7B)&&(a>0x60)) //a=61h, z=7Ah
		 return TRUE;
	 if((a<0x3C)&&(a>0x2f))//0=30h  9=39h  :3A ;3B
		 return TRUE;
	 if(a==0xA5)//Ñ
	    return TRUE;
	 if(a==0xA4)//ñ
	    return TRUE;
	 if((a<0xA4)&&(a>0x7B))//   7C<=symbols<=A3
		return TRUE;
	 if(a==0x2C)
		 return TRUE;//','=2Ch
	 if(a==0x2E)//'.'=2Eh
		 return TRUE;
	 else 
		return FALSE;
}//FIN DE LA FUNCion que determina si el ascci es numero o letra
