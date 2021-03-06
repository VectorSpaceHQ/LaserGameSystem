/**
  ******************************************************************************
  * @file   stm32f4xx_hal_msp.c
  * @author Jordan Goulder
  * @brief  Implements MCU Support Package functions that perform low level
  *         peripheral initialization. These functions are called by the HAL.
  ******************************************************************************
*/

#include "stm32f4xx_hal.h"

#include <string.h>

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    // Using the following pins for SPI
    //  NSS  = PB6
    //  SCK  = PA5
    //  MISO = PA6
    //  MOSI = PA7

    // Enable GPIO Port A clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Enable GPIO Port B clock
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Enable SPI 1 clock
    __HAL_RCC_SPI1_CLK_ENABLE();

    // Structure used to initialize GPIO pins
    GPIO_InitTypeDef gpioInit;
    memset(&gpioInit, 0, sizeof(gpioInit));

    // Configure NSS Pin
    gpioInit.Pin        = GPIO_PIN_6;
    gpioInit.Mode       = GPIO_MODE_OUTPUT_PP;
    gpioInit.Pull       = GPIO_PULLUP;
    gpioInit.Speed      = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOB, &gpioInit);

    // Configure SCK Pin
    gpioInit.Pin        = GPIO_PIN_5;
    gpioInit.Mode       = GPIO_MODE_AF_PP;
    gpioInit.Alternate  = GPIO_AF5_SPI1;
    gpioInit.Pull       = GPIO_PULLDOWN;
    gpioInit.Speed      = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOA, &gpioInit);

    // Configure MOSI Pin
    gpioInit.Pin        = GPIO_PIN_7;
    gpioInit.Mode       = GPIO_MODE_AF_PP;
    gpioInit.Alternate  = GPIO_AF5_SPI1;
    gpioInit.Pull       = GPIO_PULLUP;
    gpioInit.Speed      = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOA, &gpioInit);

    // Configure MISO Pin
    gpioInit.Pin        = GPIO_PIN_6;
    gpioInit.Mode       = GPIO_MODE_INPUT;
    gpioInit.Alternate  = GPIO_AF5_SPI1;
    gpioInit.Pull       = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &gpioInit);

    // Enable GPIO Port C clock
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Configure Laser Toggle Pin
    gpioInit.Pin        = GPIO_PIN_0;
    gpioInit.Mode       = GPIO_MODE_OUTPUT_PP;
    gpioInit.Pull       = GPIO_PULLDOWN;
    gpioInit.Speed      = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOC, &gpioInit);

}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
    // Reset SPI 1
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();

    // Put GPIO pins back to default state
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);
}

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *hTimer)
{
   if (hTimer->Instance == TIM3)
   {
       // Timer 3 Channel 1 and Channel 2 pins are on PC6 and PC7
       // Enable GPIO Port C clock
       __HAL_RCC_GPIOC_CLK_ENABLE();

       // Enable Timer 3 clock
       __HAL_RCC_TIM3_CLK_ENABLE();

       // Structure used to initialize GPIO pins
       GPIO_InitTypeDef gpioInit;

       // Configure GPIO Timer 3 channel 1 pin
       gpioInit.Pin = GPIO_PIN_6;
       gpioInit.Mode =  GPIO_MODE_AF_PP;
       gpioInit.Alternate = GPIO_AF2_TIM3;
       gpioInit.Pull = GPIO_PULLUP;
       gpioInit.Speed = GPIO_SPEED_FAST;

       HAL_GPIO_Init(GPIOC, &gpioInit);

       // Configure GPIO Timer 3 channel 2 pin
       gpioInit.Pin = GPIO_PIN_7;
       gpioInit.Mode =  GPIO_MODE_AF_PP;
       gpioInit.Alternate = GPIO_AF2_TIM3;
       gpioInit.Pull = GPIO_PULLUP;
       gpioInit.Speed = GPIO_SPEED_FAST;

       HAL_GPIO_Init(GPIOC, &gpioInit);
   }
   else if (hTimer->Instance == TIM1)
   {
       // Timer 1 Channel 1 and Channel 2 pins are on PA8 and PA9
       // Enable GPIO Port A clock
       __HAL_RCC_GPIOA_CLK_ENABLE();

       // Enable Timer 1 clock
       __HAL_RCC_TIM1_CLK_ENABLE();

       // Structure used to initialize GPIO pins
       GPIO_InitTypeDef gpioInit;

       // Configure GPIO Timer 1 channel 1 pin
       gpioInit.Pin = GPIO_PIN_8;
       gpioInit.Mode =  GPIO_MODE_AF_PP;
       gpioInit.Alternate = GPIO_AF1_TIM1;
       gpioInit.Pull = GPIO_PULLUP;
       gpioInit.Speed = GPIO_SPEED_FAST;

       HAL_GPIO_Init(GPIOA, &gpioInit);

       // Configure GPIO Timer 1 channel 2 pin
       gpioInit.Pin = GPIO_PIN_9;
       gpioInit.Mode =  GPIO_MODE_AF_PP;
       gpioInit.Alternate = GPIO_AF1_TIM1;
       gpioInit.Pull = GPIO_PULLUP;
       gpioInit.Speed = GPIO_SPEED_FAST;

       HAL_GPIO_Init(GPIOA, &gpioInit);
   }
}

void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *hTimer)
{
   if (hTimer->Instance == TIM3)
   {
       // Reset Timer 3
       __HAL_RCC_TIM3_FORCE_RESET();
       __HAL_RCC_TIM3_RELEASE_RESET();

       // Put GPIO pins back to default state
       HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);
   }
   else if (hTimer->Instance == TIM1)
   {
       // Reset Timer 1
       __HAL_RCC_TIM1_FORCE_RESET();
       __HAL_RCC_TIM1_RELEASE_RESET();

       // Put GPIO pins back to default state
       HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8 | GPIO_PIN_9);
   }
}
