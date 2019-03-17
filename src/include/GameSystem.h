/*
 * GameSystem.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_GAMESYSTEM_H_
#define INCLUDE_GAMESYSTEM_H_

#include <stdint.h>

#include "Canvas.h"
#include "DisplayIfc.h"
#include "hal.h"
#include "GamePad.h"
#include "Program.h"
#include "Programs.h"


namespace GameSystem
{
   struct ButtonStatus
   {
      bool     lastStatus;
      uint32_t frameCntr;
      GamePad& gamePad;
      ButtonId buttonId;


      ButtonStatus(GamePad& _gamePad, ButtonId _buttonId):
         lastStatus(false),
         frameCntr(0),
         gamePad(_gamePad),
         buttonId(_buttonId)
      {
      }

      Events CheckButton(Button& buttonState);
   };


   class System
   {
   private:
      HAL::Hal&      hal;
      Canvas         canvas;
      Programs       programs;
      Program&       currentProgram;
      uint32_t       runTime;
      GamePad&       gamePad1;
      GamePad&       gamePad2;
      ButtonStatus   button1Status;
      ButtonStatus   button2Status;

      static const uint32_t   GameWidth;
      static const uint32_t   GameHeight;

   public:
      System(HAL::Hal& _hal,
             DisplayIfc& _displayImpl,
             GamePad& _gamePad1,
             GamePad& _gamePad2);

      void Start(uint32_t _runTime);
      void Run();

      void StartCurrentProgram();
      void StopCurrentProgram();
};

}


#endif /* INCLUDE_GAMESYSTEM_H_ */
