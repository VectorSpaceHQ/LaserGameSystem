/*
 * Test.cpp
 *
 *  Created on: Feb 18, 2019
 *      Author: athiessen
 */

#include "CanvasObject.h"
#include "CommonShapes.h"
#include "GamePad.h"
#include "GameSystemEvents.h"
#include "Program.h"
#include "Shape.h"
#include "Sprite.h"
#include "TestProgram.h"


// MaxSize is 4096  -- resolution of the laser
//   divided by 2 for positive and negative axes (grow from 0 in the center)
//   subtract one to ensure we don't go one past the edge
const int TestProgram::MaxSize = 1024;
const int TestProgram::StepSize = 100;


TestProgram::TestProgram(Canvas&                _canvas,
                         GameSystem::GamePad&   _gamePad1,
                         GameSystem::GamePad&   _gamePad2):
   Program(_canvas, _gamePad1, _gamePad2),
   shapePtrs(),
   spritePtrs(),
   currShape(0)
{
}


void TestProgram::Init()
{
   shapePtrs[0] = new Rectangle(canvas.width, canvas.height);
   shapePtrs[1] = new Polygon(3, 4);   // Triangle
   shapePtrs[2] = new Star(5, 4, 2);
   shapePtrs[3] = new Polygon(16, 2);  // Circle
   shapePtrs[4] = new Square(4);

   spritePtrs[0] = new Sprite(shapePtrs[1]);
   spritePtrs[1] = new Sprite(shapePtrs[2]);
   spritePtrs[2] = new Sprite(shapePtrs[3]);
   spritePtrs[3] = new Sprite(shapePtrs[4]);

   spritePtrs[0]->Scale(60);
   spritePtrs[1]->Scale(60);
   spritePtrs[2]->Scale(60);
   spritePtrs[3]->Scale(60);
}


void TestProgram::Start()
{
   // Only add the shape to the canvas once at startup
   // Since the canvas maintains a pointer, we can update our vertices all day long,
   // and the canvas will pickup the changes.
   canvas.AddObject(shapePtrs[0]);
   canvas.AddObject(spritePtrs[0]);
   canvas.AddObject(spritePtrs[1]);
   canvas.AddObject(spritePtrs[2]);
   canvas.AddObject(spritePtrs[3]);

   int         xVel;
   int         yVel;

   xVel = -StepSize / (rand() %4 + 2);
   yVel = StepSize / (rand() %4 + 2);
   spritePtrs[0]->SetVelocity(xVel, yVel, 0);

   xVel = -StepSize / (rand() %4 + 2);
   yVel = StepSize / (rand() %4 + 2);
   spritePtrs[1]->SetVelocity(xVel, yVel, 0);

   xVel = StepSize / (rand() %4 + 2);
   yVel = -StepSize / (rand() %4 + 2);
   spritePtrs[2]->SetVelocity(xVel, yVel, 0);

   xVel = StepSize / (rand() %4 + 2);
   yVel = -StepSize / (rand() %4 + 2);
   spritePtrs[3]->SetVelocity(xVel, yVel, 0);
}


void TestProgram::Stop()
{
   canvas.Clear();

   for(uint32_t cntr = 0; cntr < sizeof(spritePtrs) / sizeof(Sprite*); cntr++)
   {
      spritePtrs[cntr]->ClearShapes();
      delete(spritePtrs[cntr]);
   }

   for(uint32_t cntr = 0; cntr < sizeof(shapePtrs) / sizeof(Shape*); cntr++)
   {
      delete(shapePtrs[cntr]);
   }
}


// Currently is draws an expanding/shrinking square.
// When the square reaches the limits of the display, it starts to shrink.
void TestProgram::Run()
{
   for(uint32_t cntr = 0; cntr < sizeof(spritePtrs) / sizeof(Sprite*); cntr++)
   {
      spritePtrs[cntr]->Move();
      CheckSprite(spritePtrs[cntr]);
   }
}


void TestProgram::CheckSprite(Sprite* sprite)
{
   bool collision = false;

   if(sprite->CheckTop(canvas.top))
   {
      collision = true;
      int yVel = -StepSize / (rand() % 4 + 2);
      sprite->SetVelocity(sprite->velocity(CoordX), yVel, 0);
      sprite->Move(0, -StepSize);
   }
   else if(sprite->CheckBottom(canvas.bottom))
   {
      collision = true;
      int yVel = StepSize / (rand() % 4 + 2);
      sprite->SetVelocity(sprite->velocity(CoordX), yVel, 0);
      sprite->Move(0, StepSize);
   }
   else if(sprite->CheckLeft(canvas.left))
   {
      collision = true;
      int xVel = StepSize / (rand() % 4 + 2);
      sprite->SetVelocity(xVel, sprite->velocity(CoordY), 0);
      sprite->Move(StepSize, 0);
   }
   else if(sprite->CheckRight(canvas.right))
   {
      collision = true;
      int xVel = -StepSize / (rand() % 4 + 2);
      sprite->SetVelocity(xVel, sprite->velocity(CoordY), 0);
      sprite->Move(-StepSize, 0);
   }

   if(collision)
   {
      currShape++;

      if(currShape >= sprite->NumShapes())
      {
         currShape = 0;
      }

      sprite->SelectShape(currShape);
   }
}


void TestProgram::Draw()
{
}


void TestProgram::HandleEvent(GameSystem::Events event, void* data)
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
