
#ifndef ROBOTDEVICES
#define ROBOTDEVICES
#include "vex.h"
using namespace vex;

brain Brain;

// VEXcode devices
controller Controller1 = controller(primary);
motor LeftBack     = motor(PORT6, ratio6_1, true);
motor LeftFront    = motor(PORT11, ratio6_1, true);
motor LeftMiddle   = motor(PORT12, ratio6_1, true);

motor_group LeftMotorGrp = motor_group(LeftBack,LeftMiddle, LeftFront);

motor RightBack    = motor(PORT8, ratio6_1, false);
motor RightMiddle  = motor(PORT7, ratio6_1, false);
motor RightFront   = motor(PORT5, ratio6_1, false);

motor_group RightMotorGrp = motor_group(RightBack,RightMiddle, RightFront);

motor IntakeS1     = motor(PORT3, ratio6_1, false);
motor IntakeS2     = motor(PORT4, ratio6_1, true);

inertial Inertial  = inertial(PORT20);

smartdrive Drivetrn = smartdrive(LeftMotorGrp,RightMotorGrp,Inertial,130,320,320,mm,1.62);

motor_group IntakesGrp = motor_group(IntakeS1, IntakeS2);


pneumatics Mogo    = pneumatics(Brain.ThreeWirePort.A);
pneumatics doinker    = pneumatics(Brain.ThreeWirePort.C);
//limit lswitch;
#endif
