#include <ServoTimer2Plus.h>
#include <Arduino.h>

#include "BC_PWM_CODE.h"

ServoTimer2Plus myservo;

int servoPin = 2;

//int testPin = 8; // Apply a HIGH and LOW to simulate a switch press

/*void servoTest(int testPin){

  pinMode(testPin, OUTPUT);

  digitalWrite(testPin, HIGH); // Apply HIGH (5V) to the mosfet's gate
  delay(5000); // Apply HIGH 5V for a duration of 5s 
  digitalWrite(testPin, LOW); // Apply LOW (5V) to the mosfets gate
  
}
*/

void servo_init(int servoPin){

  if(myservo.attach(servoPin) != 0){
    Serial.println("Servo Successfully Attached");
  }

  else{
    Serial.println("Servo Not Attached!!!!");
  }

}

void servo_detach(){

  myservo.detach();
  Serial.println("Servo Successfully Detached");


}

int servo_angle = 0; // current commanded angle (declare extern in servo.h if you need it elsewhere)

void servo_rotate(){

  static const int angles[] = {0, 90, 180, 90, 0};   // 0 -> 90 -> 180 -> back through 90
  static uint8_t idx = 0;
  static unsigned long lastMove = 0;
  static bool started = false;

  const unsigned long DWELL_MS = 3000;  //500;              // tune: 400-600 ms

  if(!started || millis() - lastMove >= DWELL_MS){
    servo_angle = angles[idx];
    myservo.writeAngle(servo_angle);

    idx = (idx + 1) % 4;
    lastMove = millis();
    started = true;
  }

}

/*void servo_rotate(){

  myservo.writeAngle(0);
  delay(10000);
  myservo.writeAngle(90);
  delay(10000);
  myservo.writeAngle(180);
  delay(10000);

}
*/