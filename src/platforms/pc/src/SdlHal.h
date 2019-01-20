/*
 * NucleoHal.h
 *
 *  Created on: Jan 19, 2019
 *      Author: Jordan Goulder
 */

#ifndef PLATFORMS_PC_SRC_SDLHAL_H_
#define PLATFORMS_PC_SRC_SDLHAL_H_

#include "hal.h"

class BoardLED: public HAL::OnOffSwitch
{
private:
   void showLed();
   bool ledOn;

public:
   BoardLED()
      : ledOn(false)
   {
   }

   void Init()
   {
      ledOn = false;
   }

   void On()
   {
      ledOn = true;
      showLed();
   }

   void Off()
   {
      ledOn = false;
      showLed();
   }

   void Toggle()
   {
      ledOn = !ledOn;
      showLed();
   }

};

class SdlHal: public HAL::Hal
{
private:
   BoardLED    mainBoardLight;

public:
   SdlHal():
      mainBoardLight()
   {
   }

   virtual ~SdlHal();

   bool Init();

   void Delay(int ms);

   int GetNumRotaryEncoders() { return 0; }
   int GetNumPushButtons() { return 0; }
   int GetNumPushServos() { return 0; }
   int GetNumPushOnOffSwitches() { return 1; }

   HAL::OnOffSwitch* GetOnOffSwitch(HAL::HalId id);
};

#endif /* PLATFORMS_PC_SRC_SDLHAL_H_ */
