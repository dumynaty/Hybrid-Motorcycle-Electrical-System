// Timer 0 - engine
// Timer 1 - DELETED
// Timer 2 - servoSpeed
// Timer 3 - digipot
// Timer 4 - clutch
// Timer 5 - clutch
// Timer 6 - engine
// Timer 7 - int_main
// Timer 8 - int_main
// Timer 9 - int_main
// Timer 10 - int_main
// Timer 20 - 
// Timer 21 -
// Timer 22 -
// Timer 23 -

#include <X9C10X.h> // Digipot Library
#include <Wire.h> // Wire library for SCA SDL
#include <MPU6050_light.h> // MPU6050 sensor Library
#include <Servo.h> // Servomotor Library

#define eSwitchElectric 3
#define eSwitchTermic 7
#define eSwitchIncarcare 4

Servo servoMotor;

int speedLever = A0; // The speedLever pin to Arduino
MPU6050 mpu(Wire); // Define MPU6050
bool mpuFailed = false;
X9C10X digipot(10000);  // Initialize the digipot with 10KΩ resistance

unsigned long RPM;

bool engine = false; // Initialize engine run variable

int clutch = 0;

int eSwitchValue = 0;

bool passing = false;

bool chargeP = true;

double voltmeterValue = 0;
float currentSensorValue;

bool debugEngaging = false;
bool debugDisengaging = false;

unsigned long startMillis[100] = {0};

void setup()
{
  pinMode(eSwitchElectric, OUTPUT);
  pinMode(eSwitchTermic, OUTPUT);
  pinMode(eSwitchIncarcare, OUTPUT);
  Serial.begin(115200);              // Changed Baud Rate
  Serial1.begin(115200);             // Start ESP32 communication through RX1 TX1 pins
  delay(100);
  Serial.println();
  Serial.println("Starting..");
  Serial2.println("Starting..");
  pinMode(speedLever, INPUT);
  eSwitchValue = 11;
  SwitchElectric();
  digipotStartup();
  mpuStartup();
  tachometerStartup();
  servoStartup();
  delay(100);
  Serial.println("Setup complete!");
  Serial2.println("Setup Complete!");
}

void loop()
{
  getVoltage();
  debugTimer();             // Send values to ESP32 and print them there
  switchesFunction();       // Set the switches values
  mpu.update();             // Update XYZ Angles from MPU6050 Sensor
  tachometer();             // Update RPM from Tachometer

  if (eSwitchValue == 11)               // Electric motor Run and check for Engine possibility to start
  {
    SwitchElectric();    
    digipotFunc();
    engineStart();
    if(passing == true)
    {
      eSwitchValue = 12;
      SwitchTrecere();
    }
    
  }
  else if (eSwitchValue == 12)          // Engage clutch and decrease electric motor digital pot value to 0
  {
    SwitchTrecere();
    if (engine == false)                // If clutch isn't engaged yet run on electric
    {
      digipotFunc();
    }
    clutchCheck();                      // clutchEngage(); returns engine = true;
    if (engine == true)                 // If cluth is engaged start decreasing electrical motor power
    {
      eSwitchValue = 13;
    }
  }
  else if (eSwitchValue == 13)          // Run on engine
  {
    SwitchTermic();
    engineRun();
    electricDecrease();
    
    // If speed is low and the clutch needs to disengage
    if (clutch == 2)
    {
      clutchCheck();
      if (engine == false)
      {
        eSwitchValue = 11;
      }
    }

    if(passing == false && chargeP == true && voltmeterValue > 10)
    {
      if(setTime(10000, 9))
      {
        eSwitchValue = 14;
      }
    }
  }
  else if (eSwitchValue == 14)          // Charge battery and run on engine
  {
    SwitchIncarcare();
    engineRun();

    if (clutch == 2)
    {
      chargeP = false;
      clutchCheck();
      if (engine == false)
      {
        eSwitchValue = 11;
      }
    }
  }
  if (eSwitchValue == 10)          // Shut every switch off
  {
    SwitchDecuplare();
  }

  /* Code for current monitoring of battery discharge to the motor 
  if (setTime(2000, 11) && currentSensorValue > 15 && digipot.getPosition() > 50)
  {
    digipot.setPosition(0);
    Serial.println("OVERCURRENT ERROR!!!");
  }
  */
}