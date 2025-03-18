

unsigned short int length(unsigned char *c,unsigned char size);
void insertChar(unsigned char *s,unsigned char size,unsigned char index,unsigned char c);
unsigned char isNumLetter(char a);
void cleanArray(unsigned char *arr,unsigned char size,unsigned char k);
void getCharsFromUINT_var(unsigned char *p,unsigned short int var);
void convertir_usint_to_BCD(unsigned char *p,unsigned short int var);
void suma_BCD(unsigned char dm1,unsigned char m1,unsigned char c1,unsigned char d1,unsigned char u1,unsigned char *p);
void suma_BCD_digito(unsigned char op,unsigned char n,unsigned char *p);
unsigned char func_Alge(unsigned char x);
void Formato_USInt(unsigned char *orig,unsigned char *dest,unsigned char size,unsigned char *n);
void vaciar_A2B(unsigned char *a,unsigned char *b,unsigned char i,unsigned char f);