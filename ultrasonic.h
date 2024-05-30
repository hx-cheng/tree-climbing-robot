#ifndef __ULTRASONIC_H
#define	__ULTRASONIC_H

# include "arduino.h"

void ini_ultrasonic(int trigPinl, int echoPinl, int trigPinr, int echoPinr);
float measure_d(int trigPin, int echoPin);

#endif /* __ULTRASONIC_H */