#include <Arduino.h>

#ifndef VOLTAGE_INDICATOR
#define VOLTAGE_INDICATOR

extern float V_REF_MIN;
extern float V_REF_MAX;

extern float V_REF_MEAS_BOOST;
extern float V_REF_MEAS_BUCK;

// Boost Converter
extern float V_REF_TARGET_MIN_BOOST; // 11V
extern float V_REF_TARGET_MAX_BOOST; // 12V

// Buck Converter
extern float V_REF_TARGET_MIN_BUCK; 
extern float V_REF_TARGET_MAX_BUCK; 

extern int adcInputPin_boost;
extern int adcInputPin_buck;

void READ_AND_CONVERT_VOLTAGES();

#endif
