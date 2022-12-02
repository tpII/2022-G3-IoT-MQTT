from mqtt_client import connect, disconnect, publicar, suscribirse
from io_system import handle_led, io_init
from events_system import register_event, dispatch
from time import sleep
import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library


DEBUGGING = 0

io_init()
register_event("pressed_button", publicar)
register_event("released_button", publicar)
register_event("control_received", handle_led)


cliente = connect()
suscribirse(cliente)


while(True):
    #DEBUGGING:
    if (DEBUGGING == 1):
        print("Boton presionado!")
        data = (cliente,"PRESSED")
        dispatch("pressed_button", data)
        sleep(10)
        print("Boton soltado!")
        data = (cliente,"RELEASED")
        dispatch("released_button", data)
        sleep(3)
    if GPIO.input(10) == GPIO.HIGH:
        print("Button was pushed!")
    #pass
    #Sensar boton (disparado por evento)
    
    #Publicaciones de boton(disparado por evento)
    
    #Suscripcion (LED)

    #Control de LED

disconnect(client)