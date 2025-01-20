
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

int driveType = 0;

void driveSelect(){
  bool selecting = true;
  bool changed = false;

  Controller1.Screen.print("1: Tank");
  
  while(selecting){


    if(Controller1.ButtonA.pressing()){
      selecting = false;
    }


    if(!(Controller1.ButtonLeft.pressing() || Controller1.ButtonRight.pressing() || Controller1.ButtonUp.pressing())){
     if (changed) changed = false;
    }

    //Use left and right arrows to select auton.
    else if (!changed){
      if(Controller1.ButtonRight.pressing() && driveType < 4){
        driveType++;
        changed = true;
      }
      else if(Controller1.ButtonLeft.pressing() && driveType > 0){
        driveType--;
        changed = true;
      }

      Controller1.Screen.clearLine(3);
      Controller1.Screen.setCursor(3, 1);

      if(driveType == 0){
        Controller1.Screen.print("1: Tank");
        }
      else if(driveType == 1){
        Controller1.Screen.print("2: Arcade, Right");
      }
      else if(driveType == 2){
        Controller1.Screen.print("3: Arcade, Left");
      }
      else if(driveType == 3){
        Controller1.Screen.print("4: DL, TR");
      }
      else if(driveType == 4){
        Controller1.Screen.print("5: TL, DR");
      }
    }
  }

  Controller1.Screen.clearLine(3);
  Controller1.Screen.setCursor(3, 1);
  Controller1.rumble("--..-");
  Controller1.Screen.print("Drivetype Selected!");
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
 
  //  Controller1.Screen.clearScreen();
  //  Controller1.Screen.setCursor(1, 1);
  //  Controller1.Screen.print("Auton sel %d",autonomousSelection);

  // switch(autonomousSelection) {
  //   case 0: {oneMplusoneR(true);}  // set to true when going for positive side
  //   case 1: {oneMplusoneR(false);}   // set to false when going for negative side
  //   default: ;
  // }
 double distToMogo = -29;
  double fwdLength = 17;
  double ladder = 25;
  bool debug = false;
  bool skills = false; 
     // Set to true to see mssages on controller

   if (debug) CtrlDbgPrt("Intake spin");
  IntakeS1.spin(reverse,100, pct);
  IntakeS2.spin(reverse,100, pct);
  vex::this_thread::sleep_for(200);

 if (debug) CtrlDbgPrt("Go to rings");
  goStraight (5,true);

  if (debug) CtrlDbgPrt("Intake spin");
  IntakeS1.spin(forward,100, pct);
  IntakeS2.spin(forward,100, pct);
    vex::this_thread::sleep_for(800);
    

     // Stop intake
  IntakeS1.stop();
  IntakeS2.stop();
  if (debug) CtrlDbgPrt("Intake Stop");
 

    // All motors run at the same speed
  LeftMotorGrp.setVelocity(40, pct);
  RightMotorGrp.setVelocity(40, pct);

  // Make it go forward
  if (debug) CtrlDbgPrt("Go Forward");
  goStraight(distToMogo, true); // Robot starts in reverse position

  // mOGO CLAMP
  
  if (debug) CtrlDbgPrt("MOGO");
  vex::this_thread::sleep_for(900); // Need this not to clamp too soon
  Mogo.set(true);

  //Run intake
   vex::this_thread::sleep_for(500); 
  if (debug) CtrlDbgPrt("Intake spin");
  IntakeS1.spin(fwd,100, pct);
  IntakeS2.spin(fwd,100, pct);
 

  // Turn
  if (debug) CtrlDbgPrt("Turn to rings");
  turn(-90.0, false);

  vex::this_thread::sleep_for(1400);
  if (debug) CtrlDbgPrt("Go to rings");
  goStraight (fwdLength,true);
    


  //turn
  vex::this_thread::sleep_for(2000);  
  // Stop intake
  IntakeS1.stop();
  IntakeS2.stop();
  if (debug) CtrlDbgPrt("Intake Stop");

  turn(-135.0, true);
  if (debug) CtrlDbgPrt("Turn to ladder");  
   vex::this_thread::sleep_for(1000);

  goStraight(ladder, true);
  if (debug) CtrlDbgPrt("Forward to ladder");
  
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
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    if(driveType == 0){
      double right = Controller1.Axis2.position();
      double left = Controller1.Axis3.position();
      //Dead spot if both joysticks are at low values
      if(fabs(left) < 10 && fabs(right) < 10){
        RightBack.stop(coast);
        RightFront.stop(coast);
        RightMiddle.stop(coast);
        LeftBack.stop(coast);
        LeftFront.stop(coast);
        LeftMiddle.stop(coast);
      }
      //Otherwise, move at the inputted speed
      else {
        RightFront.spin(forward, right, percent);
        RightBack.spin(forward, right, percent);
        RightMiddle.spin(forward, right, percent);
        LeftFront.spin(forward, left, percent);
        LeftBack.spin(forward, left, percent);
        LeftMiddle.spin(forward, left, percent);
      } 
    }

    else if(driveType == 1){
      double forwardSpeed = Controller1.Axis2.position();
      double turn = Controller1.Axis1.position();

      int leftSpeed = forwardSpeed + 0.4 * turn;
      int rightSpeed = forwardSpeed - 0.4 * turn;
      //Dead spot if both joysticks are at low values
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

    else if(driveType == 2){
      double forwardSpeed = Controller1.Axis3.position();
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

    else if(driveType == 3){
      double forwardSpeed = Controller1.Axis3.position();
      double turn = Controller1.Axis1.position();
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

    else if(driveType == 4){
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

    // Map Button R1 & R2 to Intake & Expel rings
  // Works as a toggle
  //Controller1.ButtonR1.pressed(intakeRings); commented out
  //Controller1.ButtonR2.pressed(expelRings); commented out

  // Map Button L1 to clamp and unclamp mobile goal
  // Works as a toggle
  Controller1.ButtonL1.pressed(mobileGoalClamp);

  // User control code here, inside the loop

    intakeFunction();
   // Read the joystick values
    //int forward = Controller1.Axis2.position();  // Left joystick Y-axis
    //int turn = Controller1.Axis1.position();     // Left joystick X-axis

    // Calculate the speed for each side
    // Scale down to reduce speed
    //int leftSpeed  = forward + turn;
    //int rightSpeed = forward - turn;

    // Set the motor speeds
 
     //LeftMotorGrp.spin(fwd,leftSpeed,pct);
    // LeftBack.spin(fwd, leftSpeed, pct);
    // LeftFront.spin(fwd, leftSpeed, pct);
    // LeftMiddle.spin(fwd, leftSpeed, pct);
      //RightMotorGrp.spin(fwd, rightSpeed, pct);
    // RightBack.spin(fwd, rightSpeed, pct);
    // RightFront.spin(fwd, rightSpeed, pct);
    // RightMiddle.spin(fwd, rightSpeed, pct);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Run the pre-autonomous function.

  // // Set up callbacks for autonomous and driver control periods.
  // Competition.autonomous(autonomous);
  // Competition.drivercontrol(usercontrol);

  //   // register events for button selection
  //   Brain.Screen.pressed( userTouchCallbackPressed );
  //   Brain.Screen.released( userTouchCallbackReleased );

  //   // make nice background
  //   Brain.Screen.setFillColor( vex::color(0x404040) );
  //   Brain.Screen.setPenColor( vex::color(0x404040) );
  //   Brain.Screen.drawRectangle( 0, 0, 480, 120 );
  //   Brain.Screen.setFillColor( vex::color(0x808080) );
  //   Brain.Screen.setPenColor( vex::color(0x808080) );
  //   Brain.Screen.drawRectangle( 0, 120, 480, 120 );

  //   // initial display
  //   displayButtonControls( 0, false );


  // Prevent main from exiting with an infinite loop.

    // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  driveSelect();

  // Run the pre-autonomous function.
  pre_auton();

  while (true) {
    printTemps();  // Prints motor temperature on the controller
    wait(100, msec);
  }
}
