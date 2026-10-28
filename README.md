# ENEL200-2026-Final-Project-Cyclist-Safety-Collision-Avoidance-Detection-System
Full Arduino code and libraries for the Cyclist Safety Detection System (ENEL200, University of Canterbury). 

<img width="1536" height="2048" alt="acbb3419-27fd-44f9-87c1-2323544d7bf3" src="https://github.com/user-attachments/assets/a328dacd-02a0-42ea-8a57-14a902495493" />

## Overview
The aim of this project was to design and build a system to improve cyclist safety by mitigating the risk of collisions with environmental hazards. The system includes a light bulb to enhance visibility and an LCD to display the rider’s speed. It also uses an ultrasonic sensor and a water sensor to detect obstructions and water, triggering a buzzer and an LCD message to indicate the hazard. 

## Features
- Drives and turns in response to Logo commands sent over the serial interface
- Ultrasonic sensor detects obstructions greater than 0 cm and up to 30 cm away
- Active buzzer sounds whenever an obstruction is detected
- Custom PCB shield designed in KiCad to drive the two DC motors and connect the buzzer and ultrasonic sensor

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

## Results
- 

Grade: 3.6 / 6 (60%)

## How to build and upload
1. Open the `.ino` file in Arduino IDE.
2. Install any libraries listed above.
3. Select your board and port, then click Upload.

## Author
Subath Heenkenda Mudiyanselage | [LinkedIn](https://www.linkedin.com/in/subath-heenkenda27/) | subath.heenkenda@outlook.com

Team: Jed Skuse worked on the mechanical design and Kaitati Robertson assisted with soldering.
