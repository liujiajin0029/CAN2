#include <hidef.h>           /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#define MODE_ONE PORTC_PC4
#define MODE_ONE_dir DDRC_DDRC4

#define MODE_TWO PORTC_PC5
#define MODE_TWO_dir DDRC_DDRC5


void main(void)
{
  /* put your own code here */

  DisableInterrupts;
  PLL_init();
  PIT_Init();
  initialize_ect();
  CAN1_Init();

  MODE_ONE=1;
  MODE_ONE_dir=1;
  MODE_TWO=0;
  MODE_TWO_dir=1;
  EnableInterrupts;
 
  for(;;)
  {
    _FEED_COP();   /* feeds the dog */
  }                /* loop forever */
                   /* please make sure that you never leave main */
}
