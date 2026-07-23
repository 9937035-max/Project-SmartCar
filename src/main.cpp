#include <Arduino.h>
#include <vehicle.h>
#include <ultrasonic.h>
#include <ESP32Servo.h>

vehicle myCar;

#define leftLED 2
#define rightLED 12
#define antiClockwise Contrarotate
#define buzzer 33

void setup()
{
 Serial.begin(115200);
pinMode(leftLED, OUTPUT);
pinMode(rightLED, OUTPUT);
pinMode(buzzer, OUTPUT);
myCar.Init();


}

void loop()
{


    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, LOW);
    tone(buzzer, 262);
    delay(1000);

    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, HIGH);
    noTone(buzzer);
    delay(1000);

    
}
