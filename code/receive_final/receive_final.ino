
#include"SPI.h"
#include"RF24.h"

RF24 radio(7,8);
byte addresses[][5] = {"15_T", "15_R"};
long readings[2];
int radio_number = 1;
void setup(){
	servo_setup();
	wireless_setup(radio_number);
}


void loop(){

	(&readings);
	set_motor(0,readings[0]);
	set_motor(0,readings[1]);
	delay(100);
	
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

void get_readings(long* &readings){

	while(radio.available()){
		radio.read(&readings, sizeof(long) *2);
 	 }
}

// This sets up timer 1 to be fast pwm with a 256 prescaler
// and a 1250 top, pins 9 and 10 are outputs.
void servo_setup(){

	TCCR1A = 0b10100010;
	TCCR1B = 0b00011100;
	ICR1 = 1250;
	DDRB = 0x06;
}

// this function takes in a reading value
// 	assumed to be a 10 bit value(like an analog sensor would read)
// 	and a motor, motor 0 changes oin 9, motor 1 change pin 10
void set_motor(int motor, int speed){
	if (motor == 0)
		OCR1A = map(speed, 3, 40, 63,125);
	if (motor == 1)
		OCR1B = map(speed, 3, 40, 63, 125);
}
