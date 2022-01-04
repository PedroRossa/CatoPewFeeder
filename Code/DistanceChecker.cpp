/*
    Feeder.h - Library for manage HC-04 Ultrasonic distance sensor to detect feeder fill.
    Created by Pedro Rossa, January 4, 2022.
    Released into the public domain.
*/
#include "DistanceChecker.h"
   
DistanceChecker::DistanceChecker(uint16_t echo_pin, uint16_t trigger_pin, uint empty_distance_in_cm, uint full_distance_in_cm)
{
    _echo_pin = echo_pin;
    _trigger_pin = trigger_pin;
    _empty_distance_in_cm = empty_distance_in_cm;
    _full_distance_in_cm = full_distance_in_cm;

    pinMode(_echo_pin, INPUT);
    pinMode(_trigger_pin, OUTPUT);
}
    
uint DistanceChecker::checkDistance()
{
    return _ultrasonicDistance();
}

void DistanceChecker::serialPrintDebugDistance()
{
  uint distance = checkDistance();

  Serial.print("Food is: ");
  if(distance <= _full_distance_in_cm)
  {
    Serial.println("Full Filed");
  }
  else if(distance <= _full_distance_in_cm/2)
  {
    Serial.println("You are in the middle of your food");
  }
  else if(distance <= _empty_distance_in_cm)
  {
    Serial.println("You are almost without food");
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
}

uint DistanceChecker::_ultrasonicDistance()
{
  _pingUltrasonic();
  long time = pulseIn(_echo_pin, HIGH);
  return (uint)((time / 2) / 29.1); //cm distance
}

void DistanceChecker::_pingUltrasonic()
{
  digitalWrite(_trigger_pin, LOW); //PULSE ___|---|___
  delayMicroseconds(2);
  digitalWrite(_trigger_pin, HIGH);
  delayMicroseconds(10);
}