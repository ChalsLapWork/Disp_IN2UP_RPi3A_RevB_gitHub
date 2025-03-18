#define CROJO1     31
#define CNEGRO    30
#define CVERDE    32
#define CAMARILLO 33
#define CAZUL1    34
#define CMAGNETA  35
#define CCIAN     36
#define CBLANCO   37
#define CRESET1    0

#define CROJO  "\033[31m"
#define CVERD  "\033[32m"
#define CAMAR  "\033[33m"
#define CAZUL  "\033[34m"
#define CMORA  "\033[35m"
#define CVIOL  CMORA
#define CAQUA  "\033[36m"
#define CBLAN  "\033[37m"
#define CRESET "\033[0m"

void errorCritico(char *c);
void NoErrorOK(void);
void mensOK(const char *s,unsigned char color);
void errorCritico2(char *c,unsigned char n);
void mens_Warnning_Debug(char *c);