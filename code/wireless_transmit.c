#include <SPI.h>
#include "RF24.h"

bool radioNumber = 0; // or 1
RF24 radio(7,8);
byte addresses[][5] = {"15_T","15_R"};

void setup(){
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
	//radio.startListening(); only if recieving 
	radio.stopListening(); // makes sure we are not recieving
}

void loop(){
	Serial.println("Test Sending");
	radio.startListening();
	unsigned long startTime = micros();
	bool timeout = 0;
	while (!radio.available()){ // for debugging
		if (micros() - startTime > 100000){ // if waited longer for 100ms. This could be increased or decreased depending on the scenario
			timeout = 1;
			break;
		}
	}
	if(timeout)
		Serial.println("Timed Out");
	else{
		/* DO SOMETHING DEPENDENT ON SOMETHING*/
	}
	delay(10); // delayed for 10 ms

}

// git add and git commit