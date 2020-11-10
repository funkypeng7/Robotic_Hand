#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

#define outputA 2
#define outputB 4
#define switchPin 5

//UI
byte menu = 0;
short page = 0;
bool beenClick, beenHold, beenReturnHold;
volatile unsigned long lastInteraction;
bool lockArduino;

//Bluetooth Information
SoftwareSerial BTSerial(8,9); 

//Connection
int connectionType = 0;
bool allowControl = true;

// Encoder Data
volatile int deltaEncoder;
bool beenPressed;
unsigned long pressTime;

// Finger class - used to hold all data on a finger - with default values (for factory reset)
class Finger
{
  public:
  bool reverse;
  short currentPosition;
  short holdPosition = 30;
  short minPulse = 400, maxPulse = 2900;
  byte minValue= 10, maxValue = 240; 
};

// All fingers
Finger fingers[5];
Finger allFingers;
// Current Selected Finger
int currentFinger = 0;

// LCD Screen
LiquidCrystal_I2C lcd(0x27,16,2);

// LCD Display Info 
const char empty[2][16] = {"                ", "                "};
char LCDData[2][16] = {"                ", "                "};
char prevLCDData[2][16] = {"                ", "                "};


// Servo Driver
Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver();
// Pulse Info
short servoPulse[5] = {0,0,0,0,0};
short actualServoPulse[5] = {0,0,0,0,0};


void setup() {

  
  
  InitTimer1();
 
  
  // Set Initial Menu Location
  connectionType = 0;
  menu = 0;
  
  // Retrieve saved finger configuration from EEPROM
  RetreiveFromEEPROM();
  
  // LCD Setup
  InitLCD();
  
  // Servos Initialization
  servos.begin();
  servos.setPWMFreq(50);
  
  // Serial
  Serial.begin(115200);
  Serial.println("Robotic Hand Debug:");
  BTSerial.begin(9600);
//  SetBLEName("Robo Hand");
  
  //Set servos to default
  for(int i = 0; i < 5; i++)
  {
    MoveFinger(255, i);
  }
  allFingers.currentPosition = allFingers.maxValue;
  CheckServoPulse();
  
  //Encoder Setup
    attachInterrupt(digitalPinToInterrupt(outputA), isr, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  HandleSerial();
  CheckServoPulse();
  CheckServosHoldPosition();
  CheckForInteraction();
  ManageUI();
  DisplayLCD();
}
