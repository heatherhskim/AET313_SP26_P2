#include <Servo.h>
#include <Bounce2.h> // makes copper tape work like 'buttons'
#include <Adafruit_NeoPixel.h>

// setup servo
Servo servo1_180; // Scene3 Romeo
Servo servo2_180; // Scene3 Juliets casket
Servo servo1_360; // Scene1 dancefloor
Servo servo2_360; // Scene4 statue

// setup buttons
Bounce heartButton = Bounce();
Bounce ringButton = Bounce();
Bounce poisonButton = Bounce();
Bounce swordButton = Bounce();

#define PIN 6
#define NUMPIXELS 60
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB+NEO_KHZ800);

void setup(){

  Serial.begin(9600);

  // button setup
  heartButton.attach(8, INPUT_PULLUP);
  heartButton.interval(20);
  ringButton.attach(9, INPUT_PULLUP);
  ringButton.interval(20);
  poisonButton.attach(10, INPUT_PULLUP);
  poisonButton.interval(20);
  swordButton.attach(11, INPUT_PULLUP);
  swordButton.interval(20);

  // servo setup
  servo1_180.attach(2);
  servo2_180.attach(3);
  servo1_360.attach(4);
  servo2_360.attach(5);

  // LED setup
  pixels.begin();
  pixels.show(); // start with all LEDs off

}

void loop(){

  heartButton.update();
  ringButton.update();
  poisonButton.update();
  swordButton.update();

  // Scene 1
  // - (input signal) prop interaction 
  heartButton.read();
  if (heartButton.fell()){
    // - (NEED TO ADD)(output) LED light on, rainbow light
    // pixels.setPixelColor()
    // - (output) dancefloor servo doing 360 repeatedly
    servo1_360.write(360);
    
  }

  // Scene 2
  // - (input signal) prop interaction 
  ringButton.read();
  if (ringButton.fell()){
    // - (NEED TO ADD)(output) LED light on
    // pixels.setPixelColor()
  }

  // Scene 3
  // - (input signal) poison prop interaction 
  poisonButton.read();
  // - (output) romeo collapse <- need to discuss how
  // - (output) juliet casket servo 180 moving 90 degrees
  if (poisonButton.fell()){
    // - (NEED TO ADD)(output) LED light on, blueish light
    // pixels.setPixelColor()
    servo1_180.write(180); // romeo collapse
    delay(500);
    // - (NEED TO ADD)(output) LED light on, red light twinkling
    // pixels.setPixelColor()
    servo2_180.write(180); // juliet casket
    servo2_180.write(90);
  }
  
  // Scene 4
  // - (input signal) *need to discuss how this works* 
  swordButton.read();
  // - (output) statue servo 360 
  if (swordButton.fell()){
    servo2_360.write(180);
    servo2_360.write(90);
  }

}