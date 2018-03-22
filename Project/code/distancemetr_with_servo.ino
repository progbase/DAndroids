#include <Servo.h> 

Servo myservo;
int trigPin = 11;
int echoPin = 12; 
long duration, cm;

void setup() 
{
  myservo.attach(10);
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;
  if (cm < 10)
  {
    myservo.write(90);
    delay(250);  
    myservo.write(0);
  }
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(250);
}
