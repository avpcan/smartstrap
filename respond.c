

#include "msp430.h"

void main(void)
	{
	 bulbState = OFF;
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	P1DIR |= (BIT2 | BIT0); // P1.2 to output
	P1SEL = 0; // We don't want the timer to change anything until we start sending data
	P1OUT = (BIT2 | BIT0 |BIT3);
	P1REN = BIT3; //enable resistor
	P1IE = BIT3; //Enable input at P1.3 as an interrupt


	//setup timer 1  	
	TA1CCR0 = 421-1; // PWM Period - calculated like 38 kHz = 0.02631 ms, * 16000 = 421
	TA1CCTL1 = OUTMOD_3; // set/reset mode  //page 364
	TA1CCR1 = 210; // CCR1 PWM duty cycle should be half the period
	TA1CTL = TASSEL_2 + MC_1; // SMCLK, up mode

	_BIS_SR (LPM4_bits + GIE); //Turn on interrupts and go into the lowest power mode
	
}
