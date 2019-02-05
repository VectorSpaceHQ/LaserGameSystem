/*
 * Program.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef __program_h__
#define __program_h__

#include "Canvas.h"
#include "GamePad.h"
#include "GameSystemEvents.h"


// TODO: For now, use ScheduledInterval.
//       When we get a clock, we will want to use TimedInterval... until we have something better.
class Program
{
protected:
   Canvas&    canvas;
//   GamePad&    gamePad1;
//   GamePad&    gamePad2;

public:
   // TODO: Implement the game pads
   Program(Canvas& _canvas
           //GamePad& _gamePad1,
           //GamePad& _gamePad2
          );

   virtual void HandleEvent(GameSystemEvent event) = 0;

protected:
   virtual ~Program() {};

};



#endif /* __program_h__ */
