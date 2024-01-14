#include "configurations.h"

// libc
#include <stdbool.h>
#include <stdint.h>

// project
#include "clock.h"
#include "port.h"
#include "wdt.h"
#include "pwm.h"

// prototypes
void setup(void);
void loop(void);

void main(void)
{
  setup();
  while (true)
  {
    loop();
    Wdt_Reset();
  }
}

void __interrupt() isr(void)
{
  if (PIR1bits.TMR2IF)
  {
    LATCbits.LATC0 = ~LATCbits.LATC0;

    PIR1bits.TMR2IF = 0;
  }
}

void setup()
{
  Clock_Initialize();
  Port_Initialize();
  Wdt_Initialize();
  Pwm_Initialize();
  Wdt_Start();
  Pwm_Start();
  Pwm_SetDuty(512);
}

void loop()
{
}
