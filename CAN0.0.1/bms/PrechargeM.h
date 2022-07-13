#ifndef __PRECHARGEM_H
#define __PRECHARGEM_H

#include "hidef.h"
#include "derivative.h"

typedef struct PrechargeM_HvData
{
	float vbat_mV;
	float v1_mV;
	int state_vbat;
	int state_v1;
}PrechargeM_StateType;

/* Status parameters*/
typedef enum
{
    PrechargeM_Ok                  	 = 0,		/*正常*/
    PrechargeM_Busy_Ok             	 = 1,		/*正在运行*/
    PrechargeM_Request_Pending       = 2,		/*请求挂起*/
    PrechargeM_Already_Initialized	 = 3,		/*已初始化*/
} PrechargeM_ReturnType;

typedef struct _Fault
{
	Bool FaultData1;
	Bool FaultData2;
	Bool FaultData3;
}PrechargeM_FaultType;

int PrechargeM_IsFail(void);

#endif
