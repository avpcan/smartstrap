//Lets start with off and on only

//interrupt handler on P3
	//this is where the watch will send the data
enum  Input_Type
    { 
      up_buttton, 
      select_button, 
      down_button, 
    };

//P1.2 will be the output to IR transmitter


//*this will be the hardest part of this code -->> use timer(?) to get 38kHz frequency for sending IR signals 
//send pulses consistent with observed data (address ~address data ~data)
	//on will look like 0000 0000 1111 1111 1110 0000 0001 1111




#include "msp430.h"
void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
P1DIR |= BIT2; // P1.2 to output
P1SEL |= BIT2; // P1.2 to TA0.1

//setup timer 1
BCSCTL1 = CALBC1_16MHZ; //set timer to 16MHz frequency
DCOCTL = CALDCO_16MHZ;   	
TA0CCR0 = 421-1; // PWM Period - calculated like 38 kHz = 0.02631 ms, * 16000 = 421
TA0CCTL1 = OUTMOD_3; // set/reset mode  //page 364
TA0CCR1 = 210; // CCR1 PWM duty cycle should be half the period
TA0CTL = TASSEL_2 + MC_1; // SMCLK, up mode

//setup timer 2
// TA1CCR0 |= 1000 - 1;
// TA1CCTL1 |= OUTMOD_7;
// TA1CCR1 |= 500;
// TA1CTL |= TASSEL_2 + MC_1;

_BIS_SR(LPM0_bits); // Enter Low Power Mode 0
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{ 
      
  //this is the interrupt that occurs when we get some data

}
