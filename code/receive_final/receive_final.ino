#include<Arudino.h>
#include"SPI.h"
#include"RF24.h"

int radio_number = 1;
void setup(){
	servo_setup();
	wireless_setup(radio_number);
}


void loop(){

}


void wireless_setup(int radio_number){
	radio.begin();
	radio.setPALevel(RF24_PA_HIGH);

	if(radio_number){ 	//receive
		radio.openWritingPipe(addresses[1]);
		radio.openReadingPipe(1,addresses[0]);
	}

	else{ 				//transmit
		radio.openWritingPipe(addresses[0]);
		radio.openReadingPipe(1,addresses[0]);

	}

	radio.startListening();

}


