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
#include "I2C_config.h"

#include "I2C_Hal.h"
#include "unity.h"
#include "Fib.h"
#include "I2C.h"

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

uint32_t  ACCELERMOTER_Master = 0;
uint32_t  NFC_Master = 0;

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

osThreadId_t NFCTaskHandle;
const osThreadAttr_t NFCTask_attributes = {
  .name = "NFCTask",
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


void StartNFCTask(void * argument)
{
  static uint32_t counter = 0;
  /* Infinite loop */
  uint8_t rxBuff[10];
    for(;;)
  {
      counter++;
      osDelay(5);
      if (NFC_Master != 0)
      {
        if (I2CRead(NFC_Master, counter, 0, rxBuff, 1, 1))
        {
           //printf("I2C Device Not found at 0x%x \n\r",counter);
           // printf("\n\r");
        }else
        {
          printf("2C device found..... 0x%x: Tick %d\n\r",counter,xTaskGetTickCount());
        }
      }else
      {
        printf("No Valid I2C for NFC\n\r");
        osDelay(1000);
      }
      if (counter >= 255)
      {
        counter = 0;
      }
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
      if (ACCELERMOTER_Master != 0)
      {
        if (I2CRead(ACCELERMOTER_Master, counter, 0, rxBuff, 1, 0))
        {
           //printf("I2C Device Not found at 0x%x \n\r",counter);
           // printf("\n\r");
        }else
        {
          printf("2C device found..... 0x%x: Tick %d\n\r",counter,xTaskGetTickCount());
        }
      }else
      {
        printf("No Valid I2C for accelerometer\n\r");
        osDelay(1000);
      }
      if (counter >= 255)
      {
        counter = 0;
      }
  }
  /* USER CODE END 5 */
}
 void GIO_Test(void);

void test_FindFunction_WhichIsBroken_ShouldReturnZeroIfItemIsNotInList_WhichWorksEvenInOurBrokenCode(void);
void test_FindFunction_WhichIsBroken_ShouldReturnTheIndexForItemsInList_WhichWillFailBecauseOurFunctionUnderTestIsBroken(void);
void test_TheFirst(void);
void test_eleent0_should_return1(void);
void test_eleent1_should_return1(void);
void test_eleent2_should_return2(void);
void test_eleent5_should_return8(void);
void test_part_of_sequence (void);
void test_negative_negative_values_return_0(void);
void test_overrun_values_return_0(void);

DioConfig_t * gpioConfig;
I2C_Config_t * I2C_Conf; 

void setUp(void);

int main(void) {
  int i;
  BOARD_InitBootClocks();
  gpioConfig = Gpio_ConfigGet();
  Gpio_Init(gpioConfig);
  I2C_Conf = I2C_GetConfig();
  I2C_SetConfig(I2C_Conf);
  for (i = 0; i < 2; i++)
  {
    if (I2C_Conf->I2C_conf & ACCEL)
    {
      printf("Setting up acceleroter");
      ACCELERMOTER_Master = I2C_Conf->I2CBase;

    }else
    {
      if (I2C_Conf->I2C_conf & NFC)
      {
        printf("Setting up NFC");
        NFC_Master = I2C_Conf->I2CBase;
      }
    }
    I2C_Conf++;
  }
  printf("i2C Caps: 0x%x",I2C_Conf->I2C_conf);
  I2C_Conf++;
  printf("i2C Caps: 0x%x",I2C_Conf->I2C_conf);

  UNITY_BEGIN();
  RUN_TEST(test_eleent0_should_return1);
  RUN_TEST(test_eleent1_should_return1);
  RUN_TEST(test_eleent2_should_return2);
  RUN_TEST(test_eleent5_should_return8);
  RUN_TEST(test_part_of_sequence);
  RUN_TEST(test_negative_negative_values_return_0);
  RUN_TEST(test_overrun_values_return_0);

  UNITY_END();

  osKernelInitialize();
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  testTaskHandle = osThreadNew(TestTask, NULL, &TestTask_attributes);
  //NFCTaskHandle = osThreadNew(StartNFCTask, NULL, &NFCTask_attributes); fails as device not yet set up on bus
  osKernelStart();
  for(;;);
}

/*************************** End of file ****************************/
