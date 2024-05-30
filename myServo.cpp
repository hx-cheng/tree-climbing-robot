# include "myServo.h"

int minPulseWidth = 500;  // Minimum pulse width in microseconds
int maxPulseWidth = 2500; // Maximum pulse width in microseconds
int maxAngle = 180;  // Maximum angle corresponding to maximum pulse width
int factor = (maxPulseWidth - minPulseWidth) / maxAngle; // Factor for conversion from angle to pulse width

void slow_rotate(float &current_angle, float target_angle, Servo &myServo) {
  if (current_angle < target_angle) {
    for (int angle=(int) current_angle; angle <= (int)target_angle; angle+=5) {
      myServo.write(angle);
      delay(100);
    }
  } else {
    for (int angle=(int) current_angle; angle >= (int)target_angle; angle-=5) {
      myServo.write(angle);
      delay(100);
    }
  }
}
