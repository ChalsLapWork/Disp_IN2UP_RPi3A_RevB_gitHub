#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <string.h>

#define SERIAL_PORT "/dev/serial0"
#define BAUD_RATE 9600
#define BUF_SIZE 1024

// Función para mostrar mensajes con colores (verde, amarillo, rojo)
void print_green(const char* message) {
    printf("\033[0;32m%s\033[0m\n", message);  // Verde
}

void print_yellow(const char* message) {
    printf("\033[0;33m%s\033[0m\n", message);  // Amarillo
}

void print_red(const char* message) {
    printf("\033[0;31m%s\033[0m\n", message);  // Rojo
}

// Función para enviar datos al puerto serial
void send_data(int serial_fd, const char* data) {
    serialPuts(serial_fd, data);
    printf("Enviado: %s\n", data);
}

// Función para recibir datos del puerto serial
void receive_data(int serial_fd) {
    char buffer[BUF_SIZE];
    int i = 0;
    while (1) {
        // Leer byte del puerto serial
        char byte = serialGetchar(serial_fd);
        
        // Si no hay datos, salir del bucle
        if (byte == -1) {
            break;
        }

        if (byte == '\n' || byte == '\r') {
            // Terminar la cadena de texto
            buffer[i] = '\0';
            if (i > 0) {
                print_yellow("Recibido: ");
                printf("%s\n", buffer);
            } else {
                print_green("Recibiendo datos...");
            }
            i = 0;  // Reiniciar el índice para el siguiente mensaje
        } else {
            // Almacenar byte recibido en el buffer
            if (i < BUF_SIZE - 1) {
                buffer[i++] = byte;
            } else {
                // Evitar desbordamiento de búfer
                buffer[i] = '\0';
                i = 0;
            }
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

    // Bucle para enviar y recibir datos continuamente
    while (1) {
        send_data(serial_fd, "Hola");
        usleep(1000000);  // Espera 1 segundo
        receive_data(serial_fd);
        usleep(1000000);  // Espera 1 segundo
    }

    // Cerrar el puerto serial
    serialClose(serial_fd);

    return 0;
}
