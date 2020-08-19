void OptionsHandler(char value)
{
   if(value < 6)
   {
      currentFinger = value - 1;
   }
   else
   {
      switch(value)
      {
        case 6:
          //Set Low Value
          fingers[currentFinger].minValue = fingers[currentFinger].currentPosition;
          break;
        case 7:
          //Set High Value
          fingers[currentFinger].maxValue = fingers[currentFinger].currentPosition;
          break;
        case 8:
          fingers[currentFinger].minValue = 0;
          fingers[currentFinger].maxValue = 244;
          break;
        case 9:
          fingers[currentFinger].absMaxPulse += 10;
          MoveFinger(255, currentFinger);
          break;
        case 10:
          fingers[currentFinger].absMaxPulse -= 10;
          MoveFinger(255, currentFinger);
          break;
        case 11:
          fingers[currentFinger].absMinPulse += 10;
          MoveFinger(0, currentFinger);
          break;
        case 12:
          fingers[currentFinger].absMinPulse -= 10;
          MoveFinger(0, currentFinger);
          break;
      }
   }
}
