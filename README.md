# ENEL200-2026-Final-Project-Cyclist-Safety-Collision-Avoidance-Detection-System
Full Arduino code and libraries for the Cyclist Safety Detection System (ENEL200, University of Canterbury). 

<img width="1536" height="2048" alt="acbb3419-27fd-44f9-87c1-2323544d7bf3" src="https://github.com/user-attachments/assets/a328dacd-02a0-42ea-8a57-14a902495493" />

## Overview
The aim of this project was to design and build a system to improve cyclist safety by mitigating the risk of collisions with environmental hazards. The system includes a light bulb to enhance visibility and an LCD to display the rider’s speed. It also uses an ultrasonic sensor and a water sensor to detect obstructions and water, triggering a buzzer and an LCD message to indicate the hazard. 

## Features 
- A boost converter boosts the battery pack's input voltage to 12V to power the G4 LED lamp.
- The boost converter includes a TVS diode at the output to suppress high-voltage transients.  
- A buck converter steps the battery's voltage to 5V to supply the SG90 servo motor.
- Both converters utilise a feedback system implemented through code to maintain a consistent output voltage.
- A rocker switch and a visible light sensor (photo-transistor) are inputted through a logic OR gate to toggle the G4 LED    lamp.
- A separate rocker switch is used to toggle the battery pack to turn the Arduino on/off.
- An HC-020K rotary encoder measures the rotational speed in RPM of the cycle's front wheel. The code then converts that speed from RPM to km/hr using the initialised radius of the cyclist's front wheel. The speed in km/hr is displayed on the LCD screen. 
- A water sensor detects moisture, and an ultrasonic sensor detects obstructions. Both sensors are configured in the  LCD_interface source file as a finite-state-machine (FSM) to transition and display the states on the LCD screen.
- The ultrasonic sensor is mounted on a servo motor, where the servo rotates continuously from 0 to 180 degrees to detect obstructions.

## Hardware
- Board: Arduino Uno
- 16 x 2 LCD Interface
- SG90 Servo Motor
- Sensors: ultrasonic sensor, HC-020K Rotary Encoder, Water Sensor, visible light sensor
- Buzzer: Active
- Power: 6 × AA alkaline batteries (9 V pack)
- Switches: 2 x Rocker Switches
- Custom PCB: designed in KiCad, see `docs/` for schematic and layout
- G4 LED Replacement Light, 120º, 12VAC/DC, Cool White

## Software
- Arduino C++, Arduino IDE 2.3.4
- Libraries: `HCSR04.h`, `Arduino.h`, 'ServoTimer2Plus.h', 'LiquidCrystal_I2C.h', 'Wire.h'

## How to build and upload
1. Open the `.ino` file in Arduino IDE.
2. Install any libraries listed above.
3. Select your board and port, then click Upload.

## Author
Subath Heenkenda Mudiyanselage | [LinkedIn](https://www.linkedin.com/in/subath-heenkenda27/) | subath.heenkenda@outlook.com

Team: Jed Skuse worked on the mechanical design and Kaitati Robertson assisted with soldering.
