#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define Msg_MaxLen 8

typedef enum _CAN_BSP_Type
{
	CAN_125K = 0,
	CAN_250K = 1,
}CAN_BSPType;

typedef struct _CAN_HwCfgType
{
	CAN_BSPType BPS;
}CAN_InitType;

typedef struct _can_msg
{
	unsigned int Can_MsgTypeId;
	unsigned char Can_MsgTypeIde;
	unsigned char Can_MsgTypeData[Msg_MaxLen];
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

static CAN_InitType CAN_InitTypeSendData =
{
	CAN_125K,
};

static Can_MsgType Can_MsgTypeGetData =
{
 	0x00,
	0,
	{0, 0, 0, 0, 0, 0, 0, 0},
	0,
	0,
};

void CAN_Init(void);
void CAN1_Init(CAN_TYPE *Can_InitData);
void CAN_SendTime(Can_Time Can_TimeType);
void Can_MsgSendAll(void);
Bool CAN_GetCallBack(void);


#endif