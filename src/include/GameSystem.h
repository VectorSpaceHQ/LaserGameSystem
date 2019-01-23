/*
 * GameSystem.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_GAMESYSTEM_H_
#define INCLUDE_GAMESYSTEM_H_

#include "Display.h"
#include "Hal.h"
#include "Program.h"
#include "Programs.h"


class GameSystem
{
private:
   HAL::Hal&   hal;
   Display     display;
   Programs    programs;
   Program&    currentProgram;

public:
   GameSystem(HAL::Hal& _hal);

   void Start();
   void Run();
};


#endif /* INCLUDE_GAMESYSTEM_H_ */
