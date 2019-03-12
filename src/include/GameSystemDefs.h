/*
 * GameSystemDefs.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_GAMESYSTEMDEFS_H_
#define INCLUDE_GAMESYSTEMDEFS_H_

#include <stdint.h>


namespace GameSystem
{
   enum GamePadId
   {
      GAMEPAD_ID_ANY = 0,
      GAMEPAD_ID_1,
      GAMEPAD_ID_2,
      GAMEPAD_ID_3,
      GAMEPAD_ID_4
   };


   enum AxisId
   {
      AXIS_ID_LEFT_X = 0,
      AXIS_ID_LEFT_Y,
      AXIS_ID_RIGHT_X,
      AXIS_ID_RIGHT_Y
   };


   struct Axis
   {
      AxisId   id;
      int32_t  position;
   };


   enum ButtonId
   {
      BUTTON_ID_A = 0,
      BUTTON_ID_B,
      BUTTON_ID_C,
      BUTTON_ID_D,
      BUTTON_ID_START
   };


   struct Button
   {
      GamePadId   gamPadId;
      ButtonId    id;
      bool        isPressed;
   };
}

#endif /* INCLUDE_GAMESYSTEMDEFS_H_ */
