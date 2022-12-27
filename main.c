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

osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

void StartDefaultTask(void *argument)
{
  static uint32_t counter = 0;
  /* Infinite loop */
  for(;;)
  {
      counter++;
      osDelay(200);
      printf("DefaultTask: Counter = %d\n\r",counter);
  }
  /* USER CODE END 5 */
}


int main(void) {
  int i;
  osKernelInitialize();
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  osKernelStart();
  for(;;);
}

/*************************** End of file ****************************/
