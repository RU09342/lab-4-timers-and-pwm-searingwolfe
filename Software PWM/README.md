MSP430 Microprocessors (5 boards):
------------------------------------------
MSP430F5529
MSP430FR2311
MSP430FR5994
MSP430FR6989
MSP430G2553
------------------------------------------

Software PWM

------------------------------------------

The code begins by declaring a float integer D=75 and a volatile integer count=0. Inside the main block, the first line turns off the on-board watchdog timer control. A UART pin is wired as a directional pin and wired and then wired as selection. An LED is wired as a directional pin and then wired as the NOT output (initially on). The BUTTON is enabled for interrupts and is wired to an internal resistor, wired to a high-to-low interrupt edge select, and wired to the NOT of a interrupt flag register for clearing the flag. All iterrupts are enabled on the next line. The capture/compare register (TA0CCR0) is set to a value of 1000 (this is the PWM period). The capture/compare control register (TA0CCTL1) is set to OUTMOD_7, which resets output when the timer counts to the TA0CCR1 value. The second capture/compare control register (TACCR1) is set to a value of 75 (this is the default duty cycle of the LED, 75/1000 = 7.5% duty cycle). The timer control register (TA0CTL) is configured to up mode (MC_1) and is multiplied by 8 (ID_3). Lamp-mode 0 is entered while not in any interrupt blocks.

Before the interrupt block, the #pragma vector line is equal to PORT1_VECTOR, which reads any interrupts coming from PORT1 (the BUTTON is wired to P1.3). Within the interrupt block, the variable count is incremeneted by 1 for every interrupt event. A switch-statement performs 1 of 10 cases (including the default case) depending on the value of count. In the first 9 cases, the variable D is equal to 200,300,400,500,600,700,800,900, respectively. The value of TA0CCR1 is equal to 1000 * (D/1000) for adjusting the duty cycle of the LED. TA0CTL is reconfirmed for each case to ensure that the timer registers work properly. The NOT of the BUTTON is set as the interrupt flag register, clearing the flag again. The 10th case (default case) sets D=0 for turning off the LED (duty cycle of 0%) and count=0 for resetting the switch-statement back to the first case. Outside of the switch-statement, the NOT of the BUTTON clears the interrupt flag register again, and the NOT of the LED is set as the output, turning it off. Also outside the switch-statement, a small if-statement only runs if the BUTTON is pressed, turning on the LED.

This code is almost identical for every board, with the exception found in three of them. The MSP430FR boards require one extra line to implement the same code for blinking an LED, which disables the GPIO power-on default high-impedance mode for activating the configured In/Out port settings (PM5CTL0 &= ~LOCKLPM5). Also, some boards reqire changing lines such as TA0CCR0 (TAC...generally) to TA1CCR0 or TB0CCR0, depending on the board's specific timer register declarations. And the #pragma vector value is changed accordingly, from TIMER1_A1 to TIMER0_B0 or TIMER1_B1 similar.

------------------------------------------
