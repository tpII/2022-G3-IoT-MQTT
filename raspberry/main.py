from mqtt_client import connect, disconnect, publicar, suscribirse
from io_system import handle_led, io_init, press_button_callback, release_button_callback
from events_system import register_event, dispatch
import RPi.GPIO as GPIO # Libreria de entradas y salidas de raspberry

# Inicializacion de entradas y salidas
io_init()

# Registro de eventos 
register_event("pressed_button", publicar)
register_event("released_button", publicar)
register_event("control_received", handle_led)

# Inicializacion del cliente
cliente = connect()
suscribirse(cliente)

# Super-loop
while(True):

    #Deteccion de flancos sobre el boton
    if GPIO.event_detected(10):
        button_state = GPIO.input(10)

        # Llamado a funciones manejadoras
        if button_state == False:
            press_button_callback(cliente)
        else:
            release_button_callback(cliente)
    #