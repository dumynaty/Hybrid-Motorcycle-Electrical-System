#define motorTerminal1 5
#define motorTerminal2 6


void clutchStartup()
{
  pinMode(motorTerminal1, OUTPUT);
  pinMode(motorTerminal2, OUTPUT);
  digitalWrite(motorTerminal1, LOW);
  digitalWrite(motorTerminal2, LOW);
}

void clutchEngage()
{
  clutch = 1;
  digitalWrite(motorTerminal1, HIGH);
  digitalWrite(motorTerminal2, LOW);
  debugEngaging = true;
  if(setTime(2000, 4))                            // Time has to be less than engine setTime so clutch doesn't engage while it is disengaging.
  {
    clutchHold();
    engine = true;
    debugEngaging = false;
    Serial.println("\n CLUTCH ENGAGED \n");
    startMillis[4] = 0;
  }
}

void clutchDisengage()
{
  clutch = 2;
  digitalWrite(motorTerminal1, LOW);
  digitalWrite(motorTerminal2, HIGH);
  debugDisengaging = true;
  if(setTime(2000, 5))                            // Time has to be less than engine setTime so clutch doesn't disengage while it is engaging.
  {
    clutchHold();
    engine = false;
    debugDisengaging = false;
    Serial.println("\n CLUTCH DISENGAGED \n");
    startMillis[5] = 0;
  }
}

void clutchHold()
{
  clutch = 0;
  digitalWrite(motorTerminal1, LOW);
  digitalWrite(motorTerminal2, LOW);
}

void clutchCheck()
{
  if (clutch == 0)                    // Stop the motor and hope to hold
  {
    clutchHold();
  }
  else if (clutch == 1)               // Engage the clutch by rotating motor 
  {
    clutchEngage();
  }
  else if (clutch == 2)               // Disengage the clutch by rotating motor in the other direction
  {
    clutchDisengage();
  }
}