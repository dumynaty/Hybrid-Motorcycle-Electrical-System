void servoStartup() 
{
  servoMotor.attach(11); // Define servo Pin
  servoMotor.write(0);
}

void servoSpeedFunc() 
{
  if (engine == true)
  {
    int servoCurrentPosition = servoMotor.read();
    int servoNextPosition = map(speedLeverDCFunc(), 0, 99, 0, 180);
    if (servoNextPosition > servoCurrentPosition)       // If the speedLever wants to accelerate add +1 degree to the servoMotor each setTime(x, 2) ms
    {
      if (setTime(75, 2))
      {
        servoMotor.write(++servoCurrentPosition);
      }
    }
    else
    {
      servoMotor.write(servoNextPosition);              // If the speedLever wants to decelerate then decrease the angle of the Servo to the speedLever value 
    }
  }
}