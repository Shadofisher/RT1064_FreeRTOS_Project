#include "MIMXRT1064.h"
#include <stdint.h>
#include <stdio.h>
#include "I2C.h"

#define NUM_PORTS 4

#define I2C_1 LPI2C1
#define I2C_2 LPI2C2
#define I2C_3 LPI2C3
#define I2C_4 LPI2C4


#if 0

uint32_t volatile * const portverid[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->VERID, 
	(uint32_t *)&LPI2C2->VERID, 
	(uint32_t *)&LPI2C3->VERID, 
	(uint32_t *)&LPI2C4->VERID
};

uint32_t volatile * const portmasterctrl[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MCR, 
	(uint32_t *)&LPI2C2->MCR, 
	(uint32_t *)&LPI2C3->MCR, 
	(uint32_t *)&LPI2C4->MCR
};

uint32_t volatile * const portmasterstausl[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MSR, 
	(uint32_t *)&LPI2C2->MSR, 
	(uint32_t *)&LPI2C3->MSR, 
	(uint32_t *)&LPI2C4->MSR
};

uint32_t volatile * const portmasterint[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MIER, 
	(uint32_t *)&LPI2C2->MIER, 
	(uint32_t *)&LPI2C3->MIER, 
	(uint32_t *)&LPI2C4->MIER
};

uint32_t volatile * const portmasterconfig0[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MCFGR0, 
	(uint32_t *)&LPI2C2->MCFGR0, 
	(uint32_t *)&LPI2C3->MCFGR0, 
	(uint32_t *)&LPI2C4->MCFGR0
};

uint32_t volatile * const portmasterconfig1[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MCFGR1, 
	(uint32_t *)&LPI2C2->MCFGR1, 
	(uint32_t *)&LPI2C3->MCFGR1, 
	(uint32_t *)&LPI2C4->MCFGR1
};

uint32_t volatile * const portmasterconfig2[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MCFGR2, 
	(uint32_t *)&LPI2C2->MCFGR2, 
	(uint32_t *)&LPI2C3->MCFGR2, 
	(uint32_t *)&LPI2C4->MCFGR2
};

uint32_t volatile * const portmasterdatamatch[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MDMR, 
	(uint32_t *)&LPI2C2->MDMR, 
	(uint32_t *)&LPI2C3->MDMR, 
	(uint32_t *)&LPI2C4->MDMR
};

uint32_t volatile * const portmasterclockconfig0[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MCCR0, 
	(uint32_t *)&LPI2C2->MCCR0, 
	(uint32_t *)&LPI2C3->MCCR0, 
	(uint32_t *)&LPI2C4->MCCR0
};

uint32_t volatile * const portmasterclockconfig1[NUM_PORTS] =
{
	(uint32_t *)&LPI2C1->MCCR1, 
	(uint32_t *)&LPI2C2->MCCR1, 
	(uint32_t *)&LPI2C3->MCCR1, 
	(uint32_t *)&LPI2C4->MCCR1
};

#endif

status_t i2c_result;// = kStatus_Fail;
int32_t I2CRead (uint32_t  base_address, uint8_t dev_id, uint16_t RegAddr, uint8_t *rxBuff, uint16_t rxCount, bool Addr16)
{
	uint8_t RegAddrHi = 	RegAddr>>8;  
	uint8_t RegAddrLo = 	RegAddr;
	size_t txCount;
	
        LPI2C_Type * base;
        base = (LPI2C_Type *)base_address;
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

