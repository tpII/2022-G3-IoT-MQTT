// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 8     // Digital pin connected to the DHT sensor


#define DHTTYPE DHT11   // DHT 11


//inicialización del sensor para DHT11


DHT dht(DHTPIN, DHTTYPE); 

#define LED 13 //gpio elegido para el control del led
#define tempLimit 22 //temperatura límite

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT test!"));
  pinMode(LED, OUTPUT);

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity(); // lectura de sensor
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature(); // lectura de sensor
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true); // lectura de sensor

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  //Comunicacion serie con la PC
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  //Encendido y apagado del led
  if (t > tempLimit) {
      digitalWrite(LED,HIGH); //se enciende el led si la temperatura subrepasa los 22 C
    }
   else
    digitalWrite(LED,LOW);
}
