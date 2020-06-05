#include "CD74HC4067.h"
#define DEBUG
//#define DEBUG2
CD74HC4067 u1(3, 4, 5, 6);
const int u1pin = 2;
CD74HC4067 u2(9, 10, 11, 12);
const int u2pin = 8;
CD74HC4067 u3(17, 16, 15, 14);
const int u3pin = 18;
#define SWITCH_PIN1 A0
#define SWITCH_PIN2 A1
static const uint8_t analog_pins[] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14};
void setup() {
  Serial.begin(9600);
  pinMode(u1pin, INPUT_PULLUP);
  pinMode(u2pin, INPUT_PULLUP);
  pinMode(u3pin, INPUT_PULLUP);
  for (int i=22; i <= 34; i++){
    pinMode(i, OUTPUT);
  }
  for (int i=38; i <= 50; i++){
    pinMode(i, OUTPUT);
  }
  for (int i=A2; i <= A14; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(SWITCH_PIN1, INPUT_PULLUP);
  pinMode(SWITCH_PIN2, INPUT_PULLUP);
}
boolean switch1 = 0; //switch 1 on or off
boolean switch2 = 0; //switch 2 on or off
boolean arrHold1[39];
boolean arrHold2[39];
boolean arrTouch[39]; //touch track
boolean arrPlay[39]; //play track (logical or of hold and touch)
void loop() {
  // get pin data
  for (int i = 0; i < 13; i++) {
    u2.channel(i);
    arrTouch[i] = !digitalRead(u2pin);
  }
  for (int i = 0; i < 13; i++) {
    u1.channel(i);
    arrTouch[i + 13] = !digitalRead(u1pin);
  }
  for (int i = 0; i < 13; i++) {
    u3.channel(i);
    arrTouch[i + 26] = !digitalRead(u3pin);
  }
  // switch 1
  if (switch1 != digitalRead(SWITCH_PIN1)) { //if switch changed position
  switch1 = digitalRead(SWITCH_PIN1);
    if (switch1) { //switch went on, push to hold
      for (uint8_t i=0; i<39; i++) {
        arrHold1[i] = arrTouch[i];
      }
    } else { //switch went off, clear hold
      for (uint8_t i=0; i<39; i++) {
        arrHold1[i] = false;
      }
    }
  }
  // switch 2
  if (switch2 != digitalRead(SWITCH_PIN2)) { //if switch changed position
  switch2 = digitalRead(SWITCH_PIN2);
    if (switch2) { //switch went on, push to hold
      for (uint8_t i=0; i<39; i++) {
        arrHold2[i] = arrTouch[i];
      }
    } else { //switch went off, clear hold
      for (uint8_t i=0; i<39; i++) {
        arrHold2[i] = false;
      }
    }
  }
  //combine the two
  for (int i=0; i<39; i++) {
    arrPlay[i] = arrTouch[i] || arrHold1[i] || arrHold2[i];
  }
  Serial.print('a');
  for (int i=0; i<13; i++) {
    digitalWrite(22 + i, arrPlay[i]); //play octave 1
    #ifdef DEBUG
    Serial.print(digitalRead(22+i));
    #endif
  }
  for (int i=0; i<13; i++) {
    digitalWrite(38 + i, arrPlay[i + 13]); //play octave 1
    #ifdef DEBUG
    Serial.print(digitalRead(38+i));
    #endif
  }
  
  for (int i=0; i<13; i++) {
    digitalWrite(analog_pins[2 + i], arrPlay[i + 26]); //play octave 3
    #ifdef DEBUG
    Serial.print(digitalRead(analog_pins[2+i]));
    #endif
  }
  #ifdef DEBUG
  Serial.print('\n');
  Serial.print('b');
  for (int i = 0; i < 39; i++){
    Serial.print(arrTouch[i]);
  }
  Serial.print('\n');
  #endif
  #ifdef DEBUG2
  Serial.print(switch1);
  Serial.print(switch2);
  #endif
  delay(10);
  
}
