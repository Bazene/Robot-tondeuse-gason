/*
  * This is the Arduino code BTS7960 DC motor Driver 
    Using this code you can control a motor to rotate in both direction Clockwise(CW) 
    and Counter-clockwise(CCW).

  * R_IS and L_IS : Sense current output. This pin provides a signal proportional 
    to the current flowing through the motor, which can be used for overload detection 
    or other diagnostics.
*/

#include <RobojaxBTS7960.h> // librairy for manage motors

//************************************************************ BACK MOTORS **********************************************************************
// for motor 1
const int RPWM_1 = 3; // define pin 3 for RPWM pin (output)
const int R_EN_1 = 27; // define pin 27 for R_EN pin (input)
#define R_IS_1 A4 // define pin A4 for R_IS pin (output), 

const int LPWM_1 = 4 ; // define pin 4 for LPWM pin (output)
const int L_EN_1 = 31; // define pin 31 for L_EN pin (input)
#define L_IS_1 A5 // define pin A5 for L_IS pin (output) ; Current Sense, ou détection de courant

// for motor 2
const int RPWM_2 = 6; // define pin 6 for RPWM pin (output)
const int R_EN_2 = 39; // define pin 39 for R_EN pin (input)
#define R_IS_2 A6 // define pin A6 for R_IS pin (output)

const int LPWM_2 = 7; // define pin 7 for LPWM pin (output)
const int L_EN_2 = 35; // define pin 35 for L_EN pin (input)
#define L_IS_2 A7 // define pin A7 for L_IS pin (output)

// variables that help us to control trafic
const int CW = 1; //do not change this
const int CCW = 0; //do not change this
const int debug = 0; //change to 0 to hide serial monitor debugging infornmation or set to 1 to view

// instances for our tows motors
RobojaxBTS7960 motor1(R_EN_1,RPWM_1,R_IS_1, L_EN_1,LPWM_1,L_IS_1,debug); //define motor 1 object (first instance of RobojaxBTS7960)
RobojaxBTS7960 motor2(R_EN_2,RPWM_2,R_IS_2, L_EN_2,LPWM_2,L_IS_2,debug); //define motor 2 object (second instance of RobojaxBTS7960)

bool motorRunningArriere = false; // State of motors

//************************************************************ TONTE MOTOR **********************************************************************
//const int Mt_tonte = 10;

//********************************************************* ULRASONIC SENSORS *******************************************************************
// for front ultrasonic
const int ECHO1 = 10;
const int TRIG1 = 43;

// for back ultrasonic
const int ECHO2 = 13;
const int TRIG2 = 47;

const int obstacleLimite = 30; // the distance that help us to know if we can stop the robot (30cm because this will help us turn right or left without move back)

//*********************************************************** SETUP FUNCTION *******************************************************************
void setup() {
  Serial.begin(9600); // setup Serial Monitor to display information

  // Initialize motors sensors
  motor1.begin();
  motor2.begin();

  // Initialize ultrasonics sensors
  pinMode(ECHO1, INPUT); // receiver
  pinMode(TRIG1, OUTPUT); // transmitter
  pinMode(ECHO2, INPUT);
  pinMode(TRIG2, OUTPUT);

  // set default values for ultrasonic sensors
  digitalWrite(TRIG1, LOW);
  digitalWrite(TRIG2, LOW);

  delay(2); // shot delay for stability
}

//*************************************** FUNCTION TO CALCULATE THE DISTANCE USING ULTRASONIC ******************************************************
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

//************************************* FUNCTION TO CONTROL THE ROBOT'S MOVEMENT AUTOMATICALLY ************************************************
void movement_control(){
  // Calcul of distance for each sensor
  long distanceFront = getDistance(TRIG1, ECHO1);
  long distanceBack = getDistance(TRIG2, ECHO2);

  // default state of our motors
  motor1.stop();
  motor2.stop();
  
  if (distanceFront != 0 && distanceBack != 0) { // Ensure ultrasonic sensors are working
    if(distanceFront > obstacleLimite) {
      // run motor with 50% speed in CW direction
      motor1.rotate(50,CW);
      motor2.rotate(50,CW);
    } else {
       // we stop motors of 1 seconde
       motor1.stop();
       motor2.stop();
       delay(1000); 

       motor1.rotate(70,CW); // Turn right by running motor1 faster
       motor2.rotate(50,CW); 

       motor1.stop();
       motor2.stop();
       delay(1000); // Stop motors for 1 second
 
       motor1.rotate(50,CW); // Resume forward movement
       motor2.rotate(50,CW);
    }

    // If obstacle is too close at the back, stop motors for 1 second
    if(distanceBack < obstacleLimite) {
      motor1.stop();
      motor2.stop();
      delay(1000); // Stop motors for 1 second
    }
  }
}


//*********************************************************** LOOP FUNCTION *******************************************************************
void loop() { 
  movement_control();
    
  delay(2000); // reproduice the same processusse after 2 seconds 
}
