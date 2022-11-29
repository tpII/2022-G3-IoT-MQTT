#include <SoftwareSerial.h>
#include "DHT.h"

#define DEBUG//para debug

#define LED
//#define SENSOR 


#define DHTPIN 8     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define LEDCONTROL 13 //gpio elegido para el control del led
#define tempLimit 22 //temperatura límite

//inicialización  para DHT11
DHT dht(DHTPIN, DHTTYPE); 
char caracter;
String estado_led = "false";
float temperature=0.0;
float humidity=0.0;



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
    pinMode(LEDCONTROL, OUTPUT);//codigo arduino LED
  #endif


  
  

}

void loop() {
  
  #ifdef SENSOR //codigo arduino sensor
  delay(5000);//envio de tamperatura cada 5 segundos
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity(); // lectura de sensor
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature(); // lectura de sensor

  //envio de datos a esp8266 //armar trama
  if (isnan(humidity) || isnan(temperature)) {//error de lectura
    Serial.print("Hfail");
    Serial.print("Tfail");
    Serial.print("\n");
  }else {
    Serial.print("H");
    Serial.print(humidity);
    Serial.print(F("T"));
    Serial.print(temperature);
    Serial.print("\n");
  }
  #endif

  #ifdef LED //codigo arduino LED
  serial_recive();
  if(estado_led == "true"){
    digitalWrite(LEDCONTROL,HIGH);
  }else{
     digitalWrite(LEDCONTROL,LOW);
  }
  
  delay(1000);//periodo de un segundo
  #endif

}

void serial_recive(){
  String serial_aux= "";
  if (Serial.available() > 0){
    while(Serial.available() > 0){
      caracter = Serial.read();
      if (caracter == '\n'){
        break; 
      }
      else {
        serial_aux+= caracter;
      }
      if (serial_aux == "false" || serial_aux == "true"){ //descarta basura
        estado_led = serial_aux;//solo escribe un nuevo en el estado si se recibio algo
      }
    }
  }
}
