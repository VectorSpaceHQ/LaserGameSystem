/*
 * GamePadPaddle.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef SRC_DRIVERS_GAMEPADPADDLE_H_
#define SRC_DRIVERS_GAMEPADPADDLE_H_

#include "GamePad.h"

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

class GamePadPaddle : public GameSystem::GamePad
{
public:
   GamePadPaddle(GameSystem::GamePadId gamePadId, TIM_TypeDef *aTimerInstance, int theButtonPin);
   ~GamePadPaddle();

   virtual int32_t GetAxis(GameSystem::AxisId axisId);
   virtual bool GetButton(GameSystem::ButtonId axisId);
   virtual GameSystem::GamePadId GetId() { return id; }
   virtual void Run() {};

private:
   TIM_HandleTypeDef hTimer;
   int buttonPin;
   GameSystem::GamePadId id;
};



#endif /* SRC_DRIVERS_GAMEPADPADDLE_H_ */
