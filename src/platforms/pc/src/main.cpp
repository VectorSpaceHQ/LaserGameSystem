/*
 * main.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: Jordan Goulder
 */

#include "SdlHal.h"
#include "GameSystem.h"

int main(void)
{
   SdlHal sdlHal;
   GameSystem  sys(dynamic_cast<HAL::Hal&>(sdlHal));

   sys.Start();
}
