/*
 * GameSystem.cpp
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */


#include "GameSystem.h"
#include "hal.h"


GameSystem::GameSystem(HAL::Hal& _hal):
   hal(_hal)
{
}


void GameSystem::Start()
{
   if(hal.Init())
   {
      Run();
   }
}


void GameSystem::Run()
{
   HAL::OnOffSwitch* mainLight = hal.GetOnOffSwitch(HAL::HAL_ID_MAIN_LIGHT);

   while(1)
   {
      mainLight->Toggle();
      hal.Delay(500);
   }
}
