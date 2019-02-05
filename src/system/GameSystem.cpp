/*
 * GameSystem.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */


#include "GameSystem.h"
#include "GameSystemEvents.h"
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
      StartCurrentProgram();
      Run();
   }
}


void GameSystem::Run()
{
   while(1)
   {
      currentProgram.HandleEvent(EVENT_PROGRAM_RUN);
      currentProgram.HandleEvent(EVENT_PROGRAM_DRAW);
      canvas.Run();
      hal.Delay(33);
   }
}


void GameSystem::StartCurrentProgram()
{
   currentProgram.HandleEvent(EVENT_PROGRAM_INIT);
   currentProgram.HandleEvent(EVENT_PROGRAM_START);
}


void GameSystem::StopCurrentProgram()
{
   currentProgram.HandleEvent(EVENT_PROGRAM_STOP);
}


