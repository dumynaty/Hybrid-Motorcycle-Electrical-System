unsigned long startTimeEngine;
unsigned long stopTimeEngine;
bool resetRunStart = false;
bool resetRunStop = false;

// Previously declared here: bool passing = false;

void engineStart()
{
  if (RPM >= 150 && engineIsRunning == false)   // If RPM / speed > threshold // and mpu.Angle(Y/Z) < 30 to not start the motor if just going downhill for a short while
  {
    if (resetRunStart == false)                           // Start timer
    {
      startTimeEngine = millis();
      resetRunStart = true;
    }
    if (millis() - startTimeEngine > 5000)                // If 5 seconds passed with RPM being > threshold then allow the clutch to engage
    {
      switchingToEngine = true;
      clutchState = 1;                                         // Prepare variable for clutchEngage() Function
    }
  }
  else if (RPM < 150 && engineIsRunning == false)
  {
    resetRunStart = false;
  }
}

void engineStop()
{
  if (RPM < 150 && engineIsRunning == true)   // If RPM / speed < threshold
  {
    if (resetRunStop == false)
    {
      stopTimeEngine = millis();
      resetRunStop = true;
    }
    if (millis() - stopTimeEngine > 5000)
    {
      clutchState = 2;                                         // Prepare variable for clutchDisengage() Function
    }
  }
  else if (RPM >= 150 && engineIsRunning == true)
  {
    resetRunStop = false;
  }

  if (RPM < 150 && speedLeverDCFunc() < 15 && engineIsRunning == true)
  {
    clutchState = 2;                                           // Prepare variable for clutchDisengage() Function when speedLever is really low and running shouldd be on electric.
  }
}

void electricDecrease()
{
  // Starting engine Code // 
  if (switchingToEngine == true)
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
      switchingToEngine = false;
      Serial.println("Digipot reached 0, passing complete!");
    }
  }
}

void engineRun()
{
  engineStop();
  if (mpu.getAngleX() < -60 || mpu.getAngleX() > 60)    // If fallen
  {
    // Bring servoMotor to 0 position, set the digital potentiometer to 0, stop charging, kill engine and kill dc motor
    servoMotor.write(0);
    setDigipotPosition(0);
    SwitchesOFF();

    Serial.println(" * Gyro sensor status: Fallen * ");
    while (speedLeverARFunc() > 200)
    { /* After falling keep speed 0 until speedLever has been readjusted to low level */ }
  }
  else                                                  // If sitting straight
  {
    servoSpeedFunc();                                   // Set position of servo to set the speed of engine
  }
}