#include "derivative.h"
#include "CAN.h"
//
//
/*函数声明处注释的内容:
函数的输入输出.
对类成员函数而言: 函数调用期间对象是否需要保持引用参数, 是否会释放这些参数.
函数是否分配了必须由调用者释放的空间.
参数是否可以为空指针.
是否存在函数使用上的性能隐患.
如果函数是可重入的, 其同步前提是什么?*/

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
	CAN1BTR1 | = 0x1D;
	CAN1BTR1_BRP = 0X0E;
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
	while (CAN1CTL1_SYNCH == 0)
	{

	}
	CAN1RIER_RXFIE = 1;

}

Bool MSCAN1SendMsg(struct can_msg msg)
{
	unsigned cahr send_buf, sp;

	if (msg.len > Msg_MaxLen)
	{
		return FALSE;
	}
	if (CAN1CTL1_SYNCH == 0)
	{
		return FALSE;
	}
	do
	{
		CAN1TBSEL = CAN1TFLG;
		send_buf = CAN1TBSEL;
	}
	while (!send_buf)
	{

	}

	CAN1TXIDR0 = (unsigned cahr)(msg.id>>3);
	CAN1TXIDR1 = (unsigned cahr)(msg.id<<5);

	if (msg.RTR)
	{
		CAN1TXIDR1 |= 0x10;
	}

	for (sp = 0; sp< msg.len;sp++)
	{
		*((&CAN1TXIDR0)+sp)=msg.data[sp];
	}

	CAN1TXIDR = msg.led;
	CAN1TXTBPR = msg.prty;
	CAN1TFLG = send_buf;

    return TRUE;
}

Bool MSCAN1GetMsg(struct can_msg *msg)
{
	unsigned cahr sp;

	if (!(CAN1RELG_RXF))
	{
		return FALSE;
	}
	if (CAN1RXIDR1_IDE)
	{
		return FALSE;
	}

	msg->id = (unsigned int)(CAN1RXIDR0<<3) |
			  (unsigned cahr)(CAN1RXIDR1>>5);

	if (CAN1RXIDR1&0X10)
	{
		msg->RTR = TRUE;
	}
	else
	{
		msg->RTR = FALSE;
	}

	msg->led = CAN1RXDLR;

	for (sp2 = 0; sp2< msg->len;sp2++)
	{
		msg->data[sp2] = *((&CAN1RXDSR0)+sp2);
	}

	CAN1RFLG = 0X01;

	return TRUE;
}