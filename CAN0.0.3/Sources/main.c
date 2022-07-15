#include <hidef.h>           /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "CAN.h"
#include "ECT.h"
#include "PLL.h"
#include "Node.h"
#include "PrechargeM.h"
#include "Node.h"
#include "PIT.h"

#define MODE_ONE PORTC_PC4
#define MODE_ONE_DIR DDRC_DDRC4

#define MODE_TWO PORTC_PC5
#define MODE_TWO_DIR DDRC_DDRC5

void main(void)
{
  /* put your own code here */

    DisableInterrupts;
    Pll_Init();
    Can_Init();
    Pit_Init();
    Ect_Init();
    EnableInterrupts;
    MODE_ONE=1;
    MODE_ONE_DIR=1;
    MODE_TWO=0;
    MODE_TWO_DIR=1;

    for(;;)
    {
      _FEED_COP();   /* feeds the dog */
    }                /* loop forever */
                       /* please make sure that you never leave main */
}
