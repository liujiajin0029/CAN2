#include "derivative.h"
#include "CAN.h"

void CAN_INIT(void)
{
	CAN_INITIPUT(&Can0_InitTypeSendData);
	CAN_INITIPUT(&Can1_InitTypeSendData);
}


/*CAN初始化函数*/
void CAN_INITIPUT(Can_InitType *Can_InitTypeCfg)
{
    unsigned char Memory_address = 0;

    Memory_address = Can_InitTypeCfg->CAN_InitTypeGeway;

	if (*((&CAN0CTL0) + Memory_address) & 0x01 == 0)
	{
		*((&CAN0RXDSR0) + Memory_address) |= 1;
	}
	while (*((&CAN0CTL1) + Memory_address) & 0x01 == 0)
	{

	}

	*((&CAN0BTR0) + Memory_address) |= 0xC0;

	if (Can_InitTypeCfg->Can_InitTypeBPS == CAN_BSPTYPE125K)
	{

		*((&CAN0BTR1) + Memory_address) |= 0x1D;
		*((&CAN0BTR0) + Memory_address)  = 0x0E;

	}
	else if (Can_InitTypeCfg->Can_InitTypeBPS == CAN_BSPTYPE250K)
	{
		*((&CAN0BTR1) + Memory_address) |= 0x1C;
		*((&CAN0BTR0) + Memory_address)  = 0x07;
	}
	else if (Can_InitTypeCfg->Can_InitTypeBPS == CAN_BSPTYPE500K)
    {
		*((&CAN0BTR1) + Memory_address) |= 0x1C;
		*((&CAN0BTR0) + Memory_address)  = 0x03;
    }
    else if (Can_InitTypeCfg->Can_InitTypeBPS == CAN_BSPTYPE1000K)
     {
		*((&CAN0BTR1) + Memory_address) |= 0x1C;
		*((&CAN0BTR0) + Memory_address)  = 0x01;
    }
	else
	{

	}

    *((&CAN0IDMR0) + Memory_address) = 0xFF;
    *((&CAN0IDMR1) + Memory_address) = 0xFF;
    *((&CAN0IDMR3) + Memory_address) = 0xFF;
    *((&CAN0IDMR4) + Memory_address) = 0xFF;
    *((&CAN0IDMR5) + Memory_address) = 0xFF;
    *((&CAN0IDMR6) + Memory_address) = 0XFF;
    *((&CAN0IDMR7) + Memory_address) = 0xFF;
    *((&CAN0CTL1) + Memory_address) = 0xC0;
    *((&CAN0CTL0) + Memory_address) = 0x00;

    while (*((&CAN0CTL1) + Memory_address) & 0x01 == 0)
	{

	}

	*((&CAN1RIER) + Memory_address) |= 0x01;
}

/*报文发送函数*/
Bool Can_SendMsg(Can_MsgType *Can_MsgTypeCfg)
{
	unsigned char SendBuf = 0 , sp = 0 , BlockingTime = 0;
    unsigned char Memory_address = 0;

    Memory_address = Can_MsgTypeCfg->SenGeway ;

	/*判断发送报文长度*/
	if (Can_MsgTypeCfg->Len > CAN_MSGTYPE_DATA_MAXLEN)
	{
		return FALSE;
	}
	while (*((&CAN0CTL0) + Memory_address) & 0x10 == 0)
	{
    	return FALSE;
	}
	do
	{
		*((&CAN0TBSEL) + Memory_address) = *((&CAN0TFLG) + Memory_address);
		SendBuf = *((&CAN0TBSEL) + Memory_address);
		BlockingTime++;
	}while (!(SendBuf) && BlockingTime < 5);

	/*扩展帧ID发送*/
	if (Can_MsgTypeCfg->Ide)
	{
        *((&CAN0TXIDR0) + Memory_address) = (unsigned char)((Can_MsgTypeCfg->Id) >> 21);
        *((&CAN0TXIDR1) + Memory_address) = (unsigned char)(Can_MsgTypeCfg->Id >> 13) & 0xE0;
        *((&CAN0TXIDR1) + Memory_address) |= 0x18;
        *((&CAN0TXIDR1) + Memory_address) |= (unsigned char)(Can_MsgTypeCfg->Id >> 15) & 0x07;
        *((&CAN0TXIDR2) + Memory_address) = (unsigned char)(Can_MsgTypeCfg->Id >> 7);
        *((&CAN0TXIDR3) + Memory_address) = (unsigned char)(Can_MsgTypeCfg->Id << 1);
        *((&CAN0TXIDR3) + Memory_address) |= 0x01;
	}
	else
	{
		/*标准帧ID发送*/
		*((&CAN0TXIDR0) + Memory_address) = (unsigned char)(Can_MsgTypeCfg->Id>>3);
		*((&CAN0TXIDR1) + Memory_address) = (unsigned char)(Can_MsgTypeCfg->Id<<5);
	}

	/*报文数据发送*/
	for (sp = 0; sp < Can_MsgTypeCfg->Len;sp++)
	{
		*((&CAN0TXDSR0) + sp+Memory_address) = Can_MsgTypeCfg-> Data[sp];
	}
	/*报文长度发送*/
	*((&CAN0TXDLR) + Memory_address) = Can_MsgTypeCfg-> Len;

    *((&CAN0TXTBPR) + Memory_address) = Can_MsgTypeCfg-> Prty;
	/*清除标志*/
	*((&CAN0TFLG) + Memory_address) = SendBuf;

	return TRUE;

}

/*报文周期发送函数*/
void Can_SendTime(Can_TimeType Can_TimeTypeCfg)
{
	static int Can_TIME ;

	Can_TIME++;

	if (Can_TIME == 50)
	{
	    if (Can_SendMsg(&Can_MsgTypeSendData1) == 1)
	    {

	    }
	}

	if (Can_TIME == 90)
	{
		if (Can_SendMsg(&Can_MsgTypeSendData3) == 1)
		{

		}
	}
   if (Can_TIME >= 100)
	{
    	Can_TIME = 0;
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
    Can_MsgTypeCfg ->Id = (unsigned int)(CAN1RXIDR0<<3) |
            			  (unsigned char)(CAN1RXIDR1>>5);

	if (CAN1RXIDR1 & 0x10)
	{
		Can_MsgTypeCfg->Ide = TRUE;
	}
	else
  	{
    	Can_MsgTypeCfg->Ide = FALSE;
    }

	/*读取数据长度 */
	Can_MsgTypeCfg->Len = CAN1RXDLR;

	/*读取数据*/
	for (sp = 0; sp < Can_MsgTypeCfg->Len; sp++)
  	{
    	Can_MsgTypeCfg->Data[sp] = *((&CAN1RXDSR0)+sp);
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
		if (Can_MsgTypeGetData.Id == 0x3c && (!Can_MsgTypeGetData.Ide))
		{
            if (Can_SendMsg(&Can_MsgTypeSendData3) == 1)
            {

            }
		}
    }
	return 0;
}


