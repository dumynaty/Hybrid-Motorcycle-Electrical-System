// Voltage Sensor
// Analog pin 2
int offset = 20;

void getVoltage() 
{
  int volt = analogRead(A2); // Read the input
  double voltage = map(volt, 0, 1023, 0, 2500) + offset; // Map 0-1023 to 0-2500 and add correction offset
  voltage /= 100; // Divide by 100 to get the decimal values
  voltmeterValue = voltage;
}

// Current Sensor
#define VIN A1 // Define the Arduino pin A0 as voltage input (V in)
const float VCC = 5.0; // Supply voltage is from 4.5 to 5.5V. Normally 5V.
const int model = 2;   // Value for 30A module
float cutOffLimit = 1.01;
float sensitivity[] = {
          0.185,
          0.100,
          0.066
};
const float QOV = 0.5 * VCC; // Set quiescent Output voltage of 0.5V
float voltage; // Internal variable for voltage


void readCurrentSensor() 
{
    float voltage_raw = (5.0 / 1023.0) * analogRead(VIN); // Read the voltage from sensor
    voltage = voltage_raw - QOV + 0.012; // 0.012 is a value to make voltage zero when there is no current
    currentSensorValue = voltage / sensitivity[model];
}

// Temperature Sensor
