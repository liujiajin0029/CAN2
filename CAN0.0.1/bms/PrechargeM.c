#include "PrechargeM.h"

void PRECHARGEM_INIT(hw_tab *_hw_tab )
{
  _hw_tab->state_vbat  = BAT_Get();
  _hw_tab->state_v1 = V1_Get();
}

extern PrechargeM_RETURN_TYPE PrechargeM_StartPre(void)
{
  static hw_tab  hw_tabData;
  PrechargeM_Init(&hw_tabData);

  if (hw_tabData.state_v1 > 10)
  {
    return PrechargeM_Request_Pending;
  }
  else
  {
    return PrechargeM_Busy_Ok;
  }
}
extern PrechargeM_RETURN_TYPE PrechargeM_StopPre()
{

  return PrechargeM_Request_Pending;
}


extern PrechargeM_RETURN_TYPE PrechargeM_StartMaster(void)
{

}

extern PrechargeM_RETURN_TYPE PrechargeM_StopMaster(void)
{
  return PrechargeM_Request_Pending;
}

extern PrechargeM_RETURN_TYPE PrechargeM_Change(void)
{
  return PrechargeM_Ok;
}

extern PrechargeM_RETURN_TYPE PrechargeM_IsFinish(void)
{
  return PrechargeM_Ok;
}

extern int PrechargeM_IsFail(void)
{
  return PrechargeM_Ok;
}


extern PrechargeM_RETURN_TYPE PrechargeM_FaultDetection(Fault _Fault)
{
  if (_Fault.FaultDATA1 == 1)
  {
    return PrechargeM_Ok;
  }
  if (_Fault.FaultDATA2 == 1)
  {
    return PrechargeM_Ok;
  }

}


