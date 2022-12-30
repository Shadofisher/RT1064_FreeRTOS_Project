#include "MIMXRT1064.h"
#include <stdint.h>

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
