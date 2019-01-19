/*
 * GameSystem.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_GAMESYSTEM_H_
#define INCLUDE_GAMESYSTEM_H_

#include "Hal.h"


class GameSystem
{
private:
   HAL::Hal&   hal;

public:
   GameSystem(HAL::Hal& _hal);

   void Start();
   void Run();
};


#endif /* INCLUDE_GAMESYSTEM_H_ */
