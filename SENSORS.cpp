#include <Arduino.h>
#include "SENSORS.h"
#include <HCSR04.h>

bool waterDetected = false;
bool vehicleDetected = false;

int waterPin = A1;

int TRIGGER_PIN = 12;
int ECHO_PIN = 13;
int BUZZER_PIN = 7;

#define MAX_SENSOR_DISTANCE 400 // Maximum distance the sensor can measure

#define DESIRED_SENSOR_DISTANCE 30 // 300 // Adjust this value based on the desired distance we want the sensor to detect
// u = d/t

// u = vehicle speed (km/hr -> m/s) // Typically 30km/h to 50km/hr
// d = The distance which the ultra-sonic sensor detects the vehicle // Less than 300cm (3m) d <= 3m
// t = The time available for the cyclist to react before collision

float distance_cm;
unsigned long time;


UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN);

void sensor_detection_init(int TRIGGER_PIN, int ECHO_PIN, int BUZZER_PIN){
  // UltraSonicDistanceSensor sensor(triggerPin, echoPin, maxDistanceCm, absoluteTimeout); // Can also define the max distance and max time of measurement in (us)

  // If the distance is larger than 400cm (4m) the sensor would return a negative value
  // We can adjust the distance and the measurement time
  
  pinMode(BUZZER_PIN, OUTPUT); // Assume we are using a passive buzzer. We can adjust the frequency of the noise

}

float sensor_measure_distance(){

  distance_cm = distanceSensor.measureDistanceCm();
  //float distance_m = (distance_cm / 100.0); // Could convert the distance to metres if required

  if(distance_cm > MAX_SENSOR_DISTANCE){ // distance_cm > 400cm
    //Serial.print("The distance is negative");
    Serial.println("No vehicle incoming");
  }

  if (distance_cm > 0 && distance_cm <= DESIRED_SENSOR_DISTANCE){

    Serial.print("Vehicle incoming");

    digitalWrite(BUZZER_PIN, HIGH); 
    delay(1000); // Delay for 1s
    digitalWrite(BUZZER_PIN, HIGH); 
    delay(500); // Delay for 0.5s
    digitalWrite(BUZZER_PIN, LOW); 
    delay(20); // Delay for 20ms

    vehicleDetected = true;
    // Need logic for the motor drivers to transition to BREAK then the REVERSE state
  }

  else{
    vehicleDetected = false;
  }

  return distance_cm;
}

void sensor_print_distance(){
  Serial.print(distance_cm);
  Serial.println(" cm");
}

bool waterSensor(int waterPin){

    int sensorValue = analogRead(waterPin);

    /*
    0-300: Dry / small moisture
    300-600: Damp
    600-1023: Wet
    */

    Serial.println(sensorValue);

    if(sensorValue < 250){

      Serial.print("Water Detected");

      digitalWrite(BUZZER_PIN, HIGH); 
      delay(100); 
      digitalWrite(BUZZER_PIN, LOW); 
      delay(20); 
      digitalWrite(BUZZER_PIN, HIGH); 
      delay(100); 
      digitalWrite(BUZZER_PIN, LOW); 
      delay(20); 


      waterDetected = true;
    }
    else{
        waterDetected = false;
    }

    return waterDetected;
}
