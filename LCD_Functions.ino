//Custom LCD labels
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




void InitLCD()
{
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
}



// Change only characters that differ from the current display
void DisplayLCD()
{
  if(beenHold)
  {
    LCDData[0][15] = '\2';
  }
  //Compare each character you want to display with its already displayed counterpart
  if(LCDData != prevLCDData)
  {  for(int y = 0; y < 2; y++)
    {
      for(int x = 0; x < 16; x++)
      {
        if(LCDData != prevLCDData)
        {
          lcd.setCursor(x,y);
          if(LCDData[y][x] < 7)
          {
            lcd.write((int)LCDData[y][x]);
          }
          else
          {
            lcd.print(LCDData[y][x]);
          }
          prevLCDData[y][x] = LCDData[y][x];
        }
      }
    }
  }
}

void ClearLCD()
{
  for(int x = 0; x < 16; x++)
  {
    for(int y = 0; y < 2; y++)
    {
      LCDData[y][x] = ' ';
    }
  }
}

void AddToLCD(int cursorX, int cursorY, String text)
{
  for(int i = cursorX; i < (cursorX + (int)text.length()) && i < 16; i++)
  {
    LCDData[cursorY][i] = text[i - cursorX];
  }
}
