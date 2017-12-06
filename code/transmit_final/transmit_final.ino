#include"SPI.h"
#include"RF24.h"


RF24 radio(7,8);
byte addresses[][6] = {"15_TR", "15_RR"};
int radio_number = 0;

long s1,s0;
long readings[2];

void setup(){
  Serial.begin(9600); 
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
  Serial.print(sensor);
  Serial.print(" - ");
	Serial.print(distance);
	Serial.println(" cm");
	return distance;
}


void sensor_setup(){
	//DDRD |=   0b00100100; // set pin 2 and 5 as output
	//DDRD &= !(0b01001000);//set pin 3 and 6 as input
  //DDRD = 0b10100100;
	//PORTD |= 0b01001000; //enable pullup on 3 and 6, the inputs
 pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6,INPUT);
}

void wireless_setup(int radio_number){
	radio.begin();
	radio.setPALevel(RF24_PA_LOW);

	if(radio_number){ 	//receive
		radio.openWritingPipe(addresses[1]);
		radio.openReadingPipe(1,addresses[0]);
	}

	else{ 				//transmit
		radio.openWritingPipe(addresses[0]);
		radio.openReadingPipe(1,addresses[1]);

	}

	radio.startListening();

}

void send_readings(long s0, long s1){
	readings[0] = s0;
	readings[1] = 1;
  Serial.println("A");
	radio.stopListening();
  Serial.println("B");
  if (!radio.available())
    Serial.println("Timed");
  Serial.println("C");
  unsigned long start_time = 2;
	if(!radio.write(&start_time, sizeof(unsigned long))){
		Serial.println("WIRELESS:\t failed");
 	}
  radio.startListening();
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
    }
        
    if ( timeout )                                             // Describe the results
        Serial.println(F("Failed, response timed out."));

}
