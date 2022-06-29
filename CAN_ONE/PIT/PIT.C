#include "PIT.h"
#include "derivative.h"

void PIT_Init(void)
{
	PITCFLMT_PITE = 0;
	PITCE_PCE0 = 1;
	PITMUX = 0x00;
	PITMTLD0 = 80 - 1;
	PITLD0 = 400 - 1;
	PITINTE_PINTE0 = 1;
	PITCFLMT_PITE = 1;
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vpit0 PIT0(void)
{
	CAN_Send_TIMEBCAK();
}

#pragma CODE_SEG DEFAULT


