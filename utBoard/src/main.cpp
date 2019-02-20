#include <Arduino.h>
#include <Wire.h>

const int UT_SENSOR_ADDR = 110;
const int X_REG_0_ADDR = 0xa;
const int X_REG_1_ADDR = 0xb;
const int X_REG_2_ADDR = 0xc;
const int X_REG_3_ADDR = 0xd;
const int Y_REG_0_ADDR = 0x28;
const int Y_REG_1_ADDR = 0x29;
const int Y_REG_2_ADDR = 0x2a;
const int Y_REG_3_ADDR = 0x2b;
const int ON_OFF_REG_ADDR = 0x0;

void sendAddrToSensor(int address);
float getDataFromSensor(int regAddr0, int regAddr1, int regAddr2, int regAddr3);
byte getByte();
float convert4ByteToFloat(byte num[4]);
void turnOnSensor();

union {
  float fData;
  byte bData[4];
} uData;

void setup() {
  Wire.begin();        
  Serial.begin(9600); 
  turnOnSensor(); 
}

void loop() {
  float x = getDataFromSensor(X_REG_0_ADDR, X_REG_1_ADDR, X_REG_2_ADDR, X_REG_3_ADDR);
  float y = getDataFromSensor(Y_REG_0_ADDR, Y_REG_1_ADDR, Y_REG_2_ADDR, Y_REG_3_ADDR);

  float result = x*x + y*y;

  String dataToSend = String(result);
  Serial.print(result);
  delay(100);
}

void turnOnSensor(){
  Wire.beginTransmission(UT_SENSOR_ADDR); 
  Wire.write(ON_OFF_REG_ADDR); 
  Wire.write(1);
  Wire.endTransmission(); 
}

float getDataFromSensor(int regAddr0, int regAddr1, int regAddr2, int regAddr3){
  byte data[4];
  sendAddrToSensor(regAddr0);
  data[0] = getByte();
  sendAddrToSensor(regAddr1);
  data[1] = getByte();
  sendAddrToSensor(regAddr2);
  data[2] = getByte();
  sendAddrToSensor(regAddr3);
  data[3] = getByte();
  return convert4ByteToFloat(data);
}

byte getByte(){
  Wire.requestFrom(110, 1);   
  return Wire.read();       
}

float convert4ByteToFloat(byte num[4]){
  uData.bData[0] = num[0];
  uData.bData[1] = num[1];
  uData.bData[2] = num[2];
  uData.bData[3] = num[3];
  return uData.fData;
}

void sendAddrToSensor(int address){
  Wire.beginTransmission(UT_SENSOR_ADDR); 
  Wire.write(address); 
  Wire.endTransmission(); 
}