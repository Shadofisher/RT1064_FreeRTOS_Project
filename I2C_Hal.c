#include <stdio.h>
#include <stdlib.h>
#include "I2C_Hal.h"

const lpi2c_master_config_t LPI2C3_masterConfig = {
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
};
lpi2c_master_transfer_t LPI2C3_masterTransfer = {
  .flags = kLPI2C_TransferDefaultFlag,
  .slaveAddress = 0,
  .direction = kLPI2C_Write,
  .subaddress = 0,
  .subaddressSize = 1,
  .data = LPI2C3_masterBuffer,
  .dataSize = 1
};
lpi2c_master_handle_t LPI2C3_masterHandle;
uint8_t LPI2C3_masterBuffer[LPI2C3_MASTER_BUFFER_SIZE];

static void LPI2C3_init(void) {
  LPI2C_MasterInit(IMU_MASTER, &LPI2C3_masterConfig, LPI2C3_CLOCK_FREQ);
  LPI2C_MasterTransferCreateHandle(LPI2C3_PERIPHERAL, &LPI2C3_masterHandle, NULL, NULL);
}
status_t i2c_result = kStatus_Fail;
int32_t HAL_FS_I2CRead (LPI2C_Type * base, uint8_t dev_id, uint16_t RegAddr, uint8_t *rxBuff, uint16_t rxCount, bool Addr16)
{
	uint8_t RegAddrHi = 	RegAddr>>8;  
	uint8_t RegAddrLo = 	RegAddr;
	size_t txCount;
	
	dev_id >>= 1;				// Library Functions Below Assume ID Is in Lower 7-Bits (0-6) Of dev_id (Left Shift To Counter This)
	
	i2c_result = LPI2C_MasterStart(base, dev_id, kLPI2C_Write);
	
	if (i2c_result == kStatus_Success)
	{
		LPI2C_MasterGetFifoCounts(base, NULL, &txCount);
		
		if (LPI2C_MasterGetStatusFlags(base) & kLPI2C_MasterNackDetectFlag)
		{
			printf("I2C Error: File %s Line %d",__FILE__,__LINE__);
			return kStatus_LPI2C_Nak;
		}
		
		if(Addr16)
		{
			i2c_result = LPI2C_MasterSend(base, &RegAddrHi, 1);
		
			if (i2c_result != kStatus_Success)
			{
				if (i2c_result == kStatus_LPI2C_Nak)
					LPI2C_MasterStop(base);
				
				printf("I2C Error: File %s Line %d Status (%u)", __FILE__, __LINE__, i2c_result);
				return -1;
			}
		}
		
		i2c_result = LPI2C_MasterSend(base, &RegAddrLo, 1);
		
		if (i2c_result != kStatus_Success)
		{
			if (i2c_result == kStatus_LPI2C_Nak)
				LPI2C_MasterStop(base);
			
			printf("I2C Error: File %s Line %d Status (%u)", __FILE__, __LINE__, i2c_result);
			return -1;
		}
		//wait();
		i2c_result = LPI2C_MasterRepeatedStart(base, dev_id, kLPI2C_Read);
		
		if (i2c_result != kStatus_Success)
		{
			printf("I2C Error: File %s Line %d Status (%u)", __FILE__, __LINE__, i2c_result);
			return -1;
		}

		
		i2c_result = LPI2C_MasterReceive(base, rxBuff, rxCount);
				
		if (i2c_result != kStatus_Success)
		{
			if (i2c_result == kStatus_LPI2C_Nak)
				LPI2C_MasterStop(base);
		
			//printf("I2C Error: File %s Line %d Status (%u)", __FILE__, __LINE__, i2c_result);
			return -1;
		}
		//wait();
		i2c_result = LPI2C_MasterStop(base);
		
		if (i2c_result != kStatus_Success)
		{
			printf("I2C Error: File %s Line %d Status (%u)", __FILE__, __LINE__, i2c_result);
			return -1;
		}
		return (kStatus_Success);
	}
	else
	{
		printf("I2C Error: File %s Line %d Status (%u)", __FILE__, __LINE__, i2c_result);
		return (-1);
	}
	return(0);
}

void HAL_Init()
{
//  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* iomuxc clock (iomuxc_clk_enable): 0x03U */
//  CLOCK_EnableClock(kCLOCK_IomuxcSnvs);       
//  CLOCK_EnableClock(kCLOCK_Xbar1);   
  LPI2C3_init();
//  FS_InitPin( ACCELINT1port , ACCELINT1pin , PIN_INPUT, PIN_LOW);
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_21_LPI2C3_SDA, 1U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_22_LPI2C3_SCL, 1U); 	
}
