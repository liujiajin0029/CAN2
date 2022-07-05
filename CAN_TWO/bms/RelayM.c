#include "RelayM.h"


void RelayM_Init(Hv_IOInit *_Hv_IOType) //    IO口初始化配置
{
	_Hv_IOType->IO_dir = 1;

}


void  RelayM_Control(void)
{

}



int RelayM_Change(RelayM_Change_data *RelayM_data)  //    开关切换函数
{
    if (RelayM_data->KEY_PRE == 1)
    {
		PORTC_PC4 = 1;
    }
    else
    {
		PORTC_PC4 = 0;
    }
    if (RelayM_data->KEY_RELAY == 1)
	{
		PORTC_PC4 = 1;
	}
    else
    {
		PORTC_PC4 = 0;
    }
    return 0;
}



