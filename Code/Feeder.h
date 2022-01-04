/*
    Feeder.h - Library for manage servo motors of catFeeder.
    Created by Pedro Rossa, January 4, 2022.
    Released into the public domain.
*/
#ifndef Feeder_h
#define Feeder_h

#include "Arduino.h"
#include <Servo.h>

class Feeder
{
  public:
  Feeder(uint16_t led_pin, uint16_t servo_pin, uint16_t close_position = 100, uint16_t open_position = 80);
  void setOpenPosition(uint16_t angle);
  void setClosePosition(uint16_t angle);

  void open();
  void close();
  void openAndCloseAfterMiliseconds(uint time_in_mili);

  bool isOpen();
    
  private:
  uint16_t _led_pin;
  uint16_t _servo_pin;

  uint16_t _close_position;
  uint16_t _open_position;

  bool _is_open;
  Servo _servo_motor;  

  void _setLedStatus(bool state);
};

#endif