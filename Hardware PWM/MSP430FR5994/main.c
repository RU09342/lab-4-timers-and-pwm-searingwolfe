#include <msp430fr5994.h>

//Hardware PWM
int main(void) {
    WDTCTL = WDTPW + WDTHOLD; //disable watchdog
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
    P3DIR |= BIT4; //turn on LED wired to UART
    P5REN |= BIT6; //setup button
    P5OUT |= BIT6; 
    P3SEL1 |= BIT4; //change P3SEL to P3SEL1
    TB0CCR0 = 1000; //PWM period
    TB0CCTL1 = OUTMOD_7;
    TB0CCR1 = 500; //PWM starting duty cycle. TA0CCR1 / TA0CCR0 = 0.5 = 50% duty cycle
    TB0CTL = TBSSEL_2 + MC_1; //up-counter mode.

    while(1)
    {
        if ((P5IN & BIT6) != BIT6) { //Listen for button presses.
            __delay_cycles(200000); //slow delay to show changes in brightness
            TB0CCR1 = TB0CCR1 + 100; //Increment the PWM period
        } 
        if (TB0CCR1 > 1000) { //after brightness reaches 100%, reset to 0%
            TB0CCR1 = 0; 
        } 
    }
}