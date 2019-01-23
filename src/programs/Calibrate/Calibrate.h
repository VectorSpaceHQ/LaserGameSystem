/*
 * Calibrate.h
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#ifndef PROGRAMS_CALIBRATE_CALIBRATE_H_
#define PROGRAMS_CALIBRATE_CALIBRATE_H_

#include "Program.h"


class Calibrate: public Program
{

public:
   Calibrate(Display& _display
            //GamePad& _gamePad1,
            //GamePad& _gamePad2
            );
   ~Calibrate() {};

   void Update();
};


#endif /* PROGRAMS_CALIBRATE_CALIBRATE_H_ */
