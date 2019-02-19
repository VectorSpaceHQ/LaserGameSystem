/*
 * Test.h
 *
 *  Created on: Feb 18, 2019
 *      Author: athiessen
 */

#ifndef PROGRAMS_TESTPROGRAM_TESTPROGRAM_H_
#define PROGRAMS_TESTPROGRAM_TESTPROGRAM_H_


#include "GameSystemEvents.h"
#include "Program.h"
#include "Shape.h"
#include "Sprite.h"


class TestProgram: public Program
{
private:
   Shape*      shapePtrs[5];
   Sprite*     spritePtrs[4];
   uint32_t    currShape;

   static const int  StepSize;
   static const int  MaxSize;

public:
   TestProgram(Canvas& _display
            //GamePad& _gamePad1,
            //GamePad& _gamePad2
            );
   ~TestProgram() {};

   void Init();
   void Start();
   void Stop();
   void Run();
   void Draw();
   void HandleEvent(GameSystem::Events event);
   void CheckSprite(Sprite* sprite);
};




#endif /* PROGRAMS_TESTPROGRAM_TESTPROGRAM_H_ */
