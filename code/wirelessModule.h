#include "RF24.h"

//bool radioNumber = 1; // or 1
RF24 radio(7,8);
byte addresses[][5] = {"15_T","15_R"};

void recieve_setup();
void recieve(uint32_t); 

void transmit_setup();
uint32_t transmit();