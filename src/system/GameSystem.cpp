/*
 * GameSystem.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */


#include "GameSystem.h"
#include "hal.h"
#include "Programs.h"


GameSystem::GameSystem(HAL::Hal& _hal):
   hal(_hal),
   display(),
   programs(display),
   currentProgram(programs.calibrateProgram) // Set the default program to calibrate for now
{
}


void GameSystem::Start()
{
   if(hal.Init())
   {
      display.Init(hal.GetOnOffSwitch(HAL::HAL_ID_MAIN_LIGHT));
      Run();
   }
}


void GameSystem::Run()
{
   while(1)
   {
      currentProgram.Run();
      hal.Delay(5);
   }
}
