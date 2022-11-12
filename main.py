from mqtt_client import connect, publicar, suscribirse
#from io_system import io_init
from events_system import register_event, dispatch

#io_init()
#register_event("button_pressed", publicar)
#register_event("button_released", publicar)
cliente = connect()
suscribirse(cliente)


while(True):
    pass
    #Sensar boton (disparado por evento)
    
    #Publicaciones de botón(disparado por evento)
    
    #Publicación de otras cosas (?)
    
    #Suscripciones

    #Evaluacion en base a lo recibido

    #Control de LEDs

