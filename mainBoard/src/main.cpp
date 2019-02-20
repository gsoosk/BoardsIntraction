#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

// Function Declarations
void handleDataFromBluetooth();
void showBluetoothData();
void handleDataFromSensorBoard();
void showSensorBoardData();



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int BLUETOOTH_RATE = 9600;
const int BLUETOOTH_BUFF_SIZE = 8;
char bluetoothBuff[8];
int bluetoothBuffCurr = 0;


// AltSoftSerial always uses these pins:
// Transmit  Receive   PWM Unusable
// --------  -------   ------------
//  9         8         10
AltSoftSerial sensorBoardSerial;
const int SENSOR_BOARD_RATE = 9600;
String sensorBoardBuff = "";
char END_DELIMINATOR = '#';
char DATA_DELIMINATOR = ':';



bool x = true;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  
  // We use Serial port for bluetooth module :
  Serial.begin(BLUETOOTH_RATE); // Default communication rate of the Bluetooth module

  // We use Serial port to comunicate with sensor board with rate 9600
  sensorBoardSerial.begin(SENSOR_BOARD_RATE);

}

void loop() {
  if(Serial.available())
    handleDataFromBluetooth();
  if(sensorBoardSerial.available())
    handleDataFromSensorBoard();  
}

void handleDataFromBluetooth()
{
  bluetoothBuff[bluetoothBuffCurr] = Serial.read();
  bluetoothBuffCurr ++;
  if(bluetoothBuffCurr == BLUETOOTH_BUFF_SIZE)
    showBluetoothData();
}
void showBluetoothData()
{
  lcd.setCursor(0, 0);
  lcd.print(bluetoothBuff);
  bluetoothBuffCurr = 0;
}

void handleDataFromSensorBoard()
{
  char data = sensorBoardSerial.read();
  if(data == END_DELIMINATOR)
  {
    showSensorBoardData();
    return;
  }
  sensorBoardBuff += data ;
}

void showSensorBoardData()
{ 
  String temperature =  sensorBoardBuff.substring(0, sensorBoardBuff.indexOf(DATA_DELIMINATOR));
  lcd.setCursor(0, 1);
  lcd.print(temperature.c_str());

  String distance = sensorBoardBuff.substring(sensorBoardBuff.indexOf(DATA_DELIMINATOR) + 1);
  lcd.setCursor(0, 2);
  lcd.print(distance.c_str());

  sensorBoardBuff = "";
}