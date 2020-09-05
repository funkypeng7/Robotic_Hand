void MoveFinger(short value, int finger)
{
  if(value < fingers[finger].minValue)
    value = fingers[finger].minValue;
  else if(value > fingers[finger].maxValue)
    value = fingers[finger].maxValue;

  fingers[finger].currentPosition = value;
  
  if(fingers[finger].reverse)
  {
    value = fingers[finger].maxValue - value;
  }
  servoPulse[finger] = pulseWidth(value, finger);
}

int pulseWidth(int value, int finger)
{
  int pulse_wide, analog_value;
  pulse_wide = map(value, 0, 244, fingers[finger].minPulse, fingers[finger].maxPulse);
  analog_value = int(float(pulse_wide) / 1000000 * 50 * 4096);
  return analog_value;
}

void checkServoPulse()
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
