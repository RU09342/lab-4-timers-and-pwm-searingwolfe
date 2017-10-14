MSP430 Microprocessors (5 boards):
------------------------------------------
MSP430F5529
MSP430FR2311
MSP430FR5994
MSP430FR6989
MSP430G2553
------------------------------------------

Hardware PWM

------------------------------------------

The code begins inside the main block by turning off the on-board watchdog timer control. A UART pin is wired as a directional pin and wired and then wired as selection. The BUTTON is wired to an internal resistor and wired as an output. The capture/compare register (TA0CCR0) is set to a value of 1000 (this is the PWM period). The capture/compare control register (TA0CCTL1) is set to OUTMOD_7, which resets output when the timer counts to the TA0CCR1 value. The second capture/compare control register (TACCR1) is set to a value of 500 (this is the default duty cycle of the LED, 500/1000 = 50% duty cycle). The timer control register is configured to up mode (MC_1). An infinite while-loop has two if-statements. The first if-statement runs only if the BUTTON has been pressed, which then delays cycles by 200000 for slowing the delay to show changes in LED brightness. This same if-statement also increases TA0CCR1 by 100, for increasing the duty cycle after every BUTTON press. The second if-statement only runs if TA0CCR1 is larger than 1000, or if the duty cycle reaches 100%. In this if-statement, TA0CCR1 is set to 0, restarting the LED brightness back to 0% instead of 50% on startup.

This code is almost identical for every board, with the exception found in three of them. The MSP430FR boards require one extra line to implement the same code for blinking an LED, which disables the GPIO power-on default high-impedance mode for activating the configured In/Out port settings (PM5CTL0 &= ~LOCKLPM5). Also, some boards reqire changing lines such as TA0CCR0 (TAC...generally) to TA1CCR0 or TB0CCR0, depending on the board's specific timer register declarations. And the #pragma vector value is changed accordingly, from TIMER1_A1 to TIMER0_B0 or TIMER1_B1 similar.

------------------------------------------
