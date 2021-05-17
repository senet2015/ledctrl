#include <Arduino.h>

//Heltec-wifi-lora board can use all gpio as PWM pin except 19, 26. 
#define LED 25 //On Board LED
#define redPin 5 //Red LED pin num.
#define greenPin 23 //Green LED pin num.
#define bluePin 18 //Blue LED pin num.

int rBrightness = 0;    // how bright the Red LED is
int gBrightness = 0;    // how bright the Green LED is
int bBrightness = 0;    // how bright the Blue LED is
int fadeAmount = 1;    // how many points to fade the LEDs by

// setting PWM properties
const int rChannel = 0;
const int gChannel = 1;
const int bChannel = 2;
const int wChannel = 3;
const int freq = 5000;
const int resolution = 10; //Resolution 8, 10, 12, 15

//#define COMMON_ANODE

//int redPin = 19;
//int greenPin = 23;
//int bluePin = 18;
/*
void rBrightUp(int8_t t);
void rBrightDown(int8_t t);
void gBrightUp(int8_t t);
void gBrightDown(int8_t t);
void bBrightUp(int8_t t);
void bBrightDown(int8_t t);
*/

void rBrightUp(int8_t t) {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(rChannel, rBrightness);
      rBrightness = rBrightness + fadeAmount;
      delay(t);
  }
}
void rBrightDown(int8_t t) {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(rChannel, rBrightness);
      rBrightness = rBrightness - fadeAmount;
      delay(t);
  }
}
void gBrightUp(int8_t t) {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(gChannel, gBrightness);
      gBrightness = gBrightness + fadeAmount;
      delay(t);
  }
}
void gBrightDown(int8_t t) {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(gChannel, gBrightness);
      gBrightness = gBrightness - fadeAmount;
      delay(t);
  }
}
void bBrightUp(int8_t t) {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(bChannel, bBrightness);
      bBrightness = bBrightness + fadeAmount;
      delay(t);
  }
}
void bBrightDown(int8_t t) {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(bChannel, bBrightness);
      bBrightness = bBrightness - fadeAmount;
      delay(t);
  }
}

void setup(){
  Serial.begin(115200);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(LED, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(rChannel, freq, resolution);
  ledcSetup(gChannel, freq, resolution);
  ledcSetup(bChannel, freq, resolution);
  ledcSetup(wChannel, freq, resolution);

  // attach the channel to the GPIO19(R),23(G),18(B) to be controlled
  ledcAttachPin(redPin, rChannel);
  ledcAttachPin(greenPin, gChannel);
  ledcAttachPin(bluePin, bChannel);
  ledcAttachPin(LED, wChannel);
}

void loop(){
  int8_t interval = 5; //dimming interval is 5mS
/*  
  //PWM Value varries from 0 to 1023  
  Serial.println("10 % PWM");
  ledcWrite(wChannel, 102);
  delay(2000);

  Serial.println("20 % PWM");
  ledcWrite(wChannel,205);
  delay(2000);

  Serial.println("40 % PWM");
  ledcWrite(wChannel,410);
  delay(2000);

  Serial.println("70 % PWM");
  ledcWrite(wChannel,714);
  delay(2000);

  Serial.println("100 % PWM");
  ledcWrite(wChannel,1024);
  delay(2000);
*/  
  //Continuous Fading
  Serial.println("Rainbow Color changing Started");
  rBrightUp(interval);
  
  while(1)
  {

    gBrightUp(interval);
    rBrightDown(interval);
    bBrightUp(interval);
    gBrightDown(interval);
    rBrightUp(interval);
    bBrightDown(interval);

    // reverse the direction of the fading at the ends of the fade:
    //if (brightness <= 0 || brightness >= 1023) {
    //  fadeAmount = -fadeAmount;
    //}
    // wait for 30 milliseconds to see the dimming effect
    //delay(5);
  }
}
