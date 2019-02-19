/*
 * GameSystemEvents.h
 *
 *  Created on: Feb 5, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_GAMESYSTEMEVENTS_H_
#define INCLUDE_GAMESYSTEMEVENTS_H_


namespace GameSystem
{
   enum Events
   {
      // Program Runtime Events
      EVENT_PROGRAM_INIT               = 0,     // Initialize the program
      EVENT_PROGRAM_START,                      // Start the program
      EVENT_PROGRAM_STOP,                       // Stop the current program
      EVENT_PROGRAM_RUN,                        // Time to perform run-time calculations
      EVENT_PROGRAM_DRAW,                       // Time to draw/render on the canvas

      // Gamepad Events
      EVENT_GAMEPAD_BUTTON_PRESS,
      EVENT_GAMEPAD_BUTTON_RELEASE,

      // Do not add past this line
      EVENT_MAX
   };

}

#endif /* INCLUDE_GAMESYSTEMEVENTS_H_ */
