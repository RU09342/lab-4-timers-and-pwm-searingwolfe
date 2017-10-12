#include "msp430fr5994.h"

float D = 75;
volatile int /*toTBl*/count = 0;

void main (void)
{
	//float T, X, D = 7;
	  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	  PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings

	  P5DIR |= BIT6;                       // P1.2 output
	  P5SEL0 |= BIT6;                       // P1.2 options select
	  
	  P1DIR |= BIT0;
	  P1OUT &= ~BIT0;

	  P3REN |= BIT4;
	  P3IE |= BIT4; 					// P1.3 interrupt enabled
	  P3IES |= BIT4;
	  P3IFG &= ~BIT4; 					// P1.3 IFG cleared
	  __enable_interrupt();				 // enable all interrupts

	  TB0CCR0 = 1000;                          // PWM Period
	  TB0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
//	  X = D/100; T = 512 * X;
	  TB0CCR1 = 75;
	  TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;

	  __bis_SR_register(LPM0_bits);             // Enter LPM0
	  //__no_operation();                         // For debugger
 }
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
			count++;
				switch( count ) //cycle between 1 of 10 PWM duty cycles
				{
				case 1: D = 200;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 2: D = 300;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 3: D = 400;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 4: D = 500;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 5: D = 600;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 6: D = 700;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 7: D = 800;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 8: D = 900;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				case 9: D = 1000;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						P3IFG &= ~BIT4;              // P1.3 IFG cleared
						//P1IES ^= BIT3;         			// toggle the interrupt edge,
					break;
				default : D = 0;
				TB0CCR1 = ( 1000 * (D/1000) );
								TB0CTL = TBSSEL_2 + MC_1 + TBCLR + ID_3;
						  P3IFG &= ~BIT4;              // P1.3 IFG cleared
						  //P1IES ^= BIT3;         			// toggle the interrupt edge,
						  count = 0;
					break;
				}
				//TB0CCR1 = ( 1000 * (D/1000) );
				//TB0CTL = TBSSEL_2 + MC_1 + TBCLR;
				P3IFG &= ~BIT4;              // P1.3 IFG cleared
				//P1IES ^= BIT3;         			// toggle the interrupt edge,
				
				P1OUT &= ~BIT0;
				if((P5IN & BIT6)!=BIT6) {
	                P1OUT |= BIT0;
	            }
}