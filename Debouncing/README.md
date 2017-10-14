MSP430 Microprocessors (5 boards):
------------------------------------------
MSP430F5529
MSP430FR2311
MSP430FR5994
MSP430FR6989
MSP430G2553
------------------------------------------

Debouncing

------------------------------------------

The code begins outside the main block by declaring two volatiles, int halfsecond=0, long second=0; declaring two long integers, lastdebouncetime=0, debouncedelay=10; and declaring two integeres switchstate, lastswitchstate=0. The long integer Counter(void) is also initialized. Inside the main block, the first line turns activates the watchdog timer and sets it to 0.5ms. The watchdog timer is used for delaying inputs from the button until a sufficient amount of time has passed with successive, solid 1 values coming from the button. The next line enables the watchdog timer to perform interrupts. Two lines are commented out for simplicity, but they can be used to calibrate the on-board timer to a desired frequency (1MHz by default). An LED pin is wired as directional and then wired as a NOT output (LED is on by default). A BUTTON pin is NOT wired as directional, and is wired to an internal resistor. The line after this causes the processor to enter low power mode 0 and enables interrupt code blocks. The infinite while-loop inside the main function block first declares an integer reading. The first of several if-statements within the while-loop only runs when the BUTTON is not pressed, which sets reading=1. An else-statement runs only when the button is pressed, setting reading=0. Another if-statement runs only if the variable reading is not equal to the variable lastswitchstate, which then sets lastdebouncetime=Counter() (Counter is another declared function block). Another if-statement runs only if Counter() - lastdebouncetime is greater than debouncedelay (greater than 10, this if-statement is true by default), which then sets switchstate=reading. Another if-statement runs only if switchstate is equal to 1, which turns on the LED (switchstate is already 1 by default). As soon as switchstate is not 1 (if reading is 0), then the else-statement runs that turns off the LED. Outside of these if-statements and inside the while-loop, the last line makes lastswitchstate=reading. This last line occurs infinitely when none of the if-statements are true. 

Before the interrupt block, the #pragma vector line is equal to WDT_VECTOR, which reads any interrupts coming from the watchdog timer. Within the interrupt block, the halfsecond variable is incremented by 1. A single if-statement in the interrupt block runs only if halfsecond is equal to 2 (this sets the interrupt delay time). In this if-statement, second is incremented by 1 and halfsecond=0 (this resets watchdog's halfsecond interrupt value back to 0).

The final function block called Counter(void) only has two lines of code. The long integer Count=second, and then Count is returned for future declarations of the function block. The variable second comes from the watchdog interrupt block, and keeps incrementing indefinitely. 

This code is almost identical for every board, with the exception found in three of them. The MSP430FR boards require one extra line to implement the same code for blinking an LED, which disables the GPIO power-on default high-impedance mode for activating the configured In/Out port settings (PM5CTL0 &= ~LOCKLPM5).

------------------------------------------
