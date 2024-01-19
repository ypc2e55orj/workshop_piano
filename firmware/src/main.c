#include "configurations.h"

// libc
#include <stdbool.h>
#include <stdint.h>

// project
#include "clock.h"
#include "port.h"
#include "wdt.h"
#include "tone.h"

void SetLed(uint8_t n, bool state)
{
  switch (n)
  {
  case 0:
    LATCbits.LATC0 = state;
    break;
  case 1:
    LATCbits.LATC1 = state;
    break;
  case 2:
    LATCbits.LATC2 = state;
    break;
  case 3:
    LATCbits.LATC3 = state;
    break;
  case 4:
    LATCbits.LATC4 = state;
    break;
  case 5:
    LATAbits.LATA5 = state;
    break;
  case 6:
    LATCbits.LATC6 = state;
    break;
  case 7:
    LATCbits.LATC7 = state;
    break;
  default:
    break;
  }
}

void ReadKeys()
{
  static uint8_t prev = 0;
  uint8_t curr = 0;
  uint8_t hold = 0, pressed = 0;
  uint8_t keys = (uint8_t)((PORTAbits.RA0 << 0) |
                           (PORTAbits.RA1 << 1) |
                           (PORTAbits.RA3 << 2) |
                           (PORTAbits.RA4 << 3) |
                           (PORTBbits.RB4 << 4) |
                           (PORTBbits.RB5 << 5) |
                           (PORTBbits.RB6 << 6) |
                           (PORTBbits.RB7 << 7));

  for (uint8_t n = 0; n < 8; n++)
  {
    if (((prev >> n) & 0x01) && !((keys >> n) & 0x01))
    {
      curr |= (1 << n);
      hold++;
    }
    else
    {
      SetLed(n, false);
    }
  }
  for (uint8_t n = 0; n < 8 && pressed < (TONE_NUM_SAME_TIME - hold); n++)
  {
    if (!((prev >> n) & 0x01) && !((keys >> n) & 0x01))
    {
      curr |= (1 << n);
      pressed++;
      SetLed(n, true);
    }
  }
  prev = curr;

  Tone_SetNotes(curr);
}

void main(void)
{
  Clock_Initialize();
  Port_Initialize();
  Wdt_Initialize();
  Tone_Initialize();
  Wdt_Start();
  Tone_Start();
  while (true)
  {
    ReadKeys();
    Wdt_Reset();
  }
}

void __interrupt() isr(void)
{
  if (PIR1bits.TMR2IF)
  {
    Tone_Update();
    PIR1bits.TMR2IF = 0;
  }
}
