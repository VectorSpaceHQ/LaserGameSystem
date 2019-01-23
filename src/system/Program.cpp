/*
 * Program.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#include "Program.h"
#include "Display.h"
#include "GamePad.h"

Program::Program(Display& _display
                 //GamePad& _gamePad1,
                 //GamePad& _gamePad2
                 ):
   ScheduledInterval(33),    // TODO: This will need to change when we get real time
   display(_display)
//   gamePad1(),
//   gamePad2()
{
}


void Program::Init()
{
}


void Program::Start()
{
}


void Program::Update()
{
}


void Program::Stop()
{
}
