unsigned long holdStartTime;
bool hasBeenDown;
volatile unsigned long lastInteraction;

//Menu 0
const String menus[] = {"Info screen", "Connection", "Manual Control",};
const short numOfMenus = 3;
//Menu 2 - Connection
const String typesOfConnections[] = {"Serial", "Bluetooth", "Controller"};
int numOfConnections = 3;
//Menu 3 - Manual Control
const String fingerList[] = {"Finger 1", "Finger 2", "Finger 3", "Finger 4", "Finger 5"};
int selectedFinger;

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
      Serial.println("Click");
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
    DisplayList(menus, numOfMenus);
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
      moveToMenu(0);
      return;
    }
    DisplayList(typesOfConnections, numOfConnections);
  }
  else if(menu == 3)
  {
    if((beenClick) && page < 5)
    {
      page += 5;
      beenClick = false;
    }
    if(page < 5)
      DisplayList(fingerList, 5);
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
        newPosition += deltaEncoder * 3 - deltaEncoder/abs(deltaEncoder);
        if(newPosition < fingers[page - 5].minValue)
          newPosition = fingers[page - 5].minValue;
        if(newPosition < fingers[page - 5].maxValue)
          newPosition < fingers[page - 5].maxValue;
        MoveFinger(newPosition, page - 5);
      }
      clearLCD();
      addToLCD(0,0, "Finger " + (String)(page - 4) + ": " + (String)(fingers[page - 5].currentPosition));
    }
  }
  deltaEncoder = 0;
}

void moveToMenu(int _menu)
{
  beenClick = false;
  beenHold = false;
  deltaEncoder = 0;
  menu = _menu;
  page = 0;
  ManageUI();
}

void DisplayList(String items[], int numOfItems)
{
  if(deltaEncoder != 0)
    {
      page += deltaEncoder;
      if(page < 0)
        page = 0;
      if(page >= numOfItems)
        page = numOfItems - 1;
      deltaEncoder = 0;
    }
    clearLCD();
    addToLCD(0,0, ">" + items[page]);
    if(page + 1 < numOfItems)
    {
      addToLCD(0,1," " + items[page + 1]);
    } 
}

void isr ()  {
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
