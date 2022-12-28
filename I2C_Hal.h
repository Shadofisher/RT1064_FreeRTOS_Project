#ifndef _I2C_HAL_H_
#define _I2C_HAL_H_
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_lpspi.h"
#include "fsl_lpuart.h"
#include "fsl_lpi2c.h"
#include "fsl_iomuxc.h"

#define IMU_MASTER_BASE (LPI2C3_BASE)
#define IMU_MASTER ((LPI2C_Type *)IMU_MASTER_BASE)


//#include "fsl_adc.h"
int32_t HAL_FS_I2CRead(LPI2C_Type *base, uint8_t dev_id, uint16_t RegAddr, uint8_t *rxBuff, uint16_t rxCount, bool Addr16);
/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* BOARD_InitPeripherals defines for LPSPI2 */
/* Definition of peripheral ID */
#define FLASH_SPI_PERIPHERAL LPSPI2
/* Definition of clock source */
#define FLASH_SPI_CLOCK_FREQ 6000000UL
/* Definition of peripheral ID */
#define TEMPMON_PERIPHERAL TEMPMON
/* Definition of peripheral ID */
#define RTWDOG_PERIPHERAL RTWDOG
/* Definition of the clock source frequency */
#define RTWDOG_CLOCK_SOURCE 32768UL
/* Definition of peripheral ID */
#define LPUART1_PERIPHERAL LPUART1
/* Definition of the clock source frequency */
#define LPUART1_CLOCK_SOURCE 4000000UL
/* Definition of peripheral ID */
#define GSM_LPUART5_PERIPHERAL LPUART5
/* Definition of the clock source frequency */
#define GSM_LPUART5_CLOCK_SOURCE 4000000UL
/* Definition of peripheral ID */
#define GPS_LPUART4_PERIPHERAL LPUART4
/* Definition of the clock source frequency */
#define GPS_LPUART4_CLOCK_SOURCE 4000000UL
/* Definition of peripheral ID */
#define RS232_LPUART8_PERIPHERAL LPUART8
/* Definition of the clock source frequency */
#define RS232_LPUART8_CLOCK_SOURCE 4000000UL
/* BOARD_InitPeripherals defines for LPI2C3 */
/* Definition of peripheral ID */
#define LPI2C3_PERIPHERAL LPI2C3
/* Definition of clock source */
#define LPI2C3_CLOCK_FREQ 3000000UL
/* Transfer buffer size */
#define LPI2C3_MASTER_BUFFER_SIZE 1
/* Definition of slave address */
#define LPI2C3_MASTER_SLAVE_ADDRESS 0
/* BOARD_InitPeripherals defines for ADC2 */
/* Definition of peripheral ID */
#define ADC2_PERIPHERAL ADC2
/* Definition of special channel interconnected with ADC_ETC which takes real channel to be measured from ADC_ETC. */
#define ADC2_CHANNEL_DRIVEN_BY_ADC_ETC 16U

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const lpspi_master_config_t FLASH_SPI_config;
/* TEMPMON configuration */
extern const lpi2c_master_config_t LPI2C3_masterConfig;
extern lpi2c_master_transfer_t LPI2C3_masterTransfer;
extern uint8_t LPI2C3_masterBuffer[LPI2C3_MASTER_BUFFER_SIZE];
extern lpi2c_master_handle_t LPI2C3_masterHandle;
void HAL_Init(void);

#endif //_I2C_HAL_H_