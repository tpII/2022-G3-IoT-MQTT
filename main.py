from mqtt_client import connect, disconnect, pub 
from io_system import init

io.init()

while(True):
    #Sensar boton (disparado por evento, activa flag)
    
    #Publicaciones (dependiendo el flag)
    
    try:
        # no vá aca
        clientMQTT = connect()
        data_row = {
            "button_pressed": True
        }
        pub(clientMQTT, data_row)
        disconnect(clientMQTT)

    except:
        print("No se ha podido establecer la conexion")


    #Suscripciones


    #Evaluacion en base a lo recibido


    #Control de LEDs









    
    