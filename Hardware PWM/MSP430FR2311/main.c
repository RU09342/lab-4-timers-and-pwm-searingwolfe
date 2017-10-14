#include <msp430fr2311.h>

//Hardware PWM
int main(void) {
    WDTCTL = WDTPW + WDTHOLD; //disable watchdog
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
    P2DIR |= BIT0; //turn on LED wired to UART
    P1REN |= BIT1; //setup button
    P1OUT |= BIT1; 
    P2SEL0 |= BIT0; //change P3SEL to P3SEL0
    TB1CCR0 = 1000; //PWM period
    TB1CCTL1 = OUTMOD_7; //CCR1 set/reset
    TB1CCR1 = 500; //PWM starting duty cycle. TA0CCR1 / TA0CCR0 = 0.5 = 50% duty cycle
    TB1CTL = TBSSEL_2 + MC_1; //up-counter mode.

    while(1)
    {
        if ((P1IN & BIT1) != BIT1) { //Listen for button presses.
            __delay_cycles(200000); //slow delay to show changes in brightness
            TB1CCR1 = TB1CCR1 + 100; //Increment the PWM period
        } 
        if (TB1CCR1 > 1000) { //after brightness reaches 100%, reset to 0%
            TB1CCR1 = 0; //restart LED to 0% instead of the default 50%
        } 
    }
}