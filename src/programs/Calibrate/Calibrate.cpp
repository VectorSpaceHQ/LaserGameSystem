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
   Program(_canvas/*, _gamePad1, _gamePad2*/),
   cursor(),
   currentDir(),
   cntr(0)
{
}


void Calibrate::Init()
{
   cursor = new CursorShape();
   cursor->Scale(400);
}


void Calibrate::Start()
{
   canvas.AddObject(cursor);
}


void Calibrate::Stop()
{
   delete(cursor);
   free(cursor);
}


// Currently is draws an expanding/shrinking square.
// When the square reaches the limits of the display, it starts to shrink.
void Calibrate::Run()
{
   if(cntr++ >= 30)
   {
      currentDir++;

      if(currentDir > CursorShape::UpLeft)
      {
         currentDir = 0;
      }

      cursor->SetDirection(static_cast<CursorShape::Direction>(currentDir));
      cntr = 0;
   }
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
