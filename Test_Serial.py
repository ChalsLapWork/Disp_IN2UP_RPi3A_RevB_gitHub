import serial
import time


#configuracion puerto serial
serial_port = '/dev/serial0'
baud_rate = 9600
#timepo de espera para la lectura en seg
timeout = 1
#abrir serial port
ser = serial.Serial(serial_port, baud_rate, timeout=timeout)
#func to send  data
def send_data(data):
    ser.write(data.encode()) #enviar datos como bytes
    print(f"Enviando:{data}")

def receive_data():
  if ser.in_waiting > 0: #si hay datos disponibles en puerto
     received_data = ser.read(ser.in_waiting).decode() # lee todos los datos disponibles 
     print(f"Recibido:{received_data}")
  else:
     print("Esperando datos ...")


#main loop to send and Rx data
try: 
  while True:
    send_data("Hola_mundo ") #send mesage
    time.sleep(1)
    receive_data()
    time.sleep(1)
except KeyboardInterrupt:
    print(" Programa terminado por el user")
#cierra el puerto serial
ser.close()
