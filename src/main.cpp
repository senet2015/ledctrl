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
void rBrightUp();
void rBrightDown();
void gBrightUp();
void gBrightDown();
void bBrightUp();
void bBrightDown();

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
  rBrightUp();
  
  while(1)
  {

    gBrightUp();
    rBrightDown();
    bBrightUp();
    gBrightDown();
    rBrightUp();
    bBrightDown();

    // reverse the direction of the fading at the ends of the fade:
    //if (brightness <= 0 || brightness >= 1023) {
    //  fadeAmount = -fadeAmount;
    //}
    // wait for 30 milliseconds to see the dimming effect
    //delay(5);
  }
}

void rBrightUp() {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(rChannel, rBrightness);
      rBrightness = rBrightness + fadeAmount;
      delay(5);
  }
}
void rBrightDown() {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(rChannel, rBrightness);
      rBrightness = rBrightness - fadeAmount;
      delay(5);
  }
}
void gBrightUp() {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(gChannel, gBrightness);
      gBrightness = gBrightness + fadeAmount;
      delay(5);
  }
}
void gBrightDown() {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(gChannel, gBrightness);
      gBrightness = gBrightness - fadeAmount;
      delay(5);
  }
}
void bBrightUp() {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(bChannel, bBrightness);
      bBrightness = bBrightness + fadeAmount;
      delay(5);
  }
}
void bBrightDown() {
  for (int i = 0; i <= 1023; i++) {
      ledcWrite(bChannel, bBrightness);
      bBrightness = bBrightness - fadeAmount;
      delay(5);
  }
}