#include "msp430f5529.h"

float D = 75;
volatile int /*total*/count = 0;

void main (void)
{
	//float T, X, D = 7;
	  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	  //PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings

	  P2DIR |= BIT0;                       // P1.2 output
	  P2SEL0 |= BIT0;                       // P1.2 options select
	  
	  P1DIR |= BIT0;
	  P1OUT &= ~BIT0;

	  P2REN |= BIT1;
	  P2IE |= BIT1; 					// P1.3 interrupt enabled
	  P2IES |= BIT1;
	  P2IFG &= ~BIT1; 					// P1.3 IFG cleared
	  __enable_interrupt();				 // enable all interrupts

	  TA1CCR0 = 1000;                          // PWM Period
	  TA1CCTL1 = OUTMOD_7;                      // CCR1 reset/set
//	  X = D/100; T = 512 * X;
	  TA1CCR1 = 75;
	  TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;

	  __bis_SR_register(LPM0_bits);             // Enter LPM0
	  //__no_operation();                         // For debugger
 }
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
			count++;
				switch( count ) //cycle between 1 of 10 PWM duty cycles
				{
				case 1: D = 200;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 2: D = 300;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 3: D = 400;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 4: D = 500;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 5: D = 600;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 6: D = 700;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 7: D = 800;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 8: D = 900;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 9: D = 1000;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						P2IFG &= ~BIT1;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				default : D = 0;
				TA1CCR1 = ( 1000 * (D/1000) );
								TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3;
						  P2IFG &= ~BIT1;              // P1.3 IFG cleared
						  //P1IES ^= BIT3;         			// toggle the interrupt edge,
						  count = 0;
					break;
				}
				//TA1CCR1 = ( 1000 * (D/1000) );
				//TA1CTL = TASSEL_2 + MC_1 + TACLR;
				P2IFG &= ~BIT1;              // P1.3 IFG cleared
				//P1IES ^= BIT3;         			// toggle the interrupt edge,
				
				P1OUT &= ~BIT0;
				if((P2IN & BIT1)!=BIT1) {
	                P1OUT |= BIT0;
	            }
}