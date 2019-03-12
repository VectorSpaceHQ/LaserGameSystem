/*
 * Programs.h
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#ifndef SYSTEM_PROGRAMS_H_
#define SYSTEM_PROGRAMS_H_

#include "Program.h"
#include "Calibrate/Calibrate.h"
#include "GiantPong/GiantPong.h"

namespace GameSystem
{
   struct Programs
   {
      Calibrate   calibrateProgram;
      GiantPong   pongProgram;

      Programs(Canvas& _display,
               GamePad& _gamePad1,
               GamePad& _gamePad2):
         calibrateProgram(_display, _gamePad1, _gamePad2),
         pongProgram(_display, _gamePad1, _gamePad2)
      {
      }
   };

}


#endif /* SYSTEM_PROGRAMS_H_ */
