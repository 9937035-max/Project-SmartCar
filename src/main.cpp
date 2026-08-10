#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>

vehicle myCar;
Servo myServo;
ultrasonic myUltrasonic;
int UT_distance=0;
int middleDistance=90;
Servo myServo;

int myservo_Pin=25;
int leftDistance=0;
int middleDistance=0;
int rightDistance1=0;

#define leftLED 2
#define rightLED 12
#define antiClockwise Contrarotate
#define buzzer 33
#define servopin 25
#define sonarmoter 25

void buzzersound()
{
  digitalWrite(buzzer, 255);
  delay(1000);
  digitalWrite(buzzer, 000);
  delay(1000);
  
}

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
  middleDistance=myUltrasonic.Ranging();
  myServo.write(90);
  if(middleDistance<25){
    myCar.Move(Stop, 0);
    myServo.write(0);
    for(int angle=90; angle>=0; angle--){
      myServo.write(angle);
      delay(10);
    }
   delay(500);
   rightDistance1=myUltrasonic.Ranging();
   for(int angle=0; angle<=180; angle++){
      myServo.write(angle);
      delay(10);
    }
    delay(500);
    leftDistance=myUltrasonic.Ranging();
 if(rightDistance1<20&&leftDistance<20){
  myCar.Move(Backward, 255);
  delay(500);
  myCar.Move(Move_Left, 255);
  delay(1000);
 }
  else if(rightDistance1>leftDistance){
    myCar.Move(Clockwise, 255);
    delay(1000);
  }
  else if(leftDistance>rightDistance1){
    myCar.Move(antiClockwise, 255);
    delay(1000);
  }
  else{
    myCar.Move(Backward, 255);
    delay(500);
    myCar.Move(Move_Left, 255);
    delay(1000);
  }
  }
  else{
    forward();
  }


    
}
