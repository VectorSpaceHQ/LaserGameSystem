/*
 * Calibrate.h
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#ifndef PROGRAMS_CALIBRATE_CALIBRATE_H_
#define PROGRAMS_CALIBRATE_CALIBRATE_H_

#include "Program.h"
#include "Shape.h"


class Calibrate: public Program
{
private:
   Shape    square;
   int      scale;
   int      shrinkGrow;

   static const int  StepSize;
   static const int  MaxSize;

public:
   Calibrate(Display& _display
            //GamePad& _gamePad1,
            //GamePad& _gamePad2
            );
   ~Calibrate() {};

   void Update();
};


#endif /* PROGRAMS_CALIBRATE_CALIBRATE_H_ */
