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
#include "GameSystemEvents.h"
#include "NumeralShape.h"
#include "Program.h"
#include "Shape.h"
#include "Sprite.h"


struct PongPaddle
{
   Shape*   shape;
   Sprite*  sprite;

   PongPaddle(uint16_t width, uint16_t height, int16_t xPos);
   ~PongPaddle();
};


struct Ball
{
   Shape*   shape;
   Sprite*  sprite;
   uint16_t radius;

   Ball(uint16_t _radius);
   ~Ball();
};


class GiantPong: public Program
{
private:
   static const float PaddleScalePercent;
   static const float BallScalePercent;
   static const float BallStepSize;

   GameSystem::FiniteState          StateSplashScreen;
   GameSystem::FiniteState          StateGameReady;
   GameSystem::FiniteState          StateGamePlay;
   GameSystem::FiniteState          StateFinished;
   GameSystem::FiniteStateMachine   fsm;

   Shape*         border;
   PongPaddle*    leftPaddle;
   PongPaddle*    rightPaddle;
   Ball*          ball;
   NumeralShape*  leftScore;
   NumeralShape*  rightScore;
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
   void PlayGame();
   void TearDownGamePlay();

   // State methods
   void SplashScreenEnter();
   bool SplashScreenHandle(GameSystem::Events e, void* data);
   void SplashScreenExit();
   void GameReadyEnter();
   bool GameReadyHandle(GameSystem::Events e, void* data);
   bool GamePlayHandle(GameSystem::Events e, void* data);
   bool FinishedHandle(GameSystem::Events e, void* data);
};


#endif /* SRC_PROGRAMS_PONG_GIANTPONG_H_ */
