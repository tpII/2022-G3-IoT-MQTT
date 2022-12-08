#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define MSG_BUFFER_SIZE  (50)
#define LED_BUILTIN 4
#define DELTA 2000
#define MQTTpubQos 0
#define PUB
#define SUB


const char *ssid = "pepe";//red de casa jeje
const char *password = "pepito01"; 
const char* mqtt_server = "192.168.137.106";

WiFiClient espClient;
PubSubClient client(espClient);


String temperature = "0";
String humidity = "0";
String serial_data= "";

char msg[MSG_BUFFER_SIZE];
unsigned long lastMsg = 0;
unsigned long startime = 0;
unsigned long now = 0;
int start = 0;


void setup_wifi() {

  delay(10);
  //Serial.println();
  //Serial.print("Conectando a ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi conectado");
  //Serial.println("Direccion IP: ");
  //Serial.println(WiFi.localIP());
}
/**
 * Procedimiento que se ejecuta al recibir un mensaje en un topico al cual se esta suscripto
 * Se espera que el payload del mensaje tenga formato JSON. Se realiza un parseo para identificar 
 * el atributo y el valor recibido.
 */
void callback(char* topic, byte* payload, unsigned int length) {
  char *attribute, *value;
  char *led_attribute = "{\"led_encendido\"";
  char c;
  int i = 0, j = 0, count = 0, attribute_length = 0, value_length = 0;
  //Serial.print("Mensaje recibido en [");
  //Serial.print(topic);
  //Serial.print("] --> ");
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
  }
  
  //Obtencion de las longitud del atributo y del valor
  //Saltea el '{"'
  while (count < 2) {
    c = (char)payload[i];
    if (c == '"') {
      count++;
    }
    else {
      if (count == 1) {
        attribute_length++;
      }
    }
    i++;
  }
  //Saltea el ':'
  i++;
  c = (char)payload[i];
  while (c != '}') {
    value_length++;
    i++;
    c = (char)payload[i];
  }
  
  //Se aloca memoria para poder leer los pares atributo-valor
  attribute = (char*)malloc(sizeof(char) * attribute_length);
  value = (char*)malloc(sizeof(char) * value_length);

  //Se lee el atributo y el valor
  i = 0;
  j = 0;
  count = 0;
  //Saltea el '{"'
  while (count < 2) {
    c = (char)payload[i];
    if (c == '"') {
      count++;
    }
    else {
      if (count == 1) {
        attribute[j] = c;
        j++;
      }
    }
    i++;
  }
  i++;
  //Saltea el ':'
  j = 0;
  c = (char)payload[i];
  while (c != '}') {
    value[j] = c;
    j++;
    i++;
    c = (char)payload[i];
  }

  //Serial.print("\nAtributo recibido:\n");
  for (int i = 0; i < attribute_length; i++) {
    //Serial.print((char)attribute[i]);
  }
  //Serial.print("\nValor recibido:\n");
  for (int i = 0; i < value_length; i++) {
    //Serial.print((char)value[i]);
  }
  //Serial.print("\n");

  //Se verifica que los atributos recibidos son aquellos que el dispositivo espera
  // y que los valores son true o false 
  if (strncmp(attribute, "led_encendido", attribute_length) == 0) {
    if (strncmp(value, "false", value_length) == 0) {
      //Aqui iría una comunicacion serie con el Arduino
      Serial.print("false\n");//envio a arduino para apagado del LED
      //Serial.print("\nOKEY! Apagare el led!\n\n");

    }
    else if (strncmp(value, "true", value_length) == 0) {
      //Aqui iría una comunicacion serie con el Arduino
      Serial.print("true\n");//envio a arduino para encendido del LED
      //Serial.print("\nOKEY! Encendere el led!\n\n");

    } else {
      //Serial.print("El valor del atributo led_encendido no es true or false\n");
    }
  } else {
    //Serial.print("El atributo recibido no es led_encendido\n");
  }
  free(attribute);
  free(value);

}

void reconnect() {
  // Loop hasta que se reconecte
  while (!client.connected()) {
    //Serial.print("Intentando establecer conexion MQTT...");
    String clientId = "Client-";
    clientId += String(random(0xffff), HEX);
    // Intentar conectarse
    if (client.connect(clientId.c_str(), "ESP8266", "")) {
      //Serial.println("Conectado");
      
      //Se suscribe a su topico de entrada
      #ifdef SUB
      client.subscribe("arduino/control");
      #endif
    } else {
      //Serial.print("falla de conexion, rc=");
      //Serial.print(client.state());
      //Serial.println(" intenando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void serial_recive(){
  char caracter = ' ';
  if (Serial.available() > 0){
    while(Serial.available() > 0){
      caracter = Serial.read();
      if (caracter == '\n'){//leo hasta fin de linea
        break; 
      }
      else {
        serial_data+= caracter;
      }
    }
    parse_data();
    serial_data = "";//limpio la variable para proxima lectura
  }
}

void parse_data()//parseo de la trama enviada desde el arduino
{
  //tomo el indice de los separadores -> 60H26T
  int index_hum = serial_data.indexOf("H");
  int index_temp = serial_data.indexOf("T");
  //alamaceno la info
  humidity = serial_data.substring (0, index_hum);
  temperature = serial_data.substring (index_hum+1, index_temp); 
}



void setup() {
  
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  now = millis();
  if (start == 0) {
    startime = now;
    start = 1;
  }
  #ifdef PUB
  if (now - lastMsg > DELTA) {
    //recepcion serie
    serial_recive();
    snprintf (msg, MSG_BUFFER_SIZE, "{\"temperatura\":%s}", temperature);
    //Serial.print("Mensaje publicado: ");
    //Serial.println(msg);
    client.publish("arduino/mediciones", msg, MQTTpubQos);//publica temperatura
    
    snprintf (msg, MSG_BUFFER_SIZE, "{\"humedad\":%s}",humidity );//publica humedad
    client.publish("arduino/mediciones", msg, MQTTpubQos);
    
    lastMsg = now;
  }
  delay(2000);
  #endif
  
}
