#include <SoftwareSerial.h>

SoftwareSerial SerialEsp (2,3); //rx, tx 
char caracter;
int entero =0;
float decimal =0.0;
String dato1,dato2,temp;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialEsp.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  SerialEsp.print("24\n");
  delay(1000);
  serial_recive();

}



void serial_recive(){
  //int i =0;
  if (SerialEsp.available() > 0){
    Serial.println("Recibido: ");
    while(SerialEsp.available() > 0){
      caracter = SerialEsp.read();
      if (caracter == '\n'){
        break; 
      }
      else {
        temp+= caracter;
      }
    }
    Serial.println(temp);
    temp = "";
  }
}
