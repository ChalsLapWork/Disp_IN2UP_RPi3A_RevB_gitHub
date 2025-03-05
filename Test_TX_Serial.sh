#!/bin/bash

#configurar el puerto serial
stty -F /dev/serial0 9600 cs8 -cstopb -parenb -ixon -ixoff -crtscts 

echo " Enviando datos: continuamente por TX.... " 

while true; do
    echo -ne " hola " > /dev/serial0
    sleep 0.1 #espera 100ms antes de enviar el siguiete mensaje
done
