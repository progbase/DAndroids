#include "IRremote.h" // special librrary.
#include <Servo.h>

const int IR_PIN = 12; // pin to connect
Servo servo;
Servo servo_2;
Servo servo_3;
IRrecv irrecv(IR_PIN); // an object for IRrecv

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  servo_2.attach(8);
  servo_3.attach(6);
  Serial.println("ready");
  irrecv.enableIRIn(); // start.
}

void loop() {
  decode_results results; // decode_results -->> struct for decoded commands.
  if (irrecv.decode(&results)) { // like cin.good();
    Serial.print("0x");
    Serial.println(results.value, HEX);
    if (results.value == 0xFF6897) {
      servo.write(100);
      servo_2.write(20);
      servo_3.write(85);
    } else if (results.value == 0xFF9867) {
      servo.write(125);
      servo_2.write(45);
      servo_3.write(105);
    } else if (results.value == 0xFF30CF) {
      servo.write(150);
      servo_2.write(65);
    } else if (results.value == 0xFF18E7) {
      servo.write(80);
      servo_2.write(10);
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
