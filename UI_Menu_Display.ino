unsigned long holdStartTime;
bool hasBeenDown;

//Menu 0
char buffer[16];

#define MainMenuReturnTime 1500
#define ReturnTime 500

//Menu 2 - Connection
const String typesOfConnections[] = {"Serial", "Bluetooth", "Controller"};
const byte numOfConnections = 3;
//Menu 3 - Manual Control
const String fingerList[] = {"Finger 1", "Finger 2", "Finger 3", "Finger 4", "Finger 5"};
//const String fingerListAndAll[] = {"Finger 1", "Finger 2", "Finger 3", "Finger 4", "Finger 5", "All"};
int selectedFinger;
//Menu 4 - settings
const String settings[] = {"Configuration", "Debug"};
const byte numOfSettings = 2;
//Menu 5 - callibration
const String callibrationOptions[] = {"Direction", "Range", "Pulses", "Hold Position",  "Save Settings", "Factory Reset"};
const byte numOfCOptions = 6;
const short timeAtMinPos = 500;
int setting;
bool setMax, hasBeen, beenChange;
//Menu 6 - Debug
//Menu 7
const String confirmMenu[] = {"Back", "I Want To Reset"};
byte numOfConfirm = 2;

void ManageUI()
{
  switch(menu)
  {
    // Main menu
    case 0:
    {
      if(beenClick)
      {
        MoveToMenu(page + 1);
        return;
      }
      DisplayList(menus, numOfMenus, 0);
      break;
    }
    // Info Screen - to be replaced by demo
    case 1:
    {
      ClearLCD();
      AddToLCD(0,0, F("Will be Demo"));
//      if(beenClick)
//      {
//        MoveToMenu(0);
//        return;
//      }
//      ClearLCD();
//      AddToLCD(0,0, "1:" + (String)fingers[0].currentPosition + " 2:" + (String)fingers[1].currentPosition + " 3:" + (String)fingers[2].currentPosition);
//      AddToLCD(0,1, "4:" + (String)fingers[3].currentPosition + " 5:" + (String)fingers[4].currentPosition);
//      
//      if(connectionType == 0)
//        AddToLCD(15,1, "S");
//      else if(connectionType == 1)
//        AddToLCD(15,1, "B");
//      else if(connectionType == 2)
//        AddToLCD(15,1, "C");
      break;
    }
    // Connection Menu
    case 2:
    {
      if(beenClick && page < numOfConnections)
      {
        connectionType = page;
        page += numOfConnections;
        return;
      }
      if(page < numOfConnections)
        DisplayList(typesOfConnections, numOfConnections, 0);
      else
      {
        ClearLCD();
        AddToLCD(0,0, F("Connected To:"));
        AddToLCD(0,1, typesOfConnections[connectionType]);
      }
      break;
    }
    // Manual Control
    case 3:
    {
      if((beenClick) && page < 5)
      {
        page += 6;
        beenClick = false;
        allowControl = false;
      }
      if(page < 6)
        DisplayList(fingerList, 6, 0);
//        DisplayList(fingerListAndAll, 6, 0);
      else if(page < 11)
      {
        if(beenClick)
        {
          Return();
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
        ClearLCD();
        AddToLCD(0,0, "Finger " + (String)(page - 4) + ": " + (String)(fingers[page - 5].currentPosition));
      }
//      else
//      {
//        if(beenClick)
//        {
//          Return();
//          return;
//        }
//        if(deltaEncoder != 0)
//        {
//          int newPosition = allFingers.currentPosition;
//          newPosition += deltaEncoder * 3 - 2 * deltaEncoder/abs(deltaEncoder);
//          if(newPosition < allFingers.minValue)
//            newPosition = allFingers.minValue;
//          if(newPosition > allFingers.maxValue)
//            newPosition = allFingers.maxValue;
//
//          for(int i = 1; i < 5; i++)
//          {
//            MoveFinger(map(newPosition, allFingers.minValue, allFingers.maxValue, fingers[i].minValue, fingers[i].maxValue), i);
//          }
//          
//        }
//        ClearLCD();
//        AddToLCD(0,0, "Finger " + (String)(page - 4) + ": " + (String)(fingers[page - 5].currentPosition));
//      }
      break;
    }
    // Settings
    case 4:
    {
      if(beenClick)
      {
        MoveToMenu(page + 5);
      }
      DisplayList(settings, numOfSettings, 0);
      break;
    }
    // Configuration Menu
    case 5:
    {
      if(beenClick && page < numOfCOptions)
      {
        if(page == 4)
          page = 30;
        else if(page == 5)
        {
          MoveToMenu(7);
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
          SaveToEEPROM();
          ClearLCD();
          AddToLCD(0,0, "Save Successful");
          page = 31;
          return;
        }
        else if(page == 31)
        {
          ClearLCD();
          AddToLCD(0,0, "Save Successful");
          AddToLCD(0,1, "Hold To Exit");
        }
        else
        {
          ChangeSetting(setting, page - numOfCOptions - 5);
        }
      }
      break;
    }
    // Debug
    case 6:
    {
      if(beenClick)
      {
        Return();
        return;
      }
      if(deltaEncoder != 0)
      {
        page += deltaEncoder;
        if(page < 0)
          page = 0;
        if(page > 23)
          page = 23;
      }
      ClearLCD();
      AddToLCD(0,0, GetData(page));
      AddToLCD(0,1, GetData(page + 1));
      break;
    }
    // Factory Reset
    case 7:
    {
      if(beenClick)
      {
        if(page == 0)
          Return();
        else
        {
          EEPROM.write(0,1);
          page = 3;
        }
      }
      
      if(page == 3)
      {
        ClearLCD();
        AddToLCD(0,0,"Please turn off");
        lockArduino = true;
      }
      else
      {
        DisplayList(confirmMenu, numOfConfirm, 0);
      }
      break;
    }
    default:
      MoveToMenu(0);
      break;
  }
  deltaEncoder = 0;
}

String GetData(int i)
{
  short finger = floor(i/4);
  switch(i % 5)
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
      return " Hold - "  + (String)fingers[finger].holdPosition;
      break;
    case 3: 
      return " \3" + (String)fingers[finger].minValue + " - " + (String)fingers[finger].maxValue + "\4";
      break;
    case 4: 
      return " \5" + (String)fingers[finger].minPulse + " - " + (String)fingers[finger].maxPulse + "\6";
      break;
    default:
      return " Error ";
  }
  
}

void ChangeSetting(byte setting, byte finger) {
  if(beenClick)
  {
    setMax = !setMax;
    beenChange = true;
  }
  switch (setting) {
    //Reverse
    case 0: 
      MoveFinger(255, finger);
      AdjustSingleSetting(finger, (float)fingers[finger].reverse, 1, 1, " - Reverse", 0, true);
      break;
    //Range
    case 1:
        if(!hasBeen)
        {
          setMax = true;
          hasBeen = true;
        }
        if(setMax)
          MoveFinger(255, finger);
        else
        {
          MoveFinger(0, finger, true);
          BIT_SET(fingersBelowMin, finger);
          BIT_CLEAR(fingersHeld, finger);
          timeSinceMinPos[finger] = millis();
        }
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
      {
        MoveFinger(0, finger, true);
        BIT_SET(fingersBelowMin, finger);
        BIT_CLEAR(fingersHeld, finger);
        timeSinceMinPos[finger] = millis();
      }
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
      ClearLCD();
      AddToLCD(0,0, "Finger " + (String)(finger + 1) + title);
      AddToLCD(0,1, " -" + (String)minValue + " \1+" + (String)maxValue);
    }
    else
    {
      ClearLCD();
      AddToLCD(0,0, "Finger " + (String)(finger + 1) + title);
      AddToLCD(0,1, "\1-" + (String)minValue + "  +" + (String)maxValue);
    }
}

void AdjustSingleSetting(short finger, short value, short absMax, byte scrollMultiplier, String title, byte valueToSet, bool isBool)
{
  if(deltaEncoder != 0)
  {
    short newValue = value;
    newValue += deltaEncoder * scrollMultiplier - scrollMultiplier + 1;

    if(isBool)
    {
      for(int i = 0; i< deltaEncoder; i++)
      {
        value = !(bool)value;
      }
    }
    else
    {
      if(newValue > absMax)
        newValue = absMax;
      if(newValue < 0)
        newValue = 0;
    }
    
    value = newValue;
    
    //Set Value
    switch(valueToSet)
    {
      case 0:
        fingers[finger].reverse = (bool)newValue;
        break;
      case 5:
        BIT_CLEAR(fingersHeld, finger);
        fingers[finger].holdPosition = newValue;
        break;
    }
  }
  if(!isBool)
  {
    ClearLCD();
    AddToLCD(0,0, "Finger " + (String)(finger + 1) + title);
    AddToLCD(0,1, "\1-" + (String)value);
  }
  else
  {
    ClearLCD();
    AddToLCD(0,0, "Finger " + (String)(finger + 1) + title);
    AddToLCD(0,1, "\1-" + (bool)(value) ? "Reversed": "Normal");
  }
}

void DisplayList(String items[], short numOfItems, short pageOffset)
{
  if(deltaEncoder != 0)
  {
    page += deltaEncoder;
    if(page - pageOffset < 0)
    {
      page = pageOffset;
      Serial.println("page - pageOffset < 0");
    }
    if(page - pageOffset >= numOfItems)
    {
      page = numOfItems - 1 + pageOffset;
      Serial.println("page - pageOffset >= numOfItems");
    }
      
    deltaEncoder = 0;
  }
  ClearLCD();
  AddToLCD(0,0, "\1" + items[page - pageOffset]);
  if(page - pageOffset + 1 < numOfItems)
  {
    AddToLCD(0,1," " + items[page - pageOffset + 1]);
  } 
  if(page - pageOffset + 1 == numOfItems)
  {
    ClearLCD();
    AddToLCD(0,0, " " + items[page - pageOffset - 1]);
    AddToLCD(0,1, "\1" + items[page - pageOffset]);
  }

}

void DisplayList(const char *const items[], short numOfItems, short pageOffset)
{
  if(deltaEncoder != 0)
  {
    page += deltaEncoder;
    if(page - pageOffset < 0)
    {
      page = pageOffset;
      Serial.println("page - pageOffset < 0");
    }
    if(page - pageOffset >= numOfItems)
    {
      page = numOfItems - 1 + pageOffset;
      Serial.println("page - pageOffset >= numOfItems");
    }
      
    deltaEncoder = 0;
  }
  ClearLCD();
  AddToLCD(0,0, "\1" + getString(items, page - pageOffset));
  if(page - pageOffset + 1 < numOfItems)
  {
    AddToLCD(0,1," " + getString(items, page - pageOffset + 1));
  } 
  if(page - pageOffset + 1 == numOfItems)
  {
    ClearLCD();
    AddToLCD(0,0, " " + getString(items, page - pageOffset - 1));
    AddToLCD(0,1, "\1" + getString(items, page - pageOffset));
  }
}
