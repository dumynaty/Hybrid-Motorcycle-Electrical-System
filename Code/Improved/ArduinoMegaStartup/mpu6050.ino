void mpu6050Startup()
{
  Wire.begin();
  byte status = mpu.begin();
  if (status != 0) 
  { mpuFailed = true; }
  mpu.calcOffsets();
  mpu.update();
  // mpu.update() - Request sensor update
  // mpu.getAngleZ() - Request angle data
}