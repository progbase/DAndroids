#include "IRremote.h" // special librrary.
#include <Servo.h>
//link -->> https://github.com/shirriff/Arduino-IRremote

const int IR_PIN = A0; // pin to connect
Servo left_servo;
Servo central_servo;
Servo right_servo;
IRrecv irrecv(IR_PIN); // an object for IRrecv

const int CENTRAL_SERVO_ZERO_VALUE = 105; //105
int LEFT_SERVO_ZERO_VALUE = 70; //105
int RIGHT_SERVO_ZERO_VALUE = 75; //50

const int AMLITUDE_LEFT_AND_RIGHT = 30;
const int AMLITUDE_CENTRAL = 20;

long phase;
long stepPeriod;
long lastMillis;
float angleLeftServo;
float angleRightServo;
float angleCentralServo;
boolean stopped;
boolean isattached;

void ServoAttach(){
  if (!isattached){
    left_servo.attach(11);
    central_servo.attach(10);
    right_servo.attach(9);
    isattached = true;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("ready");
  irrecv.enableIRIn(); // start.
  
  ServoAttach();  
  stopped = true;
  angleLeftServo = 0;
  angleRightServo = 0;
  angleCentralServo = 0;  
  stepPeriod = 1500;
  
  lastMillis = millis();
}

int findAngle(int amplitude, float angleservo, float phaseMillis) {
  float beta =  2 * PI * phaseMillis / stepPeriod + angleservo;
  float angle = amplitude * sin(beta);
  return (int)angle;
}

void loop() {  
  long millisNow = millis();
  long millisPassed = millisNow - lastMillis;
  if (stopped) {
    if (millisPassed >= 1000){
      left_servo.detach();
      central_servo.detach();
      right_servo.detach();
      isattached = false;
    }
    phase = 0;
  } else {
    lastMillis = millisNow;    
    phase += millisPassed;
    phase = phase % stepPeriod;
  }

  decode_results results; // decode_results -->> struct for decoded commands.
  if (irrecv.decode(&results)) { // like cin.good();
    Serial.print("0x");
    Serial.println(results.value, HEX);
    ServoAttach();
    if (results.value == 0xFF6897 || results.value == 0xFF629D) { 
      // нажаття "1"/"стрілка вгору" рух вперед  
      angleLeftServo = 0;
      angleRightServo = 0;
      angleCentralServo = PI/2;

      LEFT_SERVO_ZERO_VALUE = 70;
      RIGHT_SERVO_ZERO_VALUE = 75;
      stepPeriod = 1500; 
      
      stopped = false;
    } else if (results.value == 0xFF22DD) {
      if (!stopped) {
        angleLeftServo = 2;
        angleRightServo = 1;
      }
    } else if (results.value == 0xFFC23D) {
      if (!stopped) {
        angleLeftServo = 1;
        angleRightServo = 2;
      }
    } else if (results.value == 0xFF9867 || results.value == 0xFFA857) {  
      // нажаття "2"/"стрілка вниз" рух назад
      angleLeftServo = 0;
      angleRightServo = 0;
      angleCentralServo = -PI/2;
       
      LEFT_SERVO_ZERO_VALUE = 90;
      RIGHT_SERVO_ZERO_VALUE = 60;
      

      central_servo.write(CENTRAL_SERVO_ZERO_VALUE);
      left_servo.write(LEFT_SERVO_ZERO_VALUE);
      right_servo.write(RIGHT_SERVO_ZERO_VALUE);

      stepPeriod = 3000;
      LEFT_SERVO_ZERO_VALUE = 110;
      RIGHT_SERVO_ZERO_VALUE = 45;
      
      stopped = false;
    } else if (results.value == 0xFF02FD) {
      // нажаття "ОК" зупинка
      angleLeftServo = 0;
      angleRightServo = 0;
      angleCentralServo = 0;

      LEFT_SERVO_ZERO_VALUE = 70;
      RIGHT_SERVO_ZERO_VALUE = 75;

      stopped = true;
    } else if (results.value == 0xFF4AB5) {
      // нажаття "0" позиція для руху назад
      angleLeftServo = 0;
      angleRightServo = 0;
      angleCentralServo = 0;

      LEFT_SERVO_ZERO_VALUE = 100;
      RIGHT_SERVO_ZERO_VALUE = 70;

      stopped = true;
    }
    
    irrecv.resume(); // called to resume decoding
  }
  central_servo.write(CENTRAL_SERVO_ZERO_VALUE + 
      findAngle(AMLITUDE_LEFT_AND_RIGHT, angleCentralServo, phase));
  left_servo.write(LEFT_SERVO_ZERO_VALUE + 
      findAngle(AMLITUDE_LEFT_AND_RIGHT, angleLeftServo, phase));
  right_servo.write(RIGHT_SERVO_ZERO_VALUE + 
      findAngle(AMLITUDE_LEFT_AND_RIGHT, angleRightServo, phase));
}
