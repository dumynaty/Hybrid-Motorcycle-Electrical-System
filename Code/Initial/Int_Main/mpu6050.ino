void mpuStartup()               // Initialize MPU6050 Sensor
{
  Wire.begin();
  byte status = mpu.begin();
  if (status != 0) 
  { mpuFailed = true; }
  delay(1000);
  mpu.calcOffsets();
  mpu.update();                 // Function to call for update, mpu.getAngleZ() - Angle data
}