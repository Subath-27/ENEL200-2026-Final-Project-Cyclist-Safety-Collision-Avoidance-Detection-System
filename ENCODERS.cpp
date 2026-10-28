#include "encoders.h"
#include "SENSORS.h"
#include <Arduino.h>

volatile unsigned long pulsesA;

volatile unsigned long TIME = 0;

unsigned long TIME_PREV_A = 0;
unsigned long lastPulseTimeA = 0;

int E_PA = 3;

float RPMA;

unsigned int pulses_per_turn = 20;

float speed_km_hr;


#define CONVERSION_FACTOR 3600 // Converts from seconds -> minutes for the RPM Calculation

#define WHEEL_RADIUS 0.35 //0.00175 // 0.35 // Metres
// Typical ~ 660 - 740 mm -> Cycle wheel

void encoders_init(){

  // Reset all to 0
  RPMA = 0;

  pulsesA = 0;

  TIME = millis();
  TIME_PREV_A = millis();

  pinMode(E_PA, INPUT_PULLUP);

  // Connect the encoder's signals to external interrupts to count pulses on changes.
  attachInterrupt(digitalPinToInterrupt(E_PA), countPulsesA, RISING); 

  Serial.print("Encoder interrupt number = ");
  Serial.println(digitalPinToInterrupt(E_PA));

}

void countPulsesA(){
  unsigned long now = micros();
  if (now - lastPulseTimeA > 2000) {
    pulsesA++;
    lastPulseTimeA = now;
  }
}


float RPM_CalculationA(){

  unsigned long timeCurrent = millis();
  unsigned long DELTA_TIME = timeCurrent - TIME_PREV_A;

  if(DELTA_TIME > 100){

    noInterrupts();
    unsigned long pulseA = pulsesA;
    pulsesA = 0;
    interrupts();

    if(pulseA <= 1) {
      RPMA = 0.0;
    }

    else {
      RPMA = (pulseA * (float)CONVERSION_FACTOR) / ((float)pulses_per_turn * DELTA_TIME);
    }
    
    TIME_PREV_A = timeCurrent;

  }

  return RPMA;
}

float speed_conversion(float RPMA){

  static float angular_velocity;
  static float linear_velocity;
  static float speed_km_hr_float;

  angular_velocity = (((2.0*PI)/60.0) * RPMA); // N_rpm -> w
  linear_velocity = WHEEL_RADIUS * angular_velocity; // r * w = v

  speed_km_hr_float = linear_velocity * 3.6; // m/s to km/hr
  speed_km_hr = (float)(speed_km_hr_float);

  return speed_km_hr;

}

void print_RPMA() {

  static unsigned long TIME_PRINT_PREV = 0;
  
  if(millis() - TIME_PRINT_PREV >= 1000){

    Serial.print("Wheel speed RPM: ");
    Serial.println(RPMA);

    Serial.print("Wheel speed km/hr: ");
    Serial.println(speed_km_hr);

    Serial.print("Pulses A = ");
    Serial.println(pulsesA);

    TIME_PRINT_PREV = millis();

  }

}


