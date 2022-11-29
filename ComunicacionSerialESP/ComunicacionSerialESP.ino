int data;
char caracter;
String temp = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  checkSerialCom();
  delay(1000);

}

void checkSerialCom(){
  //int i =0;
  if (Serial.available() > 0){
    while(Serial.available() > 0){
      caracter = Serial.read();
      if (caracter == '\n'){
        temp+= caracter;
        break; 
      }
      else {
        temp+= caracter;
      }
    }
    Serial.println(temp);
    temp="";
  }
}
