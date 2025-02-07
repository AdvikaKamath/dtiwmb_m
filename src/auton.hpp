#ifndef AUTONHPP
#define AUTONHPP

#include "vex.h"
#include "robotdevices.h"
#include "preauton.hpp"
using namespace vex;
#include "motor.cpp"
#include "pidfunctions.hpp"

#define pause(x) {vex::this_thread::sleep_for(x);}

void Skills () {

 // Set to true to see mssages on controller
 
  LeftMotorGrp.setVelocity(50, pct);
  RightMotorGrp.setVelocity(50, pct);

  Drivetrn.setHeading(0,degrees);

  Drivetrn.driveFor(-6.3,inches,true);                                 // 6 inches to 1st MOGO ; clamp is in reverse/back direction
  Mogo.set(true); pause(200);                                        // Clamp 1st MOGO
  IntakeS1.spin(forward,100, pct); IntakeS2.spin(forward,100, pct);  // Start intake
  Drivetrn.turnToHeading(-64,degrees,true);                          // Turn intake towards rings


  Drivetrn.driveFor(38,  inches, true);                              // Run and load both rings
  Drivetrn.turnToHeading(-180, degrees, true);                       // Orient Mogo to corner
  Drivetrn.driveFor(-13.9,inches, true);                               // Push MOGO to corner
  Mogo.set(false); pause(200);                                       // Unclamp Mogo  
  IntakeS1.stop(); IntakeS2.stop();                                  // Stop Intake

  Drivetrn.driveFor(16,inches, true);                                // Move away from MOGO
  Drivetrn.turnToHeading(-62,degrees,true);                          // Turn clamp in direction of next mogo
  
  Drivetrn.driveFor(-102,inches, true);                               // Go to next MOGO; clamp end is in reverse direction
  Mogo.set(true); pause(200);                                        // Clamp 2nd MOGO
  Drivetrn.turnToHeading(-90,degrees,true);                         // Turn to corner
  Drivetrn.driveFor(-54,inches,true);                                // Push Mogo to corner

  Mogo.set(false); pause(200);                                       // Unclamp Mogo  
  Drivetrn.driveFor(16,inches, true);                                // Move away from MOGO

//  IntakeS1.spin(forward,100, pct); IntakeS2.spin(forward,100, pct);  // Start intake 
//  Drivetrn.turnToHeading(-240, degrees, true);


  // Drivetrn.driveFor(42, inches, true);                               // Drive into Mogo to intake
  // Drivetrn.turnToHeading(-120,degrees,true);                         // Turn to corner
  // Drivetrn.driveFor(-12,inches,true);                                // Push Mogo to corner

  // Mogo.set(false); pause(200);                                       // Unclamp Mogo  
  // IntakeS1.stop(); IntakeS2.stop();                                  // Stop Intake
  // Drivetrn.driveFor(16,inches, true);                                // Move away from MOGO

  return;










  /// RIGHT SIDE CORNER 
  goStraight(-5,false);
  Mogo.set(true); // Mogo clamp
 
  // Turn to rings
  IntakeS1.spin(forward,100, pct);
  IntakeS2.spin(forward,100, pct);
 
  turn(-70,true);    // turn intake towards rings
  goStraight(27,true);
  vex::this_thread::sleep_for(1000);


  turn (-110,false); // Turn mogo towards right corner
  vex::this_thread::sleep_for(1500); // wait for all rings intake
  goStraight(-18,true);
  vex::this_thread::sleep_for(800); // settle things down in corner
  Mogo.set(false);

  IntakeS1.stop();
  IntakeS2.stop();

  vex::this_thread::sleep_for(900); // wait for unclamp complete

  goStraight(19,true);  // Back off from Mogo (overshoot a bit because of drivetrain bias)
  vex::this_thread::sleep_for(800); // wait for backup complete 


  //// NEXT MOGO MANEUVERS
  turn(114,true);        // Orient towards next Mogo
  vex::this_thread::sleep_for(800); // wait for turn complete

  //// LEFT SIDE CORNER

  goStraight (-80, true);
  vex::this_thread::sleep_for(3000); // wait for turn complete

  Mogo.set(true); // Clamp 2nd Mogo
  vex::this_thread::sleep_for(100); // wait for unclamp complete
  turn (180, true); // Direct intake to the rings

  return;

  // intake rings
  vex::this_thread::sleep_for(2200);
 
  doinker.set(false);

  turn(-100.0, false);
   vex::this_thread::sleep_for(900);

  goStraight (-20, true);
   Mogo.set(false);
 IntakeS1.stop();
  IntakeS2.stop();
 vex::this_thread::sleep_for(900);
   goStraight (19, true);
vex::this_thread::sleep_for(900);
  turn(92.1, false);
vex::this_thread::sleep_for(900);
   goStraight (-75, true);
   vex::this_thread::sleep_for(2200);
goStraight (-5, true);
vex::this_thread::sleep_for(500);
Mogo.set(true);
 // Mogo clamp
  turn(-50.0, false);
   vex::this_thread::sleep_for(800);
    doinker.set(true);

  // Turn to rings
  IntakeS1.spin(forward,100, pct);
  IntakeS2.spin(forward,100, pct);
    
  goStraight (40, true);
  // intake rings
  vex::this_thread::sleep_for(2200);
 
  doinker.set(false);

  turn(100.0, false);
   vex::this_thread::sleep_for(900);
  
}



void RightAuto (){
    double distToMogo = -31;
  double fwdLength = 20;
  double ladder = 31;
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
  vex::this_thread::sleep_for(1000); // Need this not to clamp too soon
  Mogo.set(true);

  //Run intake
   vex::this_thread::sleep_for(500); 
  if (debug) CtrlDbgPrt("Intake spin");
  IntakeS1.spin(fwd,100, pct);
  IntakeS2.spin(fwd,100, pct);
 

  // Turn
  if (debug) CtrlDbgPrt("Turn to rings");
  turn(-87.0, false);

  vex::this_thread::sleep_for(1600);
  if (debug) CtrlDbgPrt("Go to rings");
  goStraight (fwdLength,true);
    


  //turn
  vex::this_thread::sleep_for(2300);  
  // Stop intake
  IntakeS1.stop();
  IntakeS2.stop();
  if (debug) CtrlDbgPrt("Intake Stop");
  
  turn(-140.0, true);
  if (debug) CtrlDbgPrt("Turn to ladder");  
   vex::this_thread::sleep_for(1000);

  goStraight(ladder, true);
  if (debug) CtrlDbgPrt("Forward to ladder");
}

void LeftAuto (){
    double distToMogo = -31;
  double fwdLength = 20;
  double ladder = 31;
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
  vex::this_thread::sleep_for(1000); // Need this not to clamp too soon
  Mogo.set(true);

  //Run intake
   vex::this_thread::sleep_for(500); 
  if (debug) CtrlDbgPrt("Intake spin");
  IntakeS1.spin(fwd,100, pct);
  IntakeS2.spin(fwd,100, pct);
 

  // Turn
  if (debug) CtrlDbgPrt("Turn to rings");
  turn(87.0, false);

  vex::this_thread::sleep_for(1600);
  if (debug) CtrlDbgPrt("Go to rings");
  goStraight (fwdLength,true);
    


  //turn
  vex::this_thread::sleep_for(2300);  
  // Stop intake
  IntakeS1.stop();
  IntakeS2.stop();
  if (debug) CtrlDbgPrt("Intake Stop");
  
  turn(140.0, true);
  if (debug) CtrlDbgPrt("Turn to ladder");  
   vex::this_thread::sleep_for(1000);

  goStraight(ladder, true);
  if (debug) CtrlDbgPrt("Forward to ladder");
  
}

#endif
