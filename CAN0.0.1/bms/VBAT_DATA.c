#include "derivative.h"

PrechargeM_ReturnType VOLTAGE_State[VBAT_SUM][4] = {0};

 //高压管理模块由初始化函数Hv_Init();
 void Hv_Init(void)
 {

 }

 int BAT_Get(void)
 {
	return 10;
 }

 int V1_Get(void)
 {
	return 9;
 }

PrechargeM_ReturnType  HV_Call(HV_DATA HV_DATAtype)
{

	if (HV_DATAtype.BAT > VOLTAGE_THRESHOLD_H && HV_DATAtype.BAT < VOLTAGE_THRESHOLD_L)
	{
		return PrechargeM_Ok;
	}
	else
	{
		return PrechargeM_Request_Pending;
	}
}


void HV_CallBack(int num_calls)
{
	switch (num_calls)
	{
		case 0 :
      VOLTAGE_State[0][1] = PrechargeM_Ok;
      break;
	}
}


