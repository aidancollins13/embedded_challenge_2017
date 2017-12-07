#include"SPI.h"
#include<printf.h>
#include"RF24.h"


RF24 radio(7,8);
byte addresses[][6] = {"T_15"};
int radio_number = 0; //transmit

long s1,s0;

struct motorControl
{
 long left;
 long right;
};

typedef struct motorControl Package;
Package readings;


void setup(){
  Serial.begin(115200); 
  printf_begin();
	wireless_setup(radio_number);
	sensor_setup();
}

void loop(){
	readings.left = read_dist(0);
  //readings.right = read_dist(1);
	
	send_readings();
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
  Serial.print(sensor);
  Serial.print(" - ");
	Serial.print(distance);
	Serial.println(" cm");
	return distance;
}


void sensor_setup(){
	//DDRD |=   0b00100100; // set pin 2 and 5 as output
	//DDRD &= !(0b01001000);//set pin 3 and 6 as input
  DDRD = 0b10100100;
	PORTD |= 0b01001000; //enable pullup on 3 and 6, the inputs

}

void wireless_setup(int radio_number){
	radio.begin();
  radio.setChannel(15);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  if(radio_number){
    radio.openReadingPipe(1,addresses[0]);
    radio.startListening();
  }
  else
    radio.openWritingPipe(addresses[0]);
  delay(1000);

}

void send_readings(){
  if(!radio.write(&readings, sizeof(readings)))
    Serial.println("WIRELESS\twrite failed");
  radio.printDetails();
  
}
