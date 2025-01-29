#ifndef AUTONHPP
#define AUTONHPP

#include "vex.h"
#include "robotdevices.h"
#include "preauton.hpp"
using namespace vex;
#include "motor.cpp"


void Skills () {

 // Set to true to see mssages on controller
 
 LeftMotorGrp.setVelocity(50, pct);
  RightMotorGrp.setVelocity(50, pct);
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
  
}



void RightAuto (){
    double distToMogo = -31;
  double fwdLength = 18;
  double ladder = 30;
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
  turn(-90.0, false);

  vex::this_thread::sleep_for(1600);
  if (debug) CtrlDbgPrt("Go to rings");
  goStraight (fwdLength,true);
    


  //turn
  vex::this_thread::sleep_for(2000);  
  // Stop intake
  IntakeS1.stop();
  IntakeS2.stop();
  if (debug) CtrlDbgPrt("Intake Stop");
  
  if (skills) {
     turn(-95.0, true);
     vex::this_thread::sleep_for(900);
    goStraight(-20, true);
     vex::this_thread::sleep_for(500);
     Mogo.set(false);
  } 
  else {
  turn(-140.0, true);
  if (debug) CtrlDbgPrt("Turn to ladder");  
   vex::this_thread::sleep_for(1000);

  goStraight(ladder, true);
  if (debug) CtrlDbgPrt("Forward to ladder");
  }
}

void LeftAuto (){
    double distToMogo = -31;
  double fwdLength = 18;
  double ladder = 30;
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
  turn(90.0, false);

  vex::this_thread::sleep_for(1600);
  if (debug) CtrlDbgPrt("Go to rings");
  goStraight (fwdLength,true);
    


  //turn
  vex::this_thread::sleep_for(2000);  
  // Stop intake
  IntakeS1.stop();
  IntakeS2.stop();
  if (debug) CtrlDbgPrt("Intake Stop");
  
  if (skills) {
     turn(-95.0, true);
     vex::this_thread::sleep_for(900);
    goStraight(-20, true);
     vex::this_thread::sleep_for(500);
     Mogo.set(false);
  } 
  else {
  turn(140.0, true);
  if (debug) CtrlDbgPrt("Turn to ladder");  
   vex::this_thread::sleep_for(1000);

  goStraight(ladder, true);
  if (debug) CtrlDbgPrt("Forward to ladder");
  }
}

#endif
