
#include <IRremote.h>
#include <stdlib.h>

// Arduino Pins
const int ENGINE_FORWARD_PIN = 0; // OC0A
const int ENGINE_BACKWARD_PIN = 1; // OC0B
const int RECV_PIN = 2;
const int LIGHT_PIN = 3; // OC1B
const int ENGINE_SPEED_PIN = 4;

// Remote Key Values
const unsigned long KEY_PLAY_PAUSE = 0x77E12084;
const unsigned long KEY_FORWARD = 0x77E1E084;
const unsigned long KEY_BACKWARD = 0x77E11084;
const unsigned long KEY_UP = 0x77E1D084;
const unsigned long KEY_DOWN = 0x77E1B084;
const unsigned long KEY_MENU = 0x77E14084;
const unsigned long FOLLOWUP_KEYPRESS = 0xFFFFFFFF;

const int MAX_VELOCITY = 7;
const int MAX_OUTPUT_LEVEL = 255;

// variables
IRrecv irrecv(RECV_PIN);
decode_results results;

unsigned long key;
unsigned long lastKey = 0;

bool light = false;

int enginePace = 0; // -MAX_VELOCITY .. 0 .. MAX_VELOCITY
int engineVelocity = 0; // abs(speed) -> 0 .. MAX_VELOCITY
int engineOutputPinLevel = 0;
int engineRoute = 0; // -1, 1

void setup() {
  irrecv.enableIRIn(); // Start the receiver

  pinMode(ENGINE_FORWARD_PIN, OUTPUT);
  pinMode(ENGINE_BACKWARD_PIN, OUTPUT);
  pinMode(ENGINE_SPEED_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(RECV_PIN, INPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    // Serial.println(results.value, HEX);
    key = results.value;

    if (key == FOLLOWUP_KEYPRESS) {
      key = lastKey;
    }

    switch(key) {
    case KEY_PLAY_PAUSE:
      //      Serial.println("KEY_PLAY_PAUSE");
      enginePace = 0;
      break;
    case KEY_FORWARD:
      //      Serial.println("KEY_FORWARD");
      enginePace < MAX_VELOCITY ? enginePace++ : enginePace;
      break;
    case KEY_BACKWARD:
      //      Serial.println("KEY_BACKWARD");
      enginePace > -MAX_VELOCITY ? enginePace-- : enginePace;
      break;
    case KEY_MENU:
      //      Serial.println("KEY_MENU");
      light = !light;
      break;
    }

    engineVelocity = abs(enginePace);
    engineRoute = enginePace >> 7;
    engineOutputPinLevel = (MAX_OUTPUT_LEVEL * engineVelocity ) / MAX_VELOCITY;

    analogWrite(ENGINE_SPEED_PIN, engineOutputPinLevel);
    if (enginePace >= 0) {
      digitalWrite(ENGINE_FORWARD_PIN, HIGH);
      digitalWrite(ENGINE_BACKWARD_PIN, LOW);
    }
    else {
      digitalWrite(ENGINE_FORWARD_PIN, LOW);
      digitalWrite(ENGINE_BACKWARD_PIN, HIGH);
    }

    digitalWrite(LIGHT_PIN, light);

    lastKey = key;
    irrecv.resume(); // Receive the next value
  }

}















