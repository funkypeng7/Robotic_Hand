byte whichDemo;
//                                                      Open                                              Rock on                                     Horns                                     Shaaka                                              Open                                Indivdual fingers down
const byte gesturesPositions[][5] =  {{255, 255, 255, 255, 255}, {255, 255, 255, 255, 255}, {255, 0, 0, 255, 255}, {255, 0, 0, 255, 255}, {255, 0, 0, 255, 0}, {255, 0, 0, 255, 0}, {255, 0, 0, 0, 255}, {255, 0, 0, 0, 255}, {255, 255, 255, 255, 255}, {255, 255, 255, 255, 255}, {0, 255, 255, 255, 255}, {255, 0, 255, 255, 255}, {255, 255, 0, 255, 255}, {255, 255, 255, 0, 255}, {255, 255, 255, 255, 0}, {255, 255, 255, 255, 255}  };
const byte numOfPositions = 15;

// Max time in millis is 4000          open  rock on    horns      shaaka     open        1    2    3    4    5   open
unsigned short gesturesTimeToo[] = {0, 1000, 750, 1500, 750, 1500, 750, 1500, 750, 500, 1000, 1000, 1000, 1000, 1000, 500};
volatile byte hold; 
volatile short currentPosition = 0;


void Demo()
{
  if(currentPosition == 0)
  {
    TCNT1 = 0;
    currentPosition++;
  }
  if(currentPosition > numOfPositions)
  {
    TCNT1 = 0;
    currentPosition = 1;
  }
  unsigned short timer1Millis = floor(TCNT1/15.625f);
  if(timer1Millis > gesturesTimeToo[currentPosition])
  {
    currentPosition++;
    TCNT1 = 0;
    Demo();
    return;
  }
  for(int finger = 0; finger < 5; finger++)
  {
    if(whichDemo == 0)
    {
      MoveFinger(floor(map(timer1Millis, 0, gesturesTimeToo[currentPosition], gesturesPositions[currentPosition - 1][finger] , gesturesPositions[currentPosition][finger] )), finger);
      ClearLCD();
      AddToLCD(0,0, F("Gestures"));
    }
  }
}

//Timer 1 - 15,625 every second (with 1024 prescaler)
void InitTimer1()
{
  cli();
  
  // Normal opperation
  TCCR1A = 0;
  TCCR1B = 0;
  
  // Set 1024 prescaler
  TCCR1B = (1 << CS12);
  TCCR1B |= (1 << CS10);
  
  // Enable overflow interupt
  TIMSK1 |= (1 << TOIE1);
  sei();
}

ISR(TIMER1_OVF_vect)
{
  currentPosition++;
}
