/*
 * Program.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef __program_h__
#define __program_h__

#include <Canvas.h>
#include "GamePad.h"
#include "ScheduledInterval.h"

// TODO: For now, use ScheduledInterval.
//       When we get a clock, we will want to use TimedInterval... until we have something better.
class Program: public ScheduledInterval
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
   ~Program() {};

   void Init();
   void Start();
   virtual void Update() = 0;
   //void HandleEvent();
   void Stop();
};



#endif /* __program_h__ */
