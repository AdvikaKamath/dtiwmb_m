
#ifndef PREAUTON
#define PREAUTON

#include "vex.h"
#include "robotdevices.h"

using namespace vex;

#include "motor.cpp"

//auton selector

// Auton Functions


void CtrlDbgPrt (const char * str) {
  Controller1.Screen.print(str);
  Controller1.Screen.newLine();
}

void goStraight (double dist, bool front) {
  const double  INCH_TO_DEG = 360*3.0/19;    // Measured on 11/28/2024 - 3 rotations : 22.5 in 
  const uint32_t WAIT_TIME    = 300;          // in milliseconds

  double  currentLeftPos  = LeftMotorGrp.position(degrees);
  double  currentRightPos = RightMotorGrp.position(degrees);
  if (front == true) {
    LeftMotorGrp.spinToPosition (currentLeftPos + dist * INCH_TO_DEG, degrees, false );
    RightMotorGrp.spinToPosition (currentRightPos + dist * INCH_TO_DEG, degrees, false );
  } else {
        LeftMotorGrp.spinToPosition (currentLeftPos + dist * INCH_TO_DEG, degrees, false );
    RightMotorGrp.spinToPosition (currentRightPos + dist * INCH_TO_DEG, degrees, false );
  }
  vex::this_thread::sleep_for(WAIT_TIME);

}

void turn (double angle, bool left) {
  const double  INCH_TO_DEG   = 360*3.0/19;    // Measured on 11/28/2024 - 3 rotations : 22.5 in 
  const double  TURN_RADIUS   = 8;            // Measured on 11/29
  const uint32_t WAIT_TIME    = 300;          // in milliseconds

  double linearDegree = TURN_RADIUS * 2 * M_PI * angle / 360;
  double currentLeftPos, currentRightPos;

  if (left == true) {
    currentLeftPos  = LeftMotorGrp.position(degrees);
    currentRightPos = RightMotorGrp.position(degrees);
   // LeftMotorGrp.spinFor(fwd,360,degrees);
     LeftMotorGrp.spinToPosition (currentLeftPos + linearDegree * INCH_TO_DEG, degrees, false);
     RightMotorGrp.spinToPosition (currentRightPos - linearDegree * INCH_TO_DEG, degrees, false);
  } else {
      currentLeftPos  = LeftMotorGrp.position(degrees);
    currentRightPos = RightMotorGrp.position(degrees);
   // LeftMotorGrp.spinFor(fwd,360,degrees);
     LeftMotorGrp.spinToPosition (currentLeftPos + linearDegree * INCH_TO_DEG, degrees, false);
     RightMotorGrp.spinToPosition (currentRightPos - linearDegree * INCH_TO_DEG, degrees, false);
  }

    vex::this_thread::sleep_for(WAIT_TIME);

}


#endif


