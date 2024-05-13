// ********************** MOTORS *****************************
const int MotTonte = 8; // tonte motor

// Define broches for the first H bridge
const int IN1 = 27;
const int IN2 = 31;
const int ENA = 4;

// Define broches for the second H bridge
const int IN3 = 35;
const int IN4 = 39;
const int ENB = 7;

// Define broche for ultrasonics sensors
const int ECHO1 = 10;
const int ECHO2 = 13;
const int TRIG1 = 43;
const int TRIG2 = 47;
const int obstacleLimite = 40;

void setup() {
  Serial.begin(9600); //lancer la communication serie à 9600bps
  
  // Initialisation des broches en sortie

  // motor 1
  pinMode(IN1, OUTPUT); digitalWrite(IN1, LOW); // for direct sens
  pinMode(IN2, OUTPUT); digitalWrite(IN2, HIGH); // for indirect sens
  pinMode(ENA, OUTPUT);

  // motor 2
  pinMode(IN3, OUTPUT); digitalWrite(IN3, HIGH); // for direct sens
  pinMode(IN4, OUTPUT); digitalWrite(IN4, LOW); // for indirect sens
  pinMode(ENB, OUTPUT);

  // motor tonte
  pinMode(MotTonte, OUTPUT); analogWrite(MotTonte, 0);

  // ultrasonics
  pinMode(ECHO1, INPUT); pinMode(ECHO2, INPUT);
  pinMode(TRIG1, OUTPUT); digitalWrite(TRIG1, HIGH); 
  pinMode(TRIG2, OUTPUT); digitalWrite(TRIG2, HIGH);
}

void loop() {
  // Activation de la modulation de largeur d'impulsion (PWM) pour ENA et ENB
//  analogWrite(ENA, ((dutyCycle * 255) / 100));  // Convertit le pourcentage en valeur entre 0 et 255
//  analogWrite(ENB, ((dutyCycle * 255) / 100));
    
  analogWrite(ENA, 255);  // Convertit le pourcentage en valeur entre 0 et 255
  analogWrite(ENB, 255);

  // calcul of distance 
  long duration = pulseIn(ECHO1, HIGH); // duration of impulsion in microseconds
  int distance_cm = duration * 0.034/2;
  
  if(distance_cm < obstacleLimite) {
    analogWrite(MotTonte, 255);
  } else {
    analogWrite(MotTonte, 0);
  }

  //verifier si les données sont disponibles sur le port série ici du bluetooth
  if (Serial.available() > 0) {
    //gestion moteur tonte 
    String receveidData = Serial.readStringUntil('\n'); // Lire la chaîne jusqu'au retour à la ligne


    // **************************** FOR TONTE MOTOR ************************************
    if(receveidData == "turn on mt"){
      analogWrite(MotTonte, 255);
    }

    if(receveidData == "turn off mt") {
      analogWrite(MotTonte, LOW);
    }

    // **************************** FOR LAUNCHING BACK MOTORS ************************************
    if(receveidData == "turn on m arriere") {
      digitalWrite(IN1, LOW); // for direct sens
      digitalWrite(IN2, HIGH); // for indirect sens

      digitalWrite(IN3, LOW); // for direct sens
      digitalWrite(IN4, HIGH); // for indirect sens
    }

    if(receveidData == "turn off m arriere") {
      digitalWrite(IN1, LOW); // for direct sens
      digitalWrite(IN2, LOW); // for indirect sens

      digitalWrite(IN3, LOW); // for direct sens
      digitalWrite(IN4, LOW); // for indirect sens
    }

    // **************************** MOVEMENT LEFT **************************************
    // **************************** MOVEMENT RIGHT *************************************
    // **************************** MOVEMENT BEFORE ************************************
    // **************************** MOVEMENT BACK **************************************
  }
 }
