# include "dcMotor.h"

//Arduino PWM Speed Control：
const int E1 = 5;  // motor1 PWM pin
const int M1 = 4;  // motor1 direction pin
const int E2 = 6;  // motor2 PWM pin
const int M2 = 7;  // motor2 direction pin

void ini_dcmotor() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void move_up(int run_time) {
  unsigned long startTime = millis();
  do {
    unsigned long currentTime = millis();
    if (currentTime - startTime <= run_time) {
      Serial.print(currentTime);
      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
      analogWrite(E1, 250);   //PWM Speed Control
      analogWrite(E2, 250);   //PWM Speed Control
    } else {
      break;
    }
  } while (1);

  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}
 
void move_down(int run_time) {
  unsigned long startTime = millis();
  do {
    unsigned long currentTime = millis();
    if (currentTime - startTime <= run_time) {
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      analogWrite(E1, 250);   //PWM Speed Control
      analogWrite(E2, 250);   //PWM Speed Control
    } else {
      break;
    }
  } while (1);

  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}