/*
 * main.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Jordan Goulder
 */

#include <DisplayIfc.h>

#include "MockHal.h"
#include "GameSystem.h"
#include "SVGDisplay.h"

int main(void)
{
   MockHal     mockHal;
   SVGDisplay  svgDisplay(dynamic_cast<HAL::Hal&>(mockHal));  // For now, since it's the only display we have.


   GameSystem  sys(dynamic_cast<HAL::Hal&>(mockHal),
                   dynamic_cast<DisplayIfc&>(svgDisplay));

   sys.Start(0);
}
