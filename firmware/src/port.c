#include "port.h"

#include <xc.h>

void Port_Initialize()
{
  // PORTA
  PORTA = 0x00, LATA = 0x00, WPUA = 0x00;
  /*
    RA0 Input  Key C
    RA1 Input  Key D
    RA3 Input  Key E
    RA4 Input  Key F
    RA5 Output LED 6
  */
  TRISA = 0x1B;
  ANSELA = 0x00;

  // PORTB
  PORTB = 0x00, LATB = 0x00, WPUB = 0x00;
  /*
    RB4 Input  Key G
    RB5 Input  Key A
    RB6 Input  Key B
    RB7 Input  Key C (High)
  */
  TRISB = 0xF0;
  ANSELB = 0x00;

  // PORTC
  PORTC = 0x00, LATC = 0x00;
  /*
    RC0 Output LED 1
    RC1 Output LED 2
    RC2 Output LED 3
    RC3 Output LED 4
    RC4 Output LED 5
    RC5 Hi-Z   Audio Output
    RC6 Output LED 7
    RC7 Output LED 8
  */
  TRISC = 0x20;
  ANSELC = 0x00;
}
