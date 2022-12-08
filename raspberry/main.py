from mqtt_client import connect, disconnect, publicar, suscribirse
from io_system import handle_led, io_init, press_button_callback, release_button_callback
from events_system import register_event, dispatch
from time import sleep
import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library

io_init()
register_event("pressed_button", publicar)
register_event("released_button", publicar)
register_event("control_received", handle_led)

cliente = connect()
suscribirse(cliente)

while(True):
    button_state = GPIO.input(10)
    if GPIO.event_detected(10):
        if button_state == False:
            press_button_callback(cliente)
        else:
            release_button_callback(cliente)
    #pass
    #Sensar boton (disparado por evento)
    
    #Publicaciones de boton(disparado por evento)
    
    #Suscripcion (LED)

    #Control de LED

disconnect(client)