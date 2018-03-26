#include "chip.h"

const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;

void sysint_m4(void)
{
	unsigned int *pSCB_VTOR = (unsigned int *) 0xE000ED08;
	extern void *__Vectors;
	*pSCB_VTOR = (unsigned int) &__Vectors;
	
	fpuInit();
	
	Chip_SetupCoreClock(CLKIN_CRYSTAL, MAX_CLOCK_FREQ, true);
	SystemCoreClockUpdate();
}
