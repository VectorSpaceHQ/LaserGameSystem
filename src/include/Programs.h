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
#include "TestProgram/TestProgram.h"


struct Programs
{
   Calibrate   calibrateProgram;
   TestProgram testProgram;
   GiantPong   pongProgram;

   // TODO: Implement
   Programs(Canvas& _display
            //GamePad& _gamePad1,
            //GamePad& _gamePad2
            ):
      calibrateProgram(_display),
      testProgram(_display),
      pongProgram(_display)
   {
   }
};



#endif /* SYSTEM_PROGRAMS_H_ */
