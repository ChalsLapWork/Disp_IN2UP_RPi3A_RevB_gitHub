


#define NUM_ENTRADAS 10 //num de strings antes de procesadas
#define MAX_LEN 50  // Tamaño máximo del array en cada entrada del buffer
#define MAX_BUFFER_LEN (NUM_ENTRADAS * MAX_LEN)  // Tamaño máximo para buffer2 y buffer3


// Prototipos
void *VFDserial_SendBlockProductor(void *arg);
void *VFDserial_SendBlockConsumidor(void *arg);
void VFDserial_SendBlock_Tx(unsigned char *buffer, size_t len);
unsigned char VFDserial_SendBlock_buf(void *ptr, size_t size);
void init_VFD_Threads(void);