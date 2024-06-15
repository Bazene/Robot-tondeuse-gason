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
  myServo.write(0);
  delay(3000); // Attendre 1 seconde
  
  myServo.write(90); // Faire tourner le servo à 90 degrés
  delay(3000); // Attendre 1 seconde

  myServo.write(0);
  delay(3000); // Attendre 1 seconde

  myServo.write(90); // Revenir à 90 degrés
  delay(3000); // Attendre 1 seconde
}
