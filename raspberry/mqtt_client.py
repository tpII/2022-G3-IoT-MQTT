import sys
from paho.mqtt import client, publish, subscribe
from events_system import dispatch
from json import dumps, load

broker = '127.0.0.1'
port = 1883
qos = 1
retain = True
in_topic = "raspberry/control/led"
out_topic = "raspberry/mediciones/boton"
keepal = 60


def on_message(client, userdata, msg):
    # Funcion manejadora de callback, llamada al recibir un mensaje en el topico de entrada

    payload = msg.payload.decode('utf8')
    dispatch("control_received",payload)
    

def suscribirse(cliente):
    # Funcion de suscripcion a un topico

    cliente.subscribe(in_topic, qos)
    print(f"Suscripto al topico {in_topic}")


def publicar(data):
    # Funcion de publicacion en un topico 

    cliente= data[0] 
    payload = data[1]
    info = cliente.publish(out_topic, payload, 1)

def connect():
    # Funcion de inicializacion del cliente MQTT

    cliente = client.Client("Raspberry")
    cliente.on_message = on_message
    cliente.connect(broker, port, keepal)
    cliente.loop_start()
    return cliente  

def disconnect(client):    
    # Funcion de desconeccion del cliente
  
    client.loop_stop()
    client.disconnect()
