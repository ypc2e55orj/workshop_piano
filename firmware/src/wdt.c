#include "wdt.h"

#include <xc.h>

void Wdt_Initialize()
{
  WDTCON = 0x14;
}

void Wdt_Start()
{
  WDTCONbits.SWDTEN = 1;
}

void Wdt_Stop()
{
  WDTCONbits.SWDTEN = 0;
}

void Wdt_Reset()
{
  CLRWDT();
}
