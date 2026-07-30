#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>

vehicle myCar;
Servo myServo;
ultrasonic myUltrasonic;
int UT_distance=0;

#define leftLED 2
#define rightLED 12
#define antiClockwise Contrarotate
#define buzzer 33
#define servopin 25
#define sonarmoter 25


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
  delay(1000);
  digitalWrite(leftLED, LOW);
}

void rotateRight()
{
  myCar.Move(Clockwise, 255);
  digitalWrite(rightLED, HIGH);
  delay(1000);
    digitalWrite(rightLED, LOW);
}

void strafeLeft()
{
  myCar.Move(Move_Left, 255);
  delay(1000);
}

void strafeRight()
{
  myCar.Move(Move_Right, 255);
  delay(1000);
}

void setup()
{
 Serial.begin(115200);
pinMode(leftLED, OUTPUT);
pinMode(rightLED, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(sonarmoter, OUTPUT);
myUltrasonic.Init(13, 14);
myCar.Init();
myServo.attach(servopin);
myServo.write(0);


}

void loop()
{

  UT_distance=myUltrasonic.Ranging();
  if(UT_distance<50)
  {
    rotateLeft();
  }
  else
  {
    forward();
  }
  delay(1000);


    
}
