#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define Msg_MaxLen 8

typedef enum _CAN_BSP_Type
{
	CAN_125K = 0,
	CAN_250K = 1,
}CAN_BSP_Type;

typedef struct _CAN_HwCfgType
{
	CAN_BSP_Type BPS;
}CAN_TYPE;

typedef struct _can_msg
{
	unsigned int id;
	unsigned char RTR;
	unsigned char data[Msg_MaxLen];
	unsigned char len;
	unsigned char prty;
}Can_Msg;

typedef struct _can_time
{
	int time_a;
	int time_b;
	int time_c;
	int time_sum;
}Can_Time;

static Can_Msg CanMsg_1 =
{
	0x01,
	0,
	{1, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
};

static Can_Msg CanMsg_2 =
{
	0x02,
	0,
	{2, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
};
static Can_Msg CanMsg_3 =
{
	0x03,
	0,
	{3, 0, 0, 0, 0, 0, 0, 0},
	8,
	0,
};

static Can_Time Can_Time_Type =
{
	40,
	50,
	60,
	104,
};

static CAN_TYPE CAN_HwCfg =
{
	CAN_125K,
};

static Can_Msg Can1_GetType =
{
 	0x00,
	0,
	{0, 0, 0, 0, 0, 0, 0, 0},
	0,
	0,
};

void CAN1_Init(void);
void CAN_INIT(CAN_TYPE *Can_InitData);
void CAN_Send_TIME(Can_Time Can_TimeType);
void CanMsg_SendAll(void);
extern Bool CAN1_GetCallBack(void);


#endif