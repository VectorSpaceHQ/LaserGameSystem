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


// MaxSize is 4096  -- resolution of the laser
//   divided by 2 for positive and negative axes (grow from 0 in the center)
//   subtract one to ensure we don't go one past the edge
const int Calibrate::MaxSize = 1024;
const int Calibrate::StepSize = 100;


Calibrate::Calibrate(Canvas& _canvas
         //GamePad& _gamePad1,
         //GamePad& _gamePad2
         ):
   Program(_canvas/*, _gamePad1, _gamePad2*/),
//   border(canvas.width - 2, canvas.height -2),
   triangle(3, 3),
//   square(4),
//   circle(16, 2),
   star(5, 2, 1),
   sprite1(&triangle),
   sprite2(&star),
   currShape(0)
{
//   sprite2.AddShape(&star);
//   sprite1.AddShape(&circle);
}


void Calibrate::Init()
{
   sprite1.Scale(125);
   sprite2.Scale(125);
}


void Calibrate::Start()
{
   // Only add the shape to the canvas once at startup
   // Since the canvas maintains a pointer, we can update our vertices all day long,
   // and the canvas will pickup the changes.
//   canvas.AddObject(&border);
   canvas.AddObject(&sprite1);
   canvas.AddObject(&sprite2);

   int         xVel;
   int         yVel;

   xVel = -StepSize / (rand() %4 + 2);
   yVel = StepSize / (rand() %4 + 2);
   sprite1.SetVelocity(xVel, yVel, 0);

   xVel = -StepSize / (rand() %4 + 2);
   yVel = StepSize / (rand() %4 + 2);
   sprite2.SetVelocity(xVel, yVel, 0);
}


// Currently is draws an expanding/shrinking square.
// When the square reaches the limits of the display, it starts to shrink.
void Calibrate::Run()
{
   sprite1.Move();
   sprite2.Move();

   CheckSprite(sprite1);
   CheckSprite(sprite2);
}


void Calibrate::CheckSprite(Sprite& sprite)
{
   bool collision = false;

   if(sprite.CheckTop(canvas.top))
   {
      collision = true;
      int yVel = -StepSize / (rand() % 4 + 2);
      sprite.SetVelocity(sprite.velocity(CoordX), yVel, 0);
   }
   else if(sprite.CheckBottom(canvas.bottom))
   {
      collision = true;
      int yVel = StepSize / (rand() % 4 + 2);
      sprite.SetVelocity(sprite.velocity(CoordX), yVel, 0);
   }
   else if(sprite.CheckLeft(canvas.left))
   {
      collision = true;
      int xVel = StepSize / (rand() % 4 + 2);
      sprite.SetVelocity(xVel, sprite.velocity(CoordY), 0);
   }
   else if(sprite.CheckRight(canvas.right))
   {
      collision = true;
      int xVel = -StepSize / (rand() % 4 + 2);
      sprite.SetVelocity(xVel, sprite.velocity(CoordY), 0);
   }

   if(collision)
   {
      currShape++;

      if(currShape >= sprite.NumShapes())
      {
         currShape = 0;
      }

      sprite.SelectShape(currShape);
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
