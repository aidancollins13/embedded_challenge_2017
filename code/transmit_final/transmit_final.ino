#include<Arudino.h>
#include"SPI.h"
#include"RF24.h"


RF24 radio(7,8);
byte addresses[][5] = {"15_T", "15_R"};
int radio_number = 0;

long s1,s0;
long readings[2];

void setup(){
	wireless_setup(radio_number);
	sensor_setup();
}

void loop(){
	s0 = read_dist(0);
	s1 = read_dist(1);
	
	send_readings(s0,s1);

	delay(100);

}


long read_dist(int sensor){
	int trigPin, echoPin;
	if(sensor){
 	 	 trigPin = 2;
 	 	 echoPin = 3;
	}
	else{
		trigPin = 5;
		echoPin = 6;
	}
	long duration, distance;
	PORTD  &= !(1 << trigPin); //  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2); 
	PORTD |= (1<<trigPin); //digitalWrite(trigPin, HIGH);
	delayMicroseconds(10); 
	PORTD &= !(1 << trigPin);//  digitalWrite(trigPin, LOW);  
	duration = pulseIn(echoPin, HIGH);
	distance = (duration/2) / 29.1;

	Serial.print("SENSOR:\t");
	Serial.print(distance);
	Serial.println(" cm");
	return distance;
}


void sensor_setup(){
	DDRD |=   0b00100100; // set pin 2 and 5 as output
	DDRD &= !(0b01001000);//set pin 3 and 6 as input
	PORTD |= 0b01001000; //enable pullup on 3 and 6, the inputs

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

void send_readings(long s0, long s1){
	readings[0] = s0;
	readings[1] = s1;
	radio.stopListening();
	if(!radio.write(readings, sizeof(long) *2)){
		Serial.println("WIRELESS:\t failed");
 	}
	radio.startListening();

}
