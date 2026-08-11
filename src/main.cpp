#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>
#include <IRremote.h>


vehicle myCar;
Servo myServo;
ultrasonic myUltrasonic;
int UT_distance=0;
Servo myServou;


int myservo_Pin=25;
int leftDistance=0;
int middleDistance=0;
int rightDistance=0;
#define IRpin 4
#define leftLED 2
#define rightLED 12
#define antiClockwise Contrarotate
#define servopin 25
#define sonarmoter 25

IRrecv myIRrev(IRpin);

void forward()
{
  myCar.Move(Forward, 155);
}

void backward()
{
  myCar.Move(Backward, 155);
}

void rotateLeft()
{
  myCar.Move(antiClockwise, 155);
    digitalWrite(leftLED, HIGH);
  digitalWrite(leftLED, LOW);
}

void rotateRight()
{
  myCar.Move(Clockwise, 155);
  digitalWrite(rightLED, HIGH);
    digitalWrite(rightLED, LOW);
}

void strafeLeft()
{
  myCar.Move(Move_Left, 155);
}

void strafeRight()
{
  myCar.Move(Move_Right, 155);
}

void setup()
{
 Serial.begin(115000);
pinMode(leftLED, OUTPUT);
pinMode(rightLED, OUTPUT);
pinMode(sonarmoter, OUTPUT);
pinMode(IRpin, INPUT);
myUltrasonic.Init(13, 14);
myCar.Init();
myServo.attach(servopin);
myServo.write(0);
myIRrev.enableIRIn();
}
void loop()
{
  myServo.write(100);
  if (myUltrasonic.Ranging() < 100)
  {
   rotateRight();
  }
  else
  {
    forward();
  }
  delay(100);
  if (myIRrev.decode())
  {
    Serial.println(myIRrev.decodedIRData.decodedRawData, HEX);
    myIRrev.resume();
  }
}
