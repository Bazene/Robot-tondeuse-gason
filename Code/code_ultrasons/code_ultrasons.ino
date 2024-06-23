// Define broche for ultrasonics sensors
const int ECHO1 = 3; // 10
const int TRIG1 = 2; // 43
const int ECHO2 = 13;
const int TRIG2 = 47;
const int obstacleLimite = 20; // the value that help us to know if we can stop the robot

void setup() {
  Serial.begin(9600); // the serial communication
  
  // initialisation of pins
  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(TRIG2, OUTPUT);
  
  // initialise TRIG pin at LOW
  digitalWrite(TRIG1, LOW);
  digitalWrite(TRIG2, LOW);
  
  delay(2); // shot break for showing the stability
}

long getDistance(int trigPin, int echoPin) {
  // we send an impulsion TRIG of 10 microsecondes
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // We Mesure the length of ECHO impulsion
  long duration = pulseIn(echoPin, HIGH);
  
  // Calcul of distance in cm
  long distance = duration / 58.2;
  
  return distance;
}

void loop() {
  // Calcul of distance for each sensor
  long distance_cm1 = getDistance(TRIG1, ECHO1);
  long distance_cm2 = getDistance(TRIG2, ECHO2);

  // check if mesures are not null
  if (distance_cm1 != 0 && distance_cm2 != 0) { 
    if (distance_cm1 < obstacleLimite) {
      Serial.print("La distance mesuree ultrasonic 1 est : ");
      Serial.println(distance_cm1);
    } 
    
    if (distance_cm2 < obstacleLimite) {
      Serial.print("La distance mesuree ultrasonic 2 est : ");
      Serial.println(distance_cm2);
    }
  }
  
  delay(1000); // wait for 1 seconde before making the mesure
}
