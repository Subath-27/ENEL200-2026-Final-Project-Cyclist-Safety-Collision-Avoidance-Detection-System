#include <Arduino.h>
#include "BC_PWM_CODE.h"
#include "VOLTAGE_INDICATOR.h"

#include <Arduino.h>

#include "BC_PWM_CODE.h"

int OCR_ARRAY[100] = {0};

#define OCR1N_MIN 0
#define OCR1N_MAX 159
#define OCR_STEP 1

void BC_PWM_INIT(){ // Uses Timer 1
  // A non-inverting PWM signal with an output frequency of ~= 100khz for pins 9 and 10
  DDRB |= (1 << 1); // Pin 9

  DDRB |= (1 << 2); // Pin 10
  // DDRB |= ((1 << 1) | (1 << 2));

  //Reset Counter and registers on initialization
  TCNT1 = 0;
  TCCR1A = 0;
  TCCR1B = 0;

  // Initilize the prescaler
  TCCR1B |= (1 << CS10); // N = 1
  TCCR1B &= ~((1 << CS11) | (1 << CS12));

  // Set the TOP Value
  ICR1 = 159; // Fixed

  // OCR1A & OCR1B
  // D = OCR1N / (ICR1 + 1)

  // Boost Converter Light Bulb
  OCR1A = 40; // [OCR1A = 40] 25% (New Battery -> 9V) - [OCR1A = 80] 50% (Old Battery -> 6V) 
  
  // Pin 10 ~ Buck Converter Servo
  OCR1B = 89; // [OCR1B = 89] 56% (New Battery -> 9V) - [OCR1B = 133] 83% (Old Battery -> 6V) 

  // Initialize the mode -> Fast PWM
  TCCR1A |= ((1 << WGM11)); // Waveform generation mode description Mode 14
  TCCR1B |=  (1<<WGM12) | (1<<WGM13); // Since the WGM bits are split between the two registers (TCCR1A and TCCR1B)

  // Clear OC1B on compare match, set OC1B (pin 10) at BOTTOM (non-inverting mode)
  TCCR1A |= (1 << COM1B1);
  TCCR1A &= ~(1 << COM1B0);

  // Clear OC1B on compare match, set OC1B (pin 9) at BOTTOM (non-inverting mode)
  TCCR1A |= (1 << COM1A1);
  TCCR1A &= ~(1 << COM1A0);

}

void ADJUST_DUTY_RATIO_BOOST()
{
    if (V_REF_MIN < V_REF_MEAS_BOOST && V_REF_MEAS_BOOST < V_REF_MAX)
    {

        // Output voltage too HIGH -> decrease duty
        if (V_REF_MEAS_BOOST > V_REF_TARGET_MAX_BOOST)
        {
            if (OCR1A >= OCR1N_MIN + OCR_STEP)
                OCR1A -= OCR_STEP;
            else
                OCR1A = OCR1N_MIN;

        } 

        // Output voltage too LOW -> increase duty
        else if (V_REF_MEAS_BOOST < V_REF_TARGET_MIN_BOOST)
        {
            if (OCR1A <= OCR1N_MAX - OCR_STEP)
                OCR1A += OCR_STEP;
            else
                OCR1A = OCR1N_MAX;

        }
    }
}

void ADJUST_DUTY_RATIO_BUCK(){

    if (V_REF_MIN < V_REF_MEAS_BUCK && V_REF_MEAS_BUCK < V_REF_MAX)
    {

        // Output voltage too HIGH -> decrease duty
        if (V_REF_MEAS_BUCK > V_REF_TARGET_MAX_BUCK)
        {
            if (OCR1B >= OCR1N_MIN + OCR_STEP)
                OCR1B -= OCR_STEP;
            else
                OCR1B = OCR1N_MIN;

        }

        // Output voltage too LOW -> increase duty
        else if (V_REF_MEAS_BUCK < V_REF_TARGET_MIN_BUCK)
        {
            if (OCR1B <= OCR1N_MAX - OCR_STEP)
                OCR1B += OCR_STEP;
            else
                OCR1B = OCR1N_MAX;
        }
    }
}




