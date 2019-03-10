/*
 * GiantPong.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#include <functional>
#include <stdint.h>
#include <stdlib.h>

#include "Canvas.h"
#include "CommonShapes.h"
#include "FiniteStateMachine.h"
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


Ball::Ball(uint16_t _radius):
   radius(_radius)
{
   shape = new Polygon(8, radius);
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
   StateSplashScreen("PongSplashScreen",
                     std::bind(&GiantPong::SplashScreenEnter, this),
                     std::bind(&GiantPong::SplashScreenHandle, this, std::placeholders::_1, std::placeholders::_2),
                     std::bind(&GiantPong::SplashScreenExit, this)),
   StateGameReady("PongReady",
                  std::bind(&GiantPong::GameReadyEnter, this),
                  std::bind(&GiantPong::GameReadyHandle, this, std::placeholders::_1, std::placeholders::_2),
                  nullptr),
   StateGamePlay("PongPlay",
                 std::bind(&GiantPong::StartGamePlay, this),
                 std::bind(&GiantPong::GamePlayHandle, this, std::placeholders::_1, std::placeholders::_2),
                 nullptr),
   StateFinished("PongFinished",
                 nullptr,
                 std::bind(&GiantPong::FinishedHandle, this, std::placeholders::_1, std::placeholders::_2),
                 nullptr),
   fsm(StateSplashScreen),
   border(),
   leftPaddle(),
   rightPaddle(),
   ball(),
   leftScore(),
   rightScore(),
   splash(),
   frameCntr()
{
}


void GiantPong::InitGamePlay()
{
   uint16_t paddleHeight = canvas.height * PaddleScalePercent;
   int16_t  paddleXPos = canvas.width / 9;
   uint16_t ballRadius = canvas.width * BallScalePercent;

   // First, clear the canvas
   canvas.Clear();

   frameCntr = 0;
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

   // Now Fill out the canvas
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
      if((leftPaddle->sprite->position(CoordX) - ball->sprite->position(CoordX)) > ball->radius)
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
      if((ball->sprite->position(CoordX) - rightPaddle->sprite->position(CoordX)) > ball->radius)
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


void GiantPong::TearDownGamePlay()
{
   canvas.Clear();
   delete(border);
   delete(leftPaddle);
   delete(rightPaddle);
   delete(ball);
   delete(leftScore);
   delete(rightScore);
}


void GiantPong::HandleEvent(GameSystem::Events event)
{
   switch(event)
   {
      case GameSystem::EVENT_PROGRAM_INIT:
         break;

      case GameSystem::EVENT_PROGRAM_START:
         fsm.Start();
         break;

      case GameSystem::EVENT_PROGRAM_RUN:
         fsm.HandleEvent(event, nullptr);
         break;

      case GameSystem::EVENT_PROGRAM_STOP:
         while(fsm.HandleEvent(event, nullptr))
         {
            //
         }
         break;

      default:
         break;
   }
}


void GiantPong::GameReadyEnter()
{
   frameCntr = 0;
   InitGamePlay();
}


bool GiantPong::GameReadyHandle(GameSystem::Events e, void* data)
{
   bool handled  = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         if(frameCntr++ >= 0.5 * 30)
         {
            fsm.Transition(StateGamePlay);
         }

         handled = true;
         break;

      case GameSystem::EVENT_PROGRAM_STOP:
         TearDownGamePlay();
         fsm.Transition(StateFinished);
         handled = true;
         break;

      default:
         break;
   }

   return handled;
}


bool GiantPong::GamePlayHandle(GameSystem::Events e, void* data)
{
   bool  handled = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         PlayGame();
         break;

      case GameSystem::EVENT_PROGRAM_STOP:
         TearDownGamePlay();
         fsm.Transition(StateFinished);
         handled = true;
         break;

      default:
         break;
   }

   return handled;
}


bool GiantPong::FinishedHandle(GameSystem::Events e, void* data)
{
   bool  handled = false;
   // Do nothing!
   return handled;
}


bool GiantPong::SplashScreenHandle(GameSystem::Events e, void* data)
{
   bool  handled = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         if(frameCntr++ >= 3 * 30)
         {
            fsm.Transition(StateGameReady);
         }

         handled = true;
         break;

      case GameSystem::EVENT_PROGRAM_STOP:
         fsm.Transition(StateFinished);
         handled = true;
         break;

      default:
         break;
   }

   return handled;
}


void GiantPong::SplashScreenExit()
{
   if(splash)
   {
      delete splash;
   }

   if(border)
   {
      delete border;
   }
}


void GiantPong::SplashScreenEnter()
{
   canvas.Clear();
   frameCntr = 0;

   border = new Shape(5);
   border->vertices <<
            canvas.left, canvas.top, 0, 0,
            canvas.right, canvas.top, 0, 1,
            canvas.right, canvas.bottom, 0, 1,
            canvas.left, canvas.bottom, 0, 1,
            canvas.left, canvas.top, 0, 1;

   splash = new Shape(166);
   splash->vertices <<
            -824, -53, 0, 0,
            -859, -104, 0, 1,
            -873, -101, 0, 1,
            -886, -96, 0, 1,
            -899, -99, 0, 1,
            -960, -299, 0, 1,
            -1064, -423, 0, 1,
            -1099, -431, 0, 1,
            -1188, -405, 0, 1,
            -1273, -376, 0, 1,
            -1363, -247, 0, 1,
            -1392, -28, 0, 1,
            -1346, 266, 0, 1,
            -1214, 424, 0, 1,
            -1198, 425, 0, 1,
            -1076, 393, 0, 1,
            -972, 318, 0, 1,
            -943, 234, 0, 1,
            -932, 171, 0, 1,
            -924, 130, 0, 1,
            -934, 99, 0, 1,
            -955, 78, 0, 1,
            -1033, 92, 0, 1,
            -1111, 123, 0, 1,
            -1126, 170, 0, 1,
            -1121, 182, 0, 1,
            -1116, 196, 0, 1,
            -1132, 267, 0, 1,
            -1192, 153, 0, 1,
            -1216, -83, 0, 1,
            -1163, -301, 0, 1,
            -1120, -246, 0, 1,
            -1087, -128, 0, 1,
            -1148, -97, 0, 1,
            -1187, -71, 0, 1,
            -1177, -29, 0, 1,
            -1148, 7, 0, 1,
            -1104, 16, 0, 1,
            -1058, 18, 0, 1,
            -1003, 35, 0, 1,
            -956, 47, 0, 1,
            -945, 46, 0, 1,
            -872, 1, 0, 1,
            -824, -53, 0, 1,
            -558, 377, 0, 0,
            -563, 358, 0, 1,
            -568, 343, 0, 1,
            -580, 281, 0, 1,
            -580, -332, 0, 1,
            -574, -354, 0, 1,
            -568, -369, 0, 1,
            -592, -438, 0, 1,
            -662, -425, 0, 1,
            -736, -400, 0, 1,
            -758, -365, 0, 1,
            -754, -356, 0, 1,
            -750, -339, 0, 1,
            -750, 365, 0, 1,
            -754, 377, 0, 1,
            -757, 390, 0, 1,
            -720, 422, 0, 1,
            -674, 422, 0, 1,
            -602, 411, 0, 1,
            -558, 377, 0, 1,
            147, -352, 0, 0,
            143, -395, 0, 1,
            135, -422, 0, 1,
            118, -425, 0, 1,
            36, -408, 0, 1,
            -36, -370, 0, 1,
            -52, -310, 0, 1,
            -77, -199, 0, 1,
            -188, -227, 0, 1,
            -283, -264, 0, 1,
            -323, -370, 0, 1,
            -330, -396, 0, 1,
            -347, -417, 0, 1,
            -356, -419, 0, 1,
            -437, -394, 0, 1,
            -495, -361, 0, 1,
            -476, -292, 0, 1,
            -439, -194, 0, 1,
            -460, -152, 0, 1,
            -459, -141, 0, 1,
            -398, -98, 0, 1,
            -269, 343, 0, 1,
            -268, 387, 0, 1,
            -262, 421, 0, 1,
            -238, 426, 0, 1,
            -104, 402, 0, 1,
            0, 359, 0, 1,
            45, 26, 0, 1,
            147, -352, 0, 1,
            -114, -48, 0, 0,
            -130, 35, 0, 1,
            -145, 174, 0, 1,
            -192, 38, 0, 1,
            -223, -76, 0, 1,
            -114, -48, 0, 1,
            793, 377, 0, 0,
            789, 356, 0, 1,
            780, 329, 0, 1,
            780, -330, 0, 1,
            785, -367, 0, 1,
            773, -427, 0, 1,
            692, -435, 0, 1,
            609, -416, 0, 1,
            542, -376, 0, 1,
            539, -333, 0, 1,
            409, -8, 0, 1,
            409, -304, 0, 1,
            416, -325, 0, 1,
            425, -343, 0, 1,
            430, -373, 0, 1,
            394, -413, 0, 1,
            295, -393, 0, 1,
            227, -362, 0, 1,
            227, -321, 0, 1,
            239, -290, 0, 1,
            239, 336, 0, 1,
            236, 354, 0, 1,
            235, 373, 0, 1,
            274, 419, 0, 1,
            296, 421, 0, 1,
            376, 411, 0, 1,
            450, 377, 0, 1,
            523, 194, 0, 1,
            609, -60, 0, 1,
            609, 333, 0, 1,
            605, 355, 0, 1,
            601, 378, 0, 1,
            603, 389, 0, 1,
            641, 414, 0, 1,
            691, 419, 0, 1,
            746, 408, 0, 1,
            793, 377, 0, 1,
            1351, 257, 0, 0,
            1329, 263, 0, 1,
            1306, 268, 0, 1,
            1203, 240, 0, 1,
            1203, -286, 0, 1,
            1217, -349, 0, 1,
            1215, -387, 0, 1,
            1196, -426, 0, 1,
            1186, -427, 0, 1,
            1094, -414, 0, 1,
            1016, -385, 0, 1,
            1017, -337, 0, 1,
            1030, -299, 0, 1,
            1030, 196, 0, 1,
            959, 178, 0, 1,
            942, 169, 0, 1,
            923, 164, 0, 1,
            860, 223, 0, 1,
            825, 296, 0, 1,
            872, 331, 0, 1,
            898, 332, 0, 1,
            923, 332, 0, 1,
            1271, 421, 0, 1,
            1300, 433, 0, 1,
            1329, 438, 0, 1,
            1367, 416, 0, 1,
            1382, 371, 0, 1,
            1392, 303, 0, 1,
            1386, 269, 0, 1,
            1351, 257, 0, 1;

   canvas.AddObject(border);
   canvas.AddObject(splash);
}
