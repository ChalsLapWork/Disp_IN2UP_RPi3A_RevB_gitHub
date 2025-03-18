
#!/bn/bash
#config puerto serial
stty -F /dev/serial0 9600 cs8 -cstopb -parenb

#bucle de enviar recibir datos
while true; do 
   echo -ne  "\xFF" > /dev/serial0 
#esperar un poco antes de leer
   sleep 0.1
#leer y mostrar lo recibido  de manera separada
   RECEIVED = $(cat < /dev/serial0)

#si hay datos recibidos , mostrarlo
   if  [ -n "$RECEIVED" ]; then
     echo "datos recibidos:  $(echo -n "$RECEIVED" | xxd -p)"
   else
     echo "sin datos recibidos. . ."
   fi
   sleep 0.1
done

