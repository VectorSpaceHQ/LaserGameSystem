/*
 * LaserDisplay.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */


#include <Canvas.h>
#include "Hal.h"
#include "LaserDisplay.h"


LaserDisplay::LaserDisplay(HAL::Hal& _hal):
   hal(_hal)
{
}


void LaserDisplay::Update()
{
}


void LaserDisplay::Render()
{
   hal.GetOnOffSwitch(HAL::HAL_ID_MAIN_LIGHT)->Toggle();
}
