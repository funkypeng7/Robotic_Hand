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
