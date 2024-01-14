#ifndef PORT_H
#define PORT_H

#include <xc.h>

void Port_Initialize(void);

#define LED1(level) (LATCbits.LATC0 = (level))
#define LED2(level) (LATCbits.LATC1 = (level))
#define LED3(level) (LATCbits.LATC2 = (level))
#define LED4(level) (LATCbits.LATC3 = (level))
#define LED5(level) (LATCbits.LATC4 = (level))
#define LED6(level) (LATAbits.LATA5 = (level))
#define LED7(level) (LATCbits.LATC6 = (level))
#define LED8(level) (LATCbits.LATC7 = (level))

#define KEY_C() (PORTAbits.RA0)
#define KEY_D() (PORTAbits.RA1)
#define KEY_E() (PORTAbits.RA3)
#define KEY_F() (PORTAbits.RA4)
#define KEY_G() (PORTBbits.RB4)
#define KEY_A() (PORTBbits.RB5)
#define KEY_B() (PORTBbits.RB6)
#define KEY_C_H() (PORTBbits.RB7)

#endif // PORT_H
