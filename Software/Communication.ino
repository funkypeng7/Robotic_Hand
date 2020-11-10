byte data[2] = {0,0};
int index;

void HandleSerial()
{
  if(connectionType == 1 && analogRead(A6) > 500 && BTSerial.available() > 0)
  {
      while(BTSerial.available() > 0)
      {
        Serial.println("Got BT");
        AddToBuffer(BTSerial.read());
      }
  }
  else if(connectionType == 0 && Serial.available() > 0)
  {
    byte incomingByte = Serial.read();
    if(incomingByte > 15)
    {
      while(Serial.available() > 0)
      {
        incomingByte = Serial.read();
      }
    }
    
    ActOnByte(incomingByte, currentFinger);
    
  }
}

void ActOnByte(byte incomingByte, int finger)
{
  if(allowControl)
  {
    if((short)incomingByte < 15)
    {
      OptionsHandler((char)incomingByte);
    }
    else 
    {
      MoveFinger((short)incomingByte - 15, finger);
    }
  }
}

void AddToBuffer(byte incomingByte)
{
  if(incomingByte == '\0' || index == 2)
  {
    index = 0;
    if(DataMatching && ( !BTSerial.available() > 0 || data[1] < 15))
    {
      ActOnByte(data[1], currentFinger);
    }
  }
  else
  {
    data[index] = incomingByte;
    index++;
  }
  
  
}

void SetBLEName(String name)
{
  BTSerial.print("AT+NAME" + name);
}

bool DataMatching()
{
  return (data[0] == data[1]);
}
