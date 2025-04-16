//If given input for set duration, store the current time value and check if time elapsed for each index
int indexChange[100] = {0};


bool setTime(unsigned long duration, int index) 
{
  unsigned long currentMillis = millis();
  if (indexChange[index] == 0)
  {
    startMillis[index] = currentMillis;
    indexChange[index] = 1;
  }

  if (currentMillis - startMillis[index] >= duration) 
  {
    indexChange[index] = 0;
    startMillis[index] = currentMillis;
    return true;
  }
  return false;
}