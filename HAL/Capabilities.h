#ifndef __CAPABILITIES
#define __CAPABILITIES

#include <stdint.h>
#include "MIMXRT1064.h"
#include "fsl_lpi2c.h"

#define NUM_I2C_INTERFACES (2)

/*Add other interfaces here*/


typedef enum
{
  NONE          = 0,
  ACCEL         = 1,
  NFC           = 2,
  TEMPERATURE   = 4,
} I2C_Funtions_t;

typedef struct 
{ 
  uint32_t I2CBase;
  uint8_t  I2C_cap;
  lpi2c_master_config_t hw_config;
} I2C_Capabilites_t;

I2C_Capabilites_t * I2C_GetCapabilities(void);
void I2C_SetCapabilities_Init(I2C_Capabilites_t * I2C_Cap);
#endif //__CAPBILITIES
