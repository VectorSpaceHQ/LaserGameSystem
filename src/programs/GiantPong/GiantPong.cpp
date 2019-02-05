/*
 * GiantPong.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */


#include "GameSystemEvents.h"
#include "GiantPong.h"
#include "Program.h"


GiantPong::GiantPong(Canvas& _display
         //GamePad& _gamePad1,
         //GamePad& _gamePad2
         ):
   Program(_display/*, _gamePad1, _gamePad2*/)
{
}


void GiantPong::Run()
{

}


void GiantPong::HandleEvent(GameSystemEvent event)
{
   switch(event)
   {
      case EVENT_PROGRAM_RUN:
         // Run engine here
         break;

      case EVENT_PROGRAM_DRAW:
         // Update canvas here
         break;

      default:
         break;
   }
}
