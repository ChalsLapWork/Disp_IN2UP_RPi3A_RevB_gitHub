
#define NOMBRE_PRODUCTO_SIZE  20
#define NAME_INIT             0xE8 //DETERMINA QUE LA cadena de nombre del producto es un producto con nombre real y no solo basura


struct _PRODUCTO_{
     unsigned char name[NOMBRE_PRODUCTO_SIZE]; 
};// producto +++++++++++++++++++++++++++++++++++++