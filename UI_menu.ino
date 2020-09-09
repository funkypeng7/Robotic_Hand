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
const short timeAtMinPos = 500;
int setting;
bool setMax, hasBeen, beenChange;

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
      hasBeen = false;
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
        setMax = true;
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
        ChangeSetting(setting, page - numOfCOptions - 5);
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
      addToLCD(0,0,"Please turn off");
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

void ChangeSetting(byte setting, byte finger) {
  Serial.print("Change Setting");
  if(beenClick)
  {
    setMax = !setMax;
    beenChange = true;
  }
  switch (setting) {
    //Range
    case 1:
        if(!hasBeen)
        {
          setMax = true;
          hasBeen = true;
        }
        if(setMax)
          MoveFinger(255, finger, true);
        else
          MoveFinger(0, finger, true);
 
      AdjustSetting(finger, fingers[finger].minValue, fingers[finger].maxValue, 255, setMax, 10, 1, " - Range", setMax ? 1: 2); 
      break;
   //Pulse
   case 2:
      if(!hasBeen)
      {
        setMax = true;
        hasBeen = true;
      }
      if(setMax)
        MoveFinger(255, finger);
      else
        MoveFinger(0, finger, true);

      AdjustSetting(finger, fingers[finger].minPulse, fingers[finger].maxPulse, 10000, setMax, 100, 5, " - Pulse", setMax ? 3: 4); 
      break;
  //Hold Position
  case 3:
      if(!hasBeen)
      {
        MoveFinger(0, finger);
      }

      AdjustSingleSetting(finger, fingers[finger].holdPosition, 255, 1, " - Hold", 5, false);
      break;
  }
}

void AdjustSetting(short finger, short minValue, short maxValue, short absMax, bool setMax, short offset, byte scrollMultiplier, String title, byte valueToSet)
{
  if(deltaEncoder != 0)
  {
    short newValue = setMax ? maxValue : minValue;
    newValue += deltaEncoder * scrollMultiplier - scrollMultiplier + 1;
    
    if(setMax) 
    {
      if(newValue < minValue + offset)
        newValue = minValue + offset;
      if(newValue > absMax)
        newValue = absMax;
        
      maxValue = newValue;
    } 
    else 
    {
      if(newValue > maxValue - offset)
        newValue = maxValue - offset;
      if(newValue < 0)
        newValue = 0;

      minValue = newValue;
    }

    //Set Value
    switch(valueToSet)
    {
      case 1:
        fingers[finger].maxValue = newValue;
        break;
      case 2:
        fingers[finger].minValue = newValue;
        break;
      case 3: 
        fingers[finger].maxPulse = newValue;
        break;
      case 4: 
        fingers[finger].minPulse = newValue;
        break;
    }
  }
  if(setMax)
    {
      clearLCD();
      addToLCD(0,0, "Finger " + (String)(finger + 1) + title);
      addToLCD(0,1, " -" + (String)minValue + " \1+" + (String)maxValue);
    }
    else
    {
      clearLCD();
      addToLCD(0,0, "Finger " + (String)(finger + 1) + title);
      addToLCD(0,1, "\1-" + (String)minValue + "  +" + (String)maxValue);
    }
}

void AdjustSingleSetting(short finger, short value, short absMax, byte scrollMultiplier, String title, byte valueToSet, bool isBool)
{
  if(deltaEncoder != 0)
  {
    short newValue = value;
    newValue += deltaEncoder * scrollMultiplier - scrollMultiplier + 1;
    
    if(newValue > absMax)
      newValue = absMax;
    if(newValue < 0)
      newValue = 0;

    value = newValue;
    
    //Set Value
    switch(valueToSet)
    {
      case 5:
        BIT_CLEAR(fingersHeld, finger);
        
        fingers[finger].holdPosition = newValue;
        break;
    }
  }
  if(!isBool)
  {
    clearLCD();
    addToLCD(0,0, "Finger " + (String)(finger + 1) + title);
    addToLCD(0,1, "\1-" + (String)value);
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
