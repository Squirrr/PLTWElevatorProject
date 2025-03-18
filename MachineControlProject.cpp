#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor elevatorMotor = motor(PORT10, ratio18_1, false);

distance elevatorDistance = distance(PORT2);
motor floorOneDoor = motor(PORT11, ratio18_1, false);

motor floorTwoDoor = motor(PORT12, ratio18_1, false);

motor floorThreeDoor = motor(PORT13, ratio18_1, false);

bumper floorOneBumper = bumper(Brain.ThreeWirePort.A);
bumper floorTwoBumper = bumper(Brain.ThreeWirePort.B);
bumper floorThreeBumper = bumper(Brain.ThreeWirePort.C);
led floorThreeLED = led(Brain.ThreeWirePort.H);
limit floorOneLS = limit(Brain.ThreeWirePort.D);
limit floorTwoLS = limit(Brain.ThreeWirePort.E);
limit floorThreeLS = limit(Brain.ThreeWirePort.F);
led floorTwoLED = led(Brain.ThreeWirePort.G);


// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {Abdullah Khaled}                                         */
/*    Created:      {3/3/2025}                                                */
/*    Description:  Code for elevator project for                             */
/*                  FISD PLTW Machine Control Project                         */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

// Calculations for elevator motor speed
double calculateElevatorSpeed(double kP, double curr, double setpoint) {
  return (setpoint - curr) * kP;
}

// MathUtil functions
double max(double a, double max) {
  if (a > max) {
    return max;
  } else {
    return a;
  }
}

double abs(double a) {
  if (a > 0) {
    return a;
  } else {
    return -a;
  }
}

double getDistance() {
  return elevatorDistance.objectDistance(mm);
}

double getClosestFloor() {
  return (round((getDistance() - 22) / 55) + 1);
}

// Set the elevator speed in rpm based on the distance away from the setpoint
// With a max speed of 5000 rpm
int goToHeight(double floorDist) {
  double kP = 3.0;
  elevatorMotor.setVelocity(
    max(
      calculateElevatorSpeed(kP, getDistance(), floorDist),
      5000
    ),
    rpm
  );
  elevatorMotor.spin(reverse);
  return 0;
}

int openDoor(int floor) {
  floorOneDoor.setVelocity(50, percent);
  floorTwoDoor.setVelocity(50, percent);
  floorThreeDoor.setVelocity(50, percent);

  if (floor == 1) {
    floorOneDoor.spinToPosition(60, degrees);
  }
  if (floor == 2) {
    floorTwoDoor.spinToPosition(60, degrees);
  }
  if (floor == 3) {
    floorThreeDoor.spinToPosition(60, degrees);
  }
  return 0;
}

int toggleLEDs(bool toggle) {
  if (toggle) {
    floorTwoLED.on();
    floorThreeLED.on();
  } else {
    floorTwoLED.off();
    floorThreeLED.off();
  }
  return 0;
}

// During maintenance mode, print to screen, open doors, and turn on LEDs
int maintenanceMode() {
  Brain.Screen.setCursor(5, 5);
  Brain.Screen.print("MAINTENANCE MODE");

  floorOneDoor.spinToPosition(60, degrees);
  floorTwoDoor.spinToPosition(60, degrees);
  floorThreeDoor.spinToPosition(60, degrees);

  if (floorOneLS.pressing() && floorTwoLS.pressing() && floorThreeLS.pressing()) {
    toggleLEDs(true);
  }

  return 0;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code

  // After 10 seconds (converted to ms) floor one downtime will kick in
  Brain.Timer.clear();
  int kUnusedTime = 10 * 1000;
  bool maintenanceLocked = false;

  // Store constants for floors and set the floor to floor one
  double kFloorTolerance = 5.0;
  double kFloorOneDist = 22.0;
  double kFloorTwoDist = 75.0;
  double kFloorThreeDist = 130.0;
  double distanceSetpoint = kFloorOneDist;
  double currentFloor = 1;

  // Initialize doors
  floorOneDoor.setPosition(0, degrees);
  floorTwoDoor.setPosition(0, degrees);
  floorThreeDoor.setPosition(0, degrees);

  // Initialize screen settings
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.setFont(mono60);
  Brain.Screen.setPenColor(white);

  while (true) {
    // If all three limit switches are pressed, toggle on maintenance mode
    if (floorOneLS.pressing() && floorTwoLS.pressing() && floorThreeLS.pressing()) {
      if (!maintenanceLocked) {
        maintenanceLocked = true;
        maintenanceMode();
      }
    } else {
      toggleLEDs(false);
      maintenanceLocked = false;
      Brain.Screen.clearScreen();

      // Logic for floor selection
      if (floorOneBumper.pressing() || floorOneLS.pressing()) {
        Brain.Timer.clear();
        currentFloor = 1;
        distanceSetpoint = kFloorOneDist;
      }
      if (floorTwoBumper.pressing() || floorTwoLS.pressing()) {
        Brain.Timer.clear();
        currentFloor = 2;
        distanceSetpoint = kFloorTwoDist;
      }
      if (floorThreeBumper.pressing() || floorThreeLS.pressing()) {
        Brain.Timer.clear();
        currentFloor = 3;
        distanceSetpoint = kFloorThreeDist;
      }

      // Logic for floor one default
      if (Brain.Timer.time(msec) >= kUnusedTime) {
        currentFloor = 1;
        distanceSetpoint = kFloorOneDist;
      }

      goToHeight(distanceSetpoint);

      // Telemetry for tuning P gain
      // Brain.Screen.print(distanceSetpoint);
      // Brain.Screen.newLine();
      // Brain.Screen.print(getDistance());

      // Telemetry for displaying the current floor
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(currentFloor);
      Brain.Screen.newLine();

      // Logic for opening doors (must be within tolerances)
      if (abs(getDistance() - distanceSetpoint) <= kFloorTolerance) {
        openDoor(currentFloor);
        Brain.Screen.print("FLOOR REACHED");
      } else {
        floorOneDoor.spinToPosition(0, degrees);
        floorTwoDoor.spinToPosition(0, degrees);
        floorThreeDoor.spinToPosition(0, degrees);
      }
    }
  }
}
