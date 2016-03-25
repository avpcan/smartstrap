//Lets start with off and on only


#include "msp430.h"
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

// ATTEMPT 3: FOR LOOP

//ATTEMPT 2: FUNCTION CALLS
void sendOne(){
	P1SEL &= ~BIT2;
	P1OUT = BIT3;
	__delay_cycles(578); //wait 22 pulses
	P1SEL |= BIT2;
	__delay_cycles(2250); //distance between 1s
}

void sendZero(){
	P1SEL &= ~BIT2;
	P1OUT = BIT3;
	__delay_cycles(578); //wait 22 pulses
	P1SEL |= BIT2;	
	__delay_cycles(1125); //distance between 0s	
}

void sendData(){
	P1OUT ^= (BIT2 | BIT0);
	P1SEL |= BIT2;
	__delay_cycles(9000); //leader code 
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(4500); //leader code pause

	//send address
	sendZero();sendZero();sendZero();sendZero();
	sendZero();sendZero();sendZero();sendZero();
	sendOne();sendOne();sendOne();sendOne();
	sendOne();sendOne();sendOne();sendOne();

	//send Data
	sendOne();sendOne();sendOne();sendZero();
	sendZero();sendZero();sendZero();sendZero();
	sendZero();sendZero();sendZero();sendOne();
	sendOne();sendOne();sendOne();sendOne();

}


/*
///ATTEMPT 1; HARDCODE IT
void sendData(){

  P1OUT ^= (BIT2 | BIT0);
	P1SEL |= BIT2;
	__delay_cycles(4500); //leader code pause
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;			
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	/////////////////////////////////////////////////////////////////////////
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	//=====================================================================

		__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(1125); //distance between 0s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
	__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
		__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
		__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
		__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = 0;
		__delay_cycles(2250); //distance between 1s
	P1SEL |= BIT2;
	__delay_cycles(578); //wait 22 pulses
	P1SEL &= ~BIT2;
	P1OUT = BIT3;
	__delay_cycles(57800);
}
*/
void main(void)
	{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	P1DIR |= (BIT2 | BIT0); // P1.2 to output
	P1SEL = 0; // We don't want the timer to change anything until we start sending data
	P1OUT = (BIT2 | BIT0 |BIT3);
	P1REN = BIT3; //enable resistor
	P1IE = BIT3; //Enable input at P1.3 as an interrupt


	//setup timer 0
	BCSCTL1 = CALBC1_16MHZ; //set timer to 16MHz frequency
	DCOCTL = CALDCO_16MHZ;   	
	TA0CCR0 = 421-1; // PWM Period - calculated like 38 kHz = 0.02631 ms, * 16000 = 421
	TA0CCTL1 = OUTMOD_3; // set/reset mode  //page 364
	TA0CCR1 = 210; // CCR1 PWM duty cycle should be half the period
	TA0CTL = TASSEL_2 + MC_1; // SMCLK, up mode

	_BIS_SR (LPM4_bits + GIE); //Turn on interrupts and go into the lowest power mode
	
}




// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{ 
   
  sendData();
  sendData();
  sendData();
  sendData();
  sendData();

  P1IFG &= ~BIT3;
}


