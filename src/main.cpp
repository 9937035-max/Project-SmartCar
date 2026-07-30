#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>

vehicle myCar;
Servo myServo;

#define leftLED 2
#define rightLED 12
#define antiClockwise Contrarotate
#define buzzer 33
#define servopin 25

void forward()
{
  myCar.Move(Forward, 255);
  delay(1000);
}

void backward()
{
  myCar.Move(Backward, 255);
  delay(1000);
}

void rotateLeft()
{
  myCar.Move(antiClockwise, 255);
    digitalWrite(leftLED, HIGH);
  delay(500);
  digitalWrite(leftLED, LOW);
}

void rotateRight()
{
  myCar.Move(Clockwise, 255);
  digitalWrite(rightLED, HIGH);
  delay(500);
    digitalWrite(rightLED, LOW);
}


void setup()
{
 Serial.begin(115200);
pinMode(leftLED, OUTPUT);
pinMode(rightLED, OUTPUT);
pinMode(buzzer, OUTPUT);
myCar.Init();
myServo.attach(servopin);
myServo.write(0);


}

void loop()
{

forward();

backward();

rotateLeft();

rotateRight();
    
}
