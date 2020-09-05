//Arangement in EEPROM is
//Byte 1: Wether to retreive or wipe settings bool
//Byte 2 onwards: 5 x Finger(Reverse (1), MinPulse(2), MaxPulse(2), MinValue(1), MaxValue(1))
//

void saveToEEPROM()
{
  EEPROM.put(1, fingers);
}

void retreiveFromEEPROM()
{
  if(EEPROM.read(0) == 1)
  {
    saveToEEPROM();
    EEPROM.write(0,0);
  }
  else
    EEPROM.get(1, fingers);
}
