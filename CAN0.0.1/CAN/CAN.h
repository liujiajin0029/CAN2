#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define Can_MsgTypeDataMaxLen 8

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
	unsigned int Id;
	unsigned char Ide;
	unsigned char Data[Can_MsgTypeDataMaxLen];
	unsigned char Len;
	unsigned char Prty;
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

void CAN_INIT(void);
void CAN1_Init(CAN_InitType *CAN_InitTypeCfg);
void CAN_SendTime(Can_TimeType Can_TimeTypeCfg);
void Can_SendMsgAll(void);
Bool CAN_GetCallBack(void);


#endif