/*
 * Calibrate.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#include "Calibrate.h"
#include "GameSystemEvents.h"
#include "Program.h"
#include "Shape.h"
#include "CommonShapes.h"
#include "Sprite.h"


// MaxSize is 4096  -- resolution of the laser
//   divided by 2 for positive and negative axes (grow from 0 in the center)
//   subtract one to ensure we don't go one past the edge
const int Calibrate::MaxSize = 1024;
const int Calibrate::StepSize = 48;


Calibrate::Calibrate(Canvas& _canvas
         //GamePad& _gamePad1,
         //GamePad& _gamePad2
         ):
   Program(_canvas/*, _gamePad1, _gamePad2*/),
   triangle(3, 2),
   square(4),
   circle(32, 2),
   star(5, 2, 1),
   mySprite(&triangle),
   scale(1),
   shrinkGrow(1),
   currShape(0)
{
   mySprite.AddShape(&square);
   mySprite.AddShape(&circle);
   mySprite.AddShape(&star);
}


void Calibrate::Init()
{
   triangle.Scale(1, -1, 1);
   triangle.Backup();
   star.Scale(1, -1, 1);
   star.Backup();
}


void Calibrate::Start()
{
   // Only add the shape to the canvas once at startup
   // Since the canvas maintains a pointer, we can update our vertices all day long,
   // and the canvas will pickup the changes.
   canvas.AddObject(&mySprite);
}


// Currently is draws an expanding/shrinking square.
// When the square reaches the limits of the display, it starts to shrink.
void Calibrate::Run()
{
   // Add (12 *  1) to scale if growing,
   //  or (12 * -1) to scale if shrinking.
   scale += StepSize * shrinkGrow;

   if(scale >= MaxSize)    // If scale is bigger than our max size, then
   {
      scale = MaxSize;     // Set to max size
      shrinkGrow *= -1;    // Start shrinking
   }
   else if(scale <= 1)     // If scale is smaller than 1
   {
      scale = 1;           // Set to 1
      shrinkGrow *= -1;    // Start growing

      currShape++;

      if(currShape >= mySprite.NumShapes())
      {
         currShape = 0;
      }

      mySprite.SelectShape(currShape);
   }
}


void Calibrate::Draw()
{
   // Restore our original shape
   mySprite.Restore();

   // Then scale the shape
   mySprite.Scale(scale);
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
