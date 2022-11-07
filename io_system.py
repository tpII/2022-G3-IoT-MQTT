import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library

BUTTON_GPIO = 10
LED_GPIO = 21

def press_button_callback(channel):
    print("Boton presionado!")
    #Publicación MQTT o activar flag

def release_button_callback(channel):
    print("Boton soltado!")
    #Publicación MQTT o activar flag


def init():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
    button_init()
    leds_init()

def button_init():
    GPIO.setup(BUTTON_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
    GPIO.add_event_detect(BUTTON_GPIO,GPIO.RISING,callback=press_button_callback) # Setup event on pin 10 rising edge
    GPIO.add_event_detect(BUTTON_GPIO,GPIO.RISING,callback=release_button_callback) # Setup event on pin 10 rising edge

def leds_init():
    GPIO.setup(LED_GPIO,GPIO.OUT)

def led_on():
    GPIO.output(LED_GPIO,GPIO.HIGH)

def led_of():
    GPIO.output(LED_GPIO,GPIO.HIGH)

