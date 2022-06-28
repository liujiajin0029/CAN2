#include "PIT.h"
#include "derivative.h"

void PIT_Init(void)
{
	PITMTLD0=249;     //为0通道8位计数器赋值
	PITLD0=399;     //为0通道16位计数器赋值   //(249+1)*(63999+1)=16000000个总线周期=1MS
	PITMUX_PMUX0=0;   //第0通道使用微计数器0
	PITCFLMT=0X80;    //使能周期中断定时器
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vpit0 PIT0(void)
{
	
}

#pragma CODE_SEG DEFAULT


