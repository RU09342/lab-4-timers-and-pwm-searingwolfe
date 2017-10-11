#include <msp430g2553.h>
#define BUTTON BIT3
unsigned int duty = 900;
void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop WDT

P1DIR |= BIT2; // P1.0 to output
P1SEL |= BIT2; // P1.0to TA0.1
P1IE |= BUTTON;
__enable_interrupt();
CCR0 = 6000-1; // PWM Period
CCTL0 = CCIE;
CCTL1 = OUTMOD_7; // CCR1 reset/set
//CCR1 = duty; // CCR1 PWM duty cycle
TACTL = TASSEL_2 + MC_1; // SMCLK, up mode

_BIS_SR(LPM0_bits); // Enter LPM0
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    duty = duty + 20;
    P1IFG &=~BUTTON;
}
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  CCR1 = duty; // update CCR1 PWM duty cycle
}