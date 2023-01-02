#ifndef __I2CCONFIG
#define __I2CCONFIG

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
  uint8_t  I2C_conf;
  lpi2c_master_config_t hw_config;
} I2C_Config_t;

I2C_Config_t * I2C_GetConfig(void);
void I2C_SetConfig(I2C_Config_t * I2C_Conf);
#endif //__CAPBILITIES
