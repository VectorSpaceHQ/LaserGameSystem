/*
 * TestGamePadPaddle.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: athiessen
 */

#include "GamePad.h"
#include "GameSystemDefs.h"
#include "TestGamePadPaddle.h"


TestGamePadPaddle::TestGamePadPaddle(GameSystem::GamePadId _id):
   gamePadId(_id),
   axisLeftX(0),
   buttonA(false)
{
}


TestGamePadPaddle::~TestGamePadPaddle()
{
}


GameSystem::GamePadId TestGamePadPaddle::GetId()
{
   return gamePadId;
}


int32_t TestGamePadPaddle::GetAxis(GameSystem::AxisId axis)
{
   if(axis == GameSystem::AXIS_ID_LEFT_X)
   {
      return axisLeftX;
   }
   else
   {
      return 0;
   }
}


bool TestGamePadPaddle::GetButton(GameSystem::ButtonId button)
{
   if(button == GameSystem::BUTTON_ID_A)
   {
      return buttonA;
   }
   else
   {
      return false;
   }
}
