#include "PrechargeM.h"

void PRECHARGEM_INIT(PrechargeM_StateType *PrechargeM_StateTypeCfg )
{
  PrechargeM_StateTypeCfg->state_vbat  = BAT_Get();
  PrechargeM_StateTypeCfg->state_v1 = V1_Get();
}

extern PrechargeM_ReturnType PrechargeM_StartPre(void)
{
  static PrechargeM_StateType  PrechargeM_StateTypeCfg;
  PrechargeM_Init(&hw_tabData);

  if (PrechargeM_StateTypeCfg.state_v1 > 10)
  {
    return PrechargeM_Request_Pending;
  }
  else
  {
    return PrechargeM_Busy_Ok;
  }
}
extern PrechargeM_ReturnType PrechargeM_StopPre()
{

  return PrechargeM_Request_Pending;
}


extern PrechargeM_ReturnType PrechargeM_StartMaster(void)
{

}

extern PrechargeM_ReturnType PrechargeM_StopMaster(void)
{
  return PrechargeM_Request_Pending;
}

extern PrechargeM_ReturnType PrechargeM_Change(void)
{
  return PrechargeM_Ok;
}

extern PrechargeM_ReturnType PrechargeM_IsFinish(void)
{
  return PrechargeM_Ok;
}

extern int PrechargeM_IsFail(void)
{
  return PrechargeM_Ok;
}


extern PrechargeM_ReturnType PrechargeM_FaultDetection(PrechargeM_FaultType PrechargeM_FaultTypeCfg)
{
  if (PrechargeM_FaultTypeCfg.PrechargeM_FaultTypeData1 == 1)
  {
    return PrechargeM_Ok;
  }
  if (PrechargeM_FaultTypeCfg.PrechargeM_FaultTypeData2 == 1)
  {
    return PrechargeM_Ok;
  }

}


