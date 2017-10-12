#include <msp430fr6989.h>

volatile int halfsecond = 0; //both halfsecond and second used for watchdog control
volatile long second = 0; //long = large int value
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers
int switchState;
int lastswitchState = 0;   // the previous reading from the input pin

//Debouncing
long Counter(void); //initialize
int main(void) {
	
	WDTCTL = WDT_MDLY_0_5; // Watchdog timer 0.5ms
	SFRIE1 |= WDTIE; // Watchdog interrupt enable. change IE1 to SFRIE1.
	PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
	//BCSCTL1 = CALBC1_1MHZ; // Set range. 1MHz default.
	//DCOCTL = CALDCO_1MHZ; // Set DCO step + modulation

	P1DIR |= BIT0; //led setup
	P1OUT &= ~BIT0;
	P1DIR &= ~BIT1; //button setup
	P1REN |= BIT1;

    _bis_SR_register(GIE); // Enter Low power mode 0 with interrupts enabled
    //or use _BIS_SR(GIE);
	while (1) {
		int reading; //initialize if-statement variable
		if ((P1IN & BIT1)==BIT1) { //when button is not pressed
			reading = 1;
		}
		else { //if button is pressed
			reading = 0;
		}
		if (reading != lastswitchState) { //usually true, set lastdebouncetime as the value from counter block
			lastDebounceTime = Counter(); 
		}
		if ((Counter() - lastDebounceTime) > debounceDelay) { //set the current switchstate to reading variable
			switchState = reading; 
		}
		if (switchState == 1) { //anytime switchstate is 1, turn on LED, on by default
			P1OUT |= BIT0; 
		}
		else {
			P1OUT &= ~BIT0; //as soon as switchstate is not 1, turn off LED
		}
		lastswitchState = reading; //make lastswitchstate equal to reading when none of if-statements are true
	}
}
#pragma vector=WDT_VECTOR //watchdog interrupt
  __interrupt void watchdog_timer(void) {
	  halfsecond++; //increment after each watchdog interrupt
	  if (halfsecond == 2){ //setting the interrupt delay
		  second++; //increment variable only when halfsecond = 2
		  halfsecond = 0; //reset watchdog halfsecond interrupt value to 0
	  }
}
long Counter(void) //addressasble count variable outside of interrupt block
{
	 long Count = second; //set the current Count equal to second
	 return Count;
}
