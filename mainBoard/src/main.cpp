#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

// Function Declarations
void handleDataFromBluetooth();
void handleDataFromSensorBoard();


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int bluetoothRate = 9600;

// AltSoftSerial always uses these pins:
// Transmit  Receive   PWM Unusable
// --------  -------   ------------
//  9         8         10
AltSoftSerial sensorBoardSerial;
const int sensorBoardPortRate = 9600;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  
  // We use Serial port for bluetooth module :
  Serial.begin(bluetoothRate); // Default communication rate of the Bluetooth module

  // We use Serial port to comunicate with sensor board with rate 9600
  sensorBoardSerial.begin(sensorBoardPortRate);

}

void loop() {
  if(Serial.available())
    handleDataFromBluetooth();
  if(sensorBoardSerial.available())
    handleDataFromSensorBoard();  
}

void handleDataFromBluetooth()
{

}

void handleDataFromSensorBoard()
{

}