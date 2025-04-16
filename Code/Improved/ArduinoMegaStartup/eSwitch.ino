void ApplyESwitchState()
{
  if (eSwitchState == 1)
  {
    SwitchElectric();
  }
  if (eSwitchState == 2)
  {
    SwitchSwitchingToEngine();
  }
  if (eSwitchState == 3)
  {
    SwitchEngine();
  }
  if (eSwitchState == 4)
  {
    SwitchCharging();
  }
  if (eSwitchState == 0)
  {
    SwitchesOFF();
  }
}

void SwitchElectric()
{
  digitalWrite(eSwitchEngine, LOW);
  digitalWrite(eSwitchCharging, LOW);
  digitalWrite(eSwitchElectricMotor, HIGH);
}

void SwitchSwitchingToEngine()
{
  digitalWrite(eSwitchEngine, HIGH);
  digitalWrite(eSwitchCharging, LOW);
  digitalWrite(eSwitchElectricMotor, HIGH);
}

void SwitchEngine()
{
  digitalWrite(eSwitchEngine, HIGH);
  digitalWrite(eSwitchCharging, LOW);
  digitalWrite(eSwitchElectricMotor, LOW);
}

void SwitchCharging()
{
  digitalWrite(eSwitchEngine, HIGH);
  digitalWrite(eSwitchCharging, HIGH);
  digitalWrite(eSwitchElectricMotor, LOW);
}


void SwitchesOFF()
{
  digitalWrite(eSwitchCharging, LOW);
  digitalWrite(eSwitchEngine, LOW);
  digitalWrite(eSwitchElectricMotor, LOW);
}