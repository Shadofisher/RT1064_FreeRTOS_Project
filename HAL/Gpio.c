#include "MIMXRT1064.h"
#include <stdio.h>
#include "Gpio_config.h"
#include "fsl_iomuxc.h"

/******************************************************************************
* Module Typedefs
*******************************************************************************/
#define NUM_PORTS (6)
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
/**
 *  Defines a table of pointers to the peripheral input register on the microcontroller.
 */


uint32_t volatile * const portin[NUM_PORTS] =
{
	(uint32_t *)&GPIO1->DR, 
	(uint32_t *)&GPIO2->DR, 
	(uint32_t *)&GPIO3->DR, 
	(uint32_t *)&GPIO4->DR, 
	(uint32_t *)&GPIO5->DR, 
	(uint32_t *)&GPIO6->DR
};

uint32_t volatile * const portout[NUM_PORTS] =
{
	(uint32_t *)&GPIO1->DR, 
	(uint32_t *)&GPIO2->DR, 
	(uint32_t *)&GPIO3->DR, 
	(uint32_t *)&GPIO4->DR, 
	(uint32_t *)&GPIO5->DR, 
	(uint32_t *)&GPIO6->DR
};

uint32_t volatile * const portsddr[NUM_PORTS] =
{
	(uint32_t *)&GPIO1->GDIR, 
	(uint32_t *)&GPIO2->GDIR, 
	(uint32_t *)&GPIO3->GDIR, 
	(uint32_t *)&GPIO4->GDIR, 
	(uint32_t *)&GPIO5->GDIR, 
	(uint32_t *)&GPIO6->GDIR
};
uint32_t volatile * const portstoggle[NUM_PORTS] =
{
	(uint32_t *)&GPIO1->DR_TOGGLE, 
	(uint32_t *)&GPIO2->DR_TOGGLE, 
	(uint32_t *)&GPIO3->DR_TOGGLE, 
	(uint32_t *)&GPIO4->DR_TOGGLE, 
	(uint32_t *)&GPIO5->DR_TOGGLE, 
	(uint32_t *)&GPIO6->DR_TOGGLE
};

void Gpio_Init(const DioConfig_t * Config)
{
  mux_settings_i2c_t mux;
  uint8_t numpins;
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* iomuxc clock (iomuxc_clk_enable): 0x03U */
  CLOCK_EnableClock(kCLOCK_IomuxcSnvs);       
  CLOCK_EnableClock(kCLOCK_Xbar1);   

  for (numpins = 0; numpins < 8; numpins++)
  {
    if (Config->Function == FCN_ALT)
    {
      printf("MUX Required\n\r");
      mux = Config->io_mux;
      IOMUXC_SetPinMux(mux.muxRegister,mux.muxMode,mux.inputRegister,mux.inputDaisy,mux.configRegister, 1U); 
    }else
    {
      printf("Normal GPIO\n\r");     
    }
    Config++;
  }
}