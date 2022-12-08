#include <SoftwareSerial.h>
#include "DHT.h"
//#define DEBUG//para debug

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
    pinMode(LEDCONTROL, OUTPUT);//codigo arduino LED
  #endif


  
  

}

void loop() {
  
  #ifdef SENSOR //codigo arduino sensor
  delay(2000);//envio de tamperatura cada 5 segundos
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity(); // lectura de sensor
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature(); // lectura de sensor

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
  if(estado_led == "true"){
    digitalWrite(LEDCONTROL,HIGH);
  }else if (estado_led == "false"){
     digitalWrite(LEDCONTROL,LOW);
  }
  //Serial.print(estado_led);
  
  delay(1000);//periodo de un segundo
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
      if (serial_aux == "false" || serial_aux == "true"){ //descarta basura
        estado_led = serial_aux;//solo escribe un nuevo en el estado si se recibio algo
      }
      //Serial.println("estado Led: "+estado_led+"\n");
      //delay(500);
      //Serial.println("serial aux: "+serial_aux+"\n");
    }
  }
}

#ifdef DEBUG
void serial_recive_debug(){
  String serial_aux= "";
  if (Serial.available() > 0){
    while(Serial.available() > 0){
      caracter = Serial.read();
      //Serial.println(caracter);
      if (caracter == '\n'){
        break; 
      }
      else {
        serial_aux+= caracter;
      }
      if (serial_aux == "false" || serial_aux == "true"){ //descarta basura
        estado_led = serial_aux;//solo escribe un nuevo en el estado si se recibio algo
      }
      //Serial.println("estado Led: "+estado_led+"\n");
      //delay(500);
      //Serial.println("serial aux: "+serial_aux+"\n");
    }
  }
}
#endif
