void CheckForInteraction()
{
  beenClick = false;
  beenHold = false;
  beenReturnHold = false;
  
  if(lockArduino)
    return;
    
  if(!digitalRead(5) && !hasBeenDown)
  {
    lastInteraction = millis();
    holdStartTime = millis();
    hasBeenDown = true;
  }

  if(!digitalRead(5) && millis() - holdStartTime > ReturnTime)
  {
    lastInteraction = millis();
    if(!digitalRead(5) && millis() - holdStartTime > MainMenuReturnTime)
    {
      beenReturnHold = true;
    }
    beenHold = true;
  }
  
  if(digitalRead(5) && hasBeenDown)
  {
    lastInteraction = millis();
    hasBeenDown = false;
    if(millis() - holdStartTime > MainMenuReturnTime)
    {
      hasBeen = false;
      MoveToMenu(0);
    }
    else if(millis() - holdStartTime > ReturnTime)
    {
      Return();
    }
    else
    {
      beenClick = true;
    }
    
  }
//  CheckTimeout();
  
}

//void CheckTimeout()
//{
//  if(menu != 1 && millis() - lastInteraction > 20000)
//  {
//    MoveToMenu(1);
//  }
//}

void MoveToMenu(byte _menu)
{
  beenClick = false;
  beenHold = false;
  deltaEncoder = 0;
  menu = _menu;
  page = 0;
  connectionType = 4;
  allowControl = true;
  ManageUI();
}

void MoveToMenu(byte _menu, byte _page)
{
  beenClick = false;
  beenHold = false;
  deltaEncoder = 0;
  menu = _menu;
  page = _page;
  connectionType = 4;
  allowControl = true;
  ManageUI();
}

void Return()
{
  switch(menu)
  {
    case 2:
      if(page < numOfConnections)
        MoveToMenu(0,1);
      else
      {
        page -= numOfConnections;
        connectionType = 4;
      }
      break;
    case 3:
      if(page < 6)
        MoveToMenu(0, 2);
      else
        page -= 6;
      break;
    case 4: 
      MoveToMenu(0,3);
      break;
    case 5:
      if(page < numOfCOptions)
        MoveToMenu(4);
      else if(page < numOfCOptions + 5)
        page = setting;
      else if(page == 31)
        MoveToMenu(5, 4);
      else
        page -= 5;
      break;
    case 6:
      MoveToMenu(4, 1);
      break;
    case 7:
      if(page == 0)
        MoveToMenu(5, numOfCOptions - 1);
      break;
    default:
      MoveToMenu(0);
      break;
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
