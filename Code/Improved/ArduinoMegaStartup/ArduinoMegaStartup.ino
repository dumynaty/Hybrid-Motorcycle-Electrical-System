// Timers Locations:
// Timer 0 - engine
// Timer 2 - servoSpeed
// Timer 3 - digipot
// Timer 4 - clutch
// Timer 5 - clutch
// Timer 6 - engine
// Timer 7 - Startup
// Timer 8 - Startup
// Timer 9 - Startup
// Timer 10 - Startup

#include <X9C10X.h> // Digipot Library
#include <Wire.h> // Wire library for SCA SDL
#include <MPU6050_light.h> // MPU6050 sensor Library
#include <Servo.h> // Servomotor Library

#define eSwitchElectricMotor 3
#define eSwitchEngine 7
#define eSwitchCharging 4

int speedLeverPin = A0; // Define the speedLeverPin pin to Arduino
Servo servoMotor; // Create servoMotor object
MPU6050 mpu(Wire); // Create MPU6050 Sensor object
bool mpuFailed = false; // Verification boolean for the MPU6050
X9C10X digipot(10000);  // Initialize the digipot with 10KΩ resistance

unsigned int RPM; // Define variable for RPM
bool engineIsRunning = false; // Engine running boolean
int clutchState = 0; // Set initial clutch state to 0. See clutch.ino for the 3 possible states
int eSwitchState = 1; // Set initial eSwitch state. See eSwitch.ino for the 5 possible states
bool switchingToEngine = false; // Define boolean for switching from DC motor to Engine
bool canChargeBattery = true; // Define boolean for the possibility of charging the battery

double voltmeterValue = 0;
float currentSensorValue;

bool clutchIsEngaging = false; // Boolean for engaging clutch
bool clutchIsDisengaging = false; // Boolean for disengaging clutch

unsigned long Timer[10] = {0}; // Initialize an array of Timer variables

void setup()
{
  // Set eSwitch pinmode to Output
  pinMode(eSwitchElectricMotor, OUTPUT);
  pinMode(eSwitchEngine, OUTPUT);
  pinMode(eSwitchCharging, OUTPUT);
  pinMode(speedLeverPin, INPUT);

  // Set Baud rate for Arduino and ESP
  Serial.begin(115200);
  Serial1.begin(115200);

  // Display start messsages
  Serial.println();
  Serial.println("Starting..");
  Serial2.println("Starting..");

  // Begin Initialization
  // Set inital E-Switches status On/Off
  SwitchElectric();
  // Set digipot position to 0
  digipotStartup();
  // Start MPU6050 sensor reading
  mpu6050Startup();
  // Start Interrupt for tachometer sensor
  tachometerStartup();
  // Initialize servoMotor
  servoStartup();

  // Display message when initialization has finished
  Serial.println("Setup complete!");
  Serial2.println("Setup Complete!");
}

void loop()
{
  voltmeterValue = getVoltage(); // Get voltmeter sensor voltage value
  debugTimer();                  // Send values to ESP32 and print them there
  ApplyESwitchState();            // Set the switches values
  mpu.update();                  // Update XYZ Angles from MPU6050 Sensor
  tachometer();                  // Update RPM from Tachometer

  if (eSwitchState == 1)         // Electric motor Run and check for Engine possibility to start
  {
    SwitchElectric();    
    digipotFunc();
    engineStart();
    if(switchingToEngine == true)
    {
      eSwitchState = 2;
      SwitchSwitchingToEngine();
    }
    if (clutchState == 0)
    {
      canChargeBattery = true;
    }
  }
  else if (eSwitchState == 2)     // Engage clutch and decrease electric motor digital pot value to 0
  {
    SwitchSwitchingToEngine();
    if (engineIsRunning == false) // If clutch isn't engaged yet, run on electric
    {
      digipotFunc();
    }
    clutchCheck();
    if (engineIsRunning == true) // If clutch is engaged start decreasing the electric motor power
    {
      eSwitchState = 3;
    }
  }
  else if (eSwitchState == 3)    // Run on engine
  {
    SwitchEngine();
    engineRun();
    electricDecrease();
    
    if (clutchState == 2)        // If speed is low and the clutch needs to disengage
    {
      clutchCheck();
      if (engineIsRunning == false)
      {
        eSwitchState = 1;
      }
    }

    if(switchingToEngine == false && canChargeBattery == true && voltmeterValue > 10)
    {
      if(setTime(10000, 9))
      {
        eSwitchState = 4;
      }
    }
  }
  else if (eSwitchState == 4)   // Charge battery and run on engine
  {
    SwitchCharging();
    engineRun();

    // If clutch will disengage cancel charging
    if (clutchState == 2)
    {
      canChargeBattery = false;
      clutchCheck();
      if (engineIsRunning == false)
      {
        eSwitchState = 1;
      }
    }
  }
  if (eSwitchState == 0)       // Shut every switch off
  {
    SwitchesOFF();
  }
}