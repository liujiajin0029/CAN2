#ifndef __NODE_H
#define __NODE_H

#include "hidef.h"
#include "derivative.h"

#define   true   1

typedef enum
{
  Fault_Node_Leve1  = 1,
  Fault_Node_Leve2  = 2,
  Fault_Node_Leve3  = 3,
  Fault_Node_Leve4  = 4,
  Fault_Node_Leve5  = 5,
  Fault_Node_Leve6  = 6,
} Fault_Node_Leve;


typedef struct _Node_ReturnType
{
  int  Node_ReturnTime;
  char Node_ReturnState;
  char Node_ReturnSubstate;
}_NODE_STATE;


#endif
