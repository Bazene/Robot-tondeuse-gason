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

void setup() {
  Serial.begin(9600); //lancer la communication serie à 9600bps
  
  // Initialisation des broches en sortie

  // motor 1
  pinMode(IN1, OUTPUT); digitalWrite(IN1, LOW); // for direct sens
  pinMode(IN2, OUTPUT); digitalWrite(IN2, LOW); // for indirect sens
  pinMode(ENA, OUTPUT); analogWrite(ENA, 0);

  // motor 2
  pinMode(IN3, OUTPUT); digitalWrite(IN3, LOW); // for direct sens
  pinMode(IN4, OUTPUT); digitalWrite(IN4, LOW); // for indirect sens
  pinMode(ENB, OUTPUT); analogWrite(ENB, 0);  

  // motor tonte
  pinMode(MotTonte, OUTPUT); analogWrite(MotTonte, 0);
}

void loop() {
  //verifier si les données sont disponibles sur le port série ici du bluetooth
  if (Serial.available() > 0) {
    //gestion moteur tonte 
    String receveidData = Serial.readStringUntil('\n'); // Lire la chaîne jusqu'au retour à la ligne

    // ******************** FOR LAUNCHING BACK MOTORS OR FOR BEFORE MOVEMENT ***********************
    if(receveidData == "turn on m arriere") {
      digitalWrite(IN1, LOW); // for direct sens
      digitalWrite(IN2, HIGH); // for indirect sens
  
      digitalWrite(IN3, LOW); // for direct sens
      digitalWrite(IN4, HIGH); // for indirect sens

      analogWrite(ENA, 127);  // Convertit le pourcentage en valeur entre 0 et 255
      analogWrite(ENB, 127);
    }

    if(receveidData == "turn off m arriere") {
      digitalWrite(IN1, LOW); // for direct sens
      digitalWrite(IN2, LOW); // for indirect sens

      digitalWrite(IN3, LOW); // for direct sens
      digitalWrite(IN4, LOW); // for indirect sens

      analogWrite(ENA, 0);  // Convertit le pourcentage en valeur entre 0 et 255
      analogWrite(ENB, 0);
    }

     // **************************** LEFT MOVEMENT *************************************
     if(receveidData == "left movement") {
      digitalWrite(IN1, HIGH); // for direct sens
      digitalWrite(IN2, LOW); // for indirect sens

      digitalWrite(IN3, HIGH); // for direct sens
      digitalWrite(IN4, LOW); // for indirect sens

      analogWrite(ENA, 127);  // Convertit le pourcentage en valeur entre 0 et 255
      analogWrite(ENB, 179);
    }

    // **************************** RIGHT MOVEMENT *************************************
     if(receveidData == "right movement") {
      digitalWrite(IN1, HIGH); // for direct sens
      digitalWrite(IN2, LOW); // for indirect sens

      digitalWrite(IN3, HIGH); // for direct sens
      digitalWrite(IN4, LOW); // for indirect sens

      analogWrite(ENA, 179);  // Convertit le pourcentage en valeur entre 0 et 255
      analogWrite(ENB, 127);
    }
    
    // **************************** BACK MOVEMENT **************************************
     if(receveidData == "back movement") {
      digitalWrite(IN1, HIGH); // for direct sens
      digitalWrite(IN2, LOW); // for indirect sens
  
      digitalWrite(IN3, HIGH); // for direct sens
      digitalWrite(IN4, LOW); // for indirect sens
  
      analogWrite(ENA, 127);  // Convertit le pourcentage en valeur entre 0 et 255
      analogWrite(ENB, 127);
    }
    
    // **************************** FOR TONTE MOTOR ************************************
    if(receveidData == "turn on mt") {
      analogWrite(MotTonte, 255);
    }

    if(receveidData == "turn off mt") {
      analogWrite(MotTonte, 0);
    }
  }
 }
