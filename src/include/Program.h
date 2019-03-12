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

namespace GameSystem
{
   class Program
   {
   protected:
      Canvas&    canvas;
      GamePad&   gamePad1;
      GamePad&   gamePad2;

   public:
      Program(Canvas& _canvas,
              GamePad& _gamePad1,
              GamePad& _gamePad2);

      virtual void HandleEvent(GameSystem::Events event, void* data) = 0;

   protected:
      virtual ~Program() {};

   };

}

#endif /* __program_h__ */
