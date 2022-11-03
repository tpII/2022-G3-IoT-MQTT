import sys
import paho.mqtt.client as mqtt
import json

#broker = localhost
broker = '192.168.1.100'
port = 1883

#Suficiente 1 seg?
KEEPAL = 60


def on_publish(client, userdata, result):
    print("Publicacion realizada sobre el topico \n")

def connect():
    client = mqtt.Client("Raspberry"))
    client.on_publish = on_publish
    client.connect(broker, port, KEEPAL)
    client.loop_start()
    return client

def pub(client, data):   
    payload = json.dumps(data)   
    info = client.publish('raspberry/mediciones', payload, 1)
    print("Comprobar última telemetria\n")

def disconnect(client):      
    client.loop_stop()
    client.disconnect()
