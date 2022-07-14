#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define CAN_MSGTYPE_DATA_MAXLEN 8

#define   CAN_PASSAGEWAY1  (0x40u)
#define   CAN_PASSAGEWAY0  (0u)

typedef enum CAN_Bsp
{
	CAN_BSPTYPE125K ,
	CAN_BSPTYPE250K ,
	CAN_BSPTYPE500K ,
	CAN_BSPTYPE1000K ,

}Can_BspType;

typedef struct Can_HwCfgType
{
	Can_BspType Can_InitTypeBPS;
	unsigned char CAN_InitTypeGeway;
}Can_InitType;

typedef struct Can_Msg
{
	unsigned int Id;
	unsigned char Ide;
	unsigned char Data[CAN_MSGTYPE_DATA_MAXLEN];
	unsigned char Len;
	unsigned char Prty;
	unsigned char SenGeway;
}Can_MsgType;

typedef struct Can_Time
{
	int Can_TimeTypeData1;
	int Can_TimeTypeData2;
	int Can_TimeTypeData3;
	int Can_TimeTypeData4;
}Can_TimeType;

static Can_MsgType Can_MsgTypeSendData1 =
{
	0x00000001,
	0,
	{1, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
	CAN_PASSAGEWAY0,
};

static Can_MsgType Can_MsgTypeSendData2 =
{
	0x000000002,
	0,
	{2, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
	CAN_PASSAGEWAY1,
};

static Can_MsgType Can_MsgTypeSendData3 =
{
	0x000000003,
	0,
	{3, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
	CAN_PASSAGEWAY1,
};

static Can_TimeType Can_TimeTypeSendData =
{
	40,
	50,
	60,
	104,
};

static Can_InitType Can0_InitTypeSendData =
{
	CAN_BSPTYPE500K,
	CAN_PASSAGEWAY0,
};

static Can_InitType Can1_InitTypeSendData =
{
	CAN_BSPTYPE125K,
	CAN_PASSAGEWAY1,
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
void CAN_INITIPUT(Can_InitType *Can_InitTypeCfg);
void Can_SendTime(Can_TimeType Can_TimeTypeCfg);
void Can_SendMsgAll(void);
Bool Can_GetCallBack(void);


#endif