/*
 * Display.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */


#include "Display.h"


Display::Display():
   mainLight()
{
}


void Display::Clear()
{
   if(mainLight != 0)
   {
      mainLight->Toggle();
   }
}
