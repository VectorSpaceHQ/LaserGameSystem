/*
 * Calibrate.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#include "Calibrate.h"
#include "Program.h"


Calibrate::Calibrate(Display& _display
         //GamePad& _gamePad1,
         //GamePad& _gamePad2
         ):
   Program(_display/*, _gamePad1, _gamePad2*/)
{

}


void Calibrate::Update()
{
   display.Clear();
}
