import sys
from paho.mqtt import client, publish, subscribe
from json import dumps

#broker = localhost
broker = '192.168.1.100'
port = 1883
qos = 1
retain = True
in_topic = "arduino/mediciones"
out_topic = "raspberry/mediciones"
keepal = 60


def on_message(client, userdata, message):
    pass

def on_publish(client, userdata, result):
    print("Publicacion realizada sobre el topico \n")

def on_connect(client, userdata, flags, rc):
    print("Conectado al cliente, codigo de resultado: "+str(rc))

def suscribirse():
    subscribe(in_topic, qos)

def publicar(data):
    cliente= connect()
    payload = dumps(data)   
    info = client.publish(out_topic, payload, 1)
    print("Comprobar última telemetria\n")
    disconnect(client)

def connect():
    cliente = client.Client("Raspberry")
    cliente.on_publish = on_publish
    cliente.on_connect = on_connect
    cliente.connect(broker, port, keepal)
    cliente.loop_start()
    return cliente  

def disconnect(client):      
    client.loop_stop()
    client.disconnect()
