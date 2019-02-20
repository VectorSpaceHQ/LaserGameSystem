/*
 * GiantPong.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef SRC_PROGRAMS_PONG_GIANTPONG_H_
#define SRC_PROGRAMS_PONG_GIANTPONG_H_

#include "Canvas.h"
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

   Ball(uint16_t width);
   ~Ball();
};


class GiantPong: public Program
{
private:
   enum PongState
   {
      StateSetupSplash  = 0,
      StateSplash,
      StateStopSplash,

      StateSetupGamePlay,
      StateGameReady,
      StateGamePlay,
      StateGameOver,
      StateStopGame
   };

   static const float PaddleScalePercent;
   static const float BallScalePercent;
   static const float BallStepSize;

   PongState      state;
   Shape*         border;
   PongPaddle*    leftPaddle;
   PongPaddle*    rightPaddle;
   Ball*          ball;
   NumeralShape*  leftScore;
   NumeralShape*  rightScore;

public:
   GiantPong(Canvas& _display
            //GamePad& _gamePad1,
            //GamePad& _gamePad2
            );
   ~GiantPong() {};

   void InitGamePlay();
   void StartGameReady();
   void StartGamePlay();
   void PlayGame();
   void Stop();
   void Run();
   void Draw();
   void HandleEvent(GameSystem::Events event);

};


#endif /* SRC_PROGRAMS_PONG_GIANTPONG_H_ */
