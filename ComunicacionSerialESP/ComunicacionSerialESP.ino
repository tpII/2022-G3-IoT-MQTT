int data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  checkSerialCom();
  delay(500);

}

void checkSerialCom(){
  if (Serial.available() > 0){
    Serial.println("Recibido: ");
    while(Serial.available() > 0){
      Serial.write(Serial.read());//lo mando al arduino de vuelta
    }
  }
}
