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
  static uint16_t pwmDuty = 0;
  if (PIR1bits.TMR2IF)
  {
    Pwm_SetDuty(pwmDuty);
    if (++pwmDuty > 1023)
    {
      pwmDuty = 0;
    }

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
}

void loop()
{
}
