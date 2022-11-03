import mqtt_client
import io
import json

io.init()

while(True):
    #Sensar boton (disparado por evento, activa flag)
    
    #Publicaciones (dependiendo el flag)
    
    try:
        payload=[]
        for m in measures:
            clientMQTT = mqtt_client.connect(m[0]["token"])
            data_row = {
                "ppm": m[1],        
                "id": m[0]["id"]
            }
            mqtt_client.pub(clientMQTT, data_row)
        mqtt_client.disconnect(clientMQTT)

    except:
        print("No se ha podido establecer la conexion")


    #Suscripciones


    #Evaluacion en base a lo recibido


    #Control de LEDs









    
    