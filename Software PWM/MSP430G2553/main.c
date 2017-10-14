#include "msp430g2553.h"

float D = 75;
volatile int /*total*/count = 0;

void main (void)
{
	//float T, X, D = 7;
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	  P1DIR |= BIT2;                       // P1.2 output
	  P1SEL |= BIT2;                       // P1.2 options select
	  
	  P1DIR |= BIT0;
	  P1OUT &= ~BIT0;

	  P1REN |= BIT3;
	  P1IE |= BIT3; 					// P1.3 interrupt enabled
	  P1IES |= BIT3;
	  P1IFG &= ~BIT3; 					// P1.3 IFG cleared
	  __enable_interrupt();				 // enable all interrupts

	  TA0CCR0 = 1000;                          // PWM Period
	  TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
//	  X = D/100; T = 512 * X;
	  TA0CCR1 = 75;
	  TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;

	  __bis_SR_register(LPM0_bits);             // Enter LPM0
	  //__no_operation();                         // For debugger
 }
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
			count++;
				switch( count )  //cycle between 1 of 10 PWM duty cycles
				{
				case 1: D = 200;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 2: D = 300;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 3: D = 400;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 4: D = 500;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 5: D = 600;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 6: D = 700;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 7: D = 800;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 8: D = 900;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 9: D = 1000;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				default : D = 0;
				TA0CCR1 = ( 1000 * (D/1000) );
						TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P1IFG &= ~BIT3;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
						count = 0;
					break;
				}
				//TA0CCR1 = ( 1000 * (D/1000) );
				//TA0CTL = TASSEL_2 + MC_1 + TACLR;
				P1IFG &= ~BIT3;              // P1.3 IFG cleared
				//P1IES ^= BIT3;         			// toggle the interrupt edge,
				
				P1OUT &= ~BIT0;
				if((P1IN & BIT3)!=BIT3) {
	                P1OUT |= BIT0;
	            }
}