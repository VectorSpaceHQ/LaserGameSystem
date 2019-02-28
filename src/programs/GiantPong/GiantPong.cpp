/*
 * GiantPong.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#include <stdint.h>
#include <stdlib.h>

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
   int      ballYVel;
   int      ballXVel;
   int32_t  pos = (canvas.width / 4);

   if(rand() % 1)
   {
      ball->sprite->Move(0, pos);
   }
   else
   {
      ball->sprite->Move(0, -pos);
   }

   if(rand() %1)
   {
      ballYVel = BallStepSize;
   }
   else
   {
      ballYVel = -BallStepSize;
   }

   ballXVel = BallStepSize / (rand() % 2 + 1);
   ball->sprite->SetVelocity(ballXVel, ballYVel, 0);
   canvas.AddObject(ball->sprite);
}


void GiantPong::PlayGame()
{
   int16_t     overlap;

   // Match the paddles to the ball
   leftPaddle->sprite->velocity = ball->sprite->velocity;
   rightPaddle->sprite->velocity = ball->sprite->velocity;

   // Move the sprites
   ball->sprite->Move();
   leftPaddle->sprite->Move();
   rightPaddle->sprite->Move();

   // If the ball is moving left...
   if(ball->sprite->velocity(CoordX) < 1)
   {
      // And the ball is not already past the paddle
      if(ball->sprite->position(CoordX) > leftPaddle->sprite->position(CoordX))
      {
         // Check if the left paddle and ball have collided
         overlap = leftPaddle->sprite->CheckRight(*ball->sprite);

         if(overlap < 1)
         {
            int xVel = -ball->sprite->velocity(CoordX);
            ball->sprite->SetVelocity(xVel, ball->sprite->velocity(CoordY), 0);
            ball->sprite->Move(-overlap, 0);  // Prevent from showing the overlap
         }
      }
      else
      {
         // Check to see if the ball has hit the left side
         overlap = ball->sprite->CheckLeft(canvas.left);

         if(overlap < 1)
         {
            int xVel = -ball->sprite->velocity(CoordX);
            ball->sprite->SetVelocity(xVel, ball->sprite->velocity(CoordY), 0);
         }
      }
   }
   else  // The ball is moving right
   {
      // And the ball is not already past the right paddle
      if(ball->sprite->position(CoordX) < rightPaddle->sprite->position(CoordX))
      {
         // Check if the right paddle and ball have collided
         overlap = rightPaddle->sprite->CheckLeft(*ball->sprite);

         if(rightPaddle->sprite->CheckLeft(*ball->sprite) < 1)
         {
            int xVel = -ball->sprite->velocity(CoordX);
            ball->sprite->SetVelocity(xVel, ball->sprite->velocity(CoordY), 0);
            ball->sprite->Move(overlap, 0);  // Prevent from showing the overlap
         }
      }
      else
      {
         // Check to see if the ball has hit the left side
         overlap = ball->sprite->CheckRight(canvas.right);

         if(overlap < 1)
         {
            int xVel = -ball->sprite->velocity(CoordX);
            ball->sprite->SetVelocity(xVel, ball->sprite->velocity(CoordY), 0);
         }
      }
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
