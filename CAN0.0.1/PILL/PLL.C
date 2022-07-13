#include "PLL.h"
#include "derivative.h"

void PLL_INIT(void)
{
	CLKSEL_PLLSEL = 0;
	PLLCTL_PLLON = 0;
	SYNR = 0x47;
	REFDV = 0X41;
	POSTDIV = 0X00;
	PLLCTL_PLLON = 1;
	_asm(nop);
	_asm(nop);

	CLKSEL_PLLSEL = 1;
}



