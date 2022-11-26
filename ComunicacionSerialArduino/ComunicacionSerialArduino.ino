#include <SoftwareSerial.h>

SoftwareSerial SerialEsp (2,3); //rx, tx 
int data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialEsp.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  SerialEsp.write(25);
  delay(1000);
  checkSerialCom();

}



void checkSerialCom(){
  if (SerialEsp.available() > 0){
    Serial.println("Recibido: ");
    while(SerialEsp.available() > 0){
      data = (int)SerialEsp.read();
      Serial.print(data); 
    }
  }
}
