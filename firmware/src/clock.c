#include "clock.h"

#include <xc.h>

void Clock_Initialize()
{
  OSCCONbits.IRCF = 0x0F;
}
