#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_PWMServoDriver.h>
#include <AltSoftSerial.h>

#define outputA 2
#define outputB 4
#define switchPin 5

//Bluetooth Information
AltSoftSerial BTSerial; 
bool bluetoothConnection;

// Encoder Data
volatile int deltaEncoder;
volatile bool dataChanged;
bool beenPressed;
unsigned long pressTime;

class Finger
{
  public:
  short currentPosition;
  short absMinPulse = 400, absMaxPulse = 2900;
  short minValue= 0, maxValue = 244; 
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


void setup() {
  bluetoothConnection = false;
  
  //LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.print("Hello World");
  lcd.createChar(0, arrow);
  
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
    currentFinger = i;
    MoveFinger(0);
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
