#ifndef __I2C_H
#define __I2C_H
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_lpspi.h"
#include "fsl_lpuart.h"
#include "fsl_lpi2c.h"
#include "fsl_iomuxc.h"


int32_t I2CRead (uint32_t  base_address, uint8_t dev_id, uint16_t RegAddr, uint8_t *rxBuff, uint16_t rxCount, bool Addr16);
#endif //__I2C_H