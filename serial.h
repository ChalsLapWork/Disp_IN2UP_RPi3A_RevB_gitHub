int init_Serial(void);
void Procesamiento_de_cadena_serProc(char *c,int size);
void procesarComando(unsigned char cmd,unsigned char *param);
//void procesarCmd(unsigned char cmd,unsigned char *param);
void *serial_reader(void *arg);
void *cons_serial_processor(void *arg);
void cerrar_puerto_serial(void);
void Serial_Command_Barra_Detection(unsigned char parametro);
void Serial_Command_Sens_Phase_Det(unsigned char *parametros);