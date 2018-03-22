#include "IRremote.h" // special librrary.
//link -->> https://github.com/shirriff/Arduino-IRremote

const int IR_PIN = A0; // pin to connect

IRrecv irrecv(IR_PIN); // an object for IRrecv

void setup() {
  Serial.begin(9600);
  Serial.println("ready");
  irrecv.enableIRIn(); // start.
}

void loop() {
  decode_results results; // decode_results -->> struct for decoded commands.
  
  if (irrecv.decode(&results)) { // like cin.good();
    Serial.println(results.value);
    
    irrecv.resume(); // called to resume decoding
  }
}
