#ifndef ROBOTFUNCTIONS
#define ROBOTFUNCTIONS
#include "vex.h"
#include "robotdevices.h"

// Globals for robotfunctions
int autondebug = -1;

  void WallStakesMacro(double targetPosition){


    double kp = 0.01;
    WallStakes.setPosition(0,degrees);
    
    double realTarget = (targetPosition*15);
    double error = 0.0;
    double output = 0.0;
    
    
    double tolerance = 1.0;
    double speedLimit = 50;
    
    
    while (true) {
    // get the error
    double currentPosition = WallStakes.position(degrees); // motor positions
    error = realTarget - currentPosition;
    
    
    // output
    output = kp * error;
    
    
    if (output > 120.0) {
    output = 120.0;
    } else if (output < -120.0) {
    output = -120.0;
    }
    
    
    
    
    
    output *= speedLimit;
    
    
    // spins motors
    WallStakes.spin(forward, output, percent);
    
    // checks to see if within tolerance
    if (fabs(error) < tolerance) {
    // Stop all motors
    LeftFront.stop();
    LeftMiddle.stop();
    LeftBack.stop(brake);
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop(brake);
    wait(20,msec); // wait so commands have time to work
    break; //
    }
    
    
    wait(20,msec); //
    }
    
    }
    






void expelRings() {
    static bool expelOn;
    expelOn = expelOn && (IntakeS1.direction()==reverse);
    if (expelOn==false) {
        IntakeS1.spin(reverse, 100, pct);
        IntakeS2.spin(reverse, 80, pct);
        expelOn = true;
    } else {
        IntakeS1.stop(brake);
        IntakeS2.stop(brake);       
        expelOn = false;
    }
    vex::this_thread::sleep_for(100);
}

void intakeRings () {
  static bool intakeOn;
  intakeOn = intakeOn && (IntakeS1.direction()==forward); 
  
  if (intakeOn==false) {
      IntakeS1.spin(fwd, 100, pct);
      IntakeS2.spin(fwd, 85, pct);
      intakeOn = true;
      
  } else {
      IntakeS1.stop(coast);
      IntakeS2.stop(coast);  
      intakeOn = false;
     

  }
  vex::this_thread::sleep_for(100);
}





void intakeFunction(){

  //IntakeS1.setVelocity(100,percent);
  //IntakeS2.setVelocity(100,percent);

  if (Controller1.ButtonR1.PRESSED){
    intakeRings();

  }

  else if (Controller1.ButtonR2.PRESSED){
    expelRings();

  }

}

void mobileGoalClamp() {
    // static bool clampOn ;
    static bool clamp;

    if (clamp == false) {
      Mogo.set(true);
      clamp = true;
     }
      else {
      Mogo.set (false); 
      clamp = false;
     }

    vex::this_thread::sleep_for(100);



}


void Doinker() {
   
 static bool yoinker;

    if (yoinker == false) {
      doinker.set (true);
      yoinker = true;
     }
     else {
      doinker.set (false); 
      yoinker = false;
     }
     vex::this_thread::sleep_for(100);


}


/*
 This function prints the motor temperatures on controller screen
*/

int printcount = 0;

void printTemps() {

const int TOTALLINES = 3;

float LeftMTemp = LeftMotorGrp.temperature();
float RightMTemp = RightMotorGrp.temperature();
float IntakeTemp = IntakeS2.temperature();

  //Controller1.Screen.clearScreen();

  if (printcount % TOTALLINES == 0) {
      Controller1.Screen.setCursor(2,1);
      if(LeftMTemp <= 40){
        Controller1.Screen.print(":D LM: %1.0f", LeftMTemp);
      } else if(LeftMTemp <= 55){
        Controller1.Screen.print(":) LM: %1.0f", LeftMTemp);
      } else{
        Controller1.Screen.print(":( LM: %1.0f", LeftMTemp);
      }
 
      if(RightMTemp<= 40){
        Controller1.Screen.print(":D RM: %1.0f", RightMTemp);
      } else if(RightMTemp <= 55){
        Controller1.Screen.print(":) RM: %1.0f", RightMTemp);
      }else{
        Controller1.Screen.print(":( RM: %1.0f", RightMTemp);
      }
      Controller1.Screen.newLine();
  }
}


#endif
