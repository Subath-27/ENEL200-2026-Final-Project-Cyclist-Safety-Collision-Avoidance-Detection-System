/*EVERYTHING IS WORKING FINE
ONLY PROBLEM -> NEED TO PRESS THE BUTTONS FOR YES, NO, START, END, TWICE TO ANSWER THE QUESTION -> Slightly Resolve
PROBLEM -> Currently, you would need to hold the button for a 1ms for it to work -> Need to resolve

NEED TO FIND A WAY TO TURN THE BUTTONS ON INSTANTLY ONCE PRESSED
*/

#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "LCD_INTERFACE.h"

#include "servo.h"

#include "ENCODERS.h"
#include "SENSORS.h"

#include <ServoTimer2Plus.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); // 16 x 2 LCD screen

states current_state = SPEED_DISPLAY;
states prev_state = SPEED_DISPLAY;

unsigned long PREV_US_SENSOR_TIME = 0;
unsigned long PREV_WATER_SENSOR_TIME = 0;
unsigned long SENSOR_TIME = 0;


void LCD_init(){

  lcd.init();      // Initialize the LCD hardware
  lcd.display();

  lcd.backlight(); // Start with backlight ON
  delay(1000);

}

void LCD_TRANSITION(){

  if(vehicleDetected && waterDetected){
    current_state = WATER_US_DISPLAY;
  }

  else if(waterDetected){
    current_state = WATER_DISPLAY;
  }

  else if(vehicleDetected){
    current_state = US_SENSOR_DISPLAY;
  }

  else{
    current_state = SPEED_DISPLAY; 
  }

}

void LCD_DISPLAY(states &current_state, states &prev_state){

  bool stateChanged = (current_state != prev_state);

  if (stateChanged){
    lcd.clear();
  }

  switch(current_state){

    case SPEED_DISPLAY:

      char buf[16]; // generous headroom, avoids any dtostrf overflow
      dtostrf(constrain(speed_km_hr, -99.9, 999.9), 5, 1, buf); // clamp so it never exceeds field width
      buf[15] = '\0'; // belt-and-braces null terminator
      lcd.setCursor(0, 0);
      lcd.print(buf);
      lcd.print(" km/hr   "); // trailing spaces overwrite any leftover longer text
      break;

    case WATER_US_DISPLAY:
      lcd.setCursor(0, 0);
      if(millis() - SENSOR_TIME >= 1500){
        lcd.print("OBSTACLE AHEAD!!!");
        lcd.setCursor(0, 1);
        lcd.print("WATER DETECTED!!!");
      }
      else{
        lcd.clear();
      }
      break;

    case US_SENSOR_DISPLAY:
      lcd.setCursor(0, 0);
      if(millis() - PREV_US_SENSOR_TIME >= 1500){
        lcd.print("OBSTACLE AHEAD!!!");
        PREV_US_SENSOR_TIME = millis();
      }
      else{
        lcd.clear();
      }
      break;

    case WATER_DISPLAY:

      lcd.setCursor(0, 0);

      if(millis() - PREV_WATER_SENSOR_TIME >= 1500){
        lcd.print("WATER DETECTED!!!");
        lcd.setCursor(0, 1);
        lcd.print("SLOW DOWN!!!");
      }
      else{
        lcd.clear();
      }
      break;

  }

  prev_state = current_state;

}




