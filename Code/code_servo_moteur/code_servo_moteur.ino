#include <Servo.h>

// Créer un objet Servo pour contrôler le servo
Servo myServo;

// Définir la broche à laquelle le signal du servo est connecté
const int servoPin = 9;

void setup() {
  // Attacher le servo à la broche servoPin
  myServo.attach(servoPin);
}

void loop() {
  // Faire tourner le servo à 0 degrés
  myServo.write(0);
  delay(1000); // Attendre 1 seconde

  // Faire tourner le servo à 90 degrés
  myServo.write(90);
  delay(1000); // Attendre 1 seconde

  // Faire tourner le servo à 180 degrés
  myServo.write(180);
  delay(1000); // Attendre 1 seconde

  // Revenir à 90 degrés
  myServo.write(90);
  delay(1000); // Attendre 1 seconde
}
