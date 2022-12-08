#include <SoftwareSerial.h>
#include "DHT.h"
#define DEBUG//para debug

#define LED
//#define SENSOR 


#define DHTPIN 8     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define LEDCONTROL0 13 //gpio elegido para el control del led
#define LEDCONTROL1 12

//inicialización  para DHT11
DHT dht(DHTPIN, DHTTYPE); 
char caracter;
String state_led_white = "WHITE_OFF";
String state_led_green = "GREEN_OFF";
float temperature=0;
float humidity=0;



SoftwareSerial esp_serial(2,3);//rx, tx


void setup() {
  //inicializacion serie
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  esp_serial.begin(9600);
  
  #ifdef SENSOR//codigo arduino sensor
  dht.begin();
  #endif
  
  #ifdef LED
    pinMode(LEDCONTROL0, OUTPUT);//codigo arduino LED
    pinMode(LEDCONTROL1, OUTPUT);
  #endif


  
  

}

void loop() {
  
  #ifdef SENSOR //codigo arduino sensor
  delay(2000);//envio de tamperatura cada 5 segundos
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity(); // lectura de sensor
  //Read temperature as Celsius (the default)
  temperature = dht.readTemperature(); //lectura de sensor

  //envio de datos a esp8266 //armar trama
  if (isnan(humidity) || isnan(temperature)) {//error de lectura
    esp_serial.print(F("failH"));
    esp_serial.print(F("failT"));
    esp_serial.print("\n");
  }else {
    
    esp_serial.print((int)humidity);
    esp_serial.print(F("H"));
    esp_serial.print((int)temperature);
    esp_serial.print(F("T"));
    esp_serial.print("\n");
  }
  #endif

  #ifdef LED //codigo arduino LED
  serial_recive();
  if(state_led_green =="GREEN_ON"){
    digitalWrite(LEDCONTROL0,HIGH);
  }else if (state_led_green == "GREEN_OFF"){
     digitalWrite(LEDCONTROL0,LOW);
  }
  if(state_led_white == "WHITE_ON"){
    digitalWrite(LEDCONTROL1,HIGH);
  }else if (state_led_white == "WHITE_OFF"){
     digitalWrite(LEDCONTROL1,LOW);
  }
  //Serial.print(estado_led);
  
  delay(500);//periodo de un segundo
  #endif

}

void serial_recive(){
  String serial_aux= "";
  if (esp_serial.available() > 0){
    while(esp_serial.available() > 0){
      caracter = esp_serial.read();
      //Serial.println(caracter);
      if (caracter == '\n'){
        break; 
      }
      else {
        serial_aux+= caracter;
      }
      if (serial_aux == "WHITE_ON" || serial_aux == "WHITE_OFF"){ //descarta basura
        state_led_white = serial_aux;//solo escribe un nuevo en el estado si se recibio algo
      }
      if (serial_aux == "GREEN_ON" || serial_aux == "GREEN_OFF"){ //descarta basura
        state_led_green = serial_aux;//solo escribe un nuevo en el estado si se recibio algo
      }
    }
    
  }
}
