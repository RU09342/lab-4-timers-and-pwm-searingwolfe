#include <msp430g2553.h>

//Hardware PWM
int main(void) {
    WDTCTL = WDTPW + WDTHOLD; //disable watchdog
    //PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
    P1DIR |= BIT2; //turn on LED wired to UART
    P1REN |= BIT3; //setup button
    P1OUT |= BIT3; 
    P1SEL |= BIT2;
    TA0CCR0 = 1000; //PWM period
    TA0CCTL1 = OUTMOD_7; //CCR1 set/reset
    TA0CCR1 = 500; //PWM starting duty cycle. TA0CCR1 / TA0CCR0 = 0.5 = 50% duty cycle
    TA0CTL = TASSEL_2 + MC_1; //up-counter mode.

    while(1)
    {
        if ((P1IN & BIT3) != BIT3) { //Listen for button presses.
            __delay_cycles(200000); //slow delay to show changes in brightness
            TA0CCR1 = TA0CCR1 + 100; //Increment the PWM period
        } 
        if (TA0CCR1 > 1000) { //after brightness reaches 100%, reset to 0%
            TA0CCR1 = 0; //restart LED to 0% instead of the default 50%
        } 
    }
}