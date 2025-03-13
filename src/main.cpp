
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
{
  WallStakes.resetPosition();
}


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
  // enableDrivePID = false;
//  drivePID(134,0);
/// Temporary break
// return;

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
      
      double leftSpeed = forwardSpeed + 0.9 * turn;
      double rightSpeed = forwardSpeed - 0.9 * turn;

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





void usercontrol(void) {
  int shawtyBae = 0;


  // enableDrivePID = false;

  // User control code here, inside the loop
  while (1) {

   
  //  ...................................................................
    double forwardSpeed = Controller1.Axis2.position();
      double turn = Controller1.Axis1.position();

      int leftSpeed = forwardSpeed + 0.5 * turn;
      int rightSpeed = forwardSpeed - 0.5 * turn;
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

    // Controller1.ButtonUp.pressed (nextStates);

    Controller1.ButtonX.pressed(Doinker);
    Controller1.ButtonL1.pressed(mobileGoalClamp);

    intakeFunction();




    ////
      if (Controller1.ButtonL2.pressing()){
      IntakeS2.setVelocity(30, pct);
      }

      else {
        IntakeS2.setVelocity(80, pct);
      }


    if (Controller1.ButtonLeft.PRESSED){
      shawtyBae = 1;
      WallStakesMacro(4.5);
    }

    if(Controller1.ButtonUp.pressing()){
      if ( shawtyBae == 1) {
      wait (200, msec);
      IntakeS2.spin(reverse,20, pct);
      wait (900, msec);
      IntakeS2.stop();
      shawtyBae = 0;
      }

      else {
        WallStakes.setVelocity(85, percent);
        WallStakes.spin(forward);
      }

      
    
      }
    
      else if(Controller1.ButtonDown.pressing()){
      WallStakes.setVelocity(100, percent);
      WallStakes.spin(reverse);
      }
      else{
      WallStakes.stop(hold);
      }
      
      
      
  
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
