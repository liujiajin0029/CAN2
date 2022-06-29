#include "derivative.h"
#include "CAN.h"

void CAN1_Init(void)
{
	CAN_INIT(&CAN_HwCfg);
}

void CAN_INIT(CAN_TYPE *can_InitData)
{
	if (CAN1CTL0_INITRQ == 0)
	{
		CAN1CTL0_INITRQ = 1;
	}
	while (CAN1CTL1_INITAK == 0)
	{

	}

	CAN1BTR0_SJW = 0;

	if (can_InitData->BPS == CAN_125K)
	{
	CAN1BTR1 |= 0x1D;
	CAN1BTR0_BRP = 0X0E;
	}
	else if (can_InitData->BPS == CAN_250K)
	{

	}

	CAN1IDMR0 = 0xFF;
	CAN1IDMR1 = 0xFF;
	CAN1IDMR3 = 0xFF;
	CAN1IDMR4 = 0xFF;
	CAN1IDMR5 = 0xFF;
	CAN1IDMR6 = 0XFF;
	CAN1IDMR7 = 0xFF;
	CAN1CTL1 = 0xC0;
	CAN1CTL0 = 0x00;

	while (CAN1CTL1_INITAK)
	{

	}
	while (CAN1CTL0_SYNCH == 0)
	{

	}

	CAN1RIER_RXFIE = 1;

}

char MSCAN1SendMsg(can_msg msg)
{
	unsigned char send_buf, sp;

	if (msg.len > Msg_MaxLen)
	{
		return FALSE;
	}
	if (CAN1CTL0_SYNCH == 0)
	{
		return FALSE;
	}
	do
	{
		CAN1TBSEL = CAN1TFLG;
		send_buf = CAN1TBSEL;
	}while (!(send_buf));

	CAN1TXIDR0 = (unsigned char)(msg.id>>3);
	CAN1TXIDR1 = (unsigned char)(msg.id<<5);

	if (msg.RTR)
	{
		CAN1TXIDR1 |= 0x10;
	}

	for (sp = 0; sp < msg.len;sp++)
	{
		*((&CAN1TXIDR0) + sp) = msg.data[sp];
	}

	CAN1TXDLR = msg.len;
	CAN1TXTBPR = msg.prty;
	CAN1TFLG = send_buf;

	return TRUE;
}

void CAN_Send_TIME(can_time *can_timeType)
{
	int  TMIE;
	static int CAN_TMIE_INIT=0;
	static int CAN_TMIE=0;

	CAN_TMIE++;

	if (CAN_TMIE == can_timeType->time_a)
   {
     MSCAN1SendMsg(CanMsg_3);
   }
	if (CAN_TMIE == can_timeType->time_b)
   {
     MSCAN1SendMsg(CanMsg_2);
   }
	if (CAN_TMIE >= can_timeType->time_c)
   {
     MSCAN1SendMsg(CanMsg_1);
     CAN_TMIE=0;
   }
}

void CAN_Send_TIMEBCAK(void)
{
	CAN_Send_TIME(&can_time_Type);
}

