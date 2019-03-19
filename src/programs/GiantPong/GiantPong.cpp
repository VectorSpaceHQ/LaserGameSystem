/*
 * GiantPong.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#include <Eigen/Dense>
#include <functional>
#include <stdint.h>
#include <stdlib.h>

#include "Canvas.h"
#include "CanvasObject.h"
#include "CommonShapes.h"
#include "FiniteStateMachine.h"
#include "GameSystemEvents.h"
#include "GiantPong.h"
#include "NumeralShape.h"
#include "Program.h"


const float    Player::PaddleScalePercent       = 0.10;     // Percent of canvas height for paddle scale
const uint16_t Player::PaddleSpeed              = 5;        // Multiplier for paddle movement speed
const float    GiantPong::BallScalePercent      = 0.01;     // Percent of canvas height for ball scale
const float    GiantPong::BallStepSize          = 80;       // How far to move the ball in a single frame
const uint16_t GiantPong::SplashTimeout         = 5;        // How long to show the splash screen
const uint16_t GiantPong::DemoTimeout           = 10;       // How long to display the demo game play
const uint8_t  GiantPong::MaxScore              = 3;        // The max score to play to (must be <= 10)



Ball::Ball(uint16_t _radius):
   radius(_radius),
   shape(),
   sprite()
{
}


Ball::~Ball()
{
   Clear();
}


void Ball::Init(Canvas& canvas)
{
   Clear();

   shape = new Polygon(8, radius);
   sprite = new Sprite(shape);

   // Set the limits of the ball
   Coordinate lowerLimit((canvas.left + radius), (canvas.bottom + radius), 0, 0);
   Coordinate upperLimit((canvas.right - radius), (canvas.top - radius), 0, 0);
   sprite->SetLimits(lowerLimit, upperLimit);
}


void Ball::Clear()
{
   if(sprite)
   {
      delete sprite;
      sprite = nullptr;
   }

   if(shape)
   {
      delete shape;
      shape = nullptr;
   }
}


Player::Player(PlayerId _id, GameSystem::GamePad& _gamePad):
   id(_id),
   score(0),
   computerPlays(true),
   gamePad(_gamePad),
   lastAxis(0),
   shape(),
   sprite(),
   scoreShape()
{
}


Player::~Player()
{
   Clear();
}


void Player::SelectOrOverInit(Canvas& canvas, bool selected, bool gameOver)
{
   int32_t  scorePos = canvas.width / 4;

   Clear();

   if(!gameOver)
   {
      score = 0;

      // Draw a check mark
      shape = new Shape(3);
      shape->vertices <<
                      -1.0,   0.0, 0, 0,
                      -0.3,  -1.0, 0, 1,
                       1.0,   1.0, 0, 1;
   }
   else
   {
      // Draw a W for WINNER!
      shape = new Shape(5);
      shape->vertices <<
                      -1.0,   1.0, 0, 0,
                      -0.5,  -1.0, 0, 1,
                       0.0,   0.5, 0, 1,
                       0.5,  -1.0, 0, 1,
                       1.0,   1.0, 0, 1;
   }

   scoreShape = new NumeralShape();
   sprite = new Sprite(scoreShape);
   sprite->AddShape(shape);
   sprite->Scale(300);

   if(selected)
   {
      sprite->SelectShape(1);
   }

   if(id == PLAYER_LEFT)
   {
      sprite->Move(-scorePos, 0);
   }
   else
   {
      sprite->Move(scorePos, 0);
   }
}


void Player::GameInit(Canvas& canvas)
{
   uint16_t paddleHeight = canvas.height * PaddleScalePercent;
   int32_t  paddleXPos = canvas.width / 9;
   int32_t  scorePos = canvas.width / 4;

   Clear();

   shape = new Rectangle(40, paddleHeight);
   sprite = new Sprite(shape);
   scoreShape = new NumeralShape();
   scoreShape->Scale(150);
   score = 0;

   if(id == PLAYER_LEFT)
   {
      // Set the limits of the paddle
      Coordinate lowerLimit((canvas.left + paddleXPos), (canvas.bottom + (paddleHeight /2)), 0, 0);
      Coordinate upperLimit((canvas.left + paddleXPos), (canvas.top - (paddleHeight /2)), 0, 0);

      sprite->Move(canvas.left + paddleXPos, 0);
      sprite->SetLimits(lowerLimit, upperLimit);
      scoreShape->Move(0 - scorePos, canvas.top - 300, 0);
   }
   else
   {
      Coordinate lowerLimit((canvas.right - paddleXPos), (canvas.bottom + (paddleHeight /2)), 0, 0);
      Coordinate upperLimit((canvas.right - paddleXPos), (canvas.top - (paddleHeight /2)), 0, 0);

      sprite->Move(canvas.right - paddleXPos, 0);
      sprite->SetLimits(lowerLimit, upperLimit);
      scoreShape->Move(scorePos, canvas.top - 300, 0);
   }

   lastAxis = gamePad.GetAxis(GameSystem::AXIS_ID_LEFT_X);
}


void Player::Score()
{
   score++;

   if(scoreShape)
   {
      scoreShape->operator++();
   }
}


uint8_t Player::GetScore()
{
   return score;
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
      sprite->Move(0, (currAxis - lastAxis) * PaddleSpeed);
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


void Player::Clear()
{
   if(sprite)
   {
      delete sprite;
      sprite = nullptr;
   }

   if(scoreShape)
   {
      delete scoreShape;
      scoreShape = nullptr;
   }

   if(shape)
   {
      delete shape;
      shape = nullptr;
   }
}


GiantPong::GiantPong(Canvas&              _display,
                     GameSystem::GamePad& _gamePad1,
                     GameSystem::GamePad& _gamePad2):
   Program(_display, _gamePad1, _gamePad2),
   StateSplashScreen("PongSplashScreen",
                     std::bind(&GiantPong::SplashScreenEnter, this),
                     std::bind(&GiantPong::SplashScreenHandle, this, std::placeholders::_1, std::placeholders::_2),
                     std::bind(&GiantPong::SplashScreenExit, this)),
   StateSelectPlayers("PongPlayerSelect",
                      std::bind(&GiantPong::PlayerSelectEnter, this),
                      std::bind(&GiantPong::PlayerSelectHandle, this, std::placeholders::_1, std::placeholders::_2),
                      std::bind(&GiantPong::PlayerSelectExit, this)),
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
                 std::bind(&GiantPong::GameOverEnter, this),
                 std::bind(&GiantPong::GameOverHandle, this, std::placeholders::_1, std::placeholders::_2),
                 std::bind(&GiantPong::PlayerSelectExit, this)), // Same teardown as player select
   StateFinished("PongFinished",
                 nullptr,
                 std::bind(&GiantPong::FinishedHandle, this, std::placeholders::_1, std::placeholders::_2),
                 nullptr),
   fsm(&StateSplashScreen),
   ball(canvas.width * BallScalePercent),
   leftPlayer(PLAYER_LEFT, gamePad1),
   rightPlayer(PLAYER_RIGHT, gamePad2),
   border(),
   splash(),
   frameCntr(),
   demoMode(false),
   whoseServe(GameSystem::GAMEPAD_ID_ANY)
{
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


void GiantPong::InitGamePlay()
{
   // First, clear the canvas
   canvas.Clear();

   DrawBorder(true);

   ball.Init(canvas);
   leftPlayer.GameInit(canvas);
   rightPlayer.GameInit(canvas);
   whoseServe = GameSystem::GAMEPAD_ID_ANY;

   // Now Fill out the canvas
   canvas.AddObject(border);
   canvas.AddObject(rightPlayer.sprite);
   canvas.AddObject(leftPlayer.sprite);
   canvas.AddObject(leftPlayer.scoreShape);
   canvas.AddObject(rightPlayer.scoreShape);
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
            whoseServe = GameSystem::GAMEPAD_ID_2;
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
            whoseServe = GameSystem::GAMEPAD_ID_1;
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

   leftPlayer.Clear();
   rightPlayer.Clear();
   ball.Clear();

   if(border)
   {
      delete border;
      border = nullptr;
   }
}


void GiantPong::DrawBorder(bool includeCenterline)
{
   if(includeCenterline)
   {
      border = new Shape(7);
      border->vertices <<
               canvas.left, canvas.top, 0, 0,
               canvas.right, canvas.top, 0, 1,
               canvas.right, canvas.bottom, 0, 1,
               canvas.left, canvas.bottom, 0, 1,
               canvas.left, canvas.top, 0, 1,
               0, canvas.top, 0, 0,
               0, canvas.bottom, 0, 1;
   }
   else
   {
      border = new Shape(5);
      border->vertices <<
               canvas.left, canvas.top, 0, 0,
               canvas.right, canvas.top, 0, 1,
               canvas.right, canvas.bottom, 0, 1,
               canvas.left, canvas.bottom, 0, 1,
               canvas.left, canvas.top, 0, 1;
   }
}


void GiantPong::PlayerSelectEnter()
{
   canvas.Clear();
   DrawBorder(true);
   leftPlayer.SelectOrOverInit(canvas, !leftPlayer.computerPlays);
   rightPlayer.SelectOrOverInit(canvas, !rightPlayer.computerPlays);
   frameCntr = 5.5 * 30;

   leftPlayer.scoreShape->SetValue(5);
   rightPlayer.scoreShape->SetValue(5);

   canvas.AddObject(border);
   canvas.AddObject(leftPlayer.sprite);
   canvas.AddObject(rightPlayer.sprite);
}


bool GiantPong::PlayerSelectHandle(GameSystem::Events e, void* data)
{
   bool handled  = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         if(frameCntr-- == 0)
         {
            fsm.Transition(&StateGameInit);
         }
         else if(frameCntr % 30 == 0)
         {
            leftPlayer.scoreShape->operator--();
            rightPlayer.scoreShape->operator--();
         }
         break;

      case GameSystem::EVENT_GAMEPAD_BUTTON_CLICK:
         if(data)
         {
            GameSystem::Button* buttonEvent = static_cast<GameSystem::Button*>(data);

            if(buttonEvent->gamPadId == GameSystem::GAMEPAD_ID_1)
            {
               leftPlayer.computerPlays = false;
               leftPlayer.sprite->SelectShape(1);
            }
            else if(buttonEvent->gamPadId == GameSystem::GAMEPAD_ID_2)
            {
               rightPlayer.computerPlays = false;
               rightPlayer.sprite->SelectShape(1);
            }

            // If both have selected, then knock down the frameCtr
            if(!leftPlayer.computerPlays && !rightPlayer.computerPlays)
            {
               frameCntr = 1 * 30;
            }

            handled = true;
         }
         break;

      default:
         break;
   }

   return handled;
}


void GiantPong::PlayerSelectExit()
{
   canvas.Clear();

   if(border)
   {
      delete border;
      border = nullptr;
   }

   leftPlayer.Clear();
   rightPlayer.Clear();
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

   if(leftPlayer.computerPlays && rightPlayer.computerPlays)
   {
      demoMode = true;
   }
   else
   {
      demoMode = false;
   }
}


bool GiantPong::GameReadyHandle(GameSystem::Events e, void* data)
{
   bool handled  = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         // Players can move their paddles in the ready state
         leftPlayer.Play(*(ball.sprite));
         rightPlayer.Play(*(ball.sprite));

         // Auto-start if we're in demo mode, or the computer is playing
         if((demoMode) ||
            ((whoseServe == GameSystem::GAMEPAD_ID_1) && leftPlayer.computerPlays)  ||
            ((whoseServe == GameSystem::GAMEPAD_ID_2) && rightPlayer.computerPlays)    )
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

            if(whoseServe == GameSystem::GAMEPAD_ID_ANY)
            {
               // We don't care whose serve it is at the start
               fsm.Transition(&StateGamePlay);
            }
            else
            {
               // The last player to score is the one who serves
               if(whoseServe == buttonEvent->gamPadId)
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
   int      ballYVel;
   int      ballXVel;
   int32_t  pos = (canvas.width / 4);

   frameCntr = 0;

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

   if(whoseServe != GameSystem::GAMEPAD_ID_2)
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

         if(demoMode)
         {
            if(frameCntr++ >= DemoTimeout * 30)
            {
               TearDownGamePlay();
               fsm.Transition(&StateSplashScreen);
            }
         }
         break;

      case GameSystem::EVENT_GAMEPAD_BUTTON_CLICK:
         if(data)
         {
            GameSystem::Button* buttonEvent = static_cast<GameSystem::Button*>(data);

            if(demoMode)
            {
               if(buttonEvent->gamPadId == GameSystem::GAMEPAD_ID_1)
               {
                  leftPlayer.computerPlays = false;
                  fsm.Transition(&StateSelectPlayers);
               }
               else if(buttonEvent->gamPadId == GameSystem::GAMEPAD_ID_2)
               {
                  rightPlayer.computerPlays = false;
                  fsm.Transition(&StateSelectPlayers);
               }
            }
            else
            {
               // During game play, pressing both buttons simultaneously will reset the game
               if(buttonEvent->gamPadId == GameSystem::GAMEPAD_ID_1)
               {
                  if(gamePad2.GetButton(GameSystem::BUTTON_ID_A))
                  {
                     TearDownGamePlay();
                     fsm.Transition(&StateSplashScreen);
                  }
               }
               else if(buttonEvent->gamPadId == GameSystem::GAMEPAD_ID_2)
               {
                  if(gamePad1.GetButton(GameSystem::BUTTON_ID_A))
                  {
                     TearDownGamePlay();
                     fsm.Transition(&StateSplashScreen);
                  }
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


void GiantPong::GameOverEnter()
{
   canvas.Clear();
   frameCntr = 0;

   DrawBorder(true);

   if(leftPlayer.GetScore() >= MaxScore)
   {
      leftPlayer.SelectOrOverInit(canvas, true, true);
      rightPlayer.SelectOrOverInit(canvas, false, true);
   }
   else if(rightPlayer.GetScore() >= MaxScore)
   {
      leftPlayer.SelectOrOverInit(canvas, false, true);
      rightPlayer.SelectOrOverInit(canvas, true, true);
   }
   else
   {
      leftPlayer.SelectOrOverInit(canvas, false, true);
      rightPlayer.SelectOrOverInit(canvas, false, true);
   }

   leftPlayer.scoreShape->SetValue(leftPlayer.GetScore());
   rightPlayer.scoreShape->SetValue(rightPlayer.GetScore());

   canvas.AddObject(border);
   canvas.AddObject(leftPlayer.sprite);
   canvas.AddObject(rightPlayer.sprite);
}


bool GiantPong::GameOverHandle(GameSystem::Events e, void* data)
{
   bool  handled = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         if(frameCntr++ >= 10 * 30)
         {
            fsm.Transition(&StateSplashScreen);
         }
         break;

      case GameSystem::EVENT_GAMEPAD_BUTTON_CLICK:
         // Display the score for at least three seconds
         if(frameCntr >= 3 * 30)
         {
            fsm.Transition(&StateSplashScreen);
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


void GiantPong::SplashScreenEnter()
{
   canvas.Clear();
   frameCntr = 0;
   leftPlayer.computerPlays = true;
   rightPlayer.computerPlays = true;

   InitGamePlay();

   DrawBorder(false);

//   uint32_t numPts = sizeof(Giant) / sizeof(float) / 4;
//   splash = new Shape(numPts);
//   VertexListConstMap_t giantMap(&Giant[0], numPts, static_cast<int>(CoordMax));
//   splash->vertices = giantMap;
}


bool GiantPong::SplashScreenHandle(GameSystem::Events e, void* data)
{
   bool  handled = false;

   switch(e)
   {
      case GameSystem::EVENT_PROGRAM_RUN:
         // Give time for the Laser Display to clear out it's vertices before adding the large splash
         frameCntr++;
         if(frameCntr == 2)
         {
//            canvas.AddObject(border);
//            canvas.AddObject(splash);
         }
         else if(frameCntr >= SplashTimeout * 30)
         {
            demoMode = true;
            fsm.Transition(&StateGameInit);
         }

         handled = true;
         break;

      case GameSystem::EVENT_GAMEPAD_BUTTON_CLICK:
         if(data && (frameCntr > 2 * 30))
         {
            GameSystem::Button* buttonEvent = static_cast<GameSystem::Button*>(data);

            if(buttonEvent->gamPadId == GameSystem::GAMEPAD_ID_1)
            {
               leftPlayer.computerPlays = false;
               fsm.Transition(&StateSelectPlayers);
            }
            else if(buttonEvent->gamPadId == GameSystem::GAMEPAD_ID_2)
            {
               rightPlayer.computerPlays = false;
               fsm.Transition(&StateSelectPlayers);
            }

            handled = true;
         }
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
   TearDownGamePlay();

   if(splash)
   {
      delete splash;
      splash = nullptr;
   }

   if(border)
   {
      delete border;
      border = nullptr;
   }
}


const float GiantPong::Giant[396] =
{
   -824, -53, 0, 0,
   -859, -104, 0, 1,
   -899, -99, 0, 1,
   -960, -299, 0, 1,
   -1099, -431, 0, 1,
   -1273, -376, 0, 1,
   -1363, -247, 0, 1,
   -1392, -28, 0, 1,
   -1346, 266, 0, 1,
   -1214, 424, 0, 1,
   -1076, 393, 0, 1,
   -972, 318, 0, 1,
   -943, 234, 0, 1,
   -924, 130, 0, 1,
   -955, 78, 0, 1,
   -1033, 92, 0, 1,
   -1111, 123, 0, 1,
   -1116, 196, 0, 1,
   -1132, 267, 0, 1,
   -1192, 153, 0, 1,
   -1216, -83, 0, 1,
   -1163, -301, 0, 1,
   -1120, -246, 0, 1,
   -1087, -128, 0, 1,
   -1148, -97, 0, 1,
   -1187, -71, 0, 1,
   -1148, 7, 0, 1,
   -1058, 18, 0, 1,
   -956, 47, 0, 1,
   -872, 1, 0, 1,
   -824, -53, 0, 1,
   -558, 377, 0, 0,
   -580, 281, 0, 1,
   -580, -332, 0, 1,
   -568, -369, 0, 1,
   -592, -438, 0, 1,
   -736, -400, 0, 1,
   -758, -365, 0, 1,
   -750, -339, 0, 1,
   -750, 365, 0, 1,
   -720, 422, 0, 1,
   -602, 411, 0, 1,
   -558, 377, 0, 1,
   147, -352, 0, 0,
   118, -425, 0, 1,
   -36, -370, 0, 1,
   -77, -199, 0, 1,
   -283, -264, 0, 1,
   -323, -370, 0, 1,
   -356, -419, 0, 1,
   -495, -361, 0, 1,
   -439, -194, 0, 1,
   -460, -152, 0, 1,
   -398, -98, 0, 1,
   -269, 343, 0, 1,
   -238, 426, 0, 1,
   0, 359, 0, 1,
   45, 26, 0, 1,
   147, -352, 0, 1,
   -114, -48, 0, 0,
   -145, 174, 0, 1,
   -223, -76, 0, 1,
   -114, -48, 0, 1,
   793, 377, 0, 0,
   780, 329, 0, 1,
   780, -330, 0, 1,
   773, -427, 0, 1,
   542, -376, 0, 1,
   409, -8, 0, 1,
   409, -304, 0, 1,
   430, -373, 0, 1,
   394, -413, 0, 1,
   227, -362, 0, 1,
   239, -290, 0, 1,
   235, 373, 0, 1,
   296, 421, 0, 1,
   376, 411, 0, 1,
   450, 377, 0, 1,
   523, 194, 0, 1,
   609, -60, 0, 1,
   609, 333, 0, 1,
   603, 389, 0, 1,
   691, 419, 0, 1,
   793, 377, 0, 1,
   1306, 268, 0, 0,
   1203, 240, 0, 1,
   1203, -286, 0, 1,
   1215, -387, 0, 1,
   1186, -427, 0, 1,
   1016, -385, 0, 1,
   1030, -299, 0, 1,
   1030, 196, 0, 1,
   923, 164, 0, 1,
   825, 296, 0, 1,
   923, 332, 0, 1,
   1329, 438, 0, 1,
   1382, 371, 0, 1,
   1386, 269, 0, 1,
   1306, 268, 0, 1
};
