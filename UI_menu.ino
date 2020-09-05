unsigned long holdStartTime;
bool hasBeenDown;


//Menu 0
const String menus[] = {"Info screen", "Connection Type", "Manual Control", "Calibration", "Finger Data"};
const short numOfMenus = 5;
//Menu 2 - Connection
const String typesOfConnections[] = {"Serial", "Bluetooth", "Controller"};
const short numOfConnections = 3;
//Menu 3 - Manual Control
const String fingerList[] = {"Finger 1", "Finger 2", "Finger 3", "Finger 4", "Finger 5"};
int selectedFinger;
//Menu 4 - callibration
const String callibrationOptions[] = {"Direction", "Range", "Pulses", "Stop Position",  "Save Settings", "Factory Reset"};
const short numOfCOptions = 6;
int setting;
bool setMax;
//Menu 5
//String debugList[] = {"Finger 1 - ", "Range", "Pulse", "Finger 2 - ", "Range", "Pulse", "Finger 3 - ", "Range", "Pulse", "Finger 4 - ", "Range", "Pulse", "Finger 5 - ", "Range", "Pulse",};
//Menu 6
const String confirmMenu[] {"Back", "I Want To Reset"};
byte numOfConfirm = 2;


void CheckForInteraction()
{
  Serial.println(page);

  beenClick = false;
  beenHold = false;
  
  if(lockArduino)
    return;
    
  if(!digitalRead(5) && !hasBeenDown)
  {
    lastInteraction = millis();
    holdStartTime = millis();
    hasBeenDown = true;
  }

  if(!digitalRead(5) && millis() - holdStartTime > 500)
  {
    lastInteraction = millis();
     beenHold = true;
  }
  
  if(digitalRead(5) && hasBeenDown)
  {
    lastInteraction = millis();
    hasBeenDown = false;
    if(millis() - holdStartTime > 500)
    {
      moveToMenu(0);
    }
    else
    {
      beenClick = true;
      Serial.println("click");
    }
    
  }
  CheckTimeout();
  
}
void CheckTimeout()
{
  if(menu != 1 && millis() - lastInteraction > 20000)
  {
    moveToMenu(1);
  }
}

void ManageUI()
{
  if(menu == 0)
  {
    if(beenClick)
    {
      moveToMenu(page + 1);
      return;
    }
    DisplayList(menus, numOfMenus, 0);
  }
  else if(menu == 1)
  {
    if(beenClick)
    {
      moveToMenu(0);
      return;
    }
    clearLCD();
    addToLCD(0,0, "1:" + (String)fingers[0].currentPosition + " 2:" + (String)fingers[1].currentPosition + " 3:" + (String)fingers[2].currentPosition);
    addToLCD(0,1, "4:" + (String)fingers[3].currentPosition + " 5:" + (String)fingers[4].currentPosition);
    
    if(connectionType == 0)
      addToLCD(15,1, "S");
    else if(connectionType == 1)
      addToLCD(15,1, "B");
    else if(connectionType == 2)
      addToLCD(15,1, "C");
  }
  else if(menu == 2)
  {
    if(beenClick)
    {
      connectionType = page;
      moveToMenu(1);
      return;
    }
    DisplayList(typesOfConnections, numOfConnections, 0);
  }
  else if(menu == 3)
  {
    if((beenClick) && page < 5)
    {
      page += 5;
      beenClick = false;
      allowControl = false;
    }
    if(page < 5)
      DisplayList(fingerList, 5, 0);
    else
    {
      if(beenClick)
      {
        moveToMenu(0);
        return;
      }
      if(deltaEncoder != 0)
      {
        int newPosition = fingers[page - 5].currentPosition;
        newPosition += deltaEncoder * 3 - 2 * deltaEncoder/abs(deltaEncoder);
        if(newPosition < fingers[page - 5].minValue)
          newPosition = fingers[page - 5].minValue;
        if(newPosition > fingers[page - 5].maxValue)
          newPosition = fingers[page - 5].maxValue;
        MoveFinger(newPosition, page - 5);
      }
      clearLCD();
      addToLCD(0,0, "Finger " + (String)(page - 4) + ": " + (String)(fingers[page - 5].currentPosition));
    }
  }
  else if(menu == 4)
  {
    if(beenClick && page < numOfCOptions)
    {
      if(page == 4)
        page = 30;
      else if(page == 5)
      {
        moveToMenu(6);
      }
      else
      {
        setting = page;
        page = numOfCOptions;
        beenClick = false;
        allowControl = false;
      }
    }
    if(page < numOfCOptions)
      DisplayList(callibrationOptions, numOfCOptions, 0);
    if(page >= numOfCOptions)
    {
      if(beenClick && page < numOfCOptions + 5)
      {
        page += 5;
        setMax = false;
        beenClick = false;
        allowControl = false;
      }
      if(page < numOfCOptions + 5)
        DisplayList(fingerList, 5, numOfCOptions);
      else if(page == 30)
      {
        saveToEEPROM();
        clearLCD();
        addToLCD(0,0, "Save Successful");
        page = 31;
        return;
      }
      else if(page == 31)
      {
        clearLCD();
        addToLCD(0,0, "Save Successful");
        addToLCD(0,1, "Hold To Exit");
      }
      else
      {
        ChangeSetting(setting);
      }
    }
  }
  else if(menu == 5)
  {
    if(beenClick)
    {
      moveToMenu(0);
      return;
    }
    if(deltaEncoder != 0)
    {
      page += deltaEncoder;
      if(page < 0)
        page = 0;
      if(page > 18)
        page = 18;
    }
    clearLCD();
    addToLCD(0,0, getData(page));
    addToLCD(0,1, getData(page + 1));
  }
  else if(menu == 6)
  {
    if(beenClick)
    {
      if(page == 0)
        moveToMenu(0);
      else
      {
        EEPROM.write(0,1);
        page = 3;
      }
    }
    
    if(page == 3)
    {
      clearLCD();
      addToLCD(0,0,"Please Reset Arduino");
      lockArduino = true;
    }
    else
    {
      DisplayList(confirmMenu, numOfConfirm, 0);
    }
  }
  else
  {
    moveToMenu(0);
  }
  deltaEncoder = 0;
}

String getData(int i)
{
  short finger = floor(i/4);
  switch(i % 4)
  {
    case 0:
      return "Finger " + (String)(finger + 1) + " - " + (String)fingers[finger].currentPosition;
      break;
    case 1:
      if(fingers[finger].reverse)
        return F(" Direction = R");
      else
        return  F(" Direction = N");
      break;
    case 2: 
      return " \3" + (String)fingers[finger].minValue + " - " + (String)fingers[finger].maxValue + "\4";
      break;
    case 3: 
      return " \5" + (String)fingers[finger].minPulse + " - " + (String)fingers[finger].maxPulse + "\6";
      break;
  }
  
}

void ChangeSetting(int setting) {
  if(beenClick)
  {
    setMax = !setMax;
  }
  switch (setting) {
    case 1:
      if(deltaEncoder != 0)
      {
        int newPulse = fingers[page - numOfCOptions - 5].minPulse;
        if(setMax)
          newPulse = fingers[page - numOfCOptions - 5].maxPulse;

        newPulse += deltaEncoder;
        if(setMax)
        {
          if(newPulse < fingers[page - numOfCOptions - 5].minPulse + 100)
            newPulse = fingers[page - numOfCOptions - 5].minPulse + 100;
        }
        else
        {
          if(newPulse > fingers[page - numOfCOptions - 5].maxPulse - 100)
            newPulse = fingers[page - numOfCOptions - 5].maxPulse - 100;
          if(newPulse < 0)
            newPulse = 0;
        }
        if(setMax)
        {
          fingers[page - numOfCOptions - 5].maxPulse = newPulse;
          MoveFinger(255, page - numOfCOptions - 5);
        }
        else
        {
          fingers[page - numOfCOptions - 5].minPulse = newPulse;
          MoveFinger(0, page - numOfCOptions - 5);
        }
      }
      if(setMax)
      {
        clearLCD();
        addToLCD(0,0, "Finger " + (String)(page - numOfCOptions - 4) + " - Pulse");
        addToLCD(0,1, " -" + (String)fingers[page - numOfCOptions - 5].minPulse + " \1+" + (String)fingers[page - numOfCOptions - 5].maxPulse);
      }
      else
      {
        clearLCD();
        addToLCD(0,0, "Finger " + (String)(page - numOfCOptions - 4) + " - Pulse");
        addToLCD(0,1, "\1-" + (String)fingers[page - numOfCOptions - 5].minPulse + "  +" + (String)fingers[page - numOfCOptions - 5].maxPulse);
      }
      break;
     case 2:
      if(deltaEncoder != 0)
      {
        int newRange = fingers[page - numOfCOptions - 5].minValue;
        if(setMax)
          newRange = fingers[page - numOfCOptions - 5].maxValue;

        newRange += deltaEncoder;
        if(setMax)
        {
          if(newRange < fingers[page - numOfCOptions - 5].minValue)
            newRange = fingers[page - numOfCOptions - 5].maxValue;
        }
        else
        {
          if(newRange > fingers[page - numOfCOptions - 5].minValue)
            newRange = fingers[page - numOfCOptions - 5].maxValue;
          if(newRange < 0)
            newRange = 0;
        }
        if(setMax)
        {
          fingers[page - numOfCOptions - 5].maxValue = newRange;
          MoveFinger(255, page - numOfCOptions - 5);
        }
        else
        {
          fingers[page - numOfCOptions - 5].minValue = newRange;
          MoveFinger(0, page - numOfCOptions - 5);
        }
      }
      if(setMax)
      {
        clearLCD();
        addToLCD(0,0, "Finger " + (String)(page - numOfCOptions - 4) + " - Range");
        addToLCD(0,1, " -" + (String)fingers[page - numOfCOptions - 5].minValue + " \1+" + (String)fingers[page - numOfCOptions - 5].maxValue);
      }
      else
      {
        clearLCD();
        addToLCD(0,0, "Finger " + (String)(page - numOfCOptions - 4) + " - Range");
        addToLCD(0,1, "\1-" + (String)fingers[page - numOfCOptions - 5].minValue + "  +" + (String)fingers[page - numOfCOptions - 5].maxValue);
      }
      break;
  }
}







void moveToMenu(int _menu)
{
  beenClick = false;
  beenHold = false;
  deltaEncoder = 0;
  menu = _menu;
  page = 0;
  allowControl = true;
  ManageUI();
}

void DisplayList(String items[], short numOfItems, short pageOffset)
{
  if(deltaEncoder != 0)
  {
    page += deltaEncoder;
    if(page - pageOffset < 0)
      page = pageOffset;
    if(page - pageOffset >= numOfItems)
      page = numOfItems - 1 + pageOffset;
    deltaEncoder = 0;
  }
  clearLCD();
  addToLCD(0,0, "\1" + items[page - pageOffset]);
  if(page - pageOffset + 1 < numOfItems)
  {
    addToLCD(0,1," " + items[page - pageOffset + 1]);
  } 
  if(page - pageOffset + 1 == numOfItems)
  {
    clearLCD();
    addToLCD(0,0, " " + items[page - pageOffset - 1]);
    addToLCD(0,1, "\1" + items[page - pageOffset]);
  }

}

void isr ()  
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  
  // If interrupts come faster than 5ms, assume it's a bounce and ignore
  if (interruptTime - lastInterruptTime > 5) {
    if (digitalRead(outputB) == LOW)
    {
      deltaEncoder-- ; 
    }
    else {
      deltaEncoder++ ; 
    }
  }
  lastInteraction = millis();
  // Keep track of when we were here last (no more than every 5ms)
  lastInterruptTime = interruptTime;
}
