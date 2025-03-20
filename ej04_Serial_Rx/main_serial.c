#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <string.h>

// Códigos de escape ANSI para colores
#define COLOR_VERDE "\033[32m"
#define COLOR_ROJO  "\033[31m"
#define COLOR_RESET "\033[0m"

int main() {
    int serial_port;
    char buffer[256];
    int bytes_received;

    // Inicializar WiringPi
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Error al inicializar WiringPi.\n");
        return 1;
    }

    // Abrir el puerto serial ttyAMA0
    if ((serial_port = serialOpen("/dev/ttyAMA0", 115200)) < 0) {
        fprintf(stderr, "Error al abrir el puerto serial.\n");
        return 1;
    }

    printf("%sConexión serial establecida. Esperando datos...%s\n", COLOR_VERDE, COLOR_RESET);

    // Bucle principal para recibir datos
    while (1) {
        if (serialDataAvail(serial_port) > 0) {
            bytes_received = read(serial_port, buffer, sizeof(buffer) - 1);  // Leer datos
            if (bytes_received > 0) {
                buffer[bytes_received] = '\0';  // Terminar la cadena

                // Mostrar los datos recibidos con colores
                printf("%sDatos recibidos:%s %s%s\n", COLOR_VERDE, COLOR_RESET, COLOR_ROJO, buffer);
            }
        }

        // Pequeña pausa para evitar sobrecargar la CPU
        usleep(1000);  // Esperar 1 ms
    }

    // Cerrar el puerto serial (nunca se alcanzará en este ejemplo)
    serialClose(serial_port);
    return 0;
}