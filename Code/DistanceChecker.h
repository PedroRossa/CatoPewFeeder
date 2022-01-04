/*
    Feeder.h - Library for manage HC-04 Ultrasonic distance sensor to detect feeder fill.
    Created by Pedro Rossa, January 4, 2022.
    Released into the public domain.
*/
#ifndef DistanceChecker_h
#define DistanceChecker_h

#include "Arduino.h"

class DistanceChecker
{
  public:
  DistanceChecker(uint16_t echo_pin, uint16_t trigger_pin, uint empty_distance_in_cm = 20, uint full_distance_in_cm = 5);
    
  uint checkDistance();
  void serialPrintDebugDistance();
    
  private:
  uint16_t _echo_pin;
  uint16_t _trigger_pin;
  uint _empty_distance_in_cm;
  uint _full_distance_in_cm;
    
  uint _ultrasonicDistance();
  void _pingUltrasonic();
};

#endif