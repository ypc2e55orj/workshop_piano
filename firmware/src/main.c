#include "configurations.h"

// libc
#include <stdbool.h>
#include <stdint.h>

// project
#include "clock.h"
#include "port.h"
#include "wdt.h"
#include "tone.h"

void main(void)
{
  Clock_Initialize();
  Port_Initialize();
  Wdt_Initialize();
  Tone_Initialize();
  Wdt_Start();
  Tone_Start();
  Tone_SetNotes((1 << TONE_NOTE_C) | (1 << TONE_NOTE_E) | (1 << TONE_NOTE_G));
  while (true)
  {
    __delay_ms(100);
    Wdt_Reset();
  }
}

void __interrupt() isr(void)
{
  static uint16_t pwmDuty = 0;
  if (PIR1bits.TMR2IF)
  {
    LATCbits.LATC0 = ~LATCbits.LATC0;
    Tone_Update();
    PIR1bits.TMR2IF = 0;
  }
}
