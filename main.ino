
#include "BC_PWM_CODE.h"
#include <ServoTimer2Plus.h>
#include <Arduino.h>
#include "servo.h"
#include "VOLTAGE_INDICATOR.h"
#include "LCD_INTERFACE.h"
#include "ENCODERS.h"
#include "SENSORS.h"


void setup() {

  Serial.begin(9600);

  servo_init(servoPin);
  
  BC_PWM_INIT();
  encoders_init();
  LCD_init();
  sensor_detection_init(TRIGGER_PIN, ECHO_PIN, BUZZER_PIN);
 
}

void loop() {

  // put your main code here, to run repeatedly:

  // Encoders

  RPMA = RPM_CalculationA();

  speed_km_hr = speed_conversion(RPMA);
  print_RPMA();


  LCD_TRANSITION();
  LCD_DISPLAY(current_state, prev_state);

  READ_AND_CONVERT_VOLTAGES();

  //Serial.print("  ADC Value = ");
  //Serial.println(ADC_VALUE);

  ADJUST_DUTY_RATIO_BOOST();
  ADJUST_DUTY_RATIO_BUCK();

  //Serial.print("V_ADC = ");
  //Serial.print(V_REF_MEAS);

  //Serial.print("  OCR1B = ");
  //Serial.println(OCR1B);

  //Serial.print("  OCR1A = ");
  //Serial.println(OCR1A);

  waterSensor(waterPin);

  sensor_measure_distance();
  sensor_print_distance();

  servo_rotate();


}
