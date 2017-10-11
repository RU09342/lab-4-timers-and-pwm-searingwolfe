/*
 * MSP430 Multiple Switch Debounce WatchDog - 2 functions for testing switch control
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
/*** Variables relating to void Debounce_Buttons(void); ***/
long lastDebounceTime = 0;  // The last time the output pin was toggled
long debounceDelay = 50;    // The debounce time adjust to the individual switch requirements
int buttonState1, buttonState2;
int lastButtonState1 = 0, lastButtonState2 = 0;   // the previous reading from the input pin
// Variables relating to void Press_Time(void);
long Reaction_Count = 0;			// The reaction count is taken and then used to compare to the Button_Reaction_Delay
long Button_Reaction_Delay = 150;	// Button_Reaction_Delay is tunable to the specific button and interface
/*** Function Prototype ***/
long Mils_Count(void);
void Press_Time(void);
void Debounce_Buttons(void);

int main(void) {
	
	/*** Watchdog timer and clock Set-Up ***/
	WDTCTL = WDT_MDLY_0_5;		// Watchdog timer 0.5ms
	IE1 |= WDTIE;				// Watchdog interrupt enable
	BCSCTL1 = CALBC1_1MHZ;		// Set range
	DCOCTL = CALDCO_1MHZ;		// Set DCO step + modulation

	/*** GPIO Set-Up ***/
	P1DIR |= BIT0 + BIT6;
	P1OUT &= ~(BIT0 + BIT6);
	P1DIR &= ~(BIT3 + BIT7);
	P1REN |= BIT3 + BIT7;

    _BIS_SR(GIE);             // Interrupts enabled

	while (1)
	{
		//Press_Time();				// Simply adds a delay and is dependent on the users press time
									// so not a true debounce algorithm

		Debounce_Buttons();			// This is developed from a single switch algorithm, it works well but
									// is badly implemented due to the amount of if statements being
									// executed each time it is called
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

void Press_Time(void)
{
	if (0x0088 != (P1IN & 0x0088))  // Ensures the button code inside only runs if P1.3 or P1.7 goes low
		{
		int state = (P1IN & 0x0088); 	// BitMask to discard all unwanted port data
										// temp_state will = 1000 0000 or (0x0080) if P1.3  pressed
										// or 0000 1000 or (0x0008) if P1.7 pressed
			Reaction_Count = Mils_Count();
			switch (state)
			{
			case 0x0080:
				while((Mils_Count() - Reaction_Count) < Button_Reaction_Delay) {}
					P1OUT ^= BIT0;	// BIT3 or P1.3 = 0x0008 has been pressed
				break;
			case 0x0008:
				while((Mils_Count() - Reaction_Count) < Button_Reaction_Delay) {}
					P1OUT ^= BIT6;	// BIT7 or P1.7 = 0x0080 has been pressed
				break;
			}
		}
}

void Debounce_Buttons(void)
{
	if ((P1IN & 0x0088) == (P1IN & 0x0008) || (P1IN & 0x0080))
	{
			int reading1;
			int temp1 = (P1IN & BIT3);
			if (temp1 == 0x0008) {
				reading1 = 1;}
				else {
					reading1 = 0;}
					if (reading1 != lastButtonState1) {
						lastDebounceTime = Mils_Count();}
				if ((Mils_Count() - lastDebounceTime) > debounceDelay) {
					buttonState1 = reading1;}
			if (buttonState1 == 1) {
				P1OUT |= BIT0;}
					else {
						P1OUT &= ~BIT0;}
		lastButtonState1 = reading1;

			int reading2;
			int temp2 = (P1IN & BIT7);
			if (temp2 == 0x0080) {
				reading2 = 1;}
				else {
					reading2 = 0;}
					if (reading2 != lastButtonState2) {
						lastDebounceTime = Mils_Count();}
				if ((Mils_Count() - lastDebounceTime) > debounceDelay) {
					buttonState2 = reading2;}
			if (buttonState2 == 1) {
				P1OUT |= BIT6;}
						else {
							P1OUT &= ~BIT6;}
		lastButtonState2 = reading2;
	}
}
