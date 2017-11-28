#include <SPI.h>
#include "RF24.h"

bool radioNumber = 1; // or 1
RF24 radio(7,8);
byte addresses[][5] = {"15_T","15_R"};

void setup(){
	Serial.begin(9600);
	radio.begin();
	radio.setPALevel(RF24_PA_LOW);
	if (radioNumber){
		radio.openWritingPipe(addresses[0]); // might be index 0 
		radio.openReadingPipe(1,addresses[1]); // might be index 1
	}
	else{
		radio.openWritingPipe(addresses[1]); // might be index 1
		radio.openReadingPipe(1,addresses[0]); // might be index 0
	}
	radio.startListening(); //only if recieving 
	//radio.stopListening(); // makes sure we are not recieving
}

void loop(){
	while (radio.available()){
		radio.read(...);
	}

}
