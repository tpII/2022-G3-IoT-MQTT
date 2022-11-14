#import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
from events_system import dispatch

BUTTON_GPIO = 10
LED_GPIO = 21
led_status = "LOW"

def handle_led(data):
    print(f"Mensaje recibido : {data}")
    if (data == "OFF"):
        led_off()
    if (data == "ON"):
        led_on()
    if (data == "TOGGLE"):
        led_toggle()
    pass

def press_button_callback(channel):
    print("Boton presionado!")
    data = "PRESSED"
    dispatch("pressed_button", data)

def release_button_callback(channel):
    print("Boton soltado!")
    data = "RELEASED"
    dispatch("released_button", data)


def io_init():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
    button_init()
    leds_init()

def button_init():
    GPIO.setup(BUTTON_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
    GPIO.add_event_detect(BUTTON_GPIO,GPIO.RISING,callback=press_button_callback) # Setup event on pin 10 rising edge
    GPIO.add_event_detect(BUTTON_GPIO,GPIO.FALLING,callback=release_button_callback) # Setup event on pin 10 falling edge

def leds_init():
    GPIO.setup(LED_GPIO,GPIO.OUT)
    led_off()

def led_on():
    #ANDA MAL, NO SE PUEDE MODIFICAR UN LITERAL
    #print(led_status)
    #led_status = "HIGH"
    #GPIO.output(LED_GPIO,GPIO.HIGH)
    print("Se ha encendido el LED")


def led_off():
    #ANDA MAL, NO SE PUEDE MODIFICAR UN LITERAL
    #print(led_status)
    #led_status = "LOW"
    #GPIO.output(LED_GPIO,GPIO.LOW)
    print("Se ha apagado el LED")

def led_toggle():
    #ANDA MAL, NO SE PUEDE MODIFICAR UN LITERAL
    #print(led_status)
    if (led_status == "HIGH"):
        led_off()
    else:
        led_on()