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

#define GetKeyC() (PORTAbits.RA0)
#define GetKeyD() (PORTAbits.RA1)
#define GetKeyE() (PORTAbits.RA3)
#define GetKeyF() (PORTAbits.RA4)
#define GetKeyG() (PORTBbits.RB4)
#define GetKeyA() (PORTBbits.RB5)
#define GetKeyB() (PORTBbits.RB6)
#define GetKeyCHigh() (PORTBbits.RB7)

#endif // PORT_H
