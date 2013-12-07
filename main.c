
#include <Arduino.h>
#include <IRremote-min.h>

// Arduino Pins
const int RECV_PIN = 11;
const int ENGINE_FORWARD_PIN = 6;
const int LIGHT_PIN = 3;
const int ENGINE_BACKWARD_PIN = 5;

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

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
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
      Serial.println("KEY_PLAY_PAUSE");
      enginePace = 0;
      break;
    case KEY_FORWARD:
      Serial.println("KEY_FORWARD");
      enginePace < MAX_VELOCITY ? enginePace++ : enginePace;
      break;
    case KEY_BACKWARD:
      Serial.println("KEY_BACKWARD");
      enginePace > -MAX_VELOCITY ? enginePace-- : enginePace;
      break;
    case KEY_MENU:
      Serial.println("KEY_MENU");
      light = !light;
      break;
    }

    engineVelocity = abs(enginePace);
    engineRoute = enginePace >> 7;
    engineOutputPinLevel = (MAX_OUTPUT_LEVEL * engineVelocity ) / MAX_VELOCITY;

    int  forwardLevel = (1+engineRoute) * engineOutputPinLevel;
    int backwardLevel = -1 * engineRoute * engineOutputPinLevel;   
    analogWrite(ENGINE_FORWARD_PIN, forwardLevel ); 
    analogWrite(ENGINE_BACKWARD_PIN, backwardLevel); 

//    Serial.print("enginePace: "); 
//    Serial.println(enginePace);
//    Serial.print("engineVelocity: "); 
//    Serial.println(engineVelocity);
//    Serial.print("engineRoute: "); 
//    Serial.println(engineRoute);    
//    Serial.print("forwardLevel: "); 
//    Serial.println(forwardLevel);
//    Serial.print("backwardLevel: "); 
//    Serial.println(backwardLevel);
//    Serial.println("\n");

    analogWrite(LIGHT_PIN, 255 * light);

    lastKey = key;
    irrecv.resume(); // Receive the next value
  }
	
}
	
	int main(void)
{
    init();
    setup();
    while(true) { loop(); }
    return 0;
}







