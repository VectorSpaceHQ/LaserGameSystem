/*
 * GiantPong.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef SRC_PROGRAMS_PONG_GIANTPONG_H_
#define SRC_PROGRAMS_PONG_GIANTPONG_H_

#include "Canvas.h"
#include "FiniteStateMachine.h"
#include "GameSystemDefs.h"
#include "GameSystemEvents.h"
#include "NumeralShape.h"
#include "Program.h"
#include "Shape.h"
#include "Sprite.h"

enum PlayerId
{
   PLAYER_LEFT = 0,
   PLAYER_RIGHT
};


struct Ball
{
   uint16_t radius;
   Shape*   shape;
   Sprite*  sprite;

   Ball(uint16_t _radius);
   void Init(Canvas& canvas);
   ~Ball();
};


struct Player
{
   static const float      PaddleScalePercent;

   PlayerId       id;
   bool           computerPlays;
   Shape*         shape;
   Sprite*        sprite;
   NumeralShape*  score;


   Player(PlayerId _id):
      id(_id),
      computerPlays(true),
      shape(),
      sprite(),
      score()
   {
   }


   ~Player()
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

   void Init(Canvas& canvas);
   void Score();
   uint8_t GetScore();
   void Play(Sprite& ball);
   CoordType GetPosition(CoordPositions pos);
   int16_t CheckCollision(Sprite& ball);
};


struct GameStatus
{
   bool                    demoMode;
   bool                    computerPlaysLeft;
   bool                    computerPlaysRight;
   GameSystem::GamePadId   whoseServe;

   GameStatus():
      demoMode(true),
      computerPlaysLeft(true),
      computerPlaysRight(true),
      whoseServe(GameSystem::GAMEPAD_ID_ANY)
   {
   }
};


class GiantPong: public Program
{
private:
   static const float      BallScalePercent;
   static const float      BallStepSize;
   static const uint16_t   SplashTimeout;
   static const uint16_t   DemoTimeout;
   static const uint8_t    MaxScore;

   GameSystem::FiniteState          StateSplashScreen;
   GameSystem::FiniteState          StateGameInit;       // A transition state to initialize the playing field
   GameSystem::FiniteState          StateGameReady;
   GameSystem::FiniteState          StateGamePlay;
   GameSystem::FiniteState          StateGameOver;
   GameSystem::FiniteState          StateFinished;
   GameSystem::FiniteStateMachine   fsm;

   GameStatus     gameStatus;
   Ball           ball;
   Player         leftPlayer;
   Player         rightPlayer;
   Shape*         border;
   Shape*         splash;
   uint32_t       frameCntr;

public:
   GiantPong(Canvas& _display
            //GamePad& _gamePad1,
            //GamePad& _gamePad2
            );
   ~GiantPong() {};

   void HandleEvent(GameSystem::Events event);

private:
   void InitGamePlay();
   void StartGamePlay();
   bool PlayGame();
   void TearDownGamePlay();

   // State methods
   void SplashScreenEnter();
   bool SplashScreenHandle(GameSystem::Events e, void* data);
   void SplashScreenExit();
   void GameInitEnter();
   bool GameInitHandle(GameSystem::Events e, void* data);
   void GameReadyEnter();
   bool GameReadyHandle(GameSystem::Events e, void* data);
   void GamePlayEnter();
   bool GamePlayHandle(GameSystem::Events e, void* data);
   bool GameOverHandle(GameSystem::Events e, void* data);
   bool FinishedHandle(GameSystem::Events e, void* data);
};


#endif /* SRC_PROGRAMS_PONG_GIANTPONG_H_ */
