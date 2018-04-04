#include "IRremote.h" // special librrary.
#include <Servo.h>
//link -->> https://github.com/shirriff/Arduino-IRremote

const int IR_PIN = A0; // pin to connect
Servo servo;
Servo servo_2;
Servo servo_3;
IRrecv irrecv(IR_PIN); // an object for IRrecv

void setup() {
  Serial.begin(9600);
  servo.attach(12);
  servo_2.attach(10);
  servo_3.attach(8);
  Serial.println("ready");
  irrecv.enableIRIn(); // start.
}

void loop() {
  decode_results results; // decode_results -->> struct for decoded commands.
  
  if (irrecv.decode(&results)) { // like cin.good();
    Serial.print("0x");
    Serial.println(results.value, HEX);
    if (results.value == 0xFF6897) {
      Serial.println("ochko =)");
      servo.write(90);
    } else if (results.value == 0xFF9867) {
      servo.write(0);
    } else if (results.value == 0xFF30CF) {
      servo_2.write(90);
    } else if (results.value == 0xFF18E7) {
      servo_2.write(0);
    } else if (results.value == 0xFF10EF) {
      servo_3.write(90);
    } else if (results.value == 0xFF38C7) {
      servo_3.write(0);
    }
    else if (results.value == 0xFFFFFFFF) {
//        servo.write(60);
//        delay(1000);
//        servo.write(0); 
//        delay(1000);
    }
    
    irrecv.resume(); // called to resume decoding
  }
}
