#ifndef __RELAYM_H
#define __RELAYM_H

#include "hidef.h"
#include "derivative.h"
#include "VBAT_DATA.h"



typedef struct _Hv_IOInit
{
	char IO_dir;
}Hv_IOInit;

Hv_IOInit Hv_IOType =
{
	1,
};

typedef struct _RelayM
{
   char KEY_PRE;
   char KEY_RELAY;
} RelayM_Change_data;

RelayM_Change_data MODE_IO =
{
	1,
	0,
};

void RelayM_Init();

#endif
