#include "SdlHal.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <iostream>


void BoardLED::showLed()
{
   std::cerr << "LED " << (ledOn ? "ON" : "OFF") << std::endl;
}

SdlHal::~SdlHal()
{
   SDL_Quit();
}

bool SdlHal::Init()
{
   SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
   mainBoardLight.Init();
   return true;
}

void SdlHal::Delay(int ms)
{
   SDL_Delay(ms);
}

HAL::OnOffSwitch* SdlHal::GetOnOffSwitch(HAL::HalId id)
{
   HAL::OnOffSwitch* onOffSwitch = nullptr;

   switch(id)
   {
      case HAL::HAL_ID_MAIN_LIGHT:
         onOffSwitch = &mainBoardLight;
         break;

      default:
         break;
   }

   return onOffSwitch;
}
