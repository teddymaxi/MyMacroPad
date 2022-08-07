#include <Arduino.h>
#include "HID-Project.h"

const int NUM_SLIDERS = 7;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A8, A9, A10};
int analogSliderValues[NUM_SLIDERS];
const int NUM_BUTTONS = 6;
const int buttonPins[NUM_BUTTONS] = {2,3,4,5,6,7};

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  Consumer.begin();
  BootKeyboard.begin();
  Serial.begin(9600);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

void buttonPress(){
  for(int i = 0; i < NUM_BUTTONS; i++){
    if(digitalRead(buttonPins[i])==HIGH){
      switch (i){
        case 0:
          Consumer.write(MEDIA_PLAY_PAUSE);
          // Simple debounce
          delay(300);
          break;
        case 1:
          BootKeyboard.write(KEY_F13);
          // Simple debounce
          delay(300);
          break;
        case 2:
          BootKeyboard.write(KEY_F14);
          // Simple debounce
          delay(300);
          break;
        case 3:
          BootKeyboard.write(KEY_F15);
          // Simple debounce
          delay(300);
          break;
        case 4:
          BootKeyboard.write(KEY_F16);
          // Simple debounce
          delay(300);
          break;
        case 5:
          BootKeyboard.write(KEY_F17);
          // Simple debounce
          delay(300);
          break;
      }
    }
  }
}



void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  buttonPress(); //scan for button presses
  delay(10);
}



