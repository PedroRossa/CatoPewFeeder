/*
    Feeder.h - Library for manage servo motors of catFeeder.
    Created by Pedro Rossa, January 4, 2022.
    Released into the public domain.
*/

#include "Feeder.h"

Feeder::Feeder(uint16_t led_pin, uint16_t servo_pin, uint16_t close_position, uint16_t open_position)
{
    _led_pin = led_pin;
    _servo_pin = servo_pin;
    _close_position = close_position;
    _open_position = open_position;

    pinMode(_led_pin, OUTPUT);
    _setLedStatus(false);

    _servo_motor.attach(_servo_pin);

    close();
}

void Feeder::setOpenPosition(uint16_t angle)
{
    _open_position = angle;
}

void Feeder::setClosePosition(uint16_t angle)
{
    _close_position = angle;
}

void Feeder::open()
{
    _servo_motor.write(_open_position);
    _setLedStatus(true);

    _is_open = true;
}

void Feeder::close()
{
    _servo_motor.write(_close_position);
    _setLedStatus(false);

    _is_open = false;
}

void Feeder::openAndCloseAfterMiliseconds(uint time_in_mili)
{
    open();
    delay(time_in_mili);
    close();
}

bool Feeder::isOpen()
{
    return _is_open;
}

// Private Methods

void Feeder::_setLedStatus(bool state)
{
    digitalWrite(_led_pin, state);
}

//----------------