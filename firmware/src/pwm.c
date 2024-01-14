#include "pwm.h"

#include <xc.h>

// libc
#include <stdint.h>

// defines
#define PWM2DC(val) ()

void Pwm_Initialize()
{
  // Disables all interrupts
  INTCONbits.GIE = 0;

  // Enables all active peripheral interrupts
  INTCONbits.PEIE = 1;

  /*
    24.1.9 SETUP FOR PWM OPERATION USING PWMx PINS
      The following steps should be taken when configuring the module for PWM operation using the PWMx pins:
  */
  // 1. Disable the PWMx pin output driver(s) by setting the associated TRIS bit(s).
  TRISCbits.TRISC5 = 1;

  // 2. Clear the PWMxCON register
  PWM2CON = 0x00;

  // 3. Load the PR2 register with the PWM period value.
  PR2 = 0xFF;

  // 4. Clear the PWMxDCH register and bits <7:6> of the PWMxDCL register.
  PWM2DCH = 0x00;
  PWM2DCL = 0x00;

  // 5. Configure and start Timer2:
  // Clear the TMR2IF interrupt flag bit of the PIR1 register.
  PIR1bits.TMR2IF = 0;
  // Configure the T2CKPS bits of the T2CON register with the Timer2 prescale value
  T2CON = 0x00;
  // Enable Timer2 by setting the TMR2ON bit of the T2CON register.
  T2CONbits.TMR2ON = 1;

  // 6. Enable PWM output pin and wait until Timer2 overflows; TMR2IF bit of the PIR1 register is set.
  PWM2CONbits.PWM2EN = 1;
  while (!PIR1bits.TMR2IF)
    ;

  // Enables all active interrupts
  INTCONbits.GIE = 1;
}

void Pwm_Start()
{
  TRISCbits.TRISC5 = 0;
  PWM2CONbits.PWM2OE = 1;
  PIE1bits.TMR2IE = 1;
}

void Pwm_Stop()
{
  PIE1bits.TMR2IE = 0;
  PWM2CONbits.PWM2OE = 0;
  TRISCbits.TRISC5 = 1;
}
