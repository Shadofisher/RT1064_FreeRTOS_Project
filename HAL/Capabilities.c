
#include "Capabilities.h"

#define LPI2C_CLOCK_FREQ 3000000UL
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)



I2C_Capabilites_t I2C_Capabilites[] = 
{ 
  {LPI2C4_BASE,NFC,{
  .enableMaster = true,
  .enableDoze = true,
  .debugEnable = false,
  .ignoreAck = false,
  .pinConfig = kLPI2C_2PinOpenDrain,
  .baudRate_Hz = 100000UL,
  .busIdleTimeout_ns = 0UL,
  .pinLowTimeout_ns = 0UL,
  .sdaGlitchFilterWidth_ns = 0U,
  .sclGlitchFilterWidth_ns = 0U,
  .hostRequest = {
    .enable = false,
    .source = kLPI2C_HostRequestExternalPin,
    .polarity = kLPI2C_HostRequestPinActiveHigh
  }
  }},
  {LPI2C3_BASE,ACCEL,
  {
  .enableMaster = true,
  .enableDoze = true,
  .debugEnable = false,
  .ignoreAck = false,
  .pinConfig = kLPI2C_2PinOpenDrain,
  .baudRate_Hz = 100000UL,
  .busIdleTimeout_ns = 0UL,
  .pinLowTimeout_ns = 0UL,
  .sdaGlitchFilterWidth_ns = 0U,
  .sclGlitchFilterWidth_ns = 0U,
  .hostRequest = {
    .enable = false,
    .source = kLPI2C_HostRequestExternalPin,
    .polarity = kLPI2C_HostRequestPinActiveHigh
  }
  }},
};

I2C_Capabilites_t * I2C_GetCapabilities(void)
{
  return((I2C_Capabilites_t *)I2C_Capabilites);
}

void I2C_SetCapabilities_Init(I2C_Capabilites_t * I2C_Cap)
{
  lpi2c_master_config_t * configuration;
  uint8_t i;
  CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT);
  CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);


  for (i =0; i < NUM_I2C_INTERFACES; i++)
  {
    //configuration = (lpi2c_master_config_t *)&I2C_Capabilites[i].hw_config;
    configuration = (lpi2c_master_config_t *)&I2C_Cap->hw_config;
    LPI2C_MasterInit((LPI2C_Type *)I2C_Cap->I2CBase, (lpi2c_master_config_t *)configuration, LPI2C_CLOCK_FREQ); 
    I2C_Cap++;
  }
  
}





