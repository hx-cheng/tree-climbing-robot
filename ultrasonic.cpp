# include "ultrasonic.h"

void ini_ultrasonic(int trigPinl, int echoPinl, int trigPinr, int echoPinr) {
  pinMode(trigPinl, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPinl, INPUT);  // Sets the echoPin as an Input
  pinMode(trigPinr, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPinr, INPUT);  // Sets the echoPin as an Input
}

float measure_d(int trigPin, int echoPin) {
  // defines variables
  long duration;
  float distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(500);
  return distance;
}
