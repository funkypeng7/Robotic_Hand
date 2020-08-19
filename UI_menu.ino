int menu = 0;
int page = 0;

unsigned long holdStartTime;
bool hasBeenDown;
bool beenClick, beenHold;

//Menu and Page Data
const String menus[] = {"Main Menu", "Connection Type", "Manual Control"};

//Menu 1
bool stateToDecide = false;
//Menu 2 - Manual Control
int selectedFinger;

void CheckForInteraction()
{
//  if(digitalRead(5))
//  {
//    fingers[2].currentPosition = 240;
//    servoPulse[2] = pulseWidth(240, currentFinger);
//  }
//  else
//  {
//    fingers[2].currentPosition = 0;
//    servoPulse[2] = pulseWidth(0, currentFinger);
//  }
  
  beenClick = false;
  beenHold = false;
  
  if(!digitalRead(5) && !hasBeenDown)
  {
    holdStartTime = millis();
    hasBeenDown = true;
  }

  if(digitalRead(5) && hasBeenDown)
  {
    hasBeenDown = false;
    if(millis() - holdStartTime > 500)
    {
      beenHold = true;
      Serial.println("Hold");
    }
    else
    {
      beenClick = true;
      Serial.println("Click");
    }
  }
}

void ManageUI()
{
  if(menu == 0)
  {
    if(beenClick)
    {
      beenClick = false;
      menu = 1;
      page = 0;
      stateToDecide = bluetoothConnection;
      ManageUI();
      return;
    }
    clearLCD();
    addToLCD(0,0, "1: " + (String)fingers[0].currentPosition + " 2: " + (String)fingers[1].currentPosition + " 3: " + (String)fingers[2].currentPosition);
    addToLCD(0,1, "4: " + (String)fingers[3].currentPosition + " 5: " + (String)fingers[4].currentPosition);
    if(bluetoothConnection)
      addToLCD(15,1, "B");
    else
      addToLCD(15,1, "S");
  }
  else if(menu == 1)
  {
    
  }








  
  else if(menu == 1)
  {
    if(beenClick)
    {
      beenClick = false;
      bluetoothConnection = stateToDecide;
      menu = 2;
      page = 0;
      ManageUI();
      return;
    }
    if(beenHold)
    {
      beenHold = false;
      bluetoothConnection = stateToDecide;
      menu = 0;
      page = 0;
      ManageUI();
      return;
    }
    for(int i = 0; i < abs(deltaEncoder); i++)
    {
      stateToDecide = !stateToDecide;
    }
    deltaEncoder = 0;

    clearLCD();
    if(stateToDecide)
    {
      addToLCD(0,0, "Bluetooth");
    }
    else
    {
      addToLCD(0,0, "Serial");
    }
    
  }

  
  deltaEncoder = 0;
}

void moveToMenu(int selectedMenu)
{
  beenClick = false;
  beenHold = false;
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
    dataChanged = true;
  }
  // Keep track of when we were here last (no more than every 5ms)
  lastInterruptTime = interruptTime;
}
