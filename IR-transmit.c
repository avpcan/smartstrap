//Lets start with off and on only


#include "msp430.h"
#include <stdint.h>
//interrupt handler on P3
	//this is where the watch will send the data

#define     TXD                 BIT0                      // TXD on P1.2
#define     RXD                 BIT1                      // RXD on P1.1
#define 	IROUT 				BIT2					 //send pulses through IR transmitter

#define 	OFF  				0
#define		ON  				1
#define		RED 				2
#define		GREEN 				3
#define		BLUE 				4
#define		WHITE 				5

int bulbState;


char output[] = {0,0,0,0, 0,0,0,0, 1,1,1,1, 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1};
char on[] = {1,1,1,0, 0,0,0,0, 0,0,0,1, 1,1,1,1};
char off[] = {0,1,1,0, 0,0,0,0, 1,0,0,1, 1,1,1,1};
char red[] = {1,0,0,1, 0,0,0,0, 0,1,1,0, 1,1,1,1, 0};
char green[] = {0,0,0,1, 0,0,0,0, 1,1,1,0, 1,1,1,1, 0};
char blue[] = {0,1,0,1, 0,0,0,0, 1,0,1,0, 1,1,1,1, 0};
char white[] = {1,1,0,1, 0,0,0,0, 0,0,1,0, 1,1,1,1, 0};

void updateOutput(char* newVals){
	int i;
	for(i=0; i<16; i++){
		output[i+16] = newVals[i];
	}
}

void setOutput(){
	switch(bulbState) {
		case OFF :
			updateOutput(on);
			bulbState = ON;
			break;
	
		case ON :
			updateOutput(red);
			bulbState = RED;
			break;

		case RED :
			updateOutput(green);
			bulbState = GREEN;
			break;

		case GREEN :
			updateOutput(blue);
			bulbState = BLUE;
			break;

		case BLUE :
			updateOutput(white);
			bulbState = WHITE;
			break;

		case WHITE :
			updateOutput(off);
			bulbState = OFF;
			break;

		default :
			updateOutput(on);
			bulbState = ON;
			break;
		
	}
}

void sendIRData(){    

	setOutput();
    int i;
    //Send a leader code for 9ms followed by 4.5 ms pause
	    P1SEL |= IROUT; // connect output bit to timer
		P1OUT = BIT3;	// make sure interrupt bit is still pulled high
		__delay_cycles(106000); //wait 9 ms
		P1SEL &= ~IROUT;	// disconnect output from timer
		__delay_cycles(54000); //wait 4.5ms

//send one bit of information at a time
    for(i=0; i<33; i++){
    	P1SEL |= IROUT; // connect output bit to timer
		P1OUT = BIT3;	// make sure interrupt bit is still pulled high
		__delay_cycles(6400); //wait 22 pulses, want 578Us in between start and end
		P1SEL &= ~IROUT;	// disconnect output from timer
		if(output[i]==0){
			__delay_cycles(7000);
		}
		else{
			__delay_cycles(20500);
		}
    }
}

void main(void)
	{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	P1DIR |= (IROUT | TXD); // P1.2 to output
	P1SEL = 0; // We don't want the timer to change anything until we start sending data
	P1OUT = (IROUT | TXD |BIT3);
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




// This gets called when the button is pressed
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{ 
  
  sendIRData();


  P1IFG &= ~BIT3;
}


