void MoveFinger(short value)
{
  if(value < fingers[currentFinger].minValue)
    value = fingers[currentFinger].minValue;
  else if(value > fingers[currentFinger].maxValue)
    value = fingers[currentFinger].maxValue;
    
  fingers[currentFinger].currentPosition = value;
  servoPulse[currentFinger] = pulseWidth(value, currentFinger);
}

int pulseWidth(int value, int finger)
{
  int pulse_wide, analog_value;
  pulse_wide = map(value, 0, 244, fingers[finger].absMinPulse, fingers[finger].absMaxPulse);
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
