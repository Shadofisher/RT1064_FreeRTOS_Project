/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/

#include <stdio.h>
#include <stdlib.h>
#include "clock_config.h"
#include "Gpio_config.h"

#include "I2C_Hal.h"


/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"
#include "Gpio_config.h"
#include "Gpio.h"

osThreadId_t defaultTaskHandle;
osThreadId_t testTaskHandle;

const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t TestTaskHandle;
const osThreadAttr_t TestTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

void TestTask(void *argument)
{
  static uint32_t counter = 0;
  /* Infinite loop */
  for(;;)
  {
      counter++;
      osDelay(500);
      //printf("TestTask: Counter = %d\n\r",counter);
  }
  /* USER CODE END 5 */
}


void StartDefaultTask(void *argument)
{
  static uint32_t counter = 0;
  /* Infinite loop */
  uint8_t rxBuff[10];
  for(;;)
  {
      counter++;
      osDelay(5);
     // printf("DefaultTask: Counter = %d\n\r",counter);
      if(HAL_FS_I2CRead(IMU_MASTER, counter, 0, rxBuff, 1, 0))
      {
          //printf("I2C Device Not found at 0x%x \n\r",counter);
         // printf("\n\r");
      }else
      {
        printf("2C device found..... 0x%x: Tick %d\n\r",counter,xTaskGetTickCount());
      }
      if (counter >= 255)
      {
        counter = 0;
      }
  }
  /* USER CODE END 5 */
}
 void GIO_Test(void);

#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)

DioConfig_t * gpioConfig;
int main(void) {
  int i;
  BOARD_InitBootClocks();
  gpioConfig = Dio_ConfigGet();
  Gpio_Init(gpioConfig);
  /*Clock setting for LPI2C*/
  CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
  CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
  HAL_Init();
  osKernelInitialize();
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  testTaskHandle = osThreadNew(TestTask, NULL, &TestTask_attributes);
  osKernelStart();
  for(;;);
}

/*************************** End of file ****************************/
