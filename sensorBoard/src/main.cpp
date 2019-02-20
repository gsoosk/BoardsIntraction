#include <Arduino.h>
#include <LM35.h>

#define TEMP_PIN A1
#define TRIG_PIN 13
#define ECHO_PIN 12

double tempVal;
long duration, cm;

LM35 tempSensor(TEMP_PIN);

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  tempVal = tempSensor.cel();

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW);
  
  // // Read the signal from the sensor: a HIGH pulse whose
  // // duration is the time (in microseconds) from the sending
  // // of the ping to the reception of its echo off of an object.
  duration = pulseIn(ECHO_PIN, HIGH);
 
  // // Convert the time into a distance
  cm = duration/58; 
  // The speed of sound is 340 m/s or 29 us per cm.The Ultrasonic burst travels out & back.So to find the distance of object we divide by 58 
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  String tempStr = String(tempVal);
  String distStr = String(cm);
  String msg = tempStr + ":" + distStr + "#";
  char* buffer = (char*) malloc(sizeof(char)*msg.length()+1);
  msg.toCharArray(buffer, msg.length()+1);
  // Serial.write(buffer);
  Serial.println(buffer);

}