/*
 * MSP430 Interrupt Button Control
 * Anthony Scranney
 * www.coder-tronics.com
 * Rev 1.2
 *
 * Please visit the sponsors on my site if you have found this code useful
 */

#include <msp430g2253.h>

int main(void) {
	
	/*** Watchdog timer and clock Set-Up ***/
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer
	DCOCTL = 0;             	// Select lowest DCOx and MODx
	BCSCTL1 = CALBC1_1MHZ;		// Set range
	DCOCTL = CALDCO_1MHZ;		// Set DCO step + modulation

	/*** GPIO Set-Up ***/
	P1DIR |= BIT0 + BIT6; 			// Set P1.0 & P1.6 as output
	P1OUT &= ~(BIT0 + BIT6); 		// Set P1.0 & P1.6 Low therefore LED's off
	P1DIR &= ~(BIT3 + BIT7);		// Set P1.3 & P1.7 as inputs
	P1REN |= BIT3 + BIT7;			// Enable pull-ups on P1.3 & P1.7
	P1IE |= BIT3 + BIT7; 			// P1.3 & P1.7 interrupt enabled
	P1IFG &= ~(BIT3 + BIT7); 		// P1.3 & P1.7 IFG cleared
	P1IES &= ~(BIT3 + BIT7);		// P1.3 & P1.7 interrupt edge High to Low edge

	_BIS_SR(GIE);				// Enter interrupt enabled
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){

	switch (P1IFG)
	{
		case BIT3:
			P1IES ^= BIT3;			// Toggle interrupt edge
			P1OUT ^= BIT0;			// Toggle Red LED
			__delay_cycles(40000);
			P1IFG &= ~BIT3;			// clear the interrupt flag
			break;
		case BIT7:
			P1IES ^= BIT7;			// Toggle interrupt edge
			P1OUT ^= BIT6;			// Toggle Green LED
			__delay_cycles(40000);
			P1IFG &= ~BIT7;			// clear the interrupt flag
			break;
		default:
			__delay_cycles(10000);
			P1IFG = 0x00;
			break;
	}
}