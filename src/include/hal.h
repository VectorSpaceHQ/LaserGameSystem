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

namespace HAL
{
   enum HalId
   {
      HAL_ID_NONE       = 0,
      HAL_ID_MAIN_LIGHT
   };


   /**************************************
    * A Rotary Encoder Controller
    **************************************/
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


   /**************************************
    * A Push Button
    **************************************/
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


   /**************************************
    * A Servo controller
    **************************************/
   class Servo
   {
   public:
      virtual ~Servo() {}
      virtual void SetPosition(int16_t _pos) = 0;

   protected:
      Servo() {}
   };


   /**************************************
    * An On/Off Toggle Switch
    **************************************/
   class OnOffSwitch
   {
   public:
      virtual ~OnOffSwitch() {}
      virtual void On() = 0;
      virtual void Off() = 0;
      virtual void Toggle() = 0;

   protected:
      OnOffSwitch() {}

   };


   /**************************************
    * Base class for the HAL
    **************************************/
   class Hal
   {
   public:
      virtual ~Hal() {};
      virtual bool Init() = 0;
      virtual void Delay(int ms) = 0;
      virtual uint32_t GetTime() = 0;
      virtual int GetNumRotaryEncoders() = 0;
      virtual int GetNumPushButtons() = 0;
      virtual int GetNumPushServos() = 0;
      virtual int GetNumPushOnOffSwitches() = 0;

      virtual OnOffSwitch* GetOnOffSwitch(HalId id) = 0;

   protected:
      Hal() {}
   };

}

#endif /* SRC_INCLUDE_HAL_H_ */
