unsigned long pM = 0;
const long intervalM = 1000;

void debugTimer()
{
  unsigned long cM = millis();
  if (cM - pM >= intervalM) 
  {
    pM = cM;
    debugging();
    debuggingESP32();
  }
}

void debugging()
{
  // speedLever - Maneta Viteza
  // /*
  Serial.print("speedLever    ");
  Serial.print("Analog Value: ");
  Serial.print(analogRead(speedLever));
  Serial.print("  speedLeverARFunc(): ");
  Serial.print(speedLeverARFunc());
  Serial.print("  speedLeverDCFunc(): ");
  Serial.println(speedLeverDCFunc());
  // */

  // digipot
  // /*
  Serial.print("digipot       ");
  Serial.print("Position: ");
  Serial.print(digipot.getPosition());
  Serial.print("  Resistance: ");
  Serial.print(digipot.getOhm());
  Serial.println(" Ω");
  // */

  // MPU6050
  // /*
  Serial.print("Angles        ");
  Serial.print("X: ");
  Serial.print(mpu.getAngleX());
  Serial.print("   Y: ");
  Serial.print(mpu.getAngleY());
  Serial.print("   Z: ");
  Serial.println(mpu.getAngleZ());
  // */

  // Tachometer
  // /*
  Serial.print("Tachometer    ");
  Serial.print(RPM);
  Serial.println(" RPM");
  // */
  
  // eSwitch
  //
  Serial.print("Switches      ");
  Serial.print("Engine Switch: ");
  Serial.print(digitalRead(7));
  Serial.print("  Charging Switch: ");
  Serial.print(digitalRead(4));
  Serial.print("  Electric Motor Switch: ");
  Serial.println(digitalRead(3));
  //

  // engine
  //
  Serial.print("engine        ");
  Serial.print("State: ");
  Serial.println(engine);
  //

  // clutch
  //
  Serial.print("clutch        ");
  Serial.print("State: ");
  Serial.print(engine);
  Serial.print("  Engaging: ");
  Serial.print(debugEngaging);
  Serial.print("  Disengaging: ");
  Serial.println(debugDisengaging);
  //

  // Current and Voltage Modules
  Serial.print("Current Sensor Value: ");
  Serial.println(currentSensorValue);
  Serial.print("Voltage Sensor Value: ");
  Serial.println(voltmeterValue);
  //

  Serial.println(startMillis[0]); // Don't know why this is here
  Serial.println();

  if (mpuFailed == true)
  {
    Serial.println("MPU6050 Initialization Fail!");
  }
}

void debuggingESP32()
{
  String output = "";
  output += "                                                                   \n";
  // speedLever - Maneta Viteza
  output += "\n\n\nspeedLever    ";
  output += "Analog Value: ";
  output += String(analogRead(speedLever));
  output += "  speedLeverARFunc(): ";
  output += String(speedLeverARFunc());
  output += "  speedLeverDCFunc(): ";
  output += String(speedLeverDCFunc());
  output += "\n";

  // digipot
  output += "digipot       ";
  output += "Position: ";
  output += String(digipot.getPosition());
  output += "  Resistance: ";
  output += String(digipot.getOhm());
  output += " Ω\n";

  // MPU6050
  output += "Angles        ";
  output += "X: ";
  output += String(mpu.getAngleX());
  output += "   Y: ";
  output += String(mpu.getAngleY());
  output += "   Z: ";
  output += String(mpu.getAngleZ());
  output += "\n";

  // Tachometer
  output += "Tachometer    ";
  output += String(RPM);
  output += " RPM\n";

  // eSwitch
  output += "Switches      ";
  output += "Engine Switch: ";
  output += String(digitalRead(7));
  output += "  Charging Switch: ";
  output += String(digitalRead(4));
  output += "  Electric Motor Switch: ";
  output += String(digitalRead(3));
  output += "\n";

  // engine
  output += "engine        ";
  output += "State: ";
  output += String(engine);
  output += "\n";

  // clutch
  output += "clutch        ";
  output += "State: ";
  output += String(engine);
  output += "  Engaging: ";
  output += String(debugEngaging);
  output += "  Disengaging: ";
  output += String(debugDisengaging);
  output += "\n";

  // Current and Voltage Modules
  output += "Current Sensor Value: ";
  output += String(currentSensorValue, 2); // Assuming you want 2 decimal places
  output += "\n";
  output += "Voltage Sensor Value: ";
  output += String(voltmeterValue, 2); // Assuming you want 2 decimal places
  output += "\n";

  if (mpuFailed == true)
  {
    output += "MPU6050 Initialization Fail!\n";
  }

  // Send output to Serial1 (Arduino Mega)
  Serial1.print(output);
}

void debuggingESP32Old()
{
  // speedLever - Maneta Viteza
  // /*
  Serial1.print("speedLever    ");
  Serial1.print("Analog Value: ");
  Serial1.print(analogRead(speedLever));
  Serial1.print("  speedLeverARFunc(): ");
  Serial1.print(speedLeverARFunc());
  Serial1.print("  speedLeverDCFunc(): ");
  Serial1.println(speedLeverDCFunc());
  // */

  // digipot
  // /*
  Serial1.print("digipot       ");
  Serial1.print("Position: ");
  Serial1.print(digipot.getPosition());
  Serial1.print("  Resistance: ");
  Serial1.print(digipot.getOhm());
  Serial1.println(" Ω");
  // */

  // MPU6050
  // /*
  Serial1.print("Angles        ");
  Serial1.print("X: ");
  Serial1.print(mpu.getAngleX());
  Serial1.print("   Y: ");
  Serial1.print(mpu.getAngleY());
  Serial1.print("   Z: ");
  Serial1.println(mpu.getAngleZ());
  // */

  // Tachometer
  // /*
  Serial1.print("Tachometer    ");
  Serial1.print(RPM);
  Serial1.println(" RPM");
  // */
  
  // eSwitch
  //
  Serial1.print("Switches      ");
  Serial1.print("Engine Switch: ");
  Serial1.print(digitalRead(7));
  Serial1.print("  Charging Switch: ");
  Serial1.print(digitalRead(4));
  Serial1.print("  Electric Motor Switch: ");
  Serial1.println(digitalRead(3));
  //

  // engine
  //
  Serial1.print("engine        ");
  Serial1.print("State: ");
  Serial1.println(engine);
  //

  // clutch
  //
  Serial1.print("clutch        ");
  Serial1.print("State: ");
  Serial1.print(engine);
  Serial1.print("  Engaging: ");
  Serial1.print(debugEngaging);
  Serial1.print("  Disengaging: ");
  Serial1.println(debugDisengaging);
  //

  // Current and Voltage Modules
  Serial1.print("Current Sensor Value: ");
  Serial1.println(currentSensorValue);
  Serial1.print("Voltage Sensor Value: ");
  Serial1.println(voltmeterValue);
  //

  Serial1.println(startMillis[0]); // Don't know why this is here
  Serial1.println();

  if (mpuFailed == true)
  {
    Serial1.println("MPU6050 Initialization Fail!");
  }
}
