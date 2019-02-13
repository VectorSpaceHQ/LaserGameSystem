/*
 * main.cpp
 *
 *  Created on: Feb 13, 2019
 *      Author: athiessen
 */

#include <iostream>
#include <DisplayIfc.h>

#include "MockHal.h"
#include "GameSystem.h"
#include "SVGDisplay.h"

int main(int argc, char* argv[])
{
   MockHal     mockHal;
   SVGDisplay  svgDisplay(dynamic_cast<HAL::Hal&>(mockHal));  // For now, since it's the only display we have.
   uint32_t    runTime = 1000;

   if(argc < 2)
   {
      std::cout << "Wrong number of arguments" << std::endl;
      return 0;
   }
   else if(argc >= 3)
   {
      runTime = atoi(argv[2]);
   }

   char const* svgFile = argv[1];


   GameSystem  sys(dynamic_cast<HAL::Hal&>(mockHal),
                   dynamic_cast<DisplayIfc&>(svgDisplay));

   // Run for a limited time
   sys.Start(runTime);
   svgDisplay.PrintFrames(svgFile);
}
