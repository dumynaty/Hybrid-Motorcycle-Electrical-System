# Hybrid Motorcycle Electrical System

## Description
This project focuses on designing an electrical system for a motorcycle, combining a DC motor with a combustion engine to create a plug-in hybrid vehicle.

#### Note: Used as a thesis in Robotics Engineering. Some elements (3D models, technical drawings, sizing & load calculations etc.) have been left out.

### Overview elements
* Aim and conceptual background: read **Project Design** and **Thesis Description**
* Electrical system schematic: access **Fritzing** folder for schematic file or image
* Components used: access **Components** folder for list and images
* Integration logic: access **Code** folder

### General outline
Main components:
* Combustion engine and DC motor
* Additional motors for controlling the engine's gear and speed cable (worm gear, servo)
* Motor Drivers
* Battery to power the motor and other electrical components
* Ability to charge the battery during operation
* Sensors: Hall, Gyroscope, Voltage, Current
* Electronic switches (E-switches) to control current flow paths
* Voltage regulators
* Microcontrollers: Arduino Mega (program logic), ESP32 (Bluetooth communication)

### Functionality
The system is designed to accomplish the following:
* DC motor used as primary propulsion source at speeds up to 20 km/h
* Engine's power for higher speeds
* Smooth transition when switching power sources
* Using DC motor: throttle lever provides data to the microcontroller, which then regulates current delivery via the motor driver
* Using engine: throttle lever provides data to the microcontroller, which controls the clutch actuator motor and regulates the servomotor connected to the throttle cable and, under certain conditions, also initiates battery charging

### Further development possibilities
The system can be significantly improved by integrating the regulators, sensors, drivers, and other components into a single custom PCB.
Additional sensors may be added, such as a temperature sensor, to expand monitoring capabilities.
Further optimization of the microcontroller code can enhance performance and efficiency.
A visual interface can also be developed to display the data received via Bluetooth communication.
