// Digipot Initialization
const int INC_PIN = 8;
const int UD_PIN = 9;
const int CS_PIN = 10;
// END ---

void digipotStartup()
{
  digipot.begin(INC_PIN, UD_PIN, CS_PIN);
  setDigipotPosition(99);
  setDigipotPosition(0);
}


void digipotFunc()
{
  if (mpu.getAngleX() < -60 || mpu.getAngleX() > 60)                                            // If fallen
  {
    setDigipotPosition(0); // Decrease electric motor speed to 0
    while (speedLeverARFunc() > 200)
    {
      Serial.println("FALLEN!!!"); /* After falling keep speed 0 until speedLever has been readjusted to low level */ }
  } 
  else                                                                                          // If sitting straight
  {
    int targetPosition = speedLeverDCFunc();
    int digipotCurrentPosition = digipot.getPosition();

    if (targetPosition > digipotCurrentPosition)                        // If the speedLever wants to accelerate add +1 duty cycle to the electric motor each setTime(x, 3) ms
    {
      if (setTime(75, 3))
      {
        setDigipotPosition(++digipotCurrentPosition);
      }
    }
    else
    {
      setDigipotPosition(targetPosition);
    }
  }
}


void setDigipotPosition(int targetPosition)
{
  int currentPosition = digipot.getPosition();
  int steps = targetPosition - currentPosition;

  if (steps > 0)
  {
    for (int i = 0; i < steps; i++)
    {
      digipot.incr();
    }
  } 
  else if (steps < 0) 
  {
    for (int i = 0; i < -steps; i++) 
    {
      digipot.decr();
    }
  }
}