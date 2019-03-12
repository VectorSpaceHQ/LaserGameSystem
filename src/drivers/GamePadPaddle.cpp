/*
 * GamePadPaddle.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#include "GamePadPaddle.h"
#include <string.h>

GamePadPaddle::GamePadPaddle(GameSystem::GamePadId gamePadId, TIM_TypeDef* timerInstance, int theButtonPin)
{
   id = gamePadId;

   // Configure the timer settings
   memset(&hTimer, 0, sizeof(hTimer));

   hTimer.Instance = timerInstance;
   hTimer.Init.Period = UINT16_MAX;

   // Configure the encoder settings
   TIM_Encoder_InitTypeDef hEncoderConfig;
   memset(&hEncoderConfig, 0, sizeof(hEncoderConfig));

   hEncoderConfig.EncoderMode  = TIM_ENCODERMODE_TI12;

   hEncoderConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
   hEncoderConfig.IC1Filter    = 0;
   hEncoderConfig.IC1Prescaler = TIM_ICPSC_DIV1;
   hEncoderConfig.IC1Polarity  = TIM_ICPOLARITY_RISING;

   hEncoderConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
   hEncoderConfig.IC2Filter    = 0;
   hEncoderConfig.IC2Prescaler = TIM_ICPSC_DIV1;
   hEncoderConfig.IC2Polarity  = TIM_ICPOLARITY_RISING;

   // Initialize the encoder interface
   HAL_TIM_Encoder_Init(&hTimer, &hEncoderConfig);

   // Start the encoder interface
   HAL_TIM_Encoder_Start(&hTimer, TIM_CHANNEL_ALL);

   buttonPin = theButtonPin;

   // Structure used to initialize GPIO pins
   GPIO_InitTypeDef gpioInit;
   memset(&gpioInit, 0, sizeof(gpioInit));

   // Configure GPIO for button
   gpioInit.Pin        = buttonPin;
   gpioInit.Mode       = GPIO_MODE_INPUT;
   gpioInit.Pull       = GPIO_PULLUP;
   gpioInit.Speed      = GPIO_SPEED_FAST;
   HAL_GPIO_Init(GPIOB, &gpioInit);

   HAL_GPIO_Init(GPIOB, &gpioInit);
}

GamePadPaddle::~GamePadPaddle()
{
   HAL_TIM_Encoder_DeInit(&hTimer);
   HAL_GPIO_DeInit(GPIOB, buttonPin);
}

int32_t
GamePadPaddle::GetAxis(GameSystem::AxisId axisId)
{
   int32_t axisPosition = 0;

   if (axisId == GameSystem::AXIS_ID_LEFT_X)
   {
      axisPosition = __HAL_TIM_GET_COUNTER(&hTimer);
   }

   return axisPosition;
}

bool
GamePadPaddle::GetButton(GameSystem::ButtonId axisId)
{
   return HAL_GPIO_ReadPin(GPIOB, buttonPin) == GPIO_PIN_RESET;
}
