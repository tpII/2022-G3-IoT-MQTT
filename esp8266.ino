#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define MSG_BUFFER_SIZE  (50)
#define LED_BUILTIN 4
#define DELTA 2000
#define MQTTpubQos 0


const char *ssid = "alumnosInfo"; 
const char *password = "Informatica2019"; 
const char* mqtt_server = "163.10.142.221";

WiFiClient espClient;
PubSubClient client(espClient);

char msg[MSG_BUFFER_SIZE];
int value = 0;
unsigned long lastMsg = 0;
unsigned long startime = 0;
unsigned long now = 0;
int start = 0;


void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
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
  Serial.print("Mensaje recibido en [");
  Serial.print(topic);
  Serial.print("] --> ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
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

  Serial.print("\nAtributo recibido:\n");
  for (int i = 0; i < attribute_length; i++) {
    Serial.print((char)attribute[i]);
  }
  Serial.print("\nValor recibido:\n");
  for (int i = 0; i < value_length; i++) {
    Serial.print((char)value[i]);
  }
  Serial.print("\n");

  //Se verifica que los atributos recibidos son aquellos que el dispositivo espera
  // y que los valores son true o false 
  if (strncmp(attribute, "led_encendido", attribute_length) == 0) {
    if (strncmp(value, "false", value_length) == 0) {
      //Aqui iría una comunicacion serie con el Arduino
      Serial.print("\nOKEY! Apagare el led!\n\n");

    }
    else if (strncmp(value, "true", value_length) == 0, value_length) {
      //Aqui iría una comunicacion serie con el Arduino
      Serial.print("\nOKEY! Encendere el led!\n\n");

    } else {
      Serial.print("El valor del atributo led_encendido no es true or false\n");
    }
  } else {
    Serial.print("El atributo recibido no es led_encendido\n");
  }
  free(attribute);
  free(value);

}

void reconnect() {
  // Loop hasta que se reconecte
  while (!client.connected()) {
    Serial.print("Intentando establecer conexion MQTT...");
    String clientId = "Client-";
    clientId += String(random(0xffff), HEX);
    // Intentar conectarse
    if (client.connect(clientId.c_str(), "ESP8266", "")) {
      Serial.println("Conectado");
      
      //Se suscribe a su topico de entrada
      client.subscribe("arduino/control");
    } else {
      Serial.print("falla de conexion, rc=");
      Serial.print(client.state());
      Serial.println(" intenando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  
  Serial.begin(115200);
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
  
  if (now - lastMsg > DELTA) {
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "{\"temperatura\":%ld}", value);
    Serial.print("Mensaje publicado: ");
    Serial.println(msg);
    client.publish("arduino/mediciones", msg, MQTTpubQos);
    lastMsg = now;
  }
}
