/*
 * hal.h
 *
 *  This file contains the abstract classes for the various hardware components.
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef SRC_INCLUDE_HAL_H_
#define SRC_INCLUDE_HAL_H_

#include <stdint.h>

class RotaryEncoder
{
protected:
   int16_t position;

   void SetPosition(int16_t _pos) { position = _pos; }

public:
   RotaryEncoder():
      position(0)
   {
   }

   int16_t GetPosition() { return position; }

};


class PushButton
{
protected:
   bool isPressed;

public:
   PushButton():
      isPressed(false)
   {
   }

   bool GetPressed() { return isPressed; }

};


class Servo
{
public:
   Servo() {}
   void SetPosition(int16_t _pos) = 0;

};


class OnOffSwitch
{
public:
   OnOffSwitch() {}
   void On() = 0;
   void Off() = 0;
   void Toggle() = 0;

};


#endif /* SRC_INCLUDE_HAL_H_ */
