#ifndef LCD_INTERFACE
#define LCD_INTERFACE

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

extern LiquidCrystal_I2C lcd;

enum states{
  SPEED_DISPLAY,
  WATER_DISPLAY,
  US_SENSOR_DISPLAY,
  WATER_US_DISPLAY,
};

extern states current_state;
extern states prev_state;

void LCD_init(); // Initialize the LCD  Display address -> 0x27
void LCD_TRANSITION();
void LCD_DISPLAY(states &current_state, states &prev_state);


#endif
