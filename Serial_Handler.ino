byte data[2] = {0,0};
int index;

void handleSerial()
{
  if(bluetoothConnection && analogRead(A6) > 500 && BTSerial.available() > 0)
  {
      while(BTSerial.available() > 0)
      {
        AddToBuffer(BTSerial.read());
      }
  }
  else if(!bluetoothConnection && Serial.available() > 0)
  {
    byte incomingByte = Serial.read();
    if(incomingByte > 15)
    {
      while(Serial.available() > 0)
      {
        incomingByte = Serial.read();
      }
    }
    
    ActOnByte(incomingByte);
    
  }
}

void ActOnByte(byte incomingByte)
{
  if((short)incomingByte < 15)
    {
      OptionsHandler((char)incomingByte);
    }
    else 
    {
      MoveFinger((short)incomingByte - 15);
    }

}

void AddToBuffer(byte incomingByte)
{
  Serial.println((int)incomingByte);
  if(incomingByte == '\0' || index == 2)
  {
    index = 0;
    if(DataMatching && ( !BTSerial.available() > 0 || data[1] < 15))
    {
      Serial.println(data[1]);
      ActOnByte(data[1]);
    }
  }
  else
  {
    data[index] = incomingByte;
    index++;
  }
  
  
}

bool DataMatching()
{
  return (data[0] == data[1]);
}
