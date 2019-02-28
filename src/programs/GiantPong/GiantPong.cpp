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
#include "NumeralShape.h"
#include "Program.h"


const float GiantPong::PaddleScalePercent = 0.10;
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
   ball(),
   leftScore(),
   rightScore()
{
}

void GiantPong::InitGamePlay()
{
   uint16_t paddleHeight = canvas.height * PaddleScalePercent;
   int16_t  paddleXPos = canvas.width / 9;
   uint16_t ballRadius = canvas.width * BallScalePercent;

   border = new Shape(7);
   border->vertices <<
            canvas.left, canvas.top, 0, 0,
            canvas.right, canvas.top, 0, 1,
            canvas.right, canvas.bottom, 0, 1,
            canvas.left, canvas.bottom, 0, 1,
            canvas.left, canvas.top, 0, 1,
            0, canvas.top, 0, 0,
            0, canvas.bottom, 0, 1;

   leftPaddle = new PongPaddle(40, paddleHeight, canvas.left + paddleXPos);
   rightPaddle = new PongPaddle(40, paddleHeight, canvas.right - paddleXPos);

   ball = new Ball(ballRadius);
   leftScore = new NumeralShape();
   rightScore = new NumeralShape();
   leftScore->Scale(150);
   rightScore->Scale(150);

   rightScore->SetValue(9);
   int32_t pos = (canvas.width / 4);
   leftScore->Move(0 - pos, canvas.top - 300, 0);
   rightScore->Move(pos, canvas.top - 300, 0);

   // Set the limits of the ball
   Coordinate lowerLimit((canvas.left + ballRadius), (canvas.bottom + ballRadius), 0, 0);
   Coordinate upperLimit((canvas.right - ballRadius), (canvas.top - ballRadius), 0, 0);
   ball->sprite->SetLimits(lowerLimit, upperLimit);

   // Set the limits of our left paddle
   lowerLimit << (canvas.left + paddleXPos), (canvas.bottom + (paddleHeight /2)), 0, 0;
   upperLimit << (canvas.left + paddleXPos), (canvas.top - (paddleHeight /2)), 0, 0;
   leftPaddle->sprite->SetLimits(lowerLimit, upperLimit);

   // Set the limits of our left paddle
   lowerLimit << (canvas.right - paddleXPos), (canvas.bottom + (paddleHeight /2)), 0, 0;
   upperLimit << (canvas.right - paddleXPos), (canvas.top - (paddleHeight /2)), 0, 0;
   rightPaddle->sprite->SetLimits(lowerLimit, upperLimit);
}


void GiantPong::StartGameReady()
{
   canvas.Clear();
   canvas.AddObject(border);
   canvas.AddObject(rightPaddle->sprite);
   canvas.AddObject(leftPaddle->sprite);
   canvas.AddObject(leftScore);
   canvas.AddObject(rightScore);
}


void GiantPong::StartGamePlay()
{
   canvas.AddObject(ball->sprite);
   int yVel = BallStepSize;
   int xVel = BallStepSize / 2;
   ball->sprite->SetVelocity(xVel, yVel, 0);

   leftPaddle->sprite->SetVelocity(BallStepSize, BallStepSize, 0);
   rightPaddle->sprite->SetVelocity(-BallStepSize, -BallStepSize, 0);
}


void GiantPong::PlayGame()
{
   static int frameCntr = 0;
   static int numeralCntr = 0;

   ball->sprite->Move();
   leftPaddle->sprite->Move();
   rightPaddle->sprite->Move();

   if(frameCntr++ >= 30)
   {
      numeralCntr++;

      if(numeralCntr > 9)
      {
         numeralCntr = 0;
      }

      leftScore->SetValue(numeralCntr);
      rightScore->SetValue(9 - numeralCntr);
      frameCntr = 0;
   }

   if(ball->sprite->CheckTop(canvas.top) < 1)
   {
      int yVel = -ball->sprite->velocity(CoordY);
      ball->sprite->SetVelocity(ball->sprite->velocity(CoordX), yVel, 0);
   }
   else if(ball->sprite->CheckBottom(canvas.bottom) < 1)
   {
      int yVel = -ball->sprite->velocity(CoordY);
      ball->sprite->SetVelocity(ball->sprite->velocity(CoordX), yVel, 0);
   }
   else if(ball->sprite->CheckLeft(canvas.left) < 1)
   {
      int xVel = -ball->sprite->velocity(CoordX);
      ball->sprite->SetVelocity(xVel, ball->sprite->velocity(CoordY), 0);
   }
   else if(ball->sprite->CheckRight(canvas.right) < 1)
   {
      int xVel = -ball->sprite->velocity(CoordX);
      ball->sprite->SetVelocity(xVel, ball->sprite->velocity(CoordY), 0);
   }

   if(leftPaddle->sprite->CheckTop(canvas.top) < 1)
   {
      leftPaddle->sprite->SetVelocity(0, -BallStepSize, 0);
   }
   else if(leftPaddle->sprite->CheckBottom(canvas.bottom) < 1)
   {
      leftPaddle->sprite->SetVelocity(0, BallStepSize, 0);
   }

   if(rightPaddle->sprite->CheckTop(canvas.top) < 1)
   {
      rightPaddle->sprite->SetVelocity(0, -BallStepSize, 0);
   }
   else if(rightPaddle->sprite->CheckBottom(canvas.bottom) < 1)
   {
      rightPaddle->sprite->SetVelocity(0, BallStepSize, 0);
   }
}


void GiantPong::Stop()
{
   canvas.Clear();
   delete(border);
   delete(leftPaddle);
   delete(rightPaddle);
   delete(ball);
   delete(leftScore);
   delete(rightScore);
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
         if(cntr++ >= 0.5 * 30)
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
