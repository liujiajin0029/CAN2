#include "derivative.h"
#include "CAN.h"

void CAN_INIT(void)
{
	CAN1_Init(&CAN_InitTypeSendData);
}

/*CAN初始化函数*/
void CAN1_Init(CAN_InitType *CAN_InitTypeCfg)
{
	if (CAN1CTL0_INITRQ == 0)
	{
		CAN1CTL0_INITRQ = 1;
	}
	else
	{

	}

	CAN1BTR0_SJW = 0;

	if (CAN_InitTypeCfg->BPS == CAN_125K)
	{
		CAN1BTR1 |= 0x1D;
		CAN1BTR0_BRP = 0X0E;
	}
	else if (CAN_InitTypeCfg->BPS == CAN_250K)
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

	CAN1RIER_RXFIE = 1;
}

/*报文发送函数*/
Bool CAN_SendMsg(Can_MsgType *CAN_InitTypeCfg)
{
	unsigned char SendBuf, sp;

	/*判断发送报文长度*/
	if (CAN_InitTypeCfg->len > Msg_MaxLen)
	{
		return FALSE;
	}
	else
	{

	}
	if (CAN1CTL0_SYNCH == 0)
	{
		return FALSE;
	}
	else
	{

	}
	do
	{
		CAN1TBSEL = CAN1TFLG;
		SendBuf = CAN1TBSEL;
	}while (!(SendBuf));

	/*扩展帧ID发送*/
	if (CAN_InitTypeCfg->Can_MsgTypeIde)
	{
  	CAN1TXIDR0 = (unsigned char)(CAN_InitTypeCfg->Can_MsgTypeId >> 21);
  	CAN1TXIDR1 = (unsigned char)(CAN_InitTypeCfg->Can_MsgTypeId >> 13) & 0xE0;
  	CAN1TXIDR1 |= 0x18;
  	CAN1TXIDR1 |= (unsigned char)(CAN_InitTypeCfg->Can_MsgTypeId >> 15) & 0x07;
  	CAN1TXIDR2 = (unsigned char)(CAN_InitTypeCfg->Can_MsgTypeId >> 7);
  	CAN1TXIDR3 = (unsigned char)(CAN_InitTypeCfg->Can_MsgTypeId << 1);

	CAN1TXIDR3 |= 0x01;

	}
	else
	{
	/*标准帧ID发送*/
  	CAN1TXIDR0 = (unsigned char)(CAN_InitTypeCfg->Can_MsgTypeId>>3);
  	CAN1TXIDR1 = (unsigned char)(CAN_InitTypeCfg->Can_MsgTypeId<<5);
	}

	/*报文数据发送*/
	for (sp = 0; sp < CAN_InitTypeCfg->len;sp++)
	{
		*((&CAN1TXDSR0) + sp) = CAN_InitTypeCfg-> Can_MsgTypeData[sp];
	}
	/*报文长度发送*/
	CAN1TXDLR = CAN_InitTypeCfg-> Can_MsgTypeLen;

	CAN1TXTBPR = CAN_InitTypeCfg-> Can_MsgTypePrty;
	/*清除标志*/
	CAN1TFLG = SendBuf;

	return TRUE;
}

/*报文周期发送函数*/
void CAN_SendTime(Can_TimeType Can_TimeTypeCfg)
{
	static int CAN_TMIE ;

	CAN_TMIE++;

	if (CAN_TMIE == 50)
	{
      CAN_SendMsg(&Can_MsgTypeSendData1);
	}
	else
	{

	}
	if (CAN_TMIE == 70)
	{
      CAN_SendMsg(&Can_MsgTypeSendData2);
	}
	else
	{

	}
	if (CAN_TMIE == 90)
	{
     CAN_SendMsg(&Can_MsgTypeSendData3);
	}
	else
	{

	}
   if (CAN_TMIE >= 100)
	{
     CAN_TMIE = 0;
	}
	else
	{

	}
}

/*发送所有函数*/
void Can_MsgSendAll(void)
{
	CAN_Send_TIME(Can_MsgTypeGetData);
}

/*报文接收函数*/
Bool CAN_GetMsg(Can_MsgType *Can_MsgTypeCfg)
{

	unsigned char sp;

	/*检测接收标志*/
	if(!(CAN1RFLG_RXF))
	{
		return(FALSE);
	}
	else
	{

	}

	/*检测 CAN协议报文模式 （一般/扩展） 标识符*/
	if(CAN1RXIDR1_IDE)
	{
    // IDE = Recessive (Extended Mode)
    	return(FALSE);
	}
	else
	{

	}
	/*读标识符*/
   Can_MsgTypeCfg ->Can_MsgTypeId = (unsigned int)(CAN1RXIDR0<<3) |
            (unsigned char)(CAN1RXIDR1>>5);

	if(CAN1RXIDR1&0x10)
	{
		Can_MsgTypeCfg->RTR = TRUE;
	}
	else
  	{
    	Can_MsgTypeCfg->RTR = FALSE;
    }

	/*读取数据长度 */
	Can_MsgTypeCfg->len = CAN1RXDLR;

	/*读取数据*/
	for(sp = 0; sp < Can_MsgTypeCfg->len; sp++)
  	{
    	Can_MsgTypeCfg->data[sp] = *((&CAN1RXDSR0)+sp);
	}
	/*清RXF标志位 (缓冲器准备接收)*/
	CAN1RFLG = 0x01;

	return TRUE;
}
/*接收报文数据处理函数*/
Bool CAN_GetCallBack(void)
{
	if (CAN1GetMsg(&Can_MsgTypeGetData) == TRUE)
	{
		/*接收信息*/
		if (Can_MsgTypeGetData.Can_MsgTypeId == 0x3c && (!Can_MsgTypeGetData.ide))
		{
			CAN_SendMsg(CanMsg_3);
		}
		else
		{

		}
    }
    else
	{

	}
}


