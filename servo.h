#ifndef SERVO_H
#define SERVO_H

extern int servoPin;
extern int servo_angle;

//extern int testPin; // Apply a HIGH and LOW to simulate a switch press

//void servoTest(int testPin);

void servo_init(int);
void servo_detach();

void servo_rotate();
#endif