//Lets start with off and on only


#include "msp430.h"
#include <stdint.h>
//interrupt handler on P3
	//this is where the watch will send the data
#define 	OFF  				0
#define		ON  				1
#define     TXD                 BIT2                      // TXD on P1.2
#define     RXD                 BIT1                      // RXD on P1.1
#define 	IROUT 				BIT0					 //send pulses through IR transmitter

int bulbState;

//P1.2 will be the output to IR transmitter


//*this will be the hardest part of this code -->> use timer(?) to get 38kHz frequency for sending IR signals 
//send pulses consistent with observed data (address ~address data ~data)
	//on will look like 0000 0000 1111 1111 1110 0000 0001 1111
	// off = {0,0,0,0, 0,0,0,0, 1,1,1,1, 1,1,1,1, 0,1,1,0, 0,0,0,0, 1,0,0,1, 1,1,1,1};

// ATTEMPT 3: FOR LOOP

char output[] = {0,0,0,0, 0,0,0,0, 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0, 0,0,0,1, 1,1,1,1, 1};
//START, VERSION, 4x FLAG, 2x PROFILE, CHECKSUM, END
// uint8_t helloPebble[] = {0x7E, 0x01, 0x00, 0x00, 0x00, 0x00,0x02,0x00,0xff,0x7e};

// uint8_t TEMP[] =		{0x7E, 0x01, 0x03, 0x00, 0x00, 0x00,0x02,0x00,0xff,0x7e};

// THIS FUNCTION WAS TAKEN FROM THE PEBBLE LIBRARY:
	//https://github.com/pebble/ArduinoPebbleSerial/blob/master/utility/crc.c
void crc8_calculate_byte_streaming(const uint8_t data, uint8_t *crc) {
  // Optimal polynomial chosen based on
  // http://users.ece.cmu.edu/~koopman/roses/dsn04/koopman04_crc_poly_embedded.pdf
  // Note that this is different than the standard CRC-8 polynomial, because the
  // standard CRC-8 polynomial is not particularly good.

  // nibble lookup table for (x^8 + x^5 + x^3 + x^2 + x + 1)
  static const uint8_t lookup_table[] =
      { 0, 47, 94, 113, 188, 147, 226, 205, 87, 120, 9, 38, 235, 196,
        181, 154 };

  int i;
  for (i = 2; i > 0; i--) {
    uint8_t nibble = data;
    if (i % 2 == 0) {
      nibble >>= 4;
    }
    int index = nibble ^ (*crc >> 4);
    *crc = lookup_table[index & 0xf] ^ (*crc << 4);
  }
}
//END OF PEBBLE CODE

//We need to let the watch know that we are connected to it!!
void sendData(){
	int i;
	int j;
	uint8_t parity = 0;
	uint8_t data;
	uint8_t helloPebble[10] =		{0x7E, 0x01, 0x00, 0x00, 0x00, 0x00,0x02,0x00,0xff,0x7e};

	for(i=1;i<8;i++){
		crc8_calculate_byte_streaming(helloPebble[i], &parity); 		
	}
//	crc8_calculate_byte_streaming(parity, &parity);
	helloPebble[8]=parity;
	for(i=0;i<10;i++){
			// P1OUT |= TXD;
			// __delay_cycles(1000);

			P1OUT &= ~TXD;
			__delay_cycles(1190);

		data = helloPebble[i];
		for(j=0;j<8;j++){
			if( (data >> j) & 0x01){
				P1OUT |= TXD;
			}
			else{
				P1OUT &= ~TXD;
			}
			__delay_cycles(1190); //each bit is 100Us long 	but timer is at 16MHz	
		}
		P1OUT |= TXD;
		__delay_cycles(2480);	//send this separator between bytes 2300 seemed to work before...
	 }
}

void sendIRData(){    
	if(bulbState == OFF){
		output[16] = 0;
		output[24] = 1;
		bulbState = ON;
	}
	else{
		output[16] = 1;
		output[24] = 0;
		bulbState = OFF;
	}

    int i;
    //Send a leader code for 9ms followed by 4.5 ms pause
	    P1SEL |= IROUT; // connect output bit to timer
		P1OUT = BIT3;	// make sure interrupt bit is still pulled high
		//P1OUT = IROUT | BIT3;
		__delay_cycles(106000); //wait 9 ms
		P1SEL &= ~IROUT;	// disconnect output from timer
		//P1OUT = BIT3;
		__delay_cycles(54000); //wait 4.5ms

    for(i=0; i<33; i++){
    	P1SEL |= IROUT; // connect output bit to timer
		P1OUT = BIT3;	// make sure interrupt bit is still pulled high
		__delay_cycles(6400); //wait 22 pulses, want 578Us in between start and end
								//times 16 because we changed the clock cycle => 578 * 16 = 9248 too high
								//500 * 16 = 8000 too high
								//450 * 16 = 7200 ->660Us
								//400 * 16 = 6400 ->600Us
		P1SEL &= ~IROUT;	// disconnect output from timer
		if(output[i]==0){
			//__delay_cycles(14000); //wait a length of time dependent on the value being passed
			__delay_cycles(7000);						//want 1125 ...or 520???
		}
		else{
			// __delay_cycles(27000); //want x ...or 1700????
			__delay_cycles(20500);
		}
    }
}

void main(void)
	{
	 bulbState = OFF;
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




// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{ 
  
  sendIRData();
  // sendData();
  // sendData();
  // sendData();
  // sendData();

  P1IFG &= ~BIT3;
}


