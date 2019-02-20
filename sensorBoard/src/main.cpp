#include <Arduino.h>
#include <LM35.h>

#define TEMP_PIN A1
#define TRIG_PIN 13
#define ECHO_PIN 12

LM35 tempSensor(TEMP_PIN);

int readDistance();
String encodeData(float tempreture, long distance);

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  double tempreture = tempSensor.cel();
  long distance = readDistance();

  String msg = encodeData(tempreture, distance);
  
  char* buffer = (char*) malloc(sizeof(char)*msg.length()+1);
  msg.toCharArray(buffer, msg.length()+1);
  
  Serial.write(buffer);
  delay(200);
}

int readDistance(){
  long duration, cm;
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose duration is the time (in microseconds) from the sending of the ping to the reception of its echo off of an object.
  duration = pulseIn(ECHO_PIN, HIGH);
 
  // The speed of sound is 340 m/s or 29 us per cm.The Ultrasonic burst travels out & back.So to find the distance of object we divide by 58 
  cm = ((duration/2) / 29) + 1;    
  return cm;
}

String encodeData(float tempreture, long distance){
  String tempStr = String(tempreture);
  String distStr = String(distance);
  
  String msg = tempStr + ":" + distStr + "#";

  return msg;
}