#include<Arduino.h>
#include "SPI.h"
//#include "servo.h"

long motor1_val, motor2_val;

void setup() {
  ADMUX = 0x40;
  ADCSRA = 0xE3;
	servo_setup();  // funciton is servo.g that setups the timer and pwm signals for the servo controller
	// TODO: Wireless setup
	//set_motor(0,1024); // test to set motor on pin 9 to max speed
	set_motor(1,0); //test to set motor on pin 10 to max reverse
  Serial.begin(9600);
}


void loop(){
	
set_motor(0,ADC);
}

// 16-bit timer witha 265 prescaller set to fast pwm with ICR1 as top
// ICR1 = 1250 
// period = 20ms
//full reverse 1ms | slow reverse 1.45ms |   off 1.5ms|   low forward 1.55ms |    full ahead 2ms |
//  OCR1X 63     |  OCR1X = 91       | OCR1X = 93|    OCR1X = 97    |     OCR1X = 125 |
//
//

// This sets up timer 1 to be fast pwm with a 256 prescaler
// and a 1250 top, pins 9 and 10 are outputs.
void servo_setup(){

  TCCR1A = 0b10100010;
  TCCR1B = 0b00011100;
  ICR1 = 1250;
  DDRB = 0x06;
}

// this function takes in a reading value
//  assumed to be a 10 bit value(like an analog sensor would read)
//  and a motor, motor 0 changes oin 9, motor 1 change pin 10
void set_motor(int motor, int speed){
  if (motor == 0)
    OCR1A = map(speed, 0, 1024, 63,125);
    Serial.println(map(speed, 0, 1024, 63,125));
  if (motor == 1)
    OCR1B = map(speed, 0, 1024, 63, 125);

}

