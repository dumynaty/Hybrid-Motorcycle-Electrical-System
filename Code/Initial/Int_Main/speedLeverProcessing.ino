int speedLeverARFunc() // Return the value of the speedLever Analog Reading adjusted from 175, 878 to 0, 1023
{
  int x = analogRead(speedLever);
  x = map(x, 175, 878, 0, 1023);
  x = constrain(x, 0, 1023);
  return x;
}

int speedLeverDCFunc() // Return the value of the speedLever Duty Cycle adjusted for 0, 99
{
  int x = speedLeverARFunc();
  x = map(x, 0, 1023, 0, 99);
  return x;
}