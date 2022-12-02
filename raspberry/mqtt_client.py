import sys
from paho.mqtt import client, publish, subscribe
from events_system import dispatch
from json import dumps, load

#broker = localhost
broker = '127.0.0.1'
port = 1883
qos = 1
retain = True
in_topic = "raspberry/control/led"
out_topic = "raspberry/mediciones/boton"
keepal = 60


def on_message(client, userdata, msg):
    payload = msg.payload.decode('utf8')
    dispatch("control_received",payload)
    

def on_publish(client, userdata, result):
    print("Publicacion realizada sobre el topico \n")


def suscribirse(cliente):
    cliente.subscribe(in_topic, qos)
    print(f"Suscripto al topico {in_topic}")


def publicar(data):
    cliente= data[0]
    payload = dumps(data[1])   
    info = cliente.publish(out_topic, payload, 1)

def connect():
    cliente = client.Client("Raspberry")
    cliente.on_publish = on_publish
    cliente.on_message = on_message
    cliente.connect(broker, port, keepal)
    cliente.loop_start()
    return cliente  

def disconnect(client):      
    client.loop_stop()
    client.disconnect()
