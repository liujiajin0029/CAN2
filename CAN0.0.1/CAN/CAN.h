#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define CAN_MSGTYPE_DATA_MAXLEN 8

typedef enum CAN_BSP
{
	CAN_BSPTYPE125K = 0,
	CAN_BSPTYPE250K = 1,
}Can_BspType;

typedef struct _Can_HwCfgType
{
	Can_BspType Can_InitTypeBPS;
}Can_InitType;

typedef struct Can_msg
{
	unsigned int Can_MsgTypeId;
	unsigned char Can_MsgTypeIde;
	unsigned char Can_MsgTypeData[CAN_MSGTYPE_DATA_MAXLEN];
	unsigned char Can_MsgTypeLen;
	unsigned char Can_MsgTypePrty;
}Can_MsgType;

typedef struct _can_time
{
	int Can_TimeTypeData1;
	int Can_TimeTypeData2;
	int Can_TimeTypeData3;
	int Can_TimeTypeData4;
}Can_TimeType;

static Can_MsgType Can_MsgTypeSendData1 =
{
	0x01,
	0,
	{1, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
};

static Can_MsgType Can_MsgTypeSendData2 =
{
	0x02,
	0,
	{2, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
};
static Can_MsgType Can_MsgTypeSendData3 =
{
	0x03,
	0,
	{3, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
};

static Can_TimeType Can_TimeTypeSendData =
{
	40,
	50,
	60,
	104,
};

static Can_InitType Can_InitTypeSendData =
{
	CAN_BSPTYPE125K,
};

static Can_MsgType Can_MsgTypeGetData =
{
 	0x00,
	0,
	{0, 0, 0, 0, 0, 0, 0, 0},
	0,
	0,
};

void CAN_INIT(void);
void CAN1_INIT(Can_InitType *Can_InitTypeCfg);
void Can_SendTime(Can_TimeType Can_TimeTypeCfg);
void Can_SendMsgAll(void);
Bool Can_GetCallBack(void);


#endif