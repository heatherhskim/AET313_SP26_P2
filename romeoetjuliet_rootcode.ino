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
  heartButton.interval(30); 
  ringButton.attach(9, INPUT_PULLUP);
  ringButton.interval(30);
  poisonButton.attach(10, INPUT_PULLUP);
  poisonButton.interval(30);
  swordButton.attach(11, INPUT_PULLUP);
  swordButton.interval(30);

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
    Serial.println("Scene 1 Activated! Dancefloor spinning.");
    // - (NEED TO ADD)(output) LED light on, rainbow light
    // pixels.setPixelColor()
    
    // 180 starts the continuous servo at full speed. 
    // Change to 0 to spin the other way.
    servo1_360.write(180); 
  }

  // Scene 2
  // - (input signal) prop interaction 
  ringButton.read();

  if (ringButton.fell()){
      Serial.println("Scene 2 Activated");
  }
  Serial.println("Scene 2: Warm White LED");
  for(int i=0; i<=12; i++) pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // 이전 LED 끄기
  for(int i=43; i<=52; i++) pixels.setPixelColor(i, pixels.Color(255, 100, 20));
  pixels.show();
  delay(15000);

  // Scene 3
  // - (input signal) poison prop interaction 
  Serial.println("Scene 3: Blue-Purple LED");
  for(int i=13; i<=42; i++) {
    if(i % 2 == 0) pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    else pixels.setPixelColor(i, pixels.Color(100, 0, 255));
  }
  pixels.show();
  poisonButton.read();
  // - (output) romeo collapse <- need to discuss how
  // - (output) juliet casket servo 180 moving 90 degrees
  if (poisonButton.fell()){
      Serial.println("Scene 3 Activated");
    servo1_180.write(180); // romeo collapse
    delay(10000);
    servo2_180.write(180); // juliet casket
    servo2_180.write(90);
  }

  for(int j=0; j<15; j++) {
    for(int i=13; i<=42; i++) pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();
    delay(500);
    for(int i=13; i<=42; i++) pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
    delay(500);
    }
  
  // Scene 4
  swordButton.read();
  // - (output) statue servo 360 
  if (swordButton.fell()){
    delay(5000);
    Serial.println("Scene 4 Activated");
    servo2_360.write(180);
    servo2_360.write(90);
  }

}
