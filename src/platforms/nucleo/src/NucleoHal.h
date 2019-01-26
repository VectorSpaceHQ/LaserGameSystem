/*
 * NucleoHal.h
 *
 *  Created on: Jan 18, 2019
 *      Author: athiessen
 */

#ifndef PLATFORMS_NUCLEO_SRC_NUCLEOHAL_H_
#define PLATFORMS_NUCLEO_SRC_NUCLEOHAL_H_

#include "hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"


class BoardLED: public HAL::OnOffSwitch
{
private:
   Led_TypeDef led;

public:
   BoardLED(Led_TypeDef _led):
      led(_led)
   {
   }

   void Init()
   {
      BSP_LED_Init(led);
   }

   void On()
   {
      BSP_LED_On(led);
   }

   void Off()
   {
      BSP_LED_Off(led);
   }

   void Toggle()
   {
      BSP_LED_Toggle(led);
   }
};


class NucleoHal: public HAL::Hal
{
private:
   BoardLED    mainBoardLight;

public:
   NucleoHal():
      mainBoardLight(LED2)
   {
   }

   virtual ~NucleoHal()
   {
   }

   bool Init()
   {
      mainBoardLight.Init();
      return true;
   }


   void Delay(int ms)
   {
      OSTimeDlyHMSM(0u, 0u, 0u, ms);
   }

   int GetNumRotaryEncoders() { return 0; }
   int GetNumPushButtons() { return 0; }
   int GetNumPushServos() { return 0; }
   int GetNumPushOnOffSwitches() { return 1; }

   HAL::OnOffSwitch* GetOnOffSwitch(HAL::HalId id)
   {
      HAL::OnOffSwitch* onOffSwitch = NULL;

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
};


#endif /* PLATFORMS_NUCLEO_SRC_NUCLEOHAL_H_ */
