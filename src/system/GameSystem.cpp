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

const uint32_t GameSystem::GameWidth = 4096;
const uint32_t GameSystem::GameHeight = 4096;


GameSystem::GameSystem(HAL::Hal& _hal, DisplayIfc& _displayIfc):
   hal(_hal),
   canvas(GameWidth, GameHeight, _displayIfc),
   programs(canvas),
   currentProgram(programs.calibrateProgram), // Set the default program to calibrate for now
   runTime(0)
{
}


void GameSystem::Start(uint32_t  _runTime)
{
   runTime = _runTime;

   if(hal.Init())
   {
      StartCurrentProgram();
      Run();
   }
}


void GameSystem::Run()
{
   int32_t  timeLeft = runTime - hal.GetTime();

   if(runTime == 0)
   {
      timeLeft = 1;
   }

   while(timeLeft > 0)
   {
      currentProgram.HandleEvent(EVENT_PROGRAM_RUN);
      currentProgram.HandleEvent(EVENT_PROGRAM_DRAW);
      canvas.Render();
      hal.Delay(33);

      if(runTime != 0)
      {
         timeLeft = runTime - hal.GetTime();
      }
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


