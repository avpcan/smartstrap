
// THIS FUNCTION WAS TAKEN FROM THE PEBBLE LIBRARY:
// 	https://github.com/pebble/ArduinoPebbleSerial/blob/master/utility/crc.c
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
// END OF PEBBLE CODE

// We need to let the watch know that we are connected to it!!
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

