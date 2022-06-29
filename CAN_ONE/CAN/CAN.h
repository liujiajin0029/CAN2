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
}can_msg;

typedef struct _can_time
{
	unsigned int time_a;
	unsigned int time_b;
	unsigned int time_c;
}can_time;

static can_msg CanMsg_1 =
{
	0x01,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '1'},
	8,
	1,
};

static can_msg CanMsg_2 =
{
	0x02,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '2'},
	8,
	1,
};
static can_msg CanMsg_3 =
{
	0x03,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '3'},
	8,
	1,
};

static can_time can_time_Type =                     //CAN发送间隔时间
{
  40,
  50,
  60,
};

static CAN_TYPE CAN_HwCfg =		                    //CAN通信配置函数
{
	CAN_125K,
};

void CAN1_Init(void);
void CAN_INIT(CAN_TYPE *can_InitData);
void CAN_Send_TIME(can_time *can_timeType);
void CAN_Send_TIMEBCAK(void);
#endif