#ifndef __CAN_H
#define __CAN_H

#include "derivative.h"

#define Msg_MaxLen 8

 enum _CAN_BSP_Type
{
	CAN_125K = 0;
	CAN_250K = 1;
}CAN_BSP_Type;

struct can_msg     //发送报文的结构体

{
	unsigned int id;
	Bool RTR;
	unsigned char data[8];
	unsigned char len;
	unsigned char prty;
};

#endif