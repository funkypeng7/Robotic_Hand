const short timeTillHold = 500;
unsigned long timeSinceMinPos[5] = {0,0,0,0,0};

byte fingersBelowMin = 0;
byte fingersHeld = 0;

#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


void MoveFinger(short value, byte finger)
{
  if(value < fingers[finger].minValue)
    value = fingers[finger].minValue;
  else if(value > fingers[finger].maxValue)
    value = fingers[finger].maxValue;

  if(value < fingers[finger].holdPosition)
  {
    if(!BIT_CHECK(fingersBelowMin, finger))
    {
      BIT_SET(fingersBelowMin, finger);
      timeSinceMinPos[finger] = millis();
      value = fingers[finger].minValue;
    }
    else
    {
      return;
    }
  }
  else if(value > fingers[finger].holdPosition)
  {
    BIT_CLEAR(fingersBelowMin, finger);
    BIT_CLEAR(fingersHeld, finger);
  }
  

  fingers[finger].currentPosition = value;
  
  if(fingers[finger].reverse)
  {
    value = fingers[finger].maxValue - value;
  }
  servoPulse[finger] = PulseWidth(value, finger);
}

void CheckServosHoldPosition()
{
  for(int i = 0; i < 5; i++)
  {
    if(BIT_CHECK(fingersBelowMin, i) && !BIT_CHECK(fingersHeld, i) && millis() > timeSinceMinPos[i] + timeTillHold)
    {
      BIT_SET(fingersHeld, i);
      MoveFinger(fingers[i].holdPosition, i);
    }
  }
}

void MoveFinger(short value, byte finger, bool noHoldPos)
{
  if(value < 0)
    value = 0;
  else if(value > fingers[finger].maxValue)
    value = fingers[finger].maxValue;

  fingers[finger].currentPosition = value;
  
  if(fingers[finger].reverse)
  {
    value = fingers[finger].maxValue - value;
  }
  servoPulse[finger] = PulseWidth(value, finger);
}

int PulseWidth(int value, int finger)
{
  int pulse_actual, analog_value;
  // Get the wanted Pulse length (in millisecconds)
  pulse_actual = map(value, 0, 244, fingers[finger].minPulse, fingers[finger].maxPulse);
  // Convert to a duty cycle
  analog_value = int(float(pulse_actual) / 1000000 * 50 * 4096);
  return analog_value;
}

void CheckServoPulse()
{
  for(int i = 0; i < 5; i++)
  {
    if(servoPulse[i] != actualServoPulse[i])
    {
      servos.setPWM(i, 0 , servoPulse[i]);
      actualServoPulse[i] = servoPulse[i];
    }
  }
}
