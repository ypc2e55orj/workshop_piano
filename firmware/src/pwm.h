#ifndef PWM_H
#define PWM_H

#include <xc.h>

// libc
#include <stdint.h>

void Pwm_Initialize(void);
void Pwm_Start(void);
void Pwm_Stop(void);
inline void Pwm_SetDuty(uint16_t duty);

#endif // PWM_H
