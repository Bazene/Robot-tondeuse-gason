// Define broche for ultrasonics sensors
const int ECHO1 = 10;
const int TRIG1 = 43;
const int ECHO2 = 13;
const int TRIG2 = 47;
const int obstacleLimite = 20; // the value that help us to know if we can stop or not the robot

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
  delay(2);
}

long getDistance(int trigPin, int echoPin) {
  // Envoi d'une impulsion TRIG de 10 microsecondes
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Mesure de la durée de l'impulsion ECHO
  long duration = pulseIn(echoPin, HIGH);
  
  // Calcul de la distance en cm
  long distance = duration / 58.2;
  
  return distance;
}

void loop() {
  // Calcul de la distance pour chaque capteur
  long distance_cm1 = getDistance(TRIG1, ECHO1);
  long distance_cm2 = getDistance(TRIG2, ECHO2);
  
  if (distance_cm2 < obstacleLimite) {
    Serial.println("Le moteur tourne");
  } else {
    Serial.println("Le moteur ne tourne pas");
  }
  
  delay(1000); // Attendre 1 seconde avant de refaire une mesure
}
