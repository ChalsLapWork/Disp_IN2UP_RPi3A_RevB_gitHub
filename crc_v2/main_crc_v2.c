#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char getCRC_v2(unsigned char *data, unsigned char len) {
    unsigned char crc = 0xFF; // Valor inicial de CRC (puede ajustarse según el algoritmo CRC específico)
    for (int i = 0; i < len; i++) {
        crc ^= data[i];  // XOR entre el CRC actual y el byte de datos
        for (unsigned char bit = 8; bit > 0; bit--) {
            if (crc & 0x80) { // Si el bit más significativo es 1
                crc = (crc << 1) ^ 0x07; // Desplazamiento a la izquierda y XOR con 0x07 (polinomio CRC-8)
            } else {
                crc <<= 1; // Solo desplazamiento a la izquierda
            }
        }
    }
    // Asegurarse de que el CRC no sea 0x00 o 0xFF
    if (crc == 0x00) {
        crc = 0x01;
    } else if (crc == 0xFF) {
        crc = 0xFE;
    }
    return crc;
}

int main() {
    unsigned char data[100];  // Array para almacenar los números introducidos
    unsigned char len = 0;    // Contador de la longitud de los datos
    char input[256];          // Buffer para leer la entrada del usuario

    printf("\033[33m  CRC v2 \033[0m");
    printf(" \033[33m Introduce Numeros \n. hexadecimales y presiona Enter cuando termines:\033[0m\n");
    printf("Introduce Numeros \n. hexadecimales y presiona Enter cuando termines:\n");


    // Leer la entrada del usuario
    fgets(input, sizeof(input), stdin);

    // Procesar la entrada para extraer los números hexadecimales
    char *token = strtok(input, " ");  // Dividir la entrada por espacios
    while (token != NULL) {
        unsigned int num;
        int result = sscanf(token, "%x", &num);  // Convertir el token a hexadecimal
        if (result == 1) {
            data[len++] = (unsigned char) num;  // Almacenar el número en el array
        } else {
            printf("Error al procesar el número: %s\n", token);  // Manejar error en caso de no ser un número válido
        }

        // Si hemos alcanzado el límite máximo de datos, terminamos
        if (len >= 100) {
            printf("Se alcanzó el límite máximo de números.\n");
            break;
        }

        // Obtener el siguiente token (número hexadecimal)
        token = strtok(NULL, " ");
    }

    // Verificar si se han introducido números válidos
    if (len == 0) {
        printf("No se han introducido números válidos.\n");
        return 1;
    }

    // Imprimir la cantidad de elementos introducidos
    printf("Número de elementos introducidos: %d\n", len);

    // Llamar a la función getCRC_v2
    unsigned char crc = getCRC_v2(data, len);

    // Mostrar el CRC calculado
    printf("El CRC calculado es: 0x%02X\n", crc);

    return 0;
}
