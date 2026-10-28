#include <Arduino.h>
#include "VOLTAGE_INDICATOR.h"

#define ADC_RESOLUTION 1023.0

float V_REF_MIN = 0.0;
float V_REF_MAX = 5.0;

// BOOST CONVERTER - ADJUST based on DIVIDER NETWORK (R1 & R2)
float V_REF_TARGET_MIN_BOOST = 1.0;// V_Ref_max = 55V -> 1.0; // 1.0 -> 11V
float V_REF_TARGET_MAX_BOOST =  (12.0)/(11.0); // V_Ref_max = 55V -> (12.0)/(11.0); // 1.09 -> 12V

// BUCK CONVERTER
float V_REF_TARGET_MIN_BUCK = 4.5;
float V_REF_TARGET_MAX_BUCK =  5.0;


int adcInputPin_boost = A0;
int adcInputPin_buck = A2;

float V_REF_MEAS_BOOST = 0.0;
float V_REF_MEAS_BUCK  = 0.0;

void READ_AND_CONVERT_VOLTAGES(){

  // Dummy read after each mux switch lets the ADC sample-and-hold settle
  analogRead(adcInputPin_boost);
  int adc_boost = analogRead(adcInputPin_boost);

  analogRead(adcInputPin_buck);
  int adc_buck = analogRead(adcInputPin_buck);

  V_REF_MEAS_BOOST = (adc_boost * V_REF_MAX) / ADC_RESOLUTION;
  V_REF_MEAS_BUCK  = (adc_buck  * V_REF_MAX) / ADC_RESOLUTION;
}