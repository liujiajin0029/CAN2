#include "Node.h"

/*节点状态机程序，返回值为节点状态*/
extern PrechargeM_RETURN_TYPE  NOdeData_CallBcak(_NODE_STATE NODE_STATE)
{
  static int OS_Timer;
  PrechargeM_RETURN_TYPE retval;

  switch (NODE_STATE.Node_ReturnState)
	{
    case Fault_Node_Leve1:
			if (PrechargeM_Busy_Ok == true)
			{
		  		NODE_STATE.Node_ReturnTime = OS_Timer;
				NODE_STATE.Node_ReturnState = Fault_Node_Leve2;
				retval = PrechargeM_StartPre();
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Busy_Ok;
			}
			else
			{
        		NODE_STATE.Node_ReturnState = Fault_Node_Leve1;
			}break;

		case Fault_Node_Leve2:
			if (PrechargeM_IsFail() == true)
			{
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Busy_Ok;
				NODE_STATE.Node_ReturnState = Fault_Node_Leve3;
			}
			else
			{
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Request_Pending;
				retval = PrechargeM_StopMaster();
				NODE_STATE.Node_ReturnState = Fault_Node_Leve1;
			}
			if (PrechargeM_IsFinish() == true && NODE_STATE.Node_ReturnState == Fault_Node_Leve3)
			{
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Busy_Ok;
				NODE_STATE.Node_ReturnState = Fault_Node_Leve3;
			}
			else
			{
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Request_Pending;
				retval = PrechargeM_StopPre();
				NODE_STATE.Node_ReturnState = Fault_Node_Leve1;
			}
			if (PrechargeM_IsFinish() == true && NODE_STATE.Node_ReturnState == Fault_Node_Leve3)
			{
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Busy_Ok;
				PrechargeM_StopPre();
				retval = PrechargeM_StartMaster();
				NODE_STATE.Node_ReturnState = Fault_Node_Leve3;
			}
			else if (NODE_STATE.Node_ReturnState == Fault_Node_Leve3)
			{
				NODE_STATE.Node_ReturnState = Fault_Node_Leve2;
			}break;

		case Fault_Node_Leve3:
			if (PrechargeM_IsFail() == true)
			{
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Busy_Ok;
				NODE_STATE.Node_ReturnState = Fault_Node_Leve3;
			}
			else
			{
				retval = PrechargeM_StopMaster();
				NODE_STATE.Node_ReturnState = Fault_Node_Leve1;
			}break;
	}
	return  retval;
}



