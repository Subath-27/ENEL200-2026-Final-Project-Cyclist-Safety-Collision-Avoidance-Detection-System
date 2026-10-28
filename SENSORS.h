#ifndef SENSORS_H
#define SENSORS_H

#include <HCSR04.h>

// Sensor pins
extern int waterPin;

extern int TRIGGER_PIN;
extern int ECHO_PIN;
extern int BUZZER_PIN;

// Sensor Flags
extern bool waterDetected;
extern bool vehicleDetected;

extern float distance_cm;

bool waterSensor(int);

void sensor_detection_init(int, int, int);
float sensor_measure_distance();
void sensor_print_distance(); // Prints the distance on the serial monitor for debugging purposeses

#endif