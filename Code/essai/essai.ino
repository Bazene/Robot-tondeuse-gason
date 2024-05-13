// Définition des broches pour le 1er pont H
const int IN1 = 27;
const int IN2 = 31;
const int ENA = 4;

// Définition des broches pour le 2ème pont H
const int IN3 = 35;
const int IN4 = 39;
const int ENB = 7;

// Déclaration des variables pour le rapport cyclique (35%)
const int dutyCycle = 50;  // 35% du rapport cyclique (0-255)

// Déclaration
const int MotTonte = 53;

void setup() {
  // Initialisation des broches en sortie
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(MotTonte, OUTPUT);
  
  // IN1 et IN3 à l'état haut (HIGH)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);

  // à l'état haut (HIGH)
  digitalWrite(MotTonte, HIGH);

  // IN2 et IN4 à l'état bas (LOW)
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Activation de la modulation de largeur d'impulsion (PWM) pour ENA et ENB
  analogWrite(ENA, (dutyCycle * 255) / 100);  // Convertit le pourcentage en valeur entre 0 et 255
  analogWrite(ENB, (dutyCycle * 255) / 100);

  // Mettre ici d'autres instructions si nécessaire
}
