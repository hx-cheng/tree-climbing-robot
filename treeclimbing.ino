# include "myServo.h"
# include "dcMotor.h"
# include "ultrasonic.h"

//Defines pins number for ultrasonic sensors
const int trigPin_l = 9;
const int echoPin_l = 10;
const int trigPin_r = 3;
const int echoPin_r = 2;

Servo myServo1;  //Create a servo object to control the lower gripper
Servo myServo2;  //Create a servo object to control the upper gripper
const int servoPin1 = 13;  //PWM pin where the servo is connected
const int servoPin2 = 11;  //PWM pin where the servo is connected

const int intervalGrasp = 5000;  //Timenterval for grasping (5 seconds)
const int run_time = 40000;  //Time interval for motor run (40 seconds)
const int intervalWait = 3000;  //Time interval for all waitings (3 seconds)

float ini_angle = 0;  //Intial angle
float rotate_angle1 = 190;  //Rotate angle for the lower gripper
float rotate_angle2 = 240;  //Rotate angle for the upper gripper

void setup() {
  Serial.begin(9600);
  ini_dcmotor(); 
  ini_ultrasonic(trigPin_l, echoPin_l, trigPin_r, echoPin_r);
  
  myServo1.attach(servoPin1);  //Attaches the servo on pin 13 to the first servo object 
  myServo2.attach(servoPin2);  //Attaches the servo on pin 11 to the second servo object

  myServo1.write(ini_angle);  //Initialize the lower gripper position
  myServo2.write(ini_angle);  //Initialize the upper gripper position
}

void loop() {
  float distance_r, distance_l;

  while (1) {
    distance_r = measure_d(trigPin_r, echoPin_r);
    distance_l = measure_d(trigPin_l, echoPin_l);

    //Climbing Up
    if ((abs(distance_r - distance_l) <= 1) && (distance_r < 10) && (distance_l < 10)) {
      break; // reach the rooftop
    } else {
      delay(500);  //Wait for 0.5 second
      myServo1.write(rotate_angle1);  //Closing motion of lower gripper
      delay(run_time);  //Wait for the gripper moving up
      
      move_up(run_time);  //Moving upper gripper up
      
      slow_rotate(ini_angle, rotate_angle2, myServo2);  //Closing motion of upper gripper
      delay(intervalWait);

      slow_rotate(rotate_angle1, ini_angle, myServo1);  //Opening motion of lower gripper
      delay(run_time);
  
      move_down(run_time); //Moving lower gripper up

      slow_rotate(ini_angle, rotate_angle1, myServo1);  //Closing motion of lower gripper
      delay(intervalWait);

      slow_rotate(rotate_angle2, ini_angle, myServo2);  //Opening motion of upper gripper
      delay(intervalWait);
    }
  }

  delay(3000); //Sensor Deployment

  //Climbing Down
  while (1) {
    distance_r = measure_d(trigPin_r, echoPin_r);
    distance_l = measure_d(trigPin_l, echoPin_l);

    if ((abs(distance_r - distance_l) <= 1) && (distance_r > 240) && (distance_l > 240)) {
      break; //Reach the ground
    } else {
      delay(500);  //Wait for 0.5 second
      myServo1.write(rotate_angle1);  //Closing motion of lower gripper
      delay(run_time);  //Wait for the upper gripper moving down

      move_down(run_time);  //Moving upper gripper down

      slow_rotate(ini_angle, rotate_angle2, myServo2);  //Closing motion of upper gripper
      delay(intervalWait); 

      slow_rotate(rotate_angle1, ini_angle, myServo1);  //Opening motion of lower gripper
      delay(run_time);  //Opening motion of upper gripper
  
      move_up(run_time); //Moving lower gripper down
  
      slow_rotate(ini_angle, rotate_angle1, myServo1);  //Closing motion of lower gripper
      delay(intervalWait);

      slow_rotate(rotate_angle2, ini_angle, myServo2);  //Opening motion of upper gripper
      delay(intervalWait);
    }
  }
}
