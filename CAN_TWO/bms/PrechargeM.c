#include "PrechargeM.h"

void PrechargeM_Init(hw_tab *_hw_tab )
{
  _hw_tab->state_vbat  = BAT_Get();
  _hw_tab->state_v1 = V1_Get();
}

PrechargeM_RETURN_TYPE PrechargeM_StartPre(void)
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
 char PrechargeM_StopPre()
{

  return 0;
}


void PrechargeM_StartMaster(void)
{

}

PrechargeM_RETURN_TYPE PrechargeM_StopMaster(void)
{

}

PrechargeM_RETURN_TYPE PrechargeM_Change(void)
{


}

PrechargeM_RETURN_TYPE PrechargeM_IsFinish(void)
{

}

int PrechargeM_IsFail(void)
{

}


PrechargeM_RETURN_TYPE PrechargeM_FaultDetection(Fault _Fault)
{
  if (_Fault.FaultDATA1 == 1)
  {

  }
  if (_Fault.FaultDATA2 == 1)
  {

  }

}


