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
   buttonA(false),
   frameCtr(0)
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

#include <iostream>

void TestGamePadPaddle::Run()
{
   frameCtr++;

   if( ( (gamePadId == GameSystem::GAMEPAD_ID_1) && (frameCtr > 3 * 30) && (frameCtr < 3.3 * 30)) ||
       ( (gamePadId == GameSystem::GAMEPAD_ID_1) && (frameCtr > 8 * 30) && (frameCtr < 8.3 * 30)) ||
       ( (gamePadId == GameSystem::GAMEPAD_ID_2) && (frameCtr > 6 * 30) && (frameCtr < 6.3 * 30)))
   {
      if(!buttonA)
      {
         std::cout << "GamePad " << gamePadId << " Button Pressed: " << frameCtr << std::endl;
      }

      buttonA = true;
   }
   else
   {
      if(buttonA)
      {
         std::cout << "GamePad " << gamePadId << " Button Released: " << frameCtr << std::endl;
      }

      buttonA = false;
   }
}
