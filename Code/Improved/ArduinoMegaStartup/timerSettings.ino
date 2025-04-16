// If given input for set duration, store the current time value and check if time elapsed for each index
int indexChange[10] = {0};

bool setTime(unsigned long duration, int index) 
{
  unsigned long currentMillis = millis();
  if (indexChange[index] == 0)
  {
    Timer[index] = currentMillis;
    indexChange[index] = 1;
  }

  if (currentMillis - Timer[index] >= duration) 
  {
    indexChange[index] = 0;
    Timer[index] = currentMillis;
    return true;
  }
  return false;
}