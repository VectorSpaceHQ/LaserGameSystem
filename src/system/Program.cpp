/*
 * Program.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#include "Canvas.h"
#include "Program.h"
#include "GamePad.h"

namespace GameSystem
{
   Program::Program(Canvas& _canvas,
                    GamePad& _gamePad1,
                    GamePad& _gamePad2):
      canvas(_canvas),
      gamePad1(_gamePad1),
      gamePad2(_gamePad2)
   {
   }

}
