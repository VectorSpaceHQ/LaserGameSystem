/*
 * main.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Jordan Goulder
 */

#include "SdlHal.h"
#include "GameSystem.h"
#include "LaserDisplay.h"
#include "DisplayImpl.h"

int main(void)
{
   SdlHal         sdlHal;
   LaserDisplay   laserDisplay(dynamic_cast<HAL::Hal&>(sdlHal));  // For now, since it's the only display we have.


   GameSystem  sys(dynamic_cast<HAL::Hal&>(sdlHal),
                   dynamic_cast<DisplayImpl&>(laserDisplay));

   sys.Start(0);
}
