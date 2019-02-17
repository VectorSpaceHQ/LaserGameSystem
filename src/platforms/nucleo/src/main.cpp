#include <app_cfg.h>
#include <cpu_core.h>
#include <DisplayIfc.h>
#include <ucos_ii.h>
#include <stm32f4xx_hal.h>

#include "NucleoHal.h"
#include "GameSystem.h"
#include "LaserDisplay.h"

TIM_HandleTypeDef timerHandle;
static OS_STK App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static void AppTaskStart (void *p_arg);
static void SystemClkCfg (void);
static void SetupTimerInterrupt();

int main (void)
{
#if (OS_TASK_NAME_EN > 0u)
   CPU_INT08U os_err;
#endif

   // Declare our stack on the heap
//   OS_STK*  App_TaskStartStk = new OS_STK[APP_CFG_TASK_START_STK_SIZE];
//   memset(&App_TaskStartStk[0], 0, sizeof(OS_STK) * APP_CFG_TASK_START_STK_SIZE);

   HAL_Init();
   CPU_IntDis();
   OSInit();
   OSTaskCreateExt( AppTaskStart,
         0,
         &App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
         APP_CFG_TASK_START_PRIO,
         APP_CFG_TASK_START_PRIO,
         &App_TaskStartStk[0],
         APP_CFG_TASK_START_STK_SIZE,
         0,
         (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_EN > 0u)
         OSTaskNameSet( APP_CFG_TASK_START_PRIO,
         (INT8U *)"App Task Start",
         &os_err);
#endif

   OSStart();

   while (DEF_TRUE);

   return 0;
}

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
   CPU_INT32U cpu_clk;
   HAL_NVIC_SetPriorityGrouping(0);

   if (OSRunning > 0u)
   {
      cpu_clk = HAL_RCC_GetHCLKFreq();
      OS_CPU_SysTickInitFreq(cpu_clk);
   }

   return (HAL_OK);
}

uint32_t HAL_GetTick(void)
{
   CPU_INT32U os_tick_ctr;
#if (OS_VERSION >= 30000u)
   OS_ERR os_err;
   os_tick_ctr = OSTimeGet(&os_err);
#else
   os_tick_ctr = OSTimeGet();
#endif

   return os_tick_ctr;
}

static LaserDisplay *pLaserDisplay = nullptr;

static void AppTaskStart (void *p_arg)
{
   (void)p_arg;

   SystemClkCfg();

   NucleoHal      nucleoHal;
   LaserDisplay   laserDisplay(dynamic_cast<HAL::Hal&>(nucleoHal));

   pLaserDisplay = &laserDisplay;

   SetupTimerInterrupt();

   GameSystem  sys(dynamic_cast<HAL::Hal&>(nucleoHal),
                   dynamic_cast<DisplayIfc&>(laserDisplay));

   sys.Start(0);
}


#ifdef __cplusplus
extern "C" {
#endif

void TIM2_IRQHandler(void)
{
   HAL_TIM_IRQHandler(&timerHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   if (pLaserDisplay)
   {
      pLaserDisplay->Update();
   }
}

#ifdef __cplusplus
}
#endif

static void SetupTimerInterrupt()
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM2_IRQn, TICK_INT_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    // Set Timer 2 to a frequency of 1 MHz
    uint32_t timerFreq = 1000000;

    // Use a interrupt frequency
    uint32_t interruptFreq = 2000;

    // Timer 2 Peripherial clock
    uint32_t peripherialClock = SystemCoreClock / 2;

    timerHandle.Instance = TIM2;
    timerHandle.Init.Prescaler = (peripherialClock / timerFreq) - 1;
    timerHandle.Init.Period =  (timerFreq / interruptFreq) - 1;
    timerHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    timerHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_Base_Init(&timerHandle);
    HAL_TIM_Base_Start_IT(&timerHandle);
}

static void SystemClkCfg (void)
{
   RCC_OscInitTypeDef RCC_OscInitStruct;
   RCC_ClkInitTypeDef RCC_ClkInitStruct;

   HAL_RCC_DeInit();

   __HAL_RCC_PWR_CLK_ENABLE();
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
   RCC_OscInitStruct.PLL.PLLM = 8;
   RCC_OscInitStruct.PLL.PLLN = 336;
   RCC_OscInitStruct.PLL.PLLP = 4;
   RCC_OscInitStruct.PLL.PLLQ = 7;
   HAL_RCC_OscConfig(&RCC_OscInitStruct);

   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
   HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

   if (HAL_GetREVID() == 0x1001)
   {
      __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
   }
}
