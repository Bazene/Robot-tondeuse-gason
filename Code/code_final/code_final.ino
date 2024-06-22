/*
  * This is the Arduino code BTS7960 DC motor Driver 
    Using this code you can control a motor to rotate in both direction Clockwise(CW) 
    and Counter-clockwise(CCW).

  * R_IS and L_IS : Sense current output. This pin provides a signal proportional 
    to the current flowing through the motor, which can be used for overload detection 
    or other diagnostics.
*/

#include <RobojaxBTS7960.h> // librairy for manage motors

//BACK MOTORS 
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
bool robotMode = false; // state of robot mode (Automatique or manuel)

// TONTE MOTOR
const int mt_tonte = 8;

// ULRASONIC SENSORS
// for front ultrasonic
const int ECHO1 = 10;
const int TRIG1 = 43;

// for back ultrasonic
const int ECHO2 = 13;
const int TRIG2 = 47;

const int obstacleLimite = 30; // the distance that help us to know if we can stop the robot (30cm because this will help us turn right or left without move back)

// BOBINE
const int bobine_left = A0 ;
const int bobine_right = A2 ;
int value_bobine_left ;
int value_bobine_right ;

//************************************************* INITIALISE FUNCTION **********************************************************
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

  // Initialize motor tonte
  pinMode(mt_tonte, OUTPUT); 
  analogWrite(mt_tonte, 0);

  // Initialize bobine
  pinMode(bobine_left, INPUT);
  pinMode(bobine_right, INPUT);

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

//*************************************************************** BASE FUNCTIONS ***************************************************************
void turn_left() {
  // we take 3 secondes of break, before moving left
  motor1.stop();
  motor2.stop();
  delay(3000);

  // we turn left in 3 secondes(This value must be confirmed in test)
  motor1.rotate(50,CCW);
  motor2.rotate(90,CW);
  delay(3000);

  // then stopp motors
  motor1.stop();
  motor2.stop();
}

void turn_right() {
  // we take 3 secondes of break, before moving right
  motor1.stop();
  motor2.stop();
  delay(3000);

  // we turn right in 3 secondes (This value must be confirmed in test)
  motor1.rotate(90,CW);
  motor2.rotate(50,CCW);
  delay(3000);

  // then stopp motors
  motor1.stop();
  motor2.stop();
}

void movement_back() {
  // we take 3 secondes of break, before moving back
  motor1.stop();
  motor2.stop();
  delay(3000);
  
  motor1.rotate(50,CCW);
  motor2.rotate(50,CCW);
}

void movement_front() {
  // we take 3 seondes of break, before moving fornt
  motor1.stop();
  motor2.stop();
  delay(3000);
  
  motor1.rotate(50,CW);
  motor2.rotate(50,CW);
}

//**************************************** FUNCTION TO CONTROL THE ROBOT'S MOVEMENT MANUELLY **************************************************
void manuel_control() {
  if(Serial.available() > 0) {
    String receveidData = Serial.readStringUntil('\n');

    // for tonte motor
     if(receveidData == "turn on mt_tonte") {
      analogWrite(mt_tonte, 255);
    }

    if(receveidData == "turn off mt_tonte") {
      analogWrite(mt_tonte, 0);
    }

    // for back motors
    if(receveidData == "turn on m arriere") {
       motor1.rotate(50,CW);
       motor2.rotate(50,CW); 
    }

    if(receveidData == "turn off m arriere") {
       motor1.stop();
       motor2.stop();
    }

    if(receveidData == "turn left") {
      turn_left(); // we call the specific function for this task
    }
    
    if(receveidData == "turn right") {
      turn_right(); // we call the specific function for this task
    }

    if(receveidData == "going front") {
      movement_front(); // we call the specific function for this task
    }

    if(receveidData == "going back") {
      movement_back(); // we call the specific function for this task
    }

    // For changing the robot mode
    if(receveidData == "automatical mode") {
       robotMode = true;
    }

    if(receveidData == "manuel mode") {
       robotMode = false;
    }
  }
}

//************************************* FUNCTION TO CONTROL THE ROBOT'S MOVEMENT AUTOMATICALLY ***********************************************

void automatical_control(){
  // Calcul of distance for each sensor
  long distanceFront = getDistance(TRIG1, ECHO1);
  long distanceBack = getDistance(TRIG2, ECHO2);

  // take limits values
  value_bobine_left = analogRead(bobine_left);
  value_bobine_right = analogRead(bobine_right);

  //valueRead > 300
  
  // default state of our motors in 5 secondes
  motor1.stop();
  motor2.stop();
  delay(5000);
  
  if (distanceFront != 0 && distanceBack != 0) { // Ensure ultrasonic sensors are working
    if(distanceBack > obstacleLimite) {
       motor1.stop();
       motor2.stop();
       delay(3000); 
       
      // run motor with 50% speed in CW direction
      motor1.rotate(50,CW);
      motor2.rotate(50,CW);
    } else {
       // we stop motors of 1 seconde
       motor1.stop();
       motor2.stop();
       delay(3000); 

       motor1.rotate(90,CW); // Turn right by running motor1 faster
       motor2.rotate(50,CCW); 
       delay(3000); 

       motor1.stop();
       motor2.stop();
       delay(2000); // Stop motors for 1 second
 
       motor1.rotate(50,CW); // Resume forward movement
       motor2.rotate(50,CW);
    }

    // If obstacle is too close at the back, stop motors for 1 second
    if(distanceFront < obstacleLimite) {
      motor1.stop();
      motor2.stop();
    }
  }
}


//*********************************************************** LOOP FUNCTION *******************************************************************
void loop() { 
  
  if(robotMode) {
    automatical_control();  
  } else {
    manuel_control(); // the default mode
  }
    
  delay(2000); // reproduice the same processusse after 2 seconds 
}
