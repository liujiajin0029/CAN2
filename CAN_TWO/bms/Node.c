#include "Node.h"

int NOdeData_CallBcak(_NODE_STATE NODE_STATE)
{

  static int OS_Timer;

  switch (NODE_STATE.Node_ReturnState)
	{
    case Fault_Node_Leve1:
			if (PrechargeM_Busy_Ok == true)
			{
		  		NODE_STATE.Node_ReturnTime = OS_Timer;
				NODE_STATE.Node_ReturnState = Fault_Node_Leve2;
				PrechargeM_StartPre();
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
				PrechargeM_StopMaster();
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
				PrechargeM_StopPre();
				NODE_STATE.Node_ReturnState = Fault_Node_Leve1;
			}
			if (PrechargeM_IsFinish() == true && NODE_STATE.Node_ReturnState == Fault_Node_Leve3)
			{
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Busy_Ok;
				PrechargeM_StopPre();
				PrechargeM_StartMaster();
				NODE_STATE.Node_ReturnState = Fault_Node_Leve3;
			}
			else if (NODE_STATE.Node_ReturnState == Fault_Node_Leve3)
			{
				NODE_STATE.Node_ReturnState = Fault_Node_Leve2;
			}break;

		case Fault_Node_Leve3:
			if(PrechargeM_IsFail() == true)
			{
				NODE_STATE.Node_ReturnSubstate = PrechargeM_Busy_Ok;
				NODE_STATE.Node_ReturnState = Fault_Node_Leve3;
			}
			else
			{
				PrechargeM_StopMaster();
				NODE_STATE.Node_ReturnState = Fault_Node_Leve1;
			}break;
	}
}



