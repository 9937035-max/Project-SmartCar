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
int lastCommand = 2;
#define IRpin 4
#define leftLED 2
#define rightLED 12
#define antiClockwise Contrarotate
#define servopin 25
#define sonarmoter 25
#define Speed 255

IRrecv myIRrecv(IRpin);
unsigned long lastCommandTime;            // Record the time of the last received command
const unsigned long commandTimeout = 100; // Set the timeout period (milliseconds)
uint32_t last_decode = 0;                 // Variable to store the previously decoded raw data
uint32_t current_decode = 0;              // Variable to store the currently decoded raw data

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

void manualMovment()
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
    case 0xB946FF00:
      forward;
      break;
    // Press "up" button to move forward
    case 0xEA15FF00:
      backward;
      break;
    // Press "down" button to move backward
    case 0xBB44FF00:
      rotateLeft;
      break;
    // Press "left" button to turn left
    case 0xBC43FF00:
      rotateRight;
      break;
    // Press "right" button to turn right
    case 0xE916FF00:
      strafeLeft;
      break;
    // Press button "1" to move left
    case 0xF20DFF00:
      strafeRight;
      break;
      // Press button "3" to move right
    }
  }
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
  myIRrecv.enableIRIn();
}

void loop()
{
  switch (lastCommand)
  {
  case 2:
    manualMovment();

  case 1:
    roaming();
  }

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
    case 0xBD42FF00:
      lastCommand = 1;
      // Press "*" button to move change to roming

      case 0xB54AFF00:
      lastCommand = 2;
      // Press "*" button to move change to roming
    }
  }
}

