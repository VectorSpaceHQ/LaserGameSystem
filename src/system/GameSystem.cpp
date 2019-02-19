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

namespace GameSystem
{
   const uint32_t System::GameWidth = 4094;
   const uint32_t System::GameHeight = 4094;


   System::System(HAL::Hal& _hal, DisplayIfc& _displayIfc):
            hal(_hal),
            canvas(GameWidth, GameHeight, _displayIfc),
            programs(canvas),
            currentProgram(programs.calibrateProgram),
            runTime(0)
   {
   }


   void System::Start(uint32_t  _runTime)
   {
      runTime = _runTime;

      if(hal.Init())
      {
         StartCurrentProgram();
         Run();
      }
   }


   void System::Run()
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


   void System::StartCurrentProgram()
   {
      currentProgram.HandleEvent(EVENT_PROGRAM_INIT);
      currentProgram.HandleEvent(EVENT_PROGRAM_START);
   }


   void System::StopCurrentProgram()
   {
      currentProgram.HandleEvent(EVENT_PROGRAM_STOP);
   }

}
