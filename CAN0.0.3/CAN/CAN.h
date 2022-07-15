#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define   CAN_MSGTYPE_DATA_MAXLEN   8
#define   CAN_PASSAGEWAY1  (0x40u)

#define   CAN_PASSAGEWAY0  (0u)

typedef enum CAN_Bsp
{
	CAN_BSPTYPE125K ,
	CAN_BSPTYPE250K ,
	CAN_BSPTYPE500K ,
	CAN_BSPTYPE1000K ,
}Can_BspType; 

typedef struct Can_Time
{
	int Can_Time1;
	int Can_Time2;
	int Can_Time3;
	int Can_Time4;
}Can_TimeType;


typedef struct Can_Msg
{
	unsigned int Id;
	unsigned char Ide;
	unsigned char Data[CAN_MSGTYPE_DATA_MAXLEN];
	unsigned char Len;
	unsigned char Prty;
	unsigned char SenGeway;
}Can_MsgType;


typedef struct Can_HwCfgType
{
	Can_BspType BPS;
	unsigned char Geway;
}Can_InitType;

static Can_InitType Can0_InitType =
{
	CAN_BSPTYPE125K,
	CAN_PASSAGEWAY0,
};

static Can_InitType Can1_InitType =
{
	CAN_BSPTYPE125K,
	CAN_PASSAGEWAY1,
};

void Can_Init(void);
void Can_DeInit(Can_InitType *Can_InitTypeCfg);
void Can_SendTime(Can_TimeType Can_TimeTypeCfg);
void Can_SendMsgAll(void);
Bool Can_GetCallBack(void);


#endif