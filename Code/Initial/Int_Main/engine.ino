unsigned long startTimeEngine;
unsigned long stopTimeEngine;
bool resetRunStart = false;
bool resetRunStop = false;

// Previously declared here: bool passing = false;

void engineStart()
{
  if (RPM >= 150 && engine == false)   // If RPM / speed > threshold // and mpu.Angle(Y/Z) < 30 to not start the motor if just going downhill for a short while
  {
    if (resetRunStart == false)                           // Start timer
    {
      startTimeEngine = millis();
      resetRunStart = true;
    }
    if (millis() - startTimeEngine > 5000)                // If 5 seconds passed with RPM being > threshold then allow the clutch to engage
    {
      passing = true;
      clutch = 1;                                         // Prepare variable for clutchEngage() Function
    }
  }
  else if (RPM < 150 && engine == false)
  {
    resetRunStart = false;
  }
}

void engineStop()
{
  if (RPM < 150 && engine == true)   // If RPM / speed < threshold
  {
    if (resetRunStop == false)
    {
      stopTimeEngine = millis();
      resetRunStop = true;
    }
    if (millis() - stopTimeEngine > 5000)
    {
      clutch = 2;                                         // Prepare variable for clutchDisengage() Function
    }
  }
  else if (RPM >= 150 && engine == true)
  {
    resetRunStop = false;
  }

  if (RPM < 150 && speedLeverDCFunc() < 15 && engine == true)
  {
    clutch = 2;                                           // Prepare variable for clutchDisengage() Function when speedLever is really low and running shouldd be on electric.
  }
}

void electricDecrease()
{
  // Starting engine Code // 
  if (passing == true)
  {
    int targetPosition = speedLeverDCFunc();
    if (targetPosition < digipot.getPosition()) // If the speedLever value is less than the digipot value, change the value of the digipot;
    {
      Serial.println("Decreasing Pot pot value to match speedLever during engine run!");
      setDigipotPosition(targetPosition);
    }

    if(digipot.getPosition() > 0)       // If the speedLever value is bigger than the digipot value but engine should be starting, decrease the digipot value by 1, every 500 ms
    {
      if(setTime(500, 0))
      {
        digipot.decr();
      }
    }
    else                                // If the electric motor duty cycle reached 0, starting of the engine is complete!
    {
      passing = false;
      Serial.println("Digipot reached 0, passing complete!");
    }
  }
}

void engineRun()
{
  engineStop();
  if (mpu.getAngleX() < -60 || mpu.getAngleX() > 60)    // If fallen
  {
    servoMotor.write(0);
    setDigipotPosition(0);
    Serial.println("Fallen!!!");
    SwitchDecuplare();                      // Stop the spark plug connection - add clutch motor to 0 to stop the engine 
    while (speedLeverARFunc() > 200)
    { /* After falling keep speed 0 until speedLever has been readjusted to low level */ }
  }
  else                                                  // If sitting straight
  {
    servoSpeedFunc();                                   // Set position of servo to set the speed of engine
  }
}