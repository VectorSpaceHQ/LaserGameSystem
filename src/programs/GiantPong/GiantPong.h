/*
 * GiantPong.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef SRC_PROGRAMS_PONG_GIANTPONG_H_
#define SRC_PROGRAMS_PONG_GIANTPONG_H_

#include "Program.h"


class GiantPong: public Program
{
public:
   GiantPong(Canvas& _display
            //GamePad& _gamePad1,
            //GamePad& _gamePad2
            );
   ~GiantPong() {};

   void Update();

};


#endif /* SRC_PROGRAMS_PONG_GIANTPONG_H_ */
