/*
 * GameSystem.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */


#include "GameSystem.h"
#include "hal.h"
#include "Programs.h"


GameSystem::GameSystem(HAL::Hal& _hal, DisplayIfc& _displayImpl):
   hal(_hal),
   display(_displayImpl),
   programs(display),
   currentProgram(programs.calibrateProgram) // Set the default program to calibrate for now
{
}


void GameSystem::Start()
{
   if(hal.Init())
   {
      Run();
   }
}


void GameSystem::Run()
{
   while(1)
   {
      currentProgram.Run();
      display.Run();
      hal.Delay(1);
   }
}
