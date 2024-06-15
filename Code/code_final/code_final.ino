/*
  * This is the Arduino code BTS7960 DC motor Driver 
    Using this code you can control a motor to rotate in both direction Clockwise(CW) 
    and Counter-clockwise(CCW).

  * R_IS and L_IS : Sense current output. This pin provides a signal proportional 
    to the current flowing through the motor, which can be used for overload detection 
    or other diagnostics.
*/

// for motor 1
#define RPWM_1 3 // define pin 3 for RPWM pin (output)
#define R_EN_1 27 // define pin 27 for R_EN pin (input)
#define R_IS_1 A4 // define pin A4 for R_IS pin (output), 

#define LPWM_1 4 // define pin 4 for LPWM pin (output)
#define L_EN_1 31 // define pin 31 for L_EN pin (input)
#define L_IS_1 A5 // define pin A5 for L_IS pin (output) ; Current Sense, ou détection de courant

// for motor 2
#define RPWM_2 6 // define pin 6 for RPWM pin (output)
#define R_EN_2 39 // define pin 39 for R_EN pin (input)
#define R_IS_2 A6 // define pin A6 for R_IS pin (output)

#define LPWM_2 7 // define pin 7 for LPWM pin (output)
#define L_EN_2 35 // define pin 35 for L_EN pin (input)
#define L_IS_2 A7 // define pin A7 for L_IS pin (output)

// variables that help us to control trafic
#define CW 1 //do not change this
#define CCW 0 //do not change this
#define debug 0 //change to 0 to hide serial monitor debugging infornmation or set to 1 to view

#include <RobojaxBTS7960.h>
RobojaxBTS7960 motor1(R_EN_1,RPWM_1,R_IS_1, L_EN_1,LPWM_1,L_IS_1,debug); //define motor 1 object (first instance of RobojaxBTS7960)
RobojaxBTS7960 motor2(R_EN_2,RPWM_2,R_IS_2, L_EN_2,LPWM_2,L_IS_2,debug); //define motor 2 object and the same way for other motors (second instance of RobojaxBTS7960)

bool motorRunningArriere = false; // State of motors

void setup() {
  // BTS7960 Motor Control Code by Robojax.com 20190622
  Serial.begin(9600);// setup Serial Monitor to display information

  // initialisation of our tow motors
  motor1.begin();
  motor2.begin();
}

void loop() {
//    motor1.rotate(50,CW);// run motor with 100% speed in CW direction
//    motor2.rotate(50,CW);
//    delay(5000);//run for 5 seconds
//    

    if(!motorRunningArriere) {
      motor1.stop();// stop the motor
      motor2.stop();
    }
//    delay(3000);// stop for 3 seconds
//    
//    motor1.rotate(50,CCW);// run motor at 100% speed in CCW direction
//    motor2.rotate(50,CCW);
//    delay(5000);// run for 5 seconds
//
//    motor1.stop();// stop the motor
//    motor2.stop();
//    delay(3000);// stop for 3 seconds

    if (Serial.available() > 0) {
    //gestion moteur tonte 
    String receveidData = Serial.readStringUntil('\n'); // Lire la chaîne jusqu'au retour à la ligne

      // ******************** FOR LAUNCHING BACK MOTORS OR FOR BEFORE MOVEMENT ***********************
      if(receveidData == "turn on m arriere") {
        motor1.rotate(50,CW);// run motor with 100% speed in CW direction
        motor2.rotate(50,CW);
        motorRunningArriere = true;
      }

      if(receveidData == "turn off m arriere") {
        motor1.stop();// stop the motor
        motor2.stop();
        motorRunningArriere = false;
      }
    }
  delay(2000);// stop for 3 seconds 
}
