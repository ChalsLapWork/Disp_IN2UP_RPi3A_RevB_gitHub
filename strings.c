#include "strings.h"
#include "system.h"
#include "Memoria.h"



//* Logitud de la cadena si es numero o letra*/
unsigned short int length(unsigned char *c,unsigned char size){
//unsigned short int count=0;                            
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


/* arr: es el array a limpiar, size es el tamaño del array, k es la kosntante
 * que se va allenar el array  */
void cleanArray(unsigned char *arr,unsigned char size,unsigned char k){
unsigned char  i;        
	for(i=0;i<size;i++)
	     *(arr+i)=k;
}//fin de clean array----------------------------------------------------------------


// 54321 en chars seria c[]={5,4,3,2,1}
/* obtiene  5 chars de una variable  unsigned int,(bug-> deberia ser short int esta variable */
void getCharsFromUINT_var(unsigned char *p,unsigned short int var){

	convertir_usint_to_BCD(p,var);
         
}//fin get a five chars from a uint number that should be unsigned short int
   


/*convierte los numeros en sus numeros BCD de 5 cifras para ser desplegas en display
 * */
void convertir_usint_to_BCD(unsigned char *p,unsigned short int var){
unsigned char i;	
const unsigned short int B[]={0x8000,0x4000,0x2000,0x1000,0x0800,0x0400,0x0200,0x0100,0x0080,0x0040,0x0020,0x0010,0x0008,0x0004,0x0002,0x0001};	
const unsigned char DM[]={3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const unsigned char  M[]={2,6,8,4,2,1,0,0,0,0,0,0,0,0,0,0};
const unsigned char  C[]={7,3,1,0,0,0,5,2,1,0,0,0,0,0,0,0};
const unsigned char  D[]={6,8,9,9,4,2,1,5,2,6,3,1,0,0,0,0};
const unsigned char  U[]={8,4,2,6,8,4,2,6,8,4,2,6,8,4,2,1};
         for(i=0;i<5;i++)
        	  *(p+i)=0;
         for(i=0;i<16;i++)
        	 if((var&B[i])==B[i])
        		  suma_BCD(DM[i],M[i],C[i],D[i],U[i],p);
}//--------------------------------------------------------------------------------


void suma_BCD(unsigned char dm1,unsigned char m1,unsigned char c1,unsigned char d1,unsigned char u1,unsigned char *p){
	 suma_BCD_digito(_DM_,dm1,p);
	 suma_BCD_digito(_M_ ,m1,p);
	 suma_BCD_digito(_C_ ,c1,p);
	 suma_BCD_digito(_D_ ,d1,p);
	 suma_BCD_digito(_U_ ,u1,p);
}//---------------------------------------------------------------------------------


/*  *(p+0)=DM    *(p+1)=M    *(p+2)=C   *(p+3)=D   *(p+4)=U
 * */
void suma_BCD_digito(unsigned char op,unsigned char n,unsigned char *p){
unsigned char u,d,c,m,dm;
        dm=*(p+0);          
	    m=*(p+1);
  	    c=*(p+2);
	    d=*(p+3);
  	    u=*(p+4);
	 switch(op){
		 case _U_:u+=n;
		          if(u>9){         
		             u-=10; 
		             d++;
		             goto BCD1;} 
		          else goto BCDx;;
		          break;
		 case _D_:d+=n;
BCD1:             if(d>9){
		        	 d-=10;
		        	 c++;
		        	 goto BCD2;}
				  else goto BCDx;
 	 	 	 	  break;
		 case _C_:c+=n;
BCD2:             if(c>9){
	                  c-=10;
	                  m++;
	                  goto BCD3;}
				  else goto BCDx;
				  break;
		 case _M_:m+=n;
BCD3:	  	  	  if(m>9){
		  	  		  m-=10;
		  	  		  dm++;
		  	  		  goto BCD4;}
		  	  	  else goto BCDx;
		  	  	  break;
		 case _DM_:dm+=n;
BCD4:      	     if(dm>9)
		     		   break;
		     	   break;
		 default:break;}//fin switch
BCDx:  
  	  	*(p+0)=dm;          
	    *(p+1)=m;
  	    *(p+2)=c;
	    *(p+3)=d;
  	    *(p+4)=u;
	      
}//---------------------------------------------------------------------------------


unsigned char func_Alge(unsigned char x){
    if (x == 1 || x == 2) return 2;
    if (x == 3 || x == 4) return 1;
    if (x == 5) return 0;
    return -1;     
}//fin func algebraica++++++++++++++++++++++



/*da formato a los numero unsigned short int e.g.  n="00032" resultado="32"000 
 *   e.g.    n="00000"  res="0"0000    e.g. n="01234" res="1234"0
 *    para poder mandarlo al display aparti del indice cero que es el MSB  
 *    regresa el numero de digitos a desplegar en el display de 1 a 5  
 *     size: es el tamaño del origen
 *     n: REGRESA  el numero de chars a desplegar*/
void Formato_USInt(unsigned char *orig,unsigned char *dest,unsigned char size,unsigned char *n){
auto unsigned char estado;
auto unsigned char ret=FALSE;
auto unsigned char i=0,j;
unsigned char ret2;
  while(ret!=TRUE){
	if(i>5){__asm(nop);__asm(Halt);}  
    switch(estado){// 00000
    	case 1:if((*(orig+i)>='0')||(*(orig+i)<='9')){
    		      if(*(orig+i)=='0'){//regresa el indice donde  esta el primero a desplegar
    		    	   if(i<4){i++;}
    		    	   else{estado++;}}
    		      else{estado++;}}
    		   else{__asm(nop);__asm(Halt);}
    		   break;
    	case 2:if(i>0)
    		      estado++;
    		   else estado=9;
    	       break;//01234, "xxxx0" "xxx00" "xx000"
    	case 3:if(i>4){__asm(nop);__asm(Halt);}//no debe se mayor a 4
    		   estado++;j=0;ret2=5-i;
    		   break;
    	case 4:if(j>4){ estado++;j=0;}//limpiamos destino
    	       else {*(dest+j)=0;j++;}
    	       break;
    	case 5:*(dest+j)=*(orig+i);
    	       if(++i>4)
    	    	     estado++;
    	       else{j++;}
    	       break;
    	case 6:ret=TRUE;break;
    	case 9:ret2=5;//no ha habido nada que recorrer porque e.g. var="54321"
    		   vaciar_A2B(orig,dest,0,size-1);
    	       ret=TRUE;
    	       break;
    	default:estado=1;ret=0;break;}	
    }//fin while ------------------------------
*n=ret2;
}//fin Formato_USInt-------------------------------------------------------------




