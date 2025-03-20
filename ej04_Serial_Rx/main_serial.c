#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>
#include <termios.h>

#define BUF_SIZE 256
#define BUFFER6_SIZE 1024
#define STX 0x03
#define ETX 0x02

#define CAZUL "\033[34m"
#define CAMAR "\033[31m"
#define CAQUA "\033[36m"
#define CRESET "\033[0m"

typedef struct {
    int serial_fd;
    char buffer6[BUFFER6_SIZE];
    int data_ready;
    pthread_mutex_t mutex;
} thread_data_t;

void configure_serial(int fd) {
    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag = CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);
}

void *serial_reader(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char temp_buffer[BUF_SIZE];
    ssize_t bytes_read;
    fd_set read_fds;
    struct timeval timeout;
    int ncount = 0;

    printf("%s[LECTOR] Hilo de lectura iniciado. Esperando datos...%s\n", CAZUL, CRESET);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(data->serial_fd, &read_fds);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int ret = select(data->serial_fd + 1, &read_fds, NULL, NULL, &timeout);
        if (ret > 0 && FD_ISSET(data->serial_fd, &read_fds)) {
            bytes_read = read(data->serial_fd, temp_buffer, BUF_SIZE - 1);
            if (bytes_read > 0) {
                temp_buffer[bytes_read] = '\0';
                pthread_mutex_lock(&data->mutex);
                
                if (strlen(data->buffer6) + bytes_read < BUFFER6_SIZE) {
                    strncat(data->buffer6, temp_buffer, bytes_read);
                } else {
                    printf("%s[LECTOR] Buffer desbordado, limpiando...%s\n", CAMAR, CRESET);
                    data->buffer6[0] = '\0';
                }
                
                data->data_ready = 1;
                pthread_mutex_unlock(&data->mutex);
                printf("%s[LECTOR] Datos recibidos (HEX): %s", CAZUL, CRESET);
                for (int i = 0; i < bytes_read; i++) {
                    printf("%02X ", (unsigned char)temp_buffer[i]);
                }
                printf("\n");
            } else if (bytes_read == -1) {
                perror("[LECTOR] Error al leer del puerto serial");
            }
        } else {
            if (ret == -1) {
                perror("[LECTOR] Error en select");
            } else {
                if (ncount++ > 350) {
                    ncount = 0;
                    printf("%s[LECTOR] Esperando datos...%s\n", CAQUA, CRESET);
                }
            }
        }
    }
    return NULL;
}

void *cons_serial_processor(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char local_buffer[BUFFER6_SIZE];

    printf("%s[PROCESADOR] Hilo de procesamiento iniciado.%s\n", CAQUA, CRESET);

    while (1) {
        pthread_mutex_lock(&data->mutex);
        if (data->data_ready) {
            strncpy(local_buffer, data->buffer6, BUFFER6_SIZE);
            local_buffer[BUFFER6_SIZE - 1] = '\0';
            data->data_ready = 0;
            data->buffer6[0] = '\0';
            pthread_mutex_unlock(&data->mutex);
            
            printf("%s[PROCESADOR] Procesando (HEX): %s", CAQUA, CRESET);
            for (int i = 0; i < strlen(local_buffer); i++) {
                printf("%02X ", (unsigned char)local_buffer[i]);
            }
            printf("\n");
            
            if (strchr(local_buffer, STX) && strchr(local_buffer, ETX)) {
                printf("%s[PROCESADOR] Mensaje válido recibido (HEX): %s", CAQUA, CRESET);
                for (int i = 0; i < strlen(local_buffer); i++) {
                    printf("%02X ", (unsigned char)local_buffer[i]);
                }
                printf("\n");
            } else {
                printf("%s[PROCESADOR] Esperando mensaje completo...%s\n", CAQUA, CRESET);
            }
        } else {
            pthread_mutex_unlock(&data->mutex);
        }
        usleep(1000);
    }
    return NULL;
}

int main() {
    thread_data_t data;
    pthread_t reader_thread, processor_thread;

    printf("%s[MAIN] Iniciando programa...%s\n", CAZUL, CRESET);

    data.serial_fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_SYNC);
    if (data.serial_fd == -1) {
        perror("[ERROR] No se pudo abrir el puerto serial");
        return 1;
    }

    configure_serial(data.serial_fd);
    data.buffer6[0] = '\0';
    data.data_ready = 0;
    pthread_mutex_init(&data.mutex, NULL);

    pthread_create(&reader_thread, NULL, serial_reader, (void *)&data);
    pthread_create(&processor_thread, NULL, cons_serial_processor, (void *)&data);

    pthread_join(reader_thread, NULL);
    pthread_join(processor_thread, NULL);

    pthread_mutex_destroy(&data.mutex);
    close(data.serial_fd);
    return 0;
}
