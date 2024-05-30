#include <Servo.h>  // Include the Servo library

// Arduino PWM Speed Control:
int E1 = 5;  // Motor1 PWM pin
int M1 = 4;  // Motor1 direction pin
int E2 = 6;  // Motor2 PWM pin
int M2 = 7;  // Motor2 direction pin

Servo gripper1;  // Create a Servo object for the first gripper
Servo gripper2;  // Create a Servo object for the second gripper

unsigned long previousMillis = 0;
const long intervalClamp = 5000;  // Interval for clamping (5 seconds)
const long intervalMotorRun = 20000;  // Interval for motor run (20 seconds)
const long intervalWait = 3000;  // Interval for all waitings (3 seconds)

float clampAngle1 = 140;
float unclampAngle1 = 0;
float clampAngle2 = 0;
float unclampAngle2 = 140;

enum State {
  CLAMP1,
  WAIT1,
  RUN_MOTOR_FORWARD,
  CLAMP2,
  WAIT2,
  UNCLAMP1,
  WAIT3,
  RUN_MOTOR_BACKWARD,
  WAIT4,
  CLAMP1_AGAIN,
  WAIT5,
  UNCLAMP2,
  DONE
};
State currentState = CLAMP1;

void setup() {
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  
  gripper1.attach(11);  // Attach the first gripper to pin 11
  gripper2.attach(13);  // Attach the second gripper to pin 13
  
  gripper1.write(unclampAngle1);  // Initialize the first gripper position
  gripper2.write(unclampAngle2);  // Initialize the second gripper position
}

void loop() {
  unsigned long currentMillis = millis();

  switch (currentState) {
    case CLAMP1:
      gripper1.write(clampAngle1);  // Clamp the first gripper
      currentState = WAIT1;
      previousMillis = currentMillis;
      break;

    case WAIT1:
      if (currentMillis - previousMillis >= intervalClamp) {
        currentState = RUN_MOTOR_FORWARD;
        previousMillis = currentMillis;
        
        // Start the motors forward
        digitalWrite(M1, HIGH);
        digitalWrite(M2, HIGH);
        analogWrite(E1, 255);    
        analogWrite(E2, 255);
      }
      break;

    case RUN_MOTOR_FORWARD:
      if (currentMillis - previousMillis >= intervalMotorRun) {
        // Stop the motors
        digitalWrite(M1, LOW);
        digitalWrite(M2, LOW);
        analogWrite(E1, 0);
        analogWrite(E2, 0);
        
        currentState = CLAMP2;
        previousMillis = currentMillis;
      }
      break;

    case CLAMP2:
      gripper2.write(clampAngle2);  // Clamp the second gripper in the opposite direction
      currentState = WAIT2;
      previousMillis = currentMillis;
      break;

    case WAIT2:
      if (currentMillis - previousMillis >= intervalWait) {
        currentState = UNCLAMP1;
        previousMillis = currentMillis;
      }
      break;

    case UNCLAMP1:
      gripper1.write(unclampAngle1);  // Unclamp the first gripper
      currentState = WAIT3;
      previousMillis = currentMillis;
      break;

    case WAIT3:
      if (currentMillis - previousMillis >= intervalWait) {
        currentState = RUN_MOTOR_BACKWARD;
        previousMillis = currentMillis;
        
        // Start the motors backward
        digitalWrite(M1, LOW);
        digitalWrite(M2, LOW);
        analogWrite(E1, 255);    
        analogWrite(E2, 255);
      }
      break;

    case RUN_MOTOR_BACKWARD:
      if (currentMillis - previousMillis >= intervalMotorRun) {
        // Stop the motors
        digitalWrite(M1, LOW);
        digitalWrite(M2, LOW);
        analogWrite(E1, 0);
        analogWrite(E2, 0);
        
        currentState = WAIT4;
        previousMillis = currentMillis;
      }
      break;

    case WAIT4:
      if (currentMillis - previousMillis >= intervalWait) {
        currentState = CLAMP1_AGAIN;
        previousMillis = currentMillis;
      }
      break;

    case CLAMP1_AGAIN:
      gripper1.write(clampAngle1);  // Clamp the first gripper again
      currentState = WAIT5;
      previousMillis = currentMillis;
      break;

    case WAIT5:
      if (currentMillis - previousMillis >= intervalWait) {
        currentState = UNCLAMP2;
        previousMillis = currentMillis;
      }
      break;

    case UNCLAMP2:
      gripper2.write(unclampAngle2);  // Unclamp the second gripper
      currentState = DONE;
      previousMillis = currentMillis;
      break;

    case DONE:
      // Loop back to the beginning
      currentState = CLAMP1;
      break;
  }
}