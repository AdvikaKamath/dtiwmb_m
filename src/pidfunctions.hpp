#ifndef PIDFUNC_HPP
#define PIDFUNC_HPP
#include "vex.h"
#include "robotdevices.h"


// Settings
const double kU = 2; // Measured for Zeigler Nichols method
const double pU = 4; // measured time of oscillation in seconds

double kP = 0.6*kU;      // kP = 0.6 x kU for PID         - source Wikipedia
double kI = 1.2*kU/pU;   // kI = 1.2 x kU / pU for PID    - source Wikipedia
double kD = 0.075*kU*pU; // kD = 0.075 x kU x pU for PID  - source Wikipedia

const double tkU = 0.05; // Measured for Zeigler Nichols method
const double tpU = 30;  // measured time of oscillation in seconds

double turnkP = 0.6 * tkU;
double turnkI = 1.2 * tkU / tpU;
double turnkD = 0.075 * tkU * tpU; 

bool enableDrivePID = true;

int drivePID(double dist, double angle){

  // Auto Settings
  float desiredValue;  // 10.125 in = 360 degrees , need to scale by gear ratio
  const float gearRatio = 1.35;
  float desiredTurnValue;  /// angle = required*scale
  const float angleScale = 13;
  const float angleBias  = 0.0;
  const float leftMotorScale = 1.0;    // Left part is the one that is on left when looking from clamp side
  const float rightMotorScale = 1.0;

  float error;  // SensorValue - DesireValue 
  float prevError = 0;  // Position 20 milisec  onds ago 
  float derivative; // error - prevError : Speed 
  float totalError = 0; // totalError = totalError + error
 
  float turnError;  // SensorValue - DesireValue 
  float turnPrevError = 0;  // Position 20 miliseconds ago 
  float turnDerivative; // error - prevError : Speed 
  float turnTotalError = 0; // totalError = totalError + error

  // Convert input parameter to drivetrain motor targets
  desiredValue = dist/10.125 * 360 * gearRatio;
  desiredTurnValue = (angle - angleBias) * angleScale ;

  // Start both sides at zero
  LeftMotorGrp.resetPosition();
  RightMotorGrp.resetPosition();

  while(enableDrivePID){

    int leftMotorPosition = LeftMotorGrp.position(degrees);
    int rightMotorPosition = RightMotorGrp.position(degrees);

    ////////////////////////////////////////////////////////
    // Latteral Movement PID
    ////////////////////////////////////////////////////////

    // Get avrege of the two motors 
    int averagePosition = (leftMotorPosition + rightMotorPosition )/2; 

    // Potential 
    error  = desiredValue - averagePosition; 

    //Derivative 
    derivative  = error - prevError; 

    // Velocity -> Position -> absement 
    if (error > 0) 
      totalError += error;
    else 
      totalError = 0; // Zero the integral once error goes 0 or negative


    // autondebug = error;
    double lateralMotorPower  = error * kP+ derivative * kD + totalError * kI;

     ////////////////////////////////////////////////////////
    // Turning Movement PID
    ////////////////////////////////////////////////////////
     // Get avrege of the two motors 
    int turnDiffrence = leftMotorPosition - rightMotorPosition; 

    // Potential 
    turnError = desiredTurnValue - turnDiffrence; 

    //Derivative 
    turnDerivative = turnError - turnPrevError; 

    // Velocity -> Position -> absement 
    if (turnError > 0)
      turnTotalError += turnError; 
    else
      turnTotalError = 0;

    double turnMotorPower  = turnError * turnkP+ turnDerivative * turnkD + turnTotalError * turnkI;


    ///////////////////////////////////////////////////////////

    LeftMotorGrp.spin(forward, lateralMotorPower*leftMotorScale +  turnMotorPower, vex::voltageUnits::volt);
    RightMotorGrp.spin(forward, lateralMotorPower*rightMotorScale - turnMotorPower , vex::voltageUnits::volt);

    // ...
    prevError = error; 

    turnPrevError = turnError;
    vex::task::sleep(20);

  }


  return 1; 
}


#endif
