#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


void main(void)
{
  /* put your own code here */
  DisableInterrupts;
  PIT_Init();
  initialize_ect();
  CAN1_Init();
  EnableInterrupts;

  for(;;)
  {
    _FEED_COP(); /* feeds the dog */

  } /* loop forever */
  /* please make sure that you never leave main */
}
