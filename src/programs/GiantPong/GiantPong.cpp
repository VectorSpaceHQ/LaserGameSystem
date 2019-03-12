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


const float    Player::PaddleScalePercent       = 0.10;
const float    GiantPong::BallScalePercent      = 0.01;
const float    GiantPong::BallStepSize          = 80;
const uint16_t GiantPong::SplashTimeout         = 5;
const uint16_t GiantPong::DemoTimeout           = 10;
const uint8_t  GiantPong::MaxScore              = 10;



Ball::Ball(uint16_t _radius):
   radius(_radius),
   shape(),
   sprite()
{
}


void Ball::Init(Canvas& canvas)
{
   if(shape)
   {
      delete shape;
   }

   if(sprite)
   {
      delete sprite;
   }

   shape = new Polygon(8, radius);
   sprite = new Sprite(shape);

   // Set the limits of the ball
   Coordinate lowerLimit((canvas.left + radius), (canvas.bottom + radius), 0, 0);
   Coordinate upperLimit((canvas.right - radius), (canvas.top - radius), 0, 0);
   sprite->SetLimits(lowerLimit, upperLimit);
}


Ball::~Ball()
{
   delete sprite;
   delete shape;
}


Player::Player(PlayerId _id, GameSystem::GamePad& _gamePad):
   id(_id),
   computerPlays(true),
   gamePad(_gamePad),
   lastAxis(0),
   shape(),
   sprite(),
   score()
{
}


Player::~Player()
{
   if(shape)
   {
      delete shape;
   }

   if(sprite)
   {
      delete sprite;
   }

   if(score)
   {
      delete score;
   }
}


void Player::Init(Canvas& canvas)
{
   uint16_t paddleHeight = canvas.height * PaddleScalePercent;
   int32_t  paddleXPos = canvas.width / 9;
   int32_t  scorePos = canvas.width / 4;

   if(shape)
   {
      delete shape;
   }

   if(sprite)
   {
      delete sprite;
   }

   if(score)
   {
      delete score;
   }

   shape = new Rectangle(40, paddleHeight);
   sprite = new Sprite(shape);
   score = new NumeralShape();
   score->Scale(150);

   if(id == PLAYER_LEFT)
   {
      // Set the limits of the paddle
      Coordinate lowerLimit((canvas.left + paddleXPos), (canvas.bottom + (paddleHeight /2)), 0, 0);
      Coordinate upperLimit((canvas.left + paddleXPos), (canvas.top - (paddleHeight /2)), 0, 0);

      sprite->Move(canvas.left + paddleXPos, 0);
      sprite->SetLimits(lowerLimit, upperLimit);
      score->Move(0 - scorePos, canvas.top - 300, 0);

      computerPlays = false;
   }
   else
   {
      Coordinate lowerLimit((canvas.right - paddleXPos), (canvas.bottom + (paddleHeight /2)), 0, 0);
      Coordinate upperLimit((canvas.right - paddleXPos), (canvas.top - (paddleHeight /2)), 0, 0);

      sprite->Move(canvas.right - paddleXPos, 0);
      sprite->SetLimits(lowerLimit, upperLimit);
      score->Move(scorePos, canvas.top - 300, 0);
   }

   lastAxis = gamePad.GetAxis(GameSystem::AXIS_ID_LEFT_X);
}


void Player::Score()
{
   if(score)
   {
      score->SetValue(score->value + 1);
   }
}


uint8_t Player::GetScore()
{
   if(score)
   {
      return score->value;
   }
   else
   {
      return 0;
   }
}


void Player::Play(Sprite& ball)
{
   if(computerPlays)
   {
      sprite->MoveTo(sprite->position(CoordX), ball.position(CoordY) + ((rand() % 1000) - 500));
   }
   else
   {
      int32_t  currAxis = gamePad.GetAxis(GameSystem::AXIS_ID_LEFT_X);

      // Move the difference between the two since our last poll
      sprite->Move(0, (currAxis - lastAxis) * 5);
      lastAxis = currAxis;
   }
}


CoordType Player::GetPosition(CoordPositions pos)
{
   if(sprite)
   {
      return sprite->position(pos);
   }
   else
   {
      return 0;
   }
}


int16_t Player::CheckCollision(Sprite& ball)
{
   int16_t  overlap = 1;   // No collision detected

   if(sprite)
   {
      if(id == PLAYER_LEFT)
      {
         overlap = sprite->CheckRight(ball);
      }
      else
      {
         overlap = sprite->CheckLeft(ball);
      }
   }

   return overlap;
}


GiantPong::GiantPong(Canvas&              _display,
                     GameSystem::GamePad& _gamePad1,
                     GameSystem::GamePad& _gamePad2):
   Program(_display, _gamePad1, _gamePad2),
   StateSplashScreen("PongSplashScreen",
                     std::bind(&GiantPong::SplashScreenEnter, this),
                     std::bind(&GiantPong::SplashScreenHandle, this, std::placeholders::_1, std::placeholders::_2),
                     std::bind(&GiantPong::SplashScreenExit, this)),
   StateGameInit("PongInit",
                 std::bind(&GiantPong::GameInitEnter, this),
                 std::bind(&GiantPong::GameInitHandle, this, std::placeholders::_1, std::placeholders::_2),
                 nullptr),
   StateGameReady("PongReady",
                  std::bind(&GiantPong::GameReadyEnter, this),
                  std::bind(&GiantPong::GameReadyHandle, this, std::placeholders::_1, std::placeholders::_2),
                  nullptr),
   StateGamePlay("PongPlay",
                 std::bind(&GiantPong::GamePlayEnter, this),
                 std::bind(&GiantPong::GamePlayHandle, this, std::placeholders::_1, std::placeholders::_2),
                 nullptr),
   StateGameOver("PongOver",
                 nullptr,
                 std::bind(&GiantPong::GameOverHandle, this, std::placeholders::_1, std::placeholders::_2),
                 nullptr),
   StateFinished("PongFinished",
                 nullptr,
                 std::bind(&GiantPong::FinishedHandle, this, std::placeholders::_1, std::placeholders::_2),
                 nullptr),
   fsm(&StateGameInit),
   gameStatus(),
   ball(canvas.width * BallScalePercent),
   leftPlayer(PLAYER_LEFT, gamePad1),
   rightPlayer(PLAYER_RIGHT, gamePad2),
   border(),
   splash(),
   frameCntr()
{
}


void GiantPong::InitGamePlay()
{
   // First, clear the canvas
   canvas.Clear();

   border = new Shape(7);
   border->vertices <<
            canvas.left, canvas.top, 0, 0,
            canvas.right, canvas.top, 0, 1,
            canvas.right, canvas.bottom, 0, 1,
            canvas.left, canvas.bottom, 0, 1,
            canvas.left, canvas.top, 0, 1,
            0, canvas.top, 0, 0,
            0, canvas.bottom, 0, 1;

   ball.Init(canvas);
   leftPlayer.Init(canvas);
   rightPlayer.Init(canvas);
   gameStatus.whoseServe = GameSystem::GAMEPAD_ID_ANY;

   // Now Fill out the canvas
   canvas.AddObject(border);
   canvas.AddObject(rightPlayer.sprite);
   canvas.AddObject(leftPlayer.sprite);
   canvas.AddObject(leftPlayer.score);
   canvas.AddObject(rightPlayer.score);
}


void GiantPong::StartGamePlay()
{
   int      ballYVel;
   int      ballXVel;
   int32_t  pos = (canvas.width / 4);

   if(rand() % 1)
   {
      ball.sprite->Move(0, pos);
   }
   else
   {
      ball.sprite->Move(0, -pos);
   }

   if(rand() %1)
   {
      ballYVel = BallStepSize;
   }
   else
   {
      ballYVel = -BallStepSize;
   }

   if(gameStatus.whoseServe != GameSystem::GAMEPAD_ID_2)
   {
      ballXVel = BallStepSize / (rand() % 2 + 1);
   }
   else
   {
      ballXVel = -BallStepSize / (rand() % 2 + 1);
   }

   ball.sprite->SetVelocity(ballXVel, ballYVel, 0);
   canvas.AddObject(ball.sprite);
}


bool GiantPong::PlayGame()
{
   bool        keepPlaying = true;
   int16_t     overlap;


   // Move the ball
   ball.sprite->Move();
   leftPlayer.Play(*(ball.sprite));
   rightPlayer.Play(*(ball.sprite));

   // If the ball is moving left...
   if(ball.sprite->velocity(CoordX) < 0)
   {
      // And the ball is not already past the paddle
      if(ball.sprite->position(CoordX) <= (leftPlayer.GetPosition(CoordX) - ball.radius))
      {
         // Check to see if the ball has hit the left side
         overlap = ball.sprite->CheckLeft(canvas.left + ball.radius);

         if(overlap <= 0)
         {
            // Stop drawing the ball
            canvas.RemoveObject(ball.sprite);
            // Re-center the ball
            ball.sprite->MoveTo(0, 0);
            rightPlayer.Score();
            gameStatus.whoseServe = GameSystem::GAMEPAD_ID_2;
            keepPlaying = false;
         }
      }
      else
      {
         // Check if the left paddle and ball have collided
         overlap = leftPlayer.CheckCollision(*(ball.sprite));

         if(overlap <= 0)
         {
            ball.sprite->Move(-overlap, 0);
            int xVel = -ball.sprite->velocity(CoordX);
            ball.sprite->SetVelocity(xVel, ball.sprite->velocity(CoordY), 0);
            ball.sprite->Move(-overlap, 0);  // Prevent from showing the overlap
         }
      }
   }
   else  // The ball is moving right
   {
      // And the ball is not already past the right paddle
      if(ball.sprite->position(CoordX) >= (rightPlayer.GetPosition(CoordX) + ball.radius))
      {
         // Check to see if the ball has hit the right side
         overlap = ball.sprite->CheckRight(canvas.right - ball.radius);

         if(overlap <= 0)
         {
            // Stop drawing the ball
            canvas.RemoveObject(ball.sprite);
            // Re-center the ball
            ball.sprite->MoveTo(0, 0);
            leftPlayer.Score();
            gameStatus.whoseServe = GameSystem::GAMEPAD_ID_1;
            keepPlaying = false;
         }
      }
      else
      {
         // Check if the right paddle and ball have collided
         overlap = rightPlayer.CheckCollision(*(ball.sprite));

         if(overlap <= 0)
         {
            ball.sprite->Move(overlap, 0);
            int xVel = -ball.sprite->velocity(CoordX);
            ball.sprite->SetVelocity(xVel, ball.sprite->velocity(CoordY), 0);
            ball.sprite->Move(overlap, 0);  // Prevent from showing the overlap
         }
      }
   }

   if(ball.sprite->CheckTop(canvas.top) < 1)
   {
      int yVel = -ball.sprite->velocity(CoordY);
      ball.sprite->SetVelocity(ball.sprite->velocity(CoordX), yVel, 0);
   }
   else if(ball.sprite->CheckBottom(canvas.bottom) < 1)
   {
      int yVel = -ball.sprite->velocity(CoordY);
      ball.sprite->SetVelocity(ball.sprite->velocity(CoordX), yVel, 0);
   }

   return keepPlaying;
}


void GiantPong::TearDownGamePlay()
{
   canvas.Clear();
   delete border;
}


void GiantPong::HandleEvent(GameSystem::Events event, void* data)
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

      case GameSystem::EVENT_GAMEPAD_BUTTON_PRESS:
      case GameSystem::EVENT_GAMEPAD_BUTTON_RELEASE:
      case GameSystem::EVENT_GAMEPAD_BUTTON_CLICK:
         fsm.HandleEvent(event, data);
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


void GiantPong::GameInitEnter()
{
   InitGamePlay();
}


bool GiantPong::GameInitHandle(GameSystem::Events e, void* data)
{
   bool handled  = false;

   switch(e)
   {
      // Just go directly to the Ready state
      case GameSystem::EVENT_PROGRAM_RUN:
         fsm.Transition(&StateGameReady);
         handled = true;
         break;

      default:
         break;
   }

   return handled;
}


void GiantPong::GameReadyEnter()
{
   frameCntr = 0;
}


bool GiantPong::GameReadyHandle(GameSystem::Events e, void* data)
{
   bool handled  = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         // Auto-start if we're in demo mode, or the computer is playing
         if((gameStatus.demoMode) ||
            ((gameStatus.whoseServe == GameSystem::GAMEPAD_ID_1) && leftPlayer.computerPlays)  ||
            ((gameStatus.whoseServe == GameSystem::GAMEPAD_ID_2) && rightPlayer.computerPlays)    )
         {
            if(frameCntr++ >= 0.5 * 30)
            {
               fsm.Transition(&StateGamePlay);
            }

            handled = true;
         }
         break;

      case GameSystem::EVENT_GAMEPAD_BUTTON_CLICK:
         if(data)
         {
            GameSystem::Button* buttonEvent = static_cast<GameSystem::Button*>(data);

            if(gameStatus.whoseServe == GameSystem::GAMEPAD_ID_ANY)
            {
               // We don't care whose serve it is at the start
               fsm.Transition(&StateGamePlay);
            }
            else
            {
               // The last player to score is the one who serves
               if(gameStatus.whoseServe == buttonEvent->gamPadId)
               {
                  fsm.Transition(&StateGamePlay);
               }
            }

            handled = true;
         }
         break;

      case GameSystem::EVENT_PROGRAM_STOP:
         TearDownGamePlay();
         fsm.Transition(&StateFinished);
         handled = true;
         break;

      default:
         break;
   }

   return handled;
}


void GiantPong::GamePlayEnter()
{
   frameCntr = 0;
   StartGamePlay();
}


bool GiantPong::GamePlayHandle(GameSystem::Events e, void* data)
{
   bool  handled = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         if(!PlayGame())
         {
            if((leftPlayer.GetScore() >= MaxScore) || (rightPlayer.GetScore() >= MaxScore))
            {
               TearDownGamePlay();
               frameCntr = 0;
               fsm.Transition(&StateGameOver);
            }
            else
            {
               fsm.Transition(&StateGameReady);
            }
         }

//         if(gameStatus.demoMode)
//         {
//            if(frameCntr++ >= DemoTimeout * 30)
//            {
//               TearDownGamePlay();
//               fsm.Transition(&StateSplashScreen);
//            }
//         }
         break;

      case GameSystem::EVENT_PROGRAM_STOP:
         TearDownGamePlay();
         fsm.Transition(&StateFinished);
         handled = true;
         break;

      default:
         break;
   }

   return handled;
}


bool GiantPong::GameOverHandle(GameSystem::Events e, void* data)
{
   bool  handled = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         if(frameCntr++ >= 3 * 30)
         {
            fsm.Transition(&StateGameInit);
         }
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
         if(frameCntr++ >= SplashTimeout * 30)
         {
            gameStatus.demoMode = true;
            fsm.Transition(&StateGameInit);
         }

         handled = true;
         break;

      case GameSystem::EVENT_PROGRAM_STOP:
         fsm.Transition(&StateFinished);
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
