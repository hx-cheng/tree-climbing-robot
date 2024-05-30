#ifndef __MYSERVO_H
#define	__MYSERVO_H

# include "arduino.h"
# include <Servo.h>  // Include the Servo library

void slow_rotate (float &current_angle, float target_angle, Servo &myServo);

#endif /* __MYSERVO_H */
