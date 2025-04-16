// Define motor terminals to Board Pins
#define motorTerminal1 5
#define motorTerminal2 6

// Set initial pinMode type and stop motor
void clutchStartup()
{
  pinMode(motorTerminal1, OUTPUT);
  pinMode(motorTerminal2, OUTPUT);
  digitalWrite(motorTerminal1, LOW);
  digitalWrite(motorTerminal2, LOW);
}

// Set pin status to allow current flow
void clutchEngage()
{
  clutchState = 1;
  digitalWrite(motorTerminal1, HIGH);
  digitalWrite(motorTerminal2, LOW);
  clutchIsEngaging = true;
  if(setTime(2000, 4))                            // Note: Time has to be less than engine setTime so clutch doesn't engage while it is disengaging.
  {
    clutchHold();
    engineIsRunning = true;
    clutchIsEngaging = false;
    Serial.println("\n CLUTCH ENGAGED \n");
    Timer[4] = 0;
  }
}

void clutchDisengage()
{
  clutchState = 2;
  digitalWrite(motorTerminal1, LOW);
  digitalWrite(motorTerminal2, HIGH);
  clutchIsDisengaging = true;
  if(setTime(2000, 5))                            // Note :Time has to be less than engine setTime so clutch doesn't disengage while it is engaging.
  {
    clutchHold();
    engineIsRunning = false;
    clutchIsDisengaging = false;
    Serial.println("\n CLUTCH DISENGAGED \n");
    Timer[5] = 0;
  }
}

void clutchHold()
{
  clutchState = 0;
  digitalWrite(motorTerminal1, LOW);
  digitalWrite(motorTerminal2, LOW);
}

void clutchCheck()
{
  if (clutchState == 0)         // Stop the clutch cable motor and hold position (Worm gear hold)
  {
    clutchHold();
  }
  else if (clutchState == 1)    // Engage the clutch by rotating motor 
  {
    clutchEngage();
  }
  else if (clutchState == 2)    // Disengage the clutch by rotating motor in the other direction
  {
    clutchDisengage();
  }
}