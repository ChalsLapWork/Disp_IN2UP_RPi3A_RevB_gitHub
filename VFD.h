#ifndef _VFD_H_
#define _VFD_H_

#ifndef _PTHREAD_H_
  #define _PTHREAD_H_
  #include <pthread.h>
#endif

#define keyEN  0x22U
#define keyDN  0x23U
#define keyLF  0x24U
#define keyRT  0x25U
#define keyUP  0x26U




#define FONTSIZE1   0x01U //6x8
#define FONTSIZE2   0x02U //8x16
#define FONTSIZE3   0x03U //12x24
#define FONTSIZE4   0x04U  //16x32

typedef union{//access word: 
	unsigned  short int coord16;   //   	0xaabb   
	unsigned char byte[2];        //byte[0]=aa,byte[1]=bb
}coordn16; //coordenadas de 2 bytes 

typedef struct {
    char buffer[BUFFER_SIZE][MAX_MESSAGE_LEN];
    _Atomic int head;  // Índice de escritura (hilo padre)
    _Atomic int tail;  // Índice de lectura (hilo hijo)
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} circular_buffer_t;

extern circular_buffer_t buffer;

void VFDkeypad_ISR(unsigned char c);
void init_VFD_BIOS(void);
void VFDposicionDDS(unsigned short int x,unsigned short int y);
void VFDserial_SendCharDDS(unsigned char c);
void VFDdrawLine(unsigned char pen,unsigned short int x1,unsigned short y1,unsigned short int x2,unsigned short y2);
//void VFDdotDrawing(unsigned short int x,unsigned short int y);
//void disable_keyboard_IRQ(void);
//void enable_keyboard_IRQ(void);
//void Timer_enable_keyboard_IRQ(void);
void BarraDet_VFDserial_SendChar(unsigned char c);
//void disable_keyboard_IRQ2(void);
//void enable_keyboard_IRQ2(void);
//void Timer_enable_keyboard_IRQ2(void);
void VFDboxLine(unsigned char pen,unsigned char mode,unsigned short int x1,unsigned short y1,unsigned short int x2,unsigned short y2);
void VFDclrscrForce(void);
unsigned char VFDposicion(unsigned short int x,unsigned short int y);
void VFDclrscr_DDS(void);
//void monitorDDS_Halt(void);
//void VFDserial_SendChar_DDS(unsigned char c);
void VFDcommand_Bold_DDS(unsigned char bold);
void BarraDet_VFDposicion(unsigned short int x,unsigned short int y);
void menuKey(unsigned char key,unsigned short int Et,unsigned char c);
void teclado_Control(unsigned char c,unsigned short int EnTime,unsigned short int Keytime);
unsigned char Basura(unsigned char c);
unsigned char VFDserial_SendChar1(unsigned char c);
//unsigned char VFDserial_SendBlock1(unsigned char *Ptr,unsigned short Size,unsigned short *Snd,unsigned char inst);
//unsigned char VFDserial_SendBlock1(unsigned char *Ptr,unsigned short Size,unsigned char *inst);
//unsigned char xInit_VFD(struct DPM m);
//unsigned char VFDcommand(unsigned char cmd,unsigned char s);
//unsigned char FontSizeVFD(unsigned char m);
//unsigned char VFDclrscr(void);
unsigned char VFDclrscr1(unsigned char *instancia);
unsigned char VFDboxLine1(unsigned char pen,unsigned char mode,unsigned short int x1,unsigned short y1,unsigned short int x2,unsigned short y2);
//unsigned char VFDserial_SendBlock2(const unsigned char *Ptr,unsigned short Size,unsigned char *inst);
//unsigned char VFDserial_SendBlock1(unsigned char *Ptr,unsigned char Size,unsigned char *Snd,unsigned char *mem);
unsigned char VFDserial_SendBlock1(const char *c);
//unsigned char FontSizeVFD(unsigned char m,unsigned char *s1,unsigned char *s2);
//unsigned char VFDcommand(unsigned char cmd,unsigned char *inst1,unsigned char *inst2);
void VFDclrscr(void);
//unsigned char FontSizeVFD(unsigned char m,unsigned char Padre);
void VFDdrawLine1(unsigned char pen,unsigned short int x1,unsigned short y1,unsigned short int x2,unsigned short y2);
//unsigned char FontSizeVFD(unsigned char m,unsigned char *p);
unsigned char VFDcommand(unsigned char cmd);
unsigned char VFDcommand_init(unsigned char cmd);	
unsigned char VFDdrawLine_v4(unsigned char pen,unsigned short int x1, unsigned short int y1,unsigned short int x2,unsigned short int y2,unsigned short int delay1,unsigned char *inst,unsigned short int *usi);
unsigned char VFDdrawLine_v5(unsigned char pen,unsigned short int x1, unsigned short int y1,unsigned short int x2,unsigned short int y2,unsigned short int delay1,unsigned char *inst,unsigned short int *usi,unsigned char PIDpadre);
void VFDcommand_Bold_DDS(unsigned char bold);
unsigned char VFDcommand_Bold_DDS_v2(unsigned char bold);
unsigned char FontSizeVFD(unsigned char m,unsigned char *mem);
unsigned char delay_us_VFD(unsigned short int t);
void initParallelPort_Global(void);
void writePort(unsigned char value);
void test_display(void);
void* Mon_VFD(void* arg);  //Proceso Productor<---Proceso/hilo/THread
void *Clean_VFD(void *arg);

#endif