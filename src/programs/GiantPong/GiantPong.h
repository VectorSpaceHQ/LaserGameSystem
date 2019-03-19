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
#include "GamePad.h"
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
   void Clear();
   ~Ball();
};


class Player
{
   static const float      PaddleScalePercent;
   static const uint16_t   PaddleSpeed;

public:
   PlayerId             id;
   uint8_t              score;
   bool                 computerPlays;
   GameSystem::GamePad& gamePad;
   int32_t              lastAxis;
   Shape*               shape;
   Sprite*              sprite;
   NumeralShape*        scoreShape;


   Player(PlayerId _id, GameSystem::GamePad& _gamePad);
   ~Player();

   void SelectOrOverInit(Canvas& canvas, bool selected, bool over = false);
   void GameInit(Canvas& canvas);
   void Score();
   uint8_t GetScore();
   void Play(Sprite& ball);
   CoordType GetPosition(CoordPositions pos);
   int16_t CheckCollision(Sprite& ball);
   void Clear();
};


class GiantPong: public GameSystem::Program
{
private:
   static const float      BallScalePercent;
   static const float      BallStepSize;
   static const uint16_t   SplashTimeout;
   static const uint16_t   DemoTimeout;
   static const uint8_t    MaxScore;
   static const float      Giant[396];
   static const float      Pong[80];

   GameSystem::FiniteState          StateSplashScreen;
   GameSystem::FiniteState          StateSelectPlayers;
   GameSystem::FiniteState          StateGameInit;       // A transition state to initialize the playing field
   GameSystem::FiniteState          StateGameReady;
   GameSystem::FiniteState          StateGamePlay;
   GameSystem::FiniteState          StateGameOver;
   GameSystem::FiniteState          StateFinished;
   GameSystem::FiniteStateMachine   fsm;

   Ball                    ball;
   Player                  leftPlayer;
   Player                  rightPlayer;
   Shape*                  border;
   Shape*                  splash;
   uint32_t                frameCntr;
   bool                    demoMode;
   GameSystem::GamePadId   whoseServe;

public:
   GiantPong(Canvas&                _display,
             GameSystem::GamePad&   _gamePad1,
             GameSystem::GamePad&   _gamePad2);
   ~GiantPong() {};

   void HandleEvent(GameSystem::Events event, void* data);

private:
   void InitGamePlay();
   bool PlayGame();
   void TearDownGamePlay();
   void DrawBorder(bool includeCenterline);

   // State methods
   void SplashScreenEnter();
   bool SplashScreenHandle(GameSystem::Events e, void* data);
   void SplashScreenExit();
   void PlayerSelectEnter();
   bool PlayerSelectHandle(GameSystem::Events e, void* data);
   void PlayerSelectExit();
   void GameInitEnter();
   bool GameInitHandle(GameSystem::Events e, void* data);
   void GameReadyEnter();
   bool GameReadyHandle(GameSystem::Events e, void* data);
   void GamePlayEnter();
   bool GamePlayHandle(GameSystem::Events e, void* data);
   void GameOverEnter();
   bool GameOverHandle(GameSystem::Events e, void* data);
   bool FinishedHandle(GameSystem::Events e, void* data);
};


#endif /* SRC_PROGRAMS_PONG_GIANTPONG_H_ */
