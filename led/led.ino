void setup(){
  Serial.begin(9600);
 
  for(int i = 2; i <= 4; i++){
    pinMode(i, OUTPUT);
  }
}

void loop(){
  for(int i = 2; i <=4; i++){
    digitalWrite(i, HIGH);
    delay(500);
    Serial.print("led ");
    Serial.print(i);
    Serial.println(" on");
  }
  for(int i = 2; i <=4; i++){
    digitalWrite(i, LOW);
    delay(500);
    Serial.print("led ");
    Serial.print(i);
    Serial.println(" off");
  }
}
