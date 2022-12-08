import RPi.GPIO as GPIO # Libreria de entradas y salidas de raspberry
from events_system import dispatch

BUTTON_GPIO = 10
LED_GPIO = 12

def handle_led(data):
    # Funcion manejadora que controla leds

    print(f"Mensaje recibido : {data}")
    if (data == "OFF"):
        led_off()
    if (data == "ON"):
        led_on()
    if (data == "TOGGLE"):
        led_toggle()
    pass

def press_button_callback(cliente):
    # Funcion manejadora realizada al presionar el boton

    print("Boton presionado!")
    data = (cliente, "PRESSED")
    dispatch("pressed_button", data)

def release_button_callback(cliente):
    # Funcion manejadora realizada al soltar el boton

    print("Boton soltado!")
    data = (cliente, "RELEASED")
    dispatch("released_button", data)


def io_init():
    # Funcion inicializadora de entradas y salidas

    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BOARD)
    button_init()
    leds_init()

def button_init():
    # Funcion inicializadora del boton

    GPIO.setup(BUTTON_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Setea el pin 10 como entrada con pull-up
    GPIO.add_event_detect(BUTTON_GPIO,GPIO.BOTH, bouncetime=400) # Setea eventos por flancos de subida y bajada, antirebote

def leds_init():
    # Funcion inicializadora del led

    GPIO.setup(LED_GPIO,GPIO.OUT)
    led_off()

def led_on():
    # Funcion que enciende el led

    GPIO.output(LED_GPIO,GPIO.HIGH)
    print("Se ha encendido el LED")

def led_off():
    # Funcion que apaga el led

    GPIO.output(LED_GPIO,GPIO.LOW)
    print("Se ha apagado el LED")

def led_toggle():
    # Funcion que realiza toggle sobre el led

    if (GPIO.input(LED_GPIO)):
        led_off()
    else:
        led_on()