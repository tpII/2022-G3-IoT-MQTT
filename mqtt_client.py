import sys
from paho.mqtt import client, publish, subscribe
from json import dumps, load

attributes = ["temperatura", "humedad"]

#broker = localhost
broker = '127.0.0.1'
port = 1883
qos = 1
retain = True
in_topic = "arduino/mediciones"
out_topic = "raspberry/mediciones"
keepal = 60


def on_message(client, userdata, msg):
    payload = msg.payload
    print(payload)
    #dispatch
    #data = load(msg.payload)
    #print(data)

def on_publish(client, userdata, result):
    print("Publicacion realizada sobre el topico \n")

def on_connect(client, userdata, flags, rc):
    print("Conectado al cliente, codigo de resultado: "+str(rc))

def suscribirse(cliente):
    print("me intento conectar")
    cliente.subscribe(in_topic, qos)
    print("me conecte")

def publicar(cliente, data):
    cliente= connect()
    payload = dumps(data)   
    info = client.publish(out_topic, payload, 1)
    print("Comprobar última telemetria\n")
    disconnect(client)

def connect():
    cliente = client.Client("Raspberry")
    cliente.on_publish = on_publish
    cliente.on_connect = on_connect
    cliente.on_message = on_message
    cliente.connect(broker, port, keepal)
    cliente.loop_start()
    return cliente  

def disconnect(client):      
    client.loop_stop()
    client.disconnect()
