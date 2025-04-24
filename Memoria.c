#include "Memoria.h"
#include "errorController.h"
#include "strings.h"
#include "system.h"
#include "VFDmenu.h"
#include <pthread.h>
#include <sys/stat.h>   // para verificar si existe el archivo
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // para sleep()
#include "errorController.h"
#include <time.h>
#include <sqlite3.h>






#define NUM_DE_PASSWORD 5 //caNTIDAD DE password que manejamos 
#define AGREGAR_UCHAR(id, nombre, num) { unsigned char tmp = (num); agregarItemTipo((id), (nombre), "uchar", &tmp); }
#define AGREGAR_INT(id, nombre, num) \
    do { int tmp = (num); agregarItemTipo((id), (nombre), "int", &tmp); } while(0)
#define AGREGAR_FLOAT(id, nombre, num) \
    do { float tmp = (num); agregarItemTipo((id), (nombre), "float", &tmp); } while(0)


typedef struct {// Estructura interna para pasar datos al hilo
    char tipo[32];
    char mensaje[256];
} LogData;

Seguridad g_seguridad = {0};  // Inicializada vacía
sqlite3 *db = NULL;
extern struct _PRODUCT1_ producto2;



// Verifica si el tipo de mensaje es uno válido
static int tipo_valido(const char* tipo) {
    return strcmp(tipo, "Error") == 0 ||
           strcmp(tipo, "Advertencia") == 0 ||
           strcmp(tipo, "Información") == 0 ||
           strcmp(tipo, "Metales") == 0;
}//fin de tipo valido+++++++++++++++++++++++++++++++++

// Función para imprimir texto en color
void mensPrompt(const char* texto, const char* color) {
    printf("%s%s%s\n", color, texto, CRESET);
}//FIN DE MENSAJE+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// Función ejecutada por el hilo para escribir en el log
static void* log_thread_func(void* arg) {
    LogData* data = (LogData*)arg;
    char fecha[128];// Obtener fecha y hora
    time_t ahora = time(NULL);
    struct tm* t = localtime(&ahora);
    strftime(fecha, sizeof(fecha), "%a %b %d %H:%M:%S %Y", t);

    FILE* logf = fopen("log.txt", "a");// Abrir archivo log
    if (!logf) {
        perror("Error al abrir log.txt");
        free(data);
        return NULL;}
    // Escribir mensaje
    fprintf(logf, "[%s] [%s] %s\n", fecha, data->tipo, data->mensaje);
    fclose(logf);
    free(data);
    return NULL;
}//fin de log thread fucntion++++++++++++++++++++++++++++++++++++

// Función pública para registrar un mensaje con tipo
void log_mensaje(const char* tipo, const char* mensaje) {
char tipo2[15];	
    if (!tipo_valido(tipo)) {
		 strcpy(tipo2,"informacion");}
	else{snprintf(tipo2,sizeof(tipo2),"%s",tipo);}// Copia exactamente lo necesario + asegura '\0'
    pthread_t hilo;
    LogData* data = malloc(sizeof(LogData));
    if (!data) {
        perror("malloc hilo log mensaje");
		mensPrompt("Error de malloc al hacer el log ",CAMAR);
        return;}
    strncpy(data->tipo, tipo2, sizeof(data->tipo) - 1);
    data->tipo[sizeof(data->tipo) - 1] = '\0';
    strncpy(data->mensaje, mensaje, sizeof(data->mensaje) - 1);
    data->mensaje[sizeof(data->mensaje) - 1] = '\0';
    if (pthread_create(&hilo, NULL, log_thread_func, data) != 0) {
        perror("pthread_create");
		mensPrompt("Error al escribir el LOG",CAMAR);
        free(data);
        return;}
    pthread_detach(hilo);
}// fin de funcion log mensaje++++++++++++++++++++++++++++++++++

unsigned short int getAddPassword(unsigned char level){
unsigned short int add=0;   
	   switch(level){
		   case 1:add=PASSWORD_LEVE1_ADD;break;
		   case 2:add=PASSWORD_LEVE2_ADD;break;
		   case 3:add=PASSWORD_LEVE3_ADD;break;
		   case 4:add=PASSWORD_LEVE4_ADD;break;
		   default:  }//debug error de software   		
return add;
}//fin getAddPassword-------------------------------------------------------------------

void setPasswords(unsigned char level,unsigned char *p){
    //writeEEPROMblock(getAddPassword(level),PASSWORD_SIZE,p);
    mensOK("Falta la funcion de guardar contraseñas",33); 
}//fin setPasswords---------------------------------------------------------------------

/* VAlida Passwords si es correcta en algun nivel devuelve TRUE, y 
 * *Level regresa en que nivel es aceptado
 *  *T la cadena a evualuar */
unsigned char validatePassword(unsigned char *Level,unsigned char *T){//validamos la password
	//OPERADOR=2,SUPERVISOR=3,ADMINISTRADOR=4,SERVICIO=5
const char *niveles[] = {
        g_seguridad.level1,g_seguridad.level2,
        g_seguridad.level3,g_seguridad.level4,
        g_seguridad.level5
		};

 if(g_seguridad.seguridad_iniciada==INIT){
    for (int i = 0; i < 5; i++) {
        if (strcmp((char*)T, niveles[i]) == 0) {
            *Level = '1' + i;  // Devuelve '1', '2', ..., '5'
            return 1;}
       }}//fin for----------------------------------------------------
  else{log_mensaje("error","falta carga variables del passwrd en sistema RAM");}//NO se han descargado las passwords del sistema.ini
return 0;
}//fin validate password++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//regresamos apuntador de una clave solamente seleccionada
unsigned char *getPasswords(unsigned char level){
	//return(readEEPROMblock(getAddPassword(level),PASSWORD_SIZE));
static unsigned char s[]="password";
return &s[0];
}//fin getPasswords---------------------------------------------------------------

/*Saca del sistema de archivos las variables del sistema  */
// Inicializa las variables del sistema (en un hilo separado)
void init_vars(void){
pthread_t tid;
    if (pthread_create(&tid, NULL, config_thread, NULL) != 0) {
        //perror(" init_vars - pthread_create");
        log_mensaje("error","[Error] Creation thread system var to RAM");
        return;}
	else{log_mensaje("informacion","[ OK ] Creation thread system var to RAM");}	
    pthread_detach(tid);// El hilo es autónomo, no esperamos que termine     
}//fin init vars+++++++++++++++++++++++++++++++++++++++++++


// Verifica si el archivo existe
int no_existe_init() {
    struct stat st;
    return stat(CONFIG_FILE, &st) != 0;
}//fin verifica-------------------------------------------------

// Crea el archivo con sección [General]
/**Archivo system.ini con variables del sistema
 *  para que empieze a trabajar */
void crear_init() {
    FILE *f = fopen(CONFIG_FILE, "w");
    if (!f) {perror("crear_init");
             return;}

    fprintf(f,
        "; Archivo de configuración del sistema\n"
        "; Este archivo será leído al inicio del programa\n\n"
        "[Seguridad]\n"
        "level_1=\"1\"\n"
        "level_2=\"2\"\n"
        "level_3=\"3\"\n"
        "level_4=\"4\"\n"
        "level_5=\"5\"\n\n"
        "[Producto]\n"
        "cuenta_Rechazos=\"1\"\n"
        "cuenta_Producto=\"2\"\n"
        "Producto=\"Test Set-Up\""
        "tiempo_espera=5000\n"
        "; tiempo en milisegundos\n"
        );//fin fprintf-----------------------------------------
    fclose(f);
    mensPrompt("[CONFIG] Archivo creado.",CAQUA);
}//fin crear_init-----------------------------------------------

// Verifica si la sección [Seguridad] está presente		
int no_existe_Seguridad() {
    FILE *f = fopen(CONFIG_FILE, "r");
    if (!f) return 1;
    char line[256];
    while(fgets(line, sizeof(line), f)) {
        if(strstr(line, "[Seguridad]")) {
            fclose(f);
            return 0;}}
    fclose(f);
    return 1;
}//FIN no_existe_Seguridad+++++++++++++++++++++++++++++++++++++++

// Agrega la sección [Seguridad] al final
void crear_seccion_Seguridad() {
    FILE *f=fopen(CONFIG_FILE,"a");
    if(!f){perror("crear_seccion_Seguridad");
           return;}
    fprintf(f,
        "\n[Seguridad]\n"
        "level1=\"1\"\n"
        "level2=\"2\"\n"
        "level3=\"3\"\n"
        "level4=\"4\"\n"
        "level5=\"5\"\n"
          );//fin de fprintf+++++++++++
    fclose(f);
    mensPrompt("[CONFIG] Sección [Seguridad] agregada.",CAQUA);
}//fin crear_seccion_Seguridad-------------------------------------

// Llena la estructura Seguridad desde el archivo
void leer_seguridad_a_struct(Seguridad *sec) {
    FILE *f = fopen(CONFIG_FILE, "r");
    if (!f) {perror("leer_seguridad_a_struct");
             return;}
    char line[256];
    int dentro = 0;
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;
        if (strstr(line, "[Seguridad]")) {
            dentro = 1;
            continue;}
        if (dentro) {     //%[^\"] comando: lee todo hasta encontrar comilla de cierre
            if (line[0] == '[') break; // terminó sección
            sscanf(line, "level_1=\"%[^\"]\"", sec->level1);
            sscanf(line, "level_2=\"%[^\"]\"", sec->level2);
            sscanf(line, "level_3=\"%[^\"]\"", sec->level3);
            sscanf(line, "level_4=\"%[^\"]\"", sec->level4);
            sscanf(line, "level_5=\"%[^\"]\"", sec->level5);}
        }//FIN WHILE-------------------------------------------------
    fclose(f);
       // Verificar campos vacíos y asignar valores por defecto
    if (sec->level1[0] == '\0') strcpy(sec->level1, "1");
    if (sec->level2[0] == '\0') strcpy(sec->level2, "2");
    if (sec->level3[0] == '\0') strcpy(sec->level3, "3");
    if (sec->level4[0] == '\0') strcpy(sec->level4, "4");
    if (sec->level5[0] == '\0') strcpy(sec->level5, "5");
}//FIN leer_seguridad_a_srtruct++++++++++++++++++++++++++++++++++++++++

// Función que se ejecutará en el hilo
void* config_thread(void* arg) {
//Seguridad *sys = (Seguridad*)arg;

    if(no_existe_init()){//archivo init
           crear_init();}//crear archivo init
    if(no_existe_Seguridad()){ //seccion seguridad en archivo init
           crear_seccion_Seguridad();}//crear la seccion
    leer_seguridad_a_struct(&g_seguridad);            
    g_seguridad.seguridad_iniciada=INIT;
    //printf("[CONFIG] Archivo %s creado exitosamente.\n", CONFIG_FILE);
    pthread_exit(NULL);
}//fin config threads++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************
//*************PRODUCTOS****************************************************************

void init_Product(void){
 int sens,n=0;
 unsigned char phase,phasefrac;
  if(conectar_db(PROD_FILE)!=SQLITE_OK){
	 log_mensaje("error"," Error al abrir db productos");
	 mens_Warnning_Debug("Error al abrir db prodcutos");
	 return;} 
  if(!crear_db_si_no_existe()){
	  log_mensaje("error"," Error al crear tablas db productos");
	  mens_Warnning_Debug("Error al crear tablas db prodcutos");
	  return;}
      
  //int id=getIdProductoPorNombre("Test Set-up");	
  int id=get_id_From_ConfigFile();
  if(cargar_Nombre_Producto(id)==-1)//se baja el nombre char del prod  file->vars
    log_mensaje("error","Error al leer name product init");
  producto2.id=id;
  ItemType tipo  = TYPE_INT;  
  ItemType tipo2 = TYPE_UCHAR;  
  n=getItemProducto(id, "Sensibilidad", &tipo, &sens);
  n+=getItemProducto(id, "phase", &tipo2, &phase);
  n+=getItemProducto(id, "phasefrac",  &tipo2, &phasefrac);
  if(n==3){ producto2.Sensibilidad=(unsigned short int)sens;
            producto2.phase=phase;
			producto2.Phasefrac=phasefrac;}
  else {mens_Warnning_Debug("No se pudo leer var Prod init\n");
          log_mensaje("error","Error al leer var prod init");}
}//fin init product++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Esto abre o crea la base de datos física (archivo productos.db).
int conectar_db(const char *filename) {
    return sqlite3_open(filename, &db);
}//fin conectar la base de datos+++++++++++++++++++++++++
void cerrar_db(void) { if (db) sqlite3_close(db);}//fin cerrar la db

/** Esto crea las tablas si aún no existen, 
 * y rellena el primer producto ("Test Set-up") solo si no está.*/
int crear_db_si_no_existe(void) {
    char *err = NULL;
    const char *sql_producto =
        "CREATE TABLE IF NOT EXISTS productos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nombre TEXT NOT NULL);";

    const char *sql_items =
        "CREATE TABLE IF NOT EXISTS items ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "producto_id INTEGER,"
        "nombre TEXT,"
        "tipo TEXT,"
        "valor TEXT,"
        "FOREIGN KEY(producto_id) REFERENCES productos(id));";

    if (sqlite3_exec(db, sql_producto, 0, 0, &err) != SQLITE_OK) {
        printf("\033[33mError creando tabla productos: %s\n\033[0m", err);
		log_mensaje("error"," Error al crear tablas db productos");
        return 0;}

    if (sqlite3_exec(db, sql_items, 0, 0, &err) != SQLITE_OK) {
        printf("\033[33mError creando tabla items: %s\n\033[0m", err);
		log_mensaje("error"," Error al crear tablas db productos");
        return 0;}

    sqlite3_stmt *stmt;
    const char *sql_check = "SELECT COUNT(*) FROM productos WHERE nombre = 'Test Set-up';";
    sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL);
    int existe = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0);}
    sqlite3_finalize(stmt);

    if (!existe) {
        agregarProducto("Test Set-up");
        int id = (int)sqlite3_last_insert_rowid(db);
        //unsigned char uc = 1;
        //float f = 2.5;
        //int i = 1234;
        //char nombre[20] = "Test Set-up";

        //agregarItemTipo(id, "name", "string", nombre);
        AGREGAR_UCHAR(id, "GananciaDrive", 1);  //agregarItemTipo(id, "GananciaDrive", "uchar", &uc);
        AGREGAR_UCHAR(id, "GananciaAnaloga", 1);//agregarItemTipo(id, "GananciaAnaloga", "uchar", &uc);
        AGREGAR_UCHAR(id, "FiltroConfig", 1);   //agregarItemTipo(id, "FiltroConfig", "uchar", &uc);
        AGREGAR_UCHAR(id, "BorrarContadores", 0);//agregarItemTipo(id, "BorrarContadores", "uchar", &uc);
        AGREGAR_FLOAT(id, "Fase", 45.0f);  //agregarItemTipo(id, "Fase", "float", &f);
        AGREGAR_UCHAR(id, "phase", 45);    //agregarItemTipo(id, "phase", "uchar", &uc);
        AGREGAR_UCHAR(id, "phasefrac", 0);   //agregarItemTipo(id, "phasefrac", "uchar", &uc);
        AGREGAR_UCHAR(id, "freqselect", 2);  //agregarItemTipo(id, "freqselect", "uchar", &uc);
        AGREGAR_INT(id, "MarcarAltura",0);   //agregarItemTipo(id, "MarcarAltura", "int", &i);
        AGREGAR_UCHAR(id, "GananciaDDS", 1); //agregarItemTipo(id, "GananciaDDS", "uchar", &uc);
        AGREGAR_UCHAR(id, "zoom", 30);       //agregarItemTipo(id, "zoom", "uchar", &uc);
        AGREGAR_UCHAR(id, "cuadritosDDS", 0);//agregarItemTipo(id, "cuadritosDDS", "uchar", &uc);
        AGREGAR_INT(id, "Sensibilidad",100); //agregarItemTipo(id, "Sensibilidad", "int", &i);
        AGREGAR_INT(id, "Altura",32000);     //agregarItemTipo(id, "Altura", "int", &i);
        AGREGAR_INT(id, "PulsoTiempoRechazo",80);//agregarItemTipo(id, "PulsoTiempoRechazo", "int", &i);
        AGREGAR_INT(id, "PulsosTiempoEspera",100);//agregarItemTipo(id, "PulsosTiempoEspera", "int", &i);
        AGREGAR_UCHAR(id, "Ganancia", 1);     //agregarItemTipo(id, "Ganancia", "uchar", &uc);
        AGREGAR_INT(id, "Frecuencia",1000000);//agregarItemTipo(id, "Frecuencia", "int", &i);
        }//fin de if existe-----------------------------------------
return 1;
}//crear_db_si_no_existe+++++++++++++++++++++++++++++++++++++++++++++



/*
;Set Machine type:Multi(100,286,875),Multi(30,100,286)
;Single(875,286),Single(100,30),VF(875,286),
;VF(100,30),PHARMACEUTICAL
*/
void init_system(void){
FILE *file = fopen(CONFIG_FILE, "r");//TIPO DE MAQUINA
    if (!file) {
        perror("No se pudo abrir systema.ini");
        log_mensaje("error","Error File config file system vars");
        return;}
char line[128];
int en_seccion_system = 0;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == ';' || line[0] == '\n') 
                   continue;// Ignorar comentarios o líneas vacías
        if (line[0] == '[') {// Detectar sección
            en_seccion_system = (strncmp(line, "[system]", 8) == 0);
            continue;}
        // Buscar la clave si estamos en la sección [system]
        if (en_seccion_system && strstr(line, "tipo_de_maquina") != NULL) {
            char *valor = strchr(line, '=');
            if (valor) {
                valor++; // Avanza al valor
                while (*valor == ' ' || *valor == '\"') valor++; // salta espacios y comillas iniciales
                char *fin = valor;
                while (*fin && *fin != '\"' && *fin != ';' && *fin != '\n') fin++;
                *fin = '\0'; // corta el string al final del valor válido
                strncpy(vfd.tipo_de_maquina, valor, sizeof(vfd.tipo_de_maquina) - 1);
                vfd.tipo_de_maquina[sizeof(vfd.tipo_de_maquina) - 1] = '\0'; // seguridad
                break;
            }}}
fclose(file);//fin sacar tipo de maquina----------------------
}//fin de init system------------------++++++++++++++++++++++++++++++++++


int agregarProducto(const char *nombre) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO productos(nombre) VALUES(?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}//agregarProducto++++++++++++++++++++++++++++++++++++++++++++++++++++

int quitarProducto(int productoID) {
    sqlite3_stmt *stmt;
    const char *sql1 = "DELETE FROM items WHERE producto_id=?;";
    const char *sql2 = "DELETE FROM productos WHERE id=?;";
    sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}//fin quitar producto++++++++++++++++++++++++++++++++++++++++++++++++


/** @brief Edita el nombre de un producto existente en la base de datos.
 * Esta función actualiza el campo `nombre` del producto con el ID especificado.
 * Se debe usar después de haber conectado la base de datos con `conectar_db()`.
 * @param productoID El ID del producto que se desea renombrar.
 * @param nuevoNombre El nuevo nombre que se desea asignar al producto.
 * @return Devuelve 1 si la operación fue exitosa (producto editado), o 0 si ocurrió un error.
 * Ejemplo de uso:  editarProducto(1, "Nuevo Nombre"); */
int editarProducto(int productoID, const char *nuevoNombre) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE productos SET nombre=? WHERE id=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nuevoNombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, productoID);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}//fin editar procucto++++++++++++++++++++++++++++++++++++++++++++

/** @brief Agrega un nuevo ítem a un producto en la base de datos.
 * Esta función inserta un ítem asociado a un producto, especificando su nombre,
 * tipo (como string, int, uchar o float) y el valor correspondiente.
 * El valor debe pasarse como puntero al tipo correspondiente.
 * El valor es convertido a texto para almacenarlo en la base de datos.
 * @param productoID ID del producto al que se le agregará el ítem.
 * @param nombre Nombre del ítem (por ejemplo: "Frecuencia", "GananciaDDS").
 * @param tipoStr Tipo del valor como cadena: "int", "uchar", "float" o "string".
 * @param valor Puntero al dato del tipo indicado que será convertido y almacenado.
 * @return Devuelve 1 si se insertó correctamente, o 0 en caso de error.
 * Ejemplo de uso:
 *     int i = 1000;
 *     agregarItemTipo(1, "Frecuencia", "int", &i);
 *
 *     unsigned char uc = 5;
 *     agregarItemTipo(1, "zoom", "uchar", &uc);
 *
 *     float f = 3.14;
 *     agregarItemTipo(1, "Fase", "float", &f);
 *
 *     char nombre[20] = "NombreSensor";
 *     agregarItemTipo(1, "name", "string", nombre);    */
int agregarItemTipo(int productoID, const char *nombre, const char *tipoStr, const void *valor) {
    char buffer[64] = {0};
    if (strcmp(tipoStr, "int") == 0)
        snprintf(buffer, sizeof(buffer), "%d", *(int *)valor);
    else if (strcmp(tipoStr, "uchar") == 0)
        snprintf(buffer, sizeof(buffer), "%u", *(unsigned char *)valor);
    else if (strcmp(tipoStr, "float") == 0)
        snprintf(buffer, sizeof(buffer), "%f", *(float *)valor);
    else if (strcmp(tipoStr, "string") == 0)
        snprintf(buffer, sizeof(buffer), "%s", (char *)valor);
    else return 0;

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO items(producto_id, nombre, tipo, valor) VALUES(?,?,?,?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, tipoStr, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, buffer, -1, SQLITE_STATIC);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}//FIN AGREGAR ITEM TIPO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @brief Elimina un ítem específico de un producto en la base de datos.
 * Esta función borra un ítem asociado a un producto determinado, buscando por
 * el nombre del ítem y el ID del producto. No afecta a otros ítems ni al producto.
 * @param productoID ID del producto al que pertenece el ítem.
 * @param nombre Nombre del ítem a eliminar (por ejemplo: "GananciaDDS").
 * @return Devuelve 1 si el ítem fue eliminado correctamente, o 0 si falló.
 * Ejemplo de uso:
 *     borrarItem(1, "GananciaDDS"); */
int borrarItem(int productoID, const char *nombre) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM items WHERE producto_id=? AND nombre=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_STATIC);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}//fin borrar item++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/** @brief Obtiene el valor y tipo de un ítem específico asociado a un producto.
 * Esta función busca un ítem por nombre dentro del producto indicado por su ID,
 * y extrae su valor original convertido al tipo correspondiente. El tipo detectado
 * se almacena en el parámetro de salida `tipo`, y el valor en `resultado`.
 *
 * El valor recuperado se almacena en la variable apuntada por `resultado`, la cual
 * debe ser del tipo correcto según el contenido esperado:
 * - `int *` si el tipo es TYPE_INT
 * - `unsigned char *` si el tipo es TYPE_UCHAR
 * - `float *` si el tipo es TYPE_FLOAT
 * - `char *` (con al menos 30 bytes) si el tipo es TYPE_STRING
 *
 * @param productoID ID del producto al que pertenece el ítem.
 * @param nombre Nombre del ítem a buscar.
 * @param tipo Puntero a una variable donde se almacenará el tipo del ítem encontrado.
 * @param resultado Puntero a la variable donde se almacenará el valor convertido del ítem.
 * @return Devuelve 1 si se encontró y recuperó correctamente el ítem, o 0 si falló.
 *
 * Ejemplo de uso:
 *     int frecuencia;
 *     ItemType tipo;
 *     if (getItemProducto(1, "Frecuencia", &tipo, &frecuencia)) {
 *         printf("Frecuencia: %d\n", frecuencia);
 *     }                                                                  */
int getItemProducto(int productoID, const char *nombre, ItemType *tipo, void *resultado) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT tipo, valor FROM items WHERE producto_id=? AND nombre=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, productoID);
    sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *tipoStr = (const char *)sqlite3_column_text(stmt, 0);
        const char *valorStr = (const char *)sqlite3_column_text(stmt, 1);

        if (strcmp(tipoStr, "int") == 0) {
            *(int *)resultado = atoi(valorStr);
            *tipo = TYPE_INT;
        } else if (strcmp(tipoStr, "uchar") == 0) {
            *(unsigned char *)resultado = (unsigned char)atoi(valorStr);
            *tipo = TYPE_UCHAR;
        } else if (strcmp(tipoStr, "float") == 0) {
            *(float *)resultado = atof(valorStr);
            *tipo = TYPE_FLOAT;
        } else if (strcmp(tipoStr, "string") == 0) {
            strncpy((char *)resultado, valorStr, 30);
            *tipo = TYPE_STRING;
        } else return 0;
    } else return 0;

    sqlite3_finalize(stmt);
    return 1;
}//fin get item Product++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/** @brief Actualiza el valor de un ítem asociado a un producto en la base de datos.
 * Esta función reemplaza el valor y tipo de un ítem previamente existente
 * dentro del producto especificado por su ID. El nuevo valor se pasa como puntero,
 * y el tipo debe estar correctamente especificado mediante el enum `ItemType`.
 *
 * El valor es convertido a texto y almacenado como cadena en la base de datos,
 * junto con el tipo como string para su posterior conversión correcta.
 *
 * @param productoID ID del producto que contiene el ítem a actualizar.
 * @param nombre Nombre del ítem a modificar.
 * @param tipo Tipo del nuevo valor (TYPE_INT, TYPE_UCHAR, TYPE_FLOAT, TYPE_STRING).
 * @param valor Puntero al nuevo valor del ítem (tipo correspondiente al `tipo` especificado).
 * @return Devuelve 1 si la actualización fue exitosa, o 0 en caso de error o si el ítem no existe.
 * Ejemplo de uso:
 *     int nuevaAltura = 2000;
 *     escribirItemProducto(1, "Altura", TYPE_INT, &nuevaAltura);
 *     float nuevaFase = 3.14f;
 *     escribirItemProducto(1, "Fase", TYPE_FLOAT, &nuevaFase);           */
int escribirItemProducto(int productoID, const char *nombre, ItemType tipo, const void *valor) {
    char buffer[64] = {0};
    const char *tipoStr = "";

    switch (tipo) {
        case TYPE_INT:
            snprintf(buffer, sizeof(buffer), "%d", *(int *)valor);
            tipoStr = "int"; break;
        case TYPE_UCHAR:
            snprintf(buffer, sizeof(buffer), "%u", *(unsigned char *)valor);
            tipoStr = "uchar"; break;
        case TYPE_FLOAT:
            snprintf(buffer, sizeof(buffer), "%f", *(float *)valor);
            tipoStr = "float"; break;
        case TYPE_STRING:
            snprintf(buffer, sizeof(buffer), "%s", (char *)valor);
            tipoStr = "string"; break;
    }

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE items SET valor=?, tipo=? WHERE producto_id=? AND nombre=?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, buffer, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tipoStr, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, productoID);
    sqlite3_bind_text(stmt, 4, nombre, -1, SQLITE_STATIC);
    int r = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return r == SQLITE_DONE;
}//fin escribir item Producto+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @brief Crea un nuevo producto con un conjunto predeterminado de ítems.
 * Esta función crea un nuevo producto en la base de datos con el nombre que le pases como parámetro.
 * Posteriormente, asigna valores predeterminados a varios ítems relacionados con este producto.
 * Si la creación del producto es exitosa, devuelve el ID del nuevo producto. Si ocurre un error,
 * la función retorna 0.
 * Los valores predeterminados asignados a los ítems incluyen configuraciones comunes como:
 * - Ganancia, Fase, Frecuencia, etc.
 * @param nombre Nombre del nuevo producto a crear.
 * @return int El ID del nuevo producto si fue creado correctamente, o 0 en caso de error.
 * Ejemplo de uso:
 *     int nuevoID = crearNewProducto("Nuevo Producto de Test");
 *     if (nuevoID > 0) {
 *         printf("Producto creado con ID: %d\n", nuevoID);
 *     } else {
 *         printf("Error al crear el producto.\n");
 *     }                                                 */
int crearNewProducto(const char *nombre) {
    int id = agregarProducto(nombre);  // Usa la función ya implementada
    if (id == 0) {return 0;}  // Error al crear producto
    
    AGREGAR_UCHAR(id, "GananciaDrive", 1);
    AGREGAR_UCHAR(id, "GananciaAnaloga", 1);
    AGREGAR_UCHAR(id, "FiltroConfig", 1);
    AGREGAR_UCHAR(id, "BorrarContadores", 0);
    AGREGAR_FLOAT(id, "Fase", 45.0f);
    AGREGAR_UCHAR(id, "phase", 45);
    AGREGAR_UCHAR(id, "phasefrac", 0);
    AGREGAR_UCHAR(id, "freqselect", 2);
    AGREGAR_INT(id, "MarcarAltura", 0);
    AGREGAR_UCHAR(id, "GananciaDDS", 1);
    AGREGAR_UCHAR(id, "zoom", 30);
    AGREGAR_UCHAR(id, "cuadritosDDS", 0);
    AGREGAR_INT(id, "Sensibilidad", 100);
    AGREGAR_INT(id, "Altura", 32000);
    AGREGAR_INT(id, "PulsoTiempoRechazo", 100);
    AGREGAR_INT(id, "PulsosTiempoEspera", 100);
    AGREGAR_UCHAR(id, "Ganancia", 1);
    AGREGAR_INT(id, "Frecuencia", 1000000);

return id;  // Devuelve el ID del nuevo producto
}//fin de crear  nuevo  Producto con valores de default++++++++++++++++++++++++++

/**
 * @brief Obtiene el ID de un producto dado su nombre.
 * Esta función busca en la tabla `productos` un registro cuyo campo `nombre`
 * coincida exactamente con el nombre proporcionado. Si se encuentra, se retorna
 * su ID. Si no se encuentra, se retorna 0.
 * @param nombre El nombre del producto a buscar.
 * @return int El ID del producto, o 0 si no se encuentra o hay error. */
int getIdProductoPorNombre(const char *nombre) {
sqlite3_stmt *stmt;
const char *sql = "SELECT id FROM productos WHERE nombre = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la consulta SELECT id: %s\n", sqlite3_errmsg(db));
        return 0;}
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    int id = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) { id = sqlite3_column_int(stmt, 0);}
    sqlite3_finalize(stmt);
return id;
}//get  id del nombre del producto++++++++++++++++++++++++++++++++++++++++++++++++++++++



void guardar_estado_Contadores(void){
    FILE *f_original = fopen(CONFIG_FILE, "r");
    FILE *f_temp = fopen("temp.ini", "w");

    if (!f_original || !f_temp) {
        printf("Error al abrir archivo\n");
        log_mensaje("error","error al guardar contadores");
        if (f_original) fclose(f_original);
        if (f_temp) fclose(f_temp);
        return;}

    char linea[256];
    int en_producto = 0;

    while (fgets(linea, sizeof(linea), f_original)) {
        if (strncmp(linea, "[Producto]", 10) == 0) {
            en_producto = 1;
            fputs(linea, f_temp);
            continue;}

        if (en_producto && linea[0] == '[' && linea[1] != '\0') {
            en_producto = 0;}  // Salimos de la sección

        if (en_producto && strncmp(linea, "cuenta_Rechazos=", 16) == 0) {
            fprintf(f_temp, "cuenta_Rechazos=\"%d\"\n", producto2.Cuenta_Productos);}
        else if (en_producto && strncmp(linea, "cuenta_Producto=", 16) == 0) {
            fprintf(f_temp, "cuenta_Producto=\"%d\"\n", producto2.Cuenta_Rechazos);}
        else {fputs(linea, f_temp);}  // Línea sin cambios
    }//fin while-------------------------------------------------------------
    fclose(f_original);
    fclose(f_temp);
    remove(CONFIG_FILE);// Reemplazar original
    rename("temp.ini", CONFIG_FILE);
}//fin de guardar estados de contadores---------------------------------------------


//cargar al inicio del sistema las variables de
//contar producto y rechazos.
void cargar_estado_Contadores(void) {
    FILE *archivo = fopen(CONFIG_FILE, "r");
    if (!archivo) {
        perror("No se pudo abrir el archivo de configuración");
        
        return;}
    char linea[256];
    int en_seccion_producto = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\r\n")] = '\0';// Elimina salto de línea
        if (strncmp(linea, "[Producto]", 10) == 0) {// Busca la sección [Producto]
            en_seccion_producto = 1;
            continue;}
        if (en_seccion_producto && linea[0] == '[') {// Si encontramos otra sección, salimos
            break;}
        if (en_seccion_producto) {
            if (strncmp(linea, "cuenta_Rechazos=", 16) == 0) {
                producto2.Cuenta_Rechazos = atoi(strchr(linea, '"') + 1);
            } else if (strncmp(linea, "cuenta_Producto=", 16) == 0) {
                producto2.Cuenta_Productos = atoi(strchr(linea, '"') + 1);}}}
  fclose(archivo);
}//fin de vargar las variables de cont rechazo y cont producto+++++++++++++++++++++++++++++


/* obtiene el numero del producto seleccionado que estuvo operando para 
con ese numero sacar los datos del producto de la base de datos*/
int get_id_From_ConfigFile(void) {
    FILE *archivo = fopen(CONFIG_FILE, "r");
    if (!archivo) {
        perror("No se pudo abrir el archivo de configuración");
        return 1;}//regresa, osea test Setup
    char linea[256];
    int en_seccion_producto = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\r\n")] = '\0'; // Elimina salto de línea
        if (strncmp(linea, "[Producto]", 10) == 0) {
            en_seccion_producto = 1;
            continue;}
        if (en_seccion_producto && linea[0] == '[') {
            break;} // Ya no estamos en sección Producto
        if (en_seccion_producto && strncmp(linea, "Producto_id=", 12) == 0) {
            char *comillas = strchr(linea, '"');
            if (comillas) {
                int id = atoi(comillas + 1);
                fclose(archivo);
                return id;}}}
    fclose(archivo);
return 1; // No se encontró Producto_id,asi que sera test-setup
}//leer el producto del archivo de sysstema.ini++++++++++++++++++++++++++++++++++++++++++



int cargar_Nombre_Producto(int id) {
sqlite3 *db;
sqlite3_stmt *stmt;
int rc;
const char *sql = "SELECT nombre FROM Productos WHERE id = ?";

    rc = sqlite3_open(PROD_FILE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "No se pudo abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return -1;}

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;}

    sqlite3_bind_int(stmt, 1, id);// Bind del ID del producto
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nombre = sqlite3_column_text(stmt, 0);
        strncpy(producto2.name, (const char *)nombre, sizeof(producto2.name) - 1);
        producto2.name[sizeof(producto2.name) - 1] = '\0';} // Asegura null-termination
    else {
        fprintf(stderr, "No se encontró el producto con ID %d\n", id);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;}

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}//fin de cargar nombre de producto en la var name global+++++++++++++++
