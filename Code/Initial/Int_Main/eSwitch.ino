void switchesFunction()
{
  if (eSwitchValue == 11)
  {
    SwitchElectric();
  }
  if (eSwitchValue == 12)
  {
    SwitchTrecere();
  }
  if (eSwitchValue == 13)
  {
    SwitchTermic();
  }
  if (eSwitchValue == 14)
  {
    SwitchIncarcare();
  }
  if (eSwitchValue == 10)
  {
    SwitchDecuplare();
  }
}

void SwitchElectric()
{
  digitalWrite(eSwitchTermic, LOW);
  digitalWrite(eSwitchIncarcare, LOW);
  digitalWrite(eSwitchElectric, HIGH);
}

void SwitchTrecere()
{
  digitalWrite(eSwitchTermic, HIGH);
  digitalWrite(eSwitchIncarcare, LOW);
  digitalWrite(eSwitchElectric, HIGH);
}

void SwitchTermic()
{
  digitalWrite(eSwitchTermic, HIGH);
  digitalWrite(eSwitchIncarcare, LOW);
  digitalWrite(eSwitchElectric, LOW);
}

void SwitchIncarcare()
{
  digitalWrite(eSwitchTermic, HIGH);
  digitalWrite(eSwitchIncarcare, HIGH);
  digitalWrite(eSwitchElectric, LOW);
}


void SwitchDecuplare()
{
  digitalWrite(eSwitchIncarcare, LOW);
  digitalWrite(eSwitchTermic, LOW);
  digitalWrite(eSwitchElectric, LOW);
}