// Change only characters that differ from the current display
void displayLCD(){
  //Compare each character you want to display with its already displayed counterpart
  if(LCDData != prevLCDData)
  {  for(int y = 0; y < 2; y++)
    {
      for(int x = 0; x < 16; x++)
      {
        if(LCDData != prevLCDData)
        {
          lcd.setCursor(x,y);
          lcd.print(LCDData[y][x]);
          prevLCDData[y][x] = LCDData[y][x];
        }
      }
    }
  }
}

void addToLCD(int cursorX, int cursorY, String text)
{
  for(int i = cursorX; i < (cursorX + (int)text.length()) && i < 16; i++)
  {
    LCDData[cursorY][i] = text[i - cursorX];
  }
}
