#ifndef ROBOTFUNCTIONS
#define ROBOTFUNCTIONS
#include "vex.h"
#include "robotdevices.h"

// Globals for robotfunctions
int autondebug = -1;



void expelRings() {
    static bool expelOn;
    expelOn = expelOn && (IntakeS1.direction()==reverse);
    if (expelOn==false) {
        IntakeS1.spin(reverse, 100, pct);
        IntakeS2.spin(reverse, 100, pct);
        // For debugging
        Brain.Screen.print("expel Start: %d %d",expelOn,(IntakeS1.direction()==reverse));
        Brain.Screen.newLine();
        expelOn = true;
    } else {
        IntakeS1.stop(brake);
        IntakeS2.stop(brake);       
        // For debugging
        Brain.Screen.print("expel Stop: %d %d",expelOn,(IntakeS1.direction()==reverse));
        Brain.Screen.newLine();
        expelOn = false;
    }
    vex::this_thread::sleep_for(100);
}


void intakeFunction(){

  //IntakeS1.setVelocity(100,percent);
  //IntakeS2.setVelocity(100,percent);

  if (Controller1.ButtonR1.pressing()){

    IntakeS1.spin(forward,80,percent); //change Speed of the intake
    IntakeS2.spin(forward,100,percent); //Change Speed of the convayer belt

  }

  else if (Controller1.ButtonR2.pressing()){

    IntakeS1.spin(reverse,80,percent);
    IntakeS2.spin(reverse,90,percent);

  }

  else {
    IntakeS1.stop();
    IntakeS2.stop();

  }
}

void mobileGoalClamp() {
    static bool clampOn ;

    // For debugging
    // Controller1.Screen.print("clamp Off: %d",clampOn);
    // Controller1.Screen.newLine();

    Mogo.set(clampOn);
    clampOn = not clampOn;
    vex::this_thread::sleep_for(100);
}


void Doinker() {
    static bool DoinkerOn;

    // For debugging
    // Controller1.Screen.print("Doinker On: %d",DoinkerOn);
    // Controller1.Screen.newLine();
    doinker.set(DoinkerOn);
    DoinkerOn = not DoinkerOn;
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

  if (printcount % TOTALLINES == 1) {
      Controller1.Screen.setCursor(2,1);
      if(IntakeTemp<= 40){
        Controller1.Screen.print(":D IM: %1.0f", IntakeTemp);
      } else if(IntakeTemp <= 55){
        Controller1.Screen.print(":) IM: %1.0f", IntakeTemp);
      } else{
        Controller1.Screen.print(":( IM: %1.0f", IntakeTemp);
      }
      Controller1.Screen.print("PID %c",autondebug);
      Controller1.Screen.newLine();
  }

  printcount++ ;
}

#endif
