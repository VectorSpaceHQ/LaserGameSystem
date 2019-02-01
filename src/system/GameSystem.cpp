/*
 * GameSystem.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */


#include "GameSystem.h"
#include "hal.h"
#include "Programs.h"


GameSystem::GameSystem(HAL::Hal& _hal, DisplayIfc& _displayIfc):
   hal(_hal),
   canvas(_displayIfc),
   programs(canvas),
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
      canvas.Run();
      hal.Delay(1);
   }
}
