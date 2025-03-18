#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <string.h>

#define SERIAL_PORT "/dev/serial0" // Cambiar si es necesario
#define BAUD_RATE   9600
#define BUF_SIZE 1024

// Función para mostrar mensajes con colores
void print_green(const char* message) {
    printf("\033[0;32m%s\033[0m\n", message);  // Verde
}

void print_yellow(const char* message) {
    printf("\033[0;33m%s\033[0m\n", message);  // Amarillo
}

// Función para enviar datos al puerto serial
void send_data(int serial_fd, const char* data) {
    serialPuts(serial_fd, data);  // Enviar datos al puerto serial
    serialFlush(serial_fd);       // Asegura que los datos sean enviados
    print_green("Enviado:");
    printf("\033[0;32m  %s\n \033[0m ", data);
}

// Función para recibir datos del puerto serial
void receive_data(int serial_fd) {
    char byte;
    
    // Mientras haya datos en el buffer serial
    while (serialDataAvail(serial_fd)) {
        byte = serialGetchar(serial_fd); // Leer byte del puerto serial
        
        if (byte != -1) {
            //print_yellow("Recibido: ");
            printf("\033[0;33m %x \033[0m", byte);  // Imprimir byte recibido
        }
    }
}

int main() {
    int serial_fd;

    // Inicializar wiringPi
    if (wiringPiSetup() == -1) {
        printf("Error al inicializar wiringPi\n");
        return -1;
    }

    // Abrir el puerto serial
    serial_fd = serialOpen(SERIAL_PORT, BAUD_RATE);
    if (serial_fd == -1) {
        printf("Error al abrir el puerto serial\n");
        return -1;
    }

    // Asegurarse de que el puerto está configurado correctamente
    serialFlush(serial_fd);

    // Bucle para enviar y recibir datos continuamente
    while (1) {
        send_data(serial_fd, "Hola");
        usleep(400000);  // Esperar 1 segundo

        receive_data(serial_fd);  // Leer datos recibidos
        usleep(400000);  // Espera 1 segundo
    }

    // Cerrar el puerto serial
    serialClose(serial_fd);
    return 0;
}
