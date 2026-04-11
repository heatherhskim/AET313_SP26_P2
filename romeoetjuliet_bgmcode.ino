
///////////////////////////////////
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav2;     //xy=121,203, BGM MUSIC
AudioPlaySdWav           playSdWav1;     //xy=124,114, SFX EFFECT
AudioMixer4              mixerLeft;         //xy=326,102
AudioMixer4              mixerRight;         //xy=332,209
AudioOutputI2S           i2s1;           //xy=555,162
AudioConnection          patchCord1(playSdWav2, 0, mixerLeft, 1);
AudioConnection          patchCord2(playSdWav2, 1, mixerRight, 1);
AudioConnection          patchCord3(playSdWav1, 0, mixerLeft, 0);
AudioConnection          patchCord4(playSdWav1, 1, mixerRight, 0);
AudioConnection          patchCord5(mixerLeft, 0, i2s1, 0);
AudioConnection          patchCord6(mixerRight, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=90,46
// GUItool: end automatically generated code

///////////////////////////////////

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

Bounce heartButton(8,20);
Bounce ringButton(9,20);
Bounce poisonButton(10,20);
Bounce swordButton(11,20); // will have to replace?

void setup(){

  Serial.begin(9600); // starts serial communication
  AudioMemory(16);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.75); // volume output 0~1 set default volume  
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

}

void loop(){
  heartButton.update();
  ringButton.update();
  poisonButton.update();
  swordButton.update();

  if (heartButton.fallingEdge()){
    playSdWav1.stop();
    if (playSdWav1.isPlaying()==false){
      Serial.println("Play 1");
      playSdWav1.play("scene1.wav");
      delay(200);
    }
  }
  if (ringButton.fallingEdge()){
    playSdWav1.stop();
    if (playSdWav1.isPlaying()==false){
      Serial.println("Play 2");
      playSdWav1.play("scene2.wav");
      delay(200);
    }
  }
  if (poisonButton.fallingEdge()){
    playSdWav1.stop();
    if (playSdWav1.isPlaying()==false){
      Serial.println("Play 3");
      playSdWav1.play("scene3.wav");
      delay(200);
    }
  }
  if (swordButton.fallingEdge()){
    playSdWav1.stop();
    if (playSdWav1.isPlaying()==false){
      Serial.println("Play 4");
      playSdWav1.play("scene3.wav");
      delay(200);
    }
  } 
}

