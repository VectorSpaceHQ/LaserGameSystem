/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "NucleoHal.h"
#include "GameSystem.h"
#include "LaserDisplay.h"
#include "DisplayImpl.h"

int main(void)
{
   NucleoHal      nucleoHal;
   LaserDisplay   laserDisplay(dynamic_cast<HAL::Hal&>(nucleoHal));

   GameSystem  sys(dynamic_cast<HAL::Hal&>(nucleoHal),
                   dynamic_cast<DisplayImpl&>(laserDisplay));

   sys.Start();
}
