#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>
#include <IRremote.h>

vehicle myCar;
Servo myServo;
ultrasonic myUltrasonic;
int UT_distance = 0;
Servo myServou;

int myservo_Pin = 25;
int leftDistance = 0;
int middleDistance = 0;
int rightDistance = 0;
int lastCommand = 0;
#define IRpin 4
#define leftLED 2
#define rightLED 12
#define antiClockwise Contrarotate
#define servopin 25
#define sonarmoter 25
#define Speed 255

IRrecv myIRrev(IRpin);
unsigned long lastCommandTime;            // Record the time of the last received command
const unsigned long commandTimeout = 100; // Set the timeout period (milliseconds)
uint32_t last_decode = 0;                 // Variable to store the previously decoded raw data
uint32_t current_decode = 0;              // Variable to store the currently decoded raw data

void forward()
{
  myCar.Move(Forward, 255);
}

void backward()
{
  myCar.Move(Backward, 255);
}

void rotateLeft()
{
  myCar.Move(antiClockwise, 255);
  digitalWrite(leftLED, HIGH);
  digitalWrite(leftLED, LOW);
}

void rotateRight()
{
  myCar.Move(Clockwise, 255);
  digitalWrite(rightLED, HIGH);
  digitalWrite(rightLED, LOW);
}

void strafeLeft()
{
  myCar.Move(Move_Left, 255)
}

void strafeRight()
{
  myCar.Move(Move_Right, 255);
}

void roaming()
{
  myServo.write(60);
  if (myUltrasonic.Ranging() < 100)
  {
    rotateRight();
  }
  else
  {
    forward();
  }
  delay(100);
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
  if (myIRrecv.decode())
  {                             // Check if an IR signal is received
    lastCommandTime = millis(); // Update the last command time
    current_decode = myIRrecv.decodedIRData.decodedRawData;
    if (myIRrecv.decodedIRData.flags)
    { // Check if it's a repeated IR code
      current_decode = last_decode;
      // Set current decode as the previous one
    }
    Serial.print(current_decode, HEX);
    Serial.println("");
    switch (current_decode)
    {
    case 0xBD42FFOO:
      lastCommand = 1;
      // Press "*" button to move change to roming
    }
  }

  switch (lastCommand)
  {
  case 0:
    roaming();

  case 1:
    roaming();
  }
}
