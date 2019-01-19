/*
 * GameSystemDefs.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_GAMESYSTEMDEFS_H_
#define INCLUDE_GAMESYSTEMDEFS_H_

#include <stdint.h>

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
   int16_t  position;
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
   ButtonId    id;
   bool        isPressed;
};


#endif /* INCLUDE_GAMESYSTEMDEFS_H_ */
