#include "derivative.h"

void CAN_INIT(void)
{
	CAN1_INIT(&Can_InitTypeSendData);
}

/*CAN初始化函数*/
void CAN1_INIT(Can_InitType *Can_InitTypeCfg)
{
	if (CAN1CTL0_INITRQ == 0)
	{
		CAN1CTL0_INITRQ = 1;
	}
	else
	{

	}

	CAN1BTR0_SJW = 0;

	if (Can_InitTypeCfg->Can_InitTypeBPS == CAN_BSPTYPE125K)
	{
		CAN1BTR1 |= 0x1D;
		CAN1BTR0_BRP = 0x0E;
	}
	else if (Can_InitTypeCfg->Can_InitTypeBPS == CAN_BSPTYPE250K)
	{

	}
	else
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
Bool Can_SendMsg(Can_MsgType *Can_MsgTypeCfg)
{
	unsigned char SendBuf, sp;

	/*判断发送报文长度*/
	if (Can_MsgTypeCfg->Can_MsgTypeLen > CAN_MSGTYPE_DATA_MAXLEN)
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
	if (Can_MsgTypeCfg->Can_MsgTypeIde)
	{
  	CAN1TXIDR0 = (unsigned char)(Can_MsgTypeCfg->Can_MsgTypeId >> 21);
  	CAN1TXIDR1 = (unsigned char)(Can_MsgTypeCfg->Can_MsgTypeId >> 13) & 0xE0;
  	CAN1TXIDR1 |= 0x18;
  	CAN1TXIDR1 |= (unsigned char)(Can_MsgTypeCfg->Can_MsgTypeId >> 15) & 0x07;
  	CAN1TXIDR2 = (unsigned char)(Can_MsgTypeCfg->Can_MsgTypeId >> 7);
  	CAN1TXIDR3 = (unsigned char)(Can_MsgTypeCfg->Can_MsgTypeId << 1);
	CAN1TXIDR3 |= 0x01;
	}
	else
	{
	/*标准帧ID发送*/
  	CAN1TXIDR0 = (unsigned char)(Can_MsgTypeCfg->Can_MsgTypeId>>3);
  	CAN1TXIDR1 = (unsigned char)(Can_MsgTypeCfg->Can_MsgTypeId<<5);
	}

	/*报文数据发送*/
	for (sp = 0; sp < Can_MsgTypeCfg->Can_MsgTypeLen;sp++)
	{
		*((&CAN1TXDSR0) + sp) = Can_MsgTypeCfg-> Can_MsgTypeData[sp];
	}
	/*报文长度发送*/
	CAN1TXDLR = Can_MsgTypeCfg-> Can_MsgTypeLen;

	CAN1TXTBPR = Can_MsgTypeCfg-> Can_MsgTypePrty;
	/*清除标志*/
	CAN1TFLG = SendBuf;

	return TRUE;
}

/*报文周期发送函数*/
void Can_SendTime(Can_TimeType Can_TimeTypeCfg)
{
	static int Can_TIME ;

	Can_TIME++;

	if (Can_TIME == 50)
	{
    	Can_SendMsg(&Can_MsgTypeSendData1);
	}
	else
	{

	}
	if (Can_TIME == 70)
	{
    	Can_SendMsg(&Can_MsgTypeSendData2);
	}
	else
	{

	}
	if (Can_TIME == 90)
	{
    	Can_SendMsg(&Can_MsgTypeSendData3);
	}
	else
	{

	}
   if (Can_TIME >= 100)
	{
    	Can_TIME = 0;
	}
	else
	{

	}
}

/*发送所有函数*/
void Can_SendMsgAll(void)
{
	Can_SendTime(Can_TimeTypeSendData);
}

/*报文接收函数*/
Bool Can_GetMsg(Can_MsgType *Can_MsgTypeCfg)
{

	unsigned char sp;

	/*检测接收标志*/
	if (!(CAN1RFLG_RXF))
	{
		return(FALSE);
	}
	else
	{

	}

	/*检测 CAN协议报文模式 （一般/扩展） 标识符*/
	if (CAN1RXIDR1_IDE)
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

	if (CAN1RXIDR1 & 0x10)
	{
		Can_MsgTypeCfg->Can_MsgTypeIde = TRUE;
	}
	else
  	{
    	Can_MsgTypeCfg->Can_MsgTypeIde = FALSE;
    }

	/*读取数据长度 */
	Can_MsgTypeCfg->Can_MsgTypeLen = CAN1RXDLR;

	/*读取数据*/
	for (sp = 0; sp < Can_MsgTypeCfg->Can_MsgTypeLen; sp++)
  	{
    	Can_MsgTypeCfg->Can_MsgTypeData[sp] = *((&CAN1RXDSR0)+sp);
	}
	/*清RXF标志位 (缓冲器准备接收)*/
	CAN1RFLG = 0x01;

	return TRUE;
}

/*接收报文数据处理函数*/
Bool Can_GetCallBack(void)
{
	if (Can_GetMsg(&Can_MsgTypeGetData) == TRUE)
	{
		/*接收信息*/
		if (Can_MsgTypeGetData.Can_MsgTypeId == 0x3c && (!Can_MsgTypeGetData.Can_MsgTypeIde))
		{
			Can_SendMsg(&Can_MsgTypeSendData3);
		}
		else
		{

		}
    }
    else
	{

	}
}


