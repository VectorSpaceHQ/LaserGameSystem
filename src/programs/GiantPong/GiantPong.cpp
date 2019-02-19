/*
 * GiantPong.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#include <stdint.h>
#include "Canvas.h"
#include "CommonShapes.h"
#include "GameSystemEvents.h"
#include "GiantPong.h"
#include "Program.h"


const float GiantPong::PaddleScalePercent = 0.08;
const float GiantPong::BallScalePercent = 0.01;
const float GiantPong::BallStepSize = 80;


PongPaddle::PongPaddle(uint16_t width, uint16_t height, int16_t xPos)
{
   shape = new Rectangle(width, height);
   sprite = new Sprite(shape);
   sprite->Move(xPos, 0);
}


PongPaddle::~PongPaddle()
{
   delete(sprite);
   delete(shape);
}


Ball::Ball(uint16_t width)
{
   shape = new Polygon(8, width);
   sprite = new Sprite(shape);
}


Ball::~Ball()
{
   delete(sprite);
   delete(shape);
}


GiantPong::GiantPong(Canvas& _display
         //GamePad& _gamePad1,
         //GamePad& _gamePad2
         ):
   Program(_display/*, _gamePad1, _gamePad2*/),
   state(StateSetupGamePlay),
   border(),
   leftPaddle(),
   rightPaddle(),
   ball()
{
}


void GiantPong::InitGamePlay()
{
   border = new Rectangle(canvas.width, canvas.height);
   leftPaddle = new PongPaddle(40,
                               (canvas.height * PaddleScalePercent),
                               canvas.left + (canvas.width / 9));

   rightPaddle = new PongPaddle(40,
                                (canvas.height * PaddleScalePercent),
                                canvas.right - (canvas.width / 9));

   ball = new Ball(canvas.width * BallScalePercent);
}


void GiantPong::StartGameReady()
{
   canvas.Clear();
   canvas.AddObject(border);
   canvas.AddObject(leftPaddle->sprite);
   canvas.AddObject(rightPaddle->sprite);
}


void GiantPong::StartGamePlay()
{
   canvas.AddObject(ball->sprite);
   int yVel = BallStepSize;
   int xVel = BallStepSize / 2;
   ball->sprite->SetVelocity(xVel, yVel, 0);
}


void GiantPong::PlayGame()
{
   ball->sprite->Move();

   if(ball->sprite->CheckTop(canvas.top))
   {
      int yVel = -ball->sprite->velocity(CoordY);
      ball->sprite->SetVelocity(ball->sprite->velocity(CoordX), yVel, 0);
      ball->sprite->Move(0, -BallStepSize);
   }
   else if(ball->sprite->CheckBottom(canvas.bottom))
   {
      int yVel = -ball->sprite->velocity(CoordY);
      ball->sprite->SetVelocity(ball->sprite->velocity(CoordX), yVel, 0);
      ball->sprite->Move(0, BallStepSize);
   }
   else if(ball->sprite->CheckLeft(canvas.left))
   {
      int xVel = -ball->sprite->velocity(CoordX);
      ball->sprite->SetVelocity(xVel, ball->sprite->velocity(CoordY), 0);
      ball->sprite->Move(BallStepSize, 0);
   }
   else if(ball->sprite->CheckRight(canvas.right))
   {
      int xVel = -ball->sprite->velocity(CoordX);
      ball->sprite->SetVelocity(xVel, ball->sprite->velocity(CoordY), 0);
      ball->sprite->Move(-BallStepSize, 0);
   }
}


void GiantPong::Stop()
{
   canvas.Clear();
   delete(border);
   delete(leftPaddle);
   delete(rightPaddle);
   delete(ball);
}


void GiantPong::Run()
{
   static uint16_t   cntr = 0;

   switch(state)
   {
      case StateSetupSplash:
      case StateSplash:
      case StateStopSplash:
         break;

      default:
      case StateSetupGamePlay:
         InitGamePlay();
         StartGameReady();
         state = StateGameReady;
         break;

      case StateGameReady:
         if(cntr++ >= 1.5 * 30)
         {
            cntr = 0;
            StartGamePlay();
            state = StateGamePlay;
         }
         break;

      case StateGamePlay:
         PlayGame();
         break;

      case StateGameOver:
         break;

      case StateStopGame:
         break;

   }
}


void GiantPong::Draw()
{
}


void GiantPong::HandleEvent(GameSystem::Events event)
{
   switch(event)
   {
      case GameSystem::EVENT_PROGRAM_INIT:
         break;

      case GameSystem::EVENT_PROGRAM_START:
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
