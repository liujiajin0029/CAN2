#ifndef __VBAT_DATA_H
#define __VBAT_DATA_H
#include "hidef.h"
#include "derivative.h"


#define VBAT_SUM  10

/*BMS_预充电_电压_阈值_高*/
#define VOLTAGE_THRESHOLD_H  20

/*BMS_预充电_电压_阈值_低*/
#define VOLTAGE_THRESHOLD_L  10

 
typedef struct _HV_DATA
{
	int BAT;		//BAT基准电压
	int current;		//V1电压
}HV_DATA;
 


 
 
int BAT_Get(void);
int V1_Get(void);

#endif
