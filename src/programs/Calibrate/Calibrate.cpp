/*
 * Calibrate.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#include "Calibrate.h"
#include "CanvasObject.h"
#include "CommonShapes.h"
#include "GameSystemEvents.h"
#include "Program.h"
#include "Shape.h"
#include "Sprite.h"


Calibrate::Calibrate(Canvas& _canvas
         //GamePad& _gamePad1,
         //GamePad& _gamePad2
         ):
   Program(_canvas/*, _gamePad1, _gamePad2*/)
{
}


void Calibrate::Init()
{
}


void Calibrate::Start()
{
}


void Calibrate::Stop()
{
}


// Currently is draws an expanding/shrinking square.
// When the square reaches the limits of the display, it starts to shrink.
void Calibrate::Run()
{
}


void Calibrate::Draw()
{
}


void Calibrate::HandleEvent(GameSystemEvent event)
{
   switch(event)
   {
      case EVENT_PROGRAM_INIT:
         Init();
         break;

      case EVENT_PROGRAM_START:
         Start();
         break;

      case EVENT_PROGRAM_RUN:
         Run();
         break;

      case EVENT_PROGRAM_DRAW:
         Draw();
         break;

      default:
         break;
   }
}
