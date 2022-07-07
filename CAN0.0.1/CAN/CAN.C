#include "derivative.h"
#include "CAN.h"

void CAN1_Init(void)
{
	CAN_INIT(&CAN_HwCfg);
}

/*CAN初始化函数*/
void CAN_INIT(CAN_TYPE *Can_InitData)
{
	if (CAN1CTL0_INITRQ == 0)
	{
		CAN1CTL0_INITRQ = 1;
	}
	while (CAN1CTL1_INITAK == 0)
	{

	}

	CAN1BTR0_SJW = 0;

	if (Can_InitData->BPS == CAN_125K)
	{
		CAN1BTR1 |= 0x1D;
		CAN1BTR0_BRP = 0X0E;
	}
	else if (Can_InitData->BPS == CAN_250K)
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

/*报文发送函数*/
char CAN_SendMsg(Can_Msg SendMsgData)
{
	unsigned char SendBuf, sp;

	/*判断发送报文长度*/
	if (SendMsgData.len > Msg_MaxLen)
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
		SendBuf = CAN1TBSEL;
	}while (!(SendBuf));

	/*扩展帧ID发送*/
	if (SendMsgData.RTR)
	{
  	CAN1TXIDR0 = (unsigned char)(SendMsgData.id >> 21);
  	CAN1TXIDR1 = (unsigned char)(SendMsgData.id >> 13) & 0xE0;
  	CAN1TXIDR1 |= 0x18;
  	CAN1TXIDR1 |= (unsigned char)(SendMsgData.id >> 15) & 0x07;
  	CAN1TXIDR2 = (unsigned char)(SendMsgData.id >> 7);
  	CAN1TXIDR3 = (unsigned char)(SendMsgData.id << 1);

		CAN1TXIDR3 |= 0x01;

	}
	else
	{
	/*标准帧ID发送*/
  	CAN1TXIDR0 = (unsigned char)(SendMsgData.id>>3);
  	CAN1TXIDR1 = (unsigned char)(SendMsgData.id<<5);
	}

	/*报文数据发送*/
	for (sp = 0; sp < SendMsgData.len;sp++)
	{
		*((&CAN1TXDSR0) + sp) = SendMsgData.data[sp];
	}
	/*报文长度发送*/
	CAN1TXDLR = SendMsgData.len;

	CAN1TXTBPR = SendMsgData.prty;
	/*清除标志*/
	CAN1TFLG = SendBuf;

	return TRUE;
}

/*报文周期发送函数*/
void CAN_Send_TIME(Can_Time Can_TimeType)
{
	static int CAN_TMIE ;

	CAN_TMIE++;

	if ( CAN_TMIE == 50)
	{
      CAN_SendMsg(CanMsg_3);
	}
	if ( CAN_TMIE == 70)
	{
      CAN_SendMsg(CanMsg_2);
	}
	if ( CAN_TMIE == 90)
	{
     CAN_SendMsg(CanMsg_1);
	}
   if (CAN_TMIE >= 100)
	{
     CAN_TMIE = 0;
	}
}

/*发送所有函数*/
void CanMsg_SendAll(void)
{
	CAN_Send_TIME(Can_Time_Type);
}

/*报文接收函数*/
Bool CAN1GetMsg(Can_Msg *Msg_Git)
{

	unsigned char sp;

	/*检测接收标志*/
	if(!(CAN1RFLG_RXF))
	{
		return(FALSE);
	}

	/*检测 CAN协议报文模式 （一般/扩展） 标识符*/
	if(CAN1RXIDR1_IDE)
	{
    // IDE = Recessive (Extended Mode)
    	return(FALSE);
	}
	/*读标识符*/
   Msg_Git ->id = (unsigned int)(CAN1RXIDR0<<3) |
            (unsigned char)(CAN1RXIDR1>>5);

	if(CAN1RXIDR1&0x10)
	{
		Msg_Git->RTR = TRUE;
	}
  else
  	{
    	Msg_Git->RTR = FALSE;
    }

	/*读取数据长度 */
	Msg_Git->len = CAN1RXDLR;

	/*读取数据*/
	for(sp = 0; sp < Msg_Git->len; sp++)
  	{
    	Msg_Git->data[sp] = *((&CAN1RXDSR0)+sp);
	}
	/*清RXF标志位 (缓冲器准备接收)*/
	CAN1RFLG = 0x01;

	return TRUE;
}
/*接收报文数据处理函数*/
extern Bool CAN1_GetCallBack(void)
{
	if (CAN1GetMsg(&Can1_GetType) == TRUE)
	{
		/*接收信息*/
		if (Can1_GetType.id == 0x3c && (!Can1_GetType.RTR))
		{
			CAN_SendMsg(CanMsg_3);
		}

    }
}


