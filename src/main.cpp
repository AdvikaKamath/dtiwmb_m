
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Redwood Robotics                                          */
/*    Created:      11/17/2024, 9:30:01 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "robotdevices.h"
#include "buttonapi.hpp"
#include "robotfunctions.hpp"
#include "auton.hpp"
#include "preauton.hpp"
using namespace vex;

#include "motor.cpp"

// A global instance of competition
competition Competition;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

int AUTO = 0;

void autoSelect(){
  bool selecting = true;
  bool changed = false;

  Controller1.Screen.print("Skills");
  
  while(selecting){


    if(Controller1.ButtonA.pressing()){
      selecting = false;
    }


    if(!(Controller1.ButtonLeft.pressing() || Controller1.ButtonRight.pressing() || Controller1.ButtonUp.pressing())){
     if (changed) changed = false;
    }

    //Use left and right arrows to select auton.
    else if (!changed){
      if(Controller1.ButtonRight.pressing() && AUTO < 4){
        AUTO++;
        changed = true;
      }
      else if(Controller1.ButtonLeft.pressing() && AUTO > 0){
        AUTO--;
        changed = true;
      }

      Controller1.Screen.clearLine(3);
      Controller1.Screen.setCursor(3, 1);

      if(AUTO == 0){
        Controller1.Screen.print("Skills");
        }
      else if(AUTO == 1){
        Controller1.Screen.print("oneMplusoneL");
      }
      else if(AUTO == 2){
        Controller1.Screen.print("oneMplusoneR");
      }
      else if(AUTO == 3){
        Controller1.Screen.print("4 Ring");
      }
      else if(AUTO == 4){
        Controller1.Screen.print("..");
      }
    }
  }

  Controller1.Screen.clearLine(3);
  Controller1.Screen.setCursor(3, 1);
  Controller1.rumble("--..-");
  Controller1.Screen.print("Auton Selected!");
  wait(2 ,sec);
  Controller1.Screen.clearLine(3);
  Controller1.Screen.setCursor(3, 1);
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  // vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

}


// Settings
const double kU = 0.3; // Measured for Zeigler Nichols method
const double pU = 1.4; // measured time of oscillation in seconds

double kP = 0.6*kU;      // kP = 0.6 x kU for PID         - source Wikipedia
double kI = 1.2*kU/pU;   // kI = 1.2 x kU / pU for PID    - source Wikipedia
double kD = 0.075*kU*pU; // kD = 0.075 x kU x pU for PID  - source Wikipedia

const double tkU = 0.05; // Measured for Zeigler Nichols method
const double tpU = 30;  // measured time of oscillation in seconds

double turnkP = 0.6 * tkU;
double turnkI = 1.2 * tkU / tpU;
double turnkD = 0.075 * tkU * tpU; 

bool enableDrivePID = false;

int drivePID(double dist, double angle){

  // Auto Settings
  float desiredValue;  // 10.125 in = 360 degrees , need to scale by gear ratio
  const float gearRatio = 1.35;
  float desiredTurnValue;  /// angle = required*scale
  const float angleScale = 13;
  const float angleBias  = 0;
  const float leftMotorScale = 1.0;
  const float rightMotorScale = 0.83;

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


    autondebug = error;
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

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  enableDrivePID = true;
 drivePID(40,0);
/// Temporary break
return;

if(AUTO == 0){
Skills();
    }

    else if(AUTO == 1){
      LeftAuto(); 
    }

    else if(AUTO == 2){
     RightAuto();
    }

    else if(AUTO == 4){
      double forwardSpeed = Controller1.Axis2.position();
      double turn = Controller1.Axis4.position();
      //Dead spot if both joysticks are at low values
      
      double leftSpeed = forwardSpeed + 0.4 * turn;
      double rightSpeed = forwardSpeed - 0.4 * turn;

      if(fabs(forwardSpeed) < 10 && fabs(turn) < 5){
        RightBack.stop(coast);
        RightFront.stop(coast);
        RightMiddle.stop(coast);
        LeftBack.stop(coast);
        LeftFront.stop(coast);
        LeftMiddle.stop(coast);
      }
      //Otherwise, move at the inputted speed

      
      else {
        RightFront.spin(forward, rightSpeed, percent);
        RightBack.spin(forward, rightSpeed, percent);
        RightMiddle.spin(forward, rightSpeed, percent);
        LeftFront.spin(forward, leftSpeed, percent);
        LeftBack.spin(forward, leftSpeed, percent);
        LeftMiddle.spin(forward, leftSpeed, percent);
      }
    }

  
}

  

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void intakeRings () {
    static bool intakeOn;
    intakeOn = intakeOn && (IntakeS1.direction()==forward); 
    
    if (intakeOn==false) {
        IntakeS1.spin(fwd, 100, pct);
        IntakeS2.spin(fwd, 100, pct);
        intakeOn = true;
        
    } else {
        IntakeS1.stop(coast);
        IntakeS2.stop(coast);  
        intakeOn = false;
       
  
    }
    vex::this_thread::sleep_for(100);
}


void usercontrol(void) {

  enableDrivePID = false;

  Controller1.ButtonX.pressed(Doinker);
  Controller1.ButtonL1.pressed(mobileGoalClamp);

  // User control code here, inside the loop
  while (1) {
  //  ...................................................................
    double forwardSpeed = Controller1.Axis2.position();
      double turn = Controller1.Axis1.position();

      int leftSpeed = forwardSpeed + 0.4 * turn;
      int rightSpeed = forwardSpeed - 0.4 * turn;
      //Dead stop if both joysticks are at low values
      if(fabs(forwardSpeed) < 10 && fabs(turn) < 5){
        RightBack.stop(coast);
        RightFront.stop(coast);
        RightMiddle.stop(coast);
        LeftBack.stop(coast);
        LeftFront.stop(coast);
        LeftMiddle.stop(coast);
      }
      //Otherwise, move at the inputted speed

      else {
        RightFront.spin(forward, rightSpeed, percent);
        RightBack.spin(forward, rightSpeed, percent);
        RightMiddle.spin(forward, rightSpeed, percent);
        LeftFront.spin(forward, leftSpeed, percent);
        LeftBack.spin(forward, leftSpeed, percent);
        LeftMiddle.spin(forward, leftSpeed, percent);
      }
  
    // User control code here, inside the loop

    intakeFunction();
  
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
 
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  autoSelect();
  pre_auton();

  while (true) {
    printTemps();  // Prints motor temperature on the controller
    wait(1, sec);
  }
}
