/*
 * Calibrate.h
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#ifndef PROGRAMS_CALIBRATE_CALIBRATE_H_
#define PROGRAMS_CALIBRATE_CALIBRATE_H_

#include "CommonShapes.h"
#include "GameSystemEvents.h"
#include "Program.h"
#include "Shape.h"
#include "Sprite.h"


class Calibrate: public Program
{
private:
   Polygon     triangle;
   Square      square;
   Polygon     circle;
   Star        star;
   Sprite      mySprite;
   int         scale;
   int         shrinkGrow;
   uint32_t    currShape;

   static const int  StepSize;
   static const int  MaxSize;

public:
   Calibrate(Canvas& _display
            //GamePad& _gamePad1,
            //GamePad& _gamePad2
            );
   ~Calibrate() {};

   void Init();
   void Start();
   void Run();
   void Draw();
   void HandleEvent(GameSystemEvent event);
};


#endif /* PROGRAMS_CALIBRATE_CALIBRATE_H_ */
