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
   border()
{
}


void Calibrate::Init()
{
   cursor = new CursorShape();
   border = new Rectangle(canvas.width, canvas.height);
}


void Calibrate::Start()
{
   cursor->SetPosition(0, 0, 0);
   cursor->Scale(150);
   cursor->SetDirection(CursorShape::Center);
   canvas.AddObject(cursor);
   canvas.AddObject(border);
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
   // TODO:
   //   1) Read left gamepad joystick adjust cursor, along with shape
   //   2) Read right gamepad joystick adjust selected corner
}


void Calibrate::Draw()
{
}


void Calibrate::HandleEvent(GameSystem::Events event)
{
   switch(event)
   {
      case GameSystem::EVENT_PROGRAM_INIT:
         Init();
         break;

      case GameSystem::EVENT_PROGRAM_START:
         Start();
         break;

      case GameSystem::EVENT_PROGRAM_RUN:
         Run();
         break;

      case GameSystem::EVENT_PROGRAM_DRAW:
         Draw();
         break;

      default:
         break;
   }
}
