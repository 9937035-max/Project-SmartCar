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


    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, LOW);
    
    delay(1000);

    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, HIGH);
    
    delay(1000);

    
}
