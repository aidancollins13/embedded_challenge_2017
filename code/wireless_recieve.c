#include <SPI.h>
#include "RF24.h"
#include "wirelessModule.h"

//bool radioNumber = 1; // or 1

void recieve_setup(){
	radioNumber = 1;
	Serial.begin(9600);
	radio.begin();
	radio.setPALevel(RF24_PA_LOW);
	if (radioNumber){
		radio.openWritingPipe(addresses[1]); // might be index 0 
		radio.openReadingPipe(1,addresses[0]); // might be index 1
	}
	else{
		radio.openWritingPipe(addresses[0]); // might be index 1
		radio.openReadingPipe(1,addresses[1]); // might be index 0
	}
	radio.startListening(); //only if recieving 
	//radio.stopListening(); // makes sure we are not recieving
}

void recieve(uint32_t *msg){
	if (radio.available())
		radio.read(&msg, ...);
	return NULL;
}