/*
 * MSP430 Single Switch Debounce WatchDog - based on Arduino debounce code using the millis() function.
 * Anthony Scranney
 * www.coder-tronics.com
 * Rev 1
 *
 * Please visit the sponsors on my site if you have found this code useful
 */

#include <msp430g2253.h>
/*** WatchDog Timer Variables ***/
volatile int Half_Mil_Sec = 0;
volatile long Mil_Sec = 0;
/*** Debounce variables ***/
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers
int switchState;
int lastswitchState = 0;   // the previous reading from the input pin
/*** Function Prototype ***/
long Mils_Count(void);

int main(void) {
	
	/*** Watchdog timer and clock Set-Up ***/
	WDTCTL = WDT_MDLY_0_5;		// Watchdog timer 0.5ms
	IE1 |= WDTIE;				// Watchdog interrupt enable
	BCSCTL1 = CALBC1_1MHZ;		// Set range
	DCOCTL = CALDCO_1MHZ;		// Set DCO step + modulation

	/*** GPIO Set-Up ***/
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;
	P1DIR &= ~BIT3;
	P1REN |= BIT3;

    _BIS_SR(GIE);             // Enter Low power mode 0 with interrupts enabled

	while (1)
	{
		int reading;
		int temp;
		temp = (P1IN & BIT3);
		if (temp == 0x0008) {
			reading = 1;}
		else {
			reading = 0;}

		if (reading != lastswitchState) {
			lastDebounceTime = Mils_Count();}

		if ((Mils_Count() - lastDebounceTime) > debounceDelay) {
			switchState = reading;}

		if (switchState == 1) {
			P1OUT |= BIT0;}
		else {
			P1OUT &= ~BIT0;}

		lastswitchState = reading;
	}
}

#pragma vector=WDT_VECTOR				// Watchdog Timer interrupt service routine
  __interrupt void watchdog_timer(void) {
	  Half_Mil_Sec++;
	  if (Half_Mil_Sec == 2){
		  Mil_Sec++;
		  Half_Mil_Sec = 0;
	  }
}

long Mils_Count(void)					// Based on the millis() Arduino function
 {
	 long Count = Mil_Sec;
	 return Count;
 }
