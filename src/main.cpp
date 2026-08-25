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
int Speed=155
#define IRpin 4
#define leftLED 2
#define rightLED 12
#define antiClockwise Contrarotate
#define servopin 25
#define sonarmoter 25


;IRrecv myIRrev(IRpin);
unsigned long lastCommandTime; // Record the time of the last received command
const unsigned long commandTimeout = 100; // Set the timeout period (milliseconds)
uint32_t last_decode = 0; // Variable to store the previously decoded raw data
uint32_t current_decode = 0;// Variable to store the currently decoded raw data

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

void topSpeed()
{
Speed=255
}

void roamingMode()
{
  if (myUltrasonic.Ranging() < 100)
  {
  rotateRight();
  }
  else
  {
   forward();
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
myIRrev.enableIRIn();
}



void loop()
{
 myServo.write(45);
  //if (myUltrasonic.Ranging() < 100)
 // {
 //  rotateRight();
 // }
 // else
//  {
   // forward();
 // }
  delay(100);
  
 if (myIRrev.decode()) { 
lastCommandTime = millis(); 
current_decode = myIRrev.decodedIRData.decodedRawData;
if (myIRrev.decodedIRData.flags) { 
current_decode = last_decode;
}
 }
}
Serial.print(current_decode, HEX);
Serial.println("");
switch (current_decode) {
case 0xB946FF00: myCar.Move(Forward, Speed); break;
// Press "up" button to move forward
case 0xEA15FF00: myCar.Move(Backward, Speed); break;
// Press "down" button to move backward
case 0xBB44FF00: myCar.Move(Contrarotate, Speed); break;
// Press "left" button to turn left
case 0xBC43FF00: myCar.Move(Clockwise, Speed); break;
// Press "right" button to turn right
case 0xE916FF00: myCar.Move(Move_Left, Speed); break;
// Press button "1" to move left
case 0xF20DFF00: myCar.Move(Move_Right, Speed); break;
// Press button "3" to move right
case 0xBF40FF00: myCar.Move(Stop, 0); break;
// Press button "OK" to stop
case 0xB54AFF00: roamingMode(); 
// Press button "#" starts roming mode
case 0xAD52FF00: topSpeed(); break;
// Press button "0" make the smart car quicker (isnt undo able)
}
myIRrev.resume(); // Wait for the next IR signal
 }
 if (millis() - lastCommandTime > commandTimeout) {
myCar.Move(Stop, 0);
// If no new IR signal within 100 milliseconds, stop the smart car
}
}
