from mqtt_client import connect, disconnect, publicar, suscribirse
from io_system import handle_led
from events_system import register_event, dispatch
from time import sleep

#io_init()
register_event("pressed_button", publicar)
register_event("released_button", publicar)
register_event("control_received", handle_led)


cliente = connect()
suscribirse(cliente)


while(True):
    #DEBUGGING:
    print("Boton presionado!")
    data = (cliente,"PRESSED")
    dispatch("pressed_button", data)
    sleep(10)
    print("Boton soltado!")
    data = (cliente,"RELEASED")
    dispatch("released_button", data)
    sleep(3)
    #pass
    #Sensar boton (disparado por evento)
    
    #Publicaciones de botón(disparado por evento)
    
    #Suscripcion (LED)

    #Control de LED

disconnect(client)