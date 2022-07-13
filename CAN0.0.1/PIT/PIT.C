#include "PIT.h"
#include "derivative.h"

void PIT_INIT(void)
{
	PITCFLMT_PITE = 0;
	PITCE_PCE0 = 1;
	PITMUX = 0x00;
	PITMTLD0 = 160 - 1;
	PITLD0 = 200 - 1;
	PITINTE_PINTE0 = 1;
	PITCFLMT_PITE = 1;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vpit0 PIT0(void)
{
	PITTF_PTF0 = 1;
	Can_SendMsgAll();
}

#pragma CODE_SEG DEFAULT


#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
	CAN_GetCallBack();
}

#pragma CODE_SEG DEFAULT


