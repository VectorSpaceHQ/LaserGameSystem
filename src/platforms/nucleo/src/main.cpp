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

int main(void)
{
   NucleoHal   nucleoHal;
   GameSystem  sys(dynamic_cast<HAL::Hal&>(nucleoHal));

   sys.Start();
}
