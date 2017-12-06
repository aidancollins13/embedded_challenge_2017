
#include"SPI.h"
#include"RF24.h"

RF24 radio(7,8);
byte addresses[][6] = {"T_15"};
int radio_number = 1; //receive

struct motorControl
{
 long left;
 long right;
};

typedef struct motorControl Package;
Package readings;

void setup(){
	servo_setup();
	wireless_setup(radio_number);
  Serial.begin(9600);
}


void loop(){
  
	get_readings();
  Serial.print("Received ");
  Serial.print(readings.left);
  Serial.print(" and ");
  Serial.println(readings.right);
	set_motor(0,readings.left);
	set_motor(1,readings.right);
	delay(100);
  
	
}


void wireless_setup(int radio_number){
	radio.begin();
  radio.setChannel(15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  if(radio_number){
    radio.openReadingPipe(1,addresses[0]);
    radio.startListening();
  }
  else
    radio.openWritingPipe(addresses[0]);
  delay(1000);

}

void get_readings(){
  if(radio.available()){
    while(radio.available()){
      radio.read(&readings, sizeof(readings));
    }
  }
  else
    Serial.println("WIRELESS:\tradio not available");
  
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
    if(speed > 40) OCR1A = 93;
		else OCR1A = map(speed, 3, 40, 63,125);
	if (motor == 1)
    if(speed > 40) OCR1B = 93;
		else OCR1B = map(speed, 3, 40, 63, 125);
}




