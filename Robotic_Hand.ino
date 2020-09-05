#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_PWMServoDriver.h>
#include <AltSoftSerial.h>
#include <EEPROM.h>

#define outputA 2
#define outputB 4
#define switchPin 5

//UI
byte menu = 0;
byte page = 0;
bool beenClick, beenHold;
volatile unsigned long lastInteraction;
bool lockArduino;

//Bluetooth Information
AltSoftSerial BTSerial; 

//Connection
int connectionType = 0;
bool allowControl = true;

// Encoder Data
volatile int deltaEncoder;
bool beenPressed;
unsigned long pressTime;

class Finger
{
  public:
  bool reverse;
  short currentPosition;
  short holdPosition = 30;
  short minPulse = 400, maxPulse = 2900;
  byte minValue= 10, maxValue = 240; 
};

Finger fingers[5];
int currentFinger = 0;

LiquidCrystal_I2C lcd(0x27,16,2);
char empty[2][16] = {"                ", "                "};
char LCDData[2][16] = {"                ", "                "};
char prevLCDData[2][16] = {"                ", "                "};

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver();
int servoPulse[5] = {0,0,0,0,0};
int actualServoPulse[5] = {0,0,0,0,0};

const byte arrow[] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
  B00000
};
const byte backArrow[] = {
  B00000,
  B11111,
  B00001,
  B00101,
  B01001,
  B11111,
  B01000,
  B00100
};
const byte lowerBounds[] = {
  B10000,
  B10000,
  B10000,
  B11111,
  B10000,
  B10000,
  B10000,
  B00000
};
const byte upperBounds[] = {
  B00001,
  B00001,
  B00001,
  B11111,
  B00001,
  B00001,
  B00001,
  B00000
};
const byte lowerPulseBounds[] = {
  B10000,
  B10000,
  B10101,
  B11010,
  B10101,
  B10000,
  B10000,
  B00000
};
const byte upperPulseBounds[] = {
  B00001,
  B00001,
  B10101,
  B01011,
  B10101,
  B00001,
  B00001,
  B00000
};

void setup() {
  
  connectionType = 0;
  menu = 1;
  
  

  //Retrieve from EEPROM
  retreiveFromEEPROM();
  
  fingers[4].reverse = true;
  //LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.print("Check Encoder");
  lcd.createChar(1, arrow);
  lcd.createChar(2, backArrow);
  lcd.createChar(3, lowerBounds);
  lcd.createChar(4, upperBounds);
  lcd.createChar(5, lowerPulseBounds);
  lcd.createChar(6, upperPulseBounds);
  
  //Servos
  servos.begin();
  servos.setPWMFreq(50);
  
  //Serial
  Serial.begin(115200);
  Serial.println("Robotic Hand Debug:");
  BTSerial.begin(9600);
  
  //Set servos to default
  for(int i = 0; i < 5; i++)
  {
    MoveFinger(255, i);
  }
  checkServoPulse();
  
  //Encoder Setup
    attachInterrupt(digitalPinToInterrupt(outputA), isr, LOW);
}

void loop() {

  // put your main code here, to run repeatedly:
//  addToLCD(0,0, "1: " + (String)fingers[0].minValue + " 2: " + (String)fingers[1].minValue + "        ");
  handleSerial();
  checkServoPulse();
  CheckForInteraction();
  ManageUI();
  displayLCD();
}
