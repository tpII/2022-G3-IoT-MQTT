import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
from events_system import dispatch

BUTTON_GPIO = 10
LED_GPIO = 12

def handle_led(data):
    print(f"Mensaje recibido : {data}")
    if (data == "OFF"):
        led_off()
    if (data == "ON"):
        led_on()
    if (data == "TOGGLE"):
        led_toggle()
    pass

def press_button_callback(cliente):
    print("Boton presionado!")
    data = (cliente, "PRESSED")
    dispatch("pressed_button", data)

def release_button_callback(cliente):
    print("Boton soltado!")
    data = (cliente, "RELEASED")
    dispatch("released_button", data)


def io_init():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
    button_init()
    leds_init()

def button_init():
    GPIO.setup(BUTTON_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
    GPIO.add_event_detect(BUTTON_GPIO,GPIO.BOTH, bouncetime=400) # Setup event on pin 10 falling and rising edge

def leds_init():
    GPIO.setup(LED_GPIO,GPIO.OUT)
    led_off()

def led_on():
    GPIO.output(LED_GPIO,GPIO.HIGH)
    print("Se ha encendido el LED")


def led_off():
    GPIO.output(LED_GPIO,GPIO.LOW)
    print("Se ha apagado el LED")

def led_toggle():
    if (GPIO.input(LED_GPIO)):
        led_off()
    else:
        led_on()