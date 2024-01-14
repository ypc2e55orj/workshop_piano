#ifndef PWM_H
#define PWM_H

#include <xc.h>

// libc
#include <stdint.h>

void Pwm_Initialize(void);
void Pwm_Start(void);
void Pwm_Stop(void);
#define Pwm_SetDuty(val) ((void)(PWM2DCH = ((val) >> 2) & 0xFF, PWM2DCLbits.PWM2DCL = (val) & 0x03))

#endif // PWM_H
