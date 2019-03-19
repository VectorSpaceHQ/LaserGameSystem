/*
 * GameSystem.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */


#include "GamePad.h"
#include "GameSystem.h"
#include "GameSystemDefs.h"
#include "GameSystemEvents.h"
#include "hal.h"
#include "Programs.h"


namespace GameSystem
{
   const uint32_t System::GameWidth = 4094;
//   const uint32_t System::GameHeight = 4094;    // For 1:1 ratio
   const uint32_t System::GameHeight = 3072;    // For 4:3 ratio
//   const uint32_t System::GameHeight = 2302;    // For 16:9 ratio

   Events ButtonStatus::CheckButton(Button& buttonState)
   {
      Events buttonEvent = EVENT_MAX;

      buttonState.gamPadId = gamePad.GetId();
      buttonState.id = buttonId;
      buttonState.isPressed = gamePad.GetButton(buttonId);

      ++frameCntr;

      if(timeout > 0)
      {
         --timeout;
      }

      if(buttonState.isPressed != lastStatus)
      {
         if((timeout == 0) && (frameCntr < 0.5 * 30))
         {
            buttonEvent = EVENT_GAMEPAD_BUTTON_CLICK;
            // Wait 1 second before we register another click
            timeout = 1 * 30;
         }

         frameCntr = 0;
      }

      lastStatus = buttonState.isPressed;

      return buttonEvent;
   }


   System::System(HAL::Hal& _hal,
                  DisplayIfc& _displayIfc,
                  GamePad& _gamePad1,
                  GamePad& _gamePad2):
      hal(_hal),
      canvas(GameWidth, GameHeight, _displayIfc),
      programs(canvas, _gamePad1, _gamePad2),
      currentProgram(programs.pongProgram),
      runTime(0),
      gamePad1(_gamePad1),
      gamePad2(_gamePad2),
      button1Status(gamePad1, BUTTON_ID_A),
      button2Status(gamePad2, BUTTON_ID_A)
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
         Events buttonEvent;
         Button buttonState;

         gamePad1.Run();
         gamePad2.Run();

         // Check the button status for Game Pad 1
         buttonEvent = button1Status.CheckButton(buttonState);

         if(buttonEvent != EVENT_MAX)
         {
            currentProgram.HandleEvent(buttonEvent, &buttonState);
         }

         // Check the button status for Game Pad 2
         buttonEvent = button2Status.CheckButton(buttonState);

         if(buttonEvent != EVENT_MAX)
         {
            currentProgram.HandleEvent(buttonEvent, &buttonState);
         }

         currentProgram.HandleEvent(EVENT_PROGRAM_RUN, nullptr);
         currentProgram.HandleEvent(EVENT_PROGRAM_DRAW, nullptr);
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
      currentProgram.HandleEvent(EVENT_PROGRAM_INIT, nullptr);
      currentProgram.HandleEvent(EVENT_PROGRAM_START, nullptr);
   }


   void System::StopCurrentProgram()
   {
      currentProgram.HandleEvent(EVENT_PROGRAM_STOP, nullptr);
   }

}
