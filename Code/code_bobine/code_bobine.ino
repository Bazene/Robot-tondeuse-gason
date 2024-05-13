const int limit = A0;
const int lamp = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(limit, INPUT);
  pinMode(lamp, OUTPUT); digitalWrite(lamp, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valueRead ;
  valueRead = analogRead(limit);
  
  if(valueRead > 300) {
    digitalWrite(lamp, HIGH);
    Serial.print("Lampe allumer :");
    Serial.print(valueRead);
    
  } else {
    digitalWrite(lamp, LOW);
  }
}
