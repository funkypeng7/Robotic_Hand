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
const String callibrationOptions[] = {"Range", "Pulses"};
const short numOfCOptions = 2;
bool adjustPulse, setMax;
//Menu 5
//String debugList[] = {"Finger 1 - ", "Range", "Pulse", "Finger 2 - ", "Range", "Pulse", "Finger 3 - ", "Range", "Pulse", "Finger 4 - ", "Range", "Pulse", "Finger 5 - ", "Range", "Pulse",};



void CheckForInteraction()
{
  beenClick = false;
  beenHold = false;
  
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
    if(beenClick && page < 2)
    {
      adjustPulse = page;
      page = 2;
      beenClick = false;
      allowControl = false;
    }
    if(page < 2)
      DisplayList(callibrationOptions, numOfCOptions, 0);
    if(page >= 2)
    {
      if(beenClick && page < 7)
      {
        page += 5;
        setMax = false;
        beenClick = false;
        allowControl = false;
      }
      if(page < 7)
        DisplayList(fingerList, 5, 2);
      else
      {
        if(beenClick)
        {
          setMax = !setMax;
        }
        if(adjustPulse)
        {
          if(deltaEncoder != 0)
          {
            int newPulse = fingers[page - 7].minPulse;
            if(setMax)
              newPulse = fingers[page - 7].maxPulse;

            newPulse += deltaEncoder;
            if(setMax)
            {
              if(newPulse < fingers[page - 7].minPulse + 100)
                newPulse = fingers[page - 7].minPulse + 100;
            }
            else
            {
              if(newPulse > fingers[page - 7].maxPulse - 100)
                newPulse = fingers[page - 7].maxPulse - 100;
              if(newPulse < 0)
                newPulse = 0;
            }
            if(setMax)
            {
              fingers[page - 7].maxPulse = newPulse;
              MoveFinger(255, page - 7);
            }
            else
            {
              fingers[page - 7].minPulse = newPulse;
              MoveFinger(0, page - 7);
            }
          }
          if(setMax)
          {
            clearLCD();
            addToLCD(0,0, "Finger " + (String)(page - 6) + " - Pulse");
            addToLCD(0,1, " -" + (String)fingers[page -7].minPulse + " \1+" + (String)fingers[page - 7].maxPulse);
          }
          else
          {
            clearLCD();
            addToLCD(0,0, "Finger " + (String)(page - 6) + " - Pulse");
            addToLCD(0,1, "\1-" + (String)fingers[page -7].minPulse + "  +" + (String)fingers[page - 7].maxPulse);
          }
        }
        else
        {
          if(deltaEncoder != 0)
          {
            int newRange = fingers[page - 7].minValue;
            if(setMax)
              newRange = fingers[page - 7].maxValue;

            newRange += deltaEncoder;
            if(setMax)
            {
              if(newRange < fingers[page - 7].minValue)
                newRange = fingers[page - 7].maxValue;
            }
            else
            {
              if(newRange > fingers[page - 7].minValue)
                newRange = fingers[page - 7].maxValue;
              if(newRange < 0)
                newRange = 0;
            }
            if(setMax)
            {
              fingers[page - 7].maxValue = newRange;
              MoveFinger(255, page - 7);
            }
            else
            {
              fingers[page - 7].minValue = newRange;
              MoveFinger(0, page - 7);
            }
          }
          if(setMax)
          {
            clearLCD();
            addToLCD(0,0, "Finger " + (String)(page - 6) + " - Range");
            addToLCD(0,1, " -" + (String)fingers[page -7].minValue + " \1+" + (String)fingers[page - 7].maxValue);
          }
          else
          {
            clearLCD();
            addToLCD(0,0, "Finger " + (String)(page - 6) + " - Range");
            addToLCD(0,1, "\1-" + (String)fingers[page -7].minValue + "  +" + (String)fingers[page - 7].maxValue);
          }
        }
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
