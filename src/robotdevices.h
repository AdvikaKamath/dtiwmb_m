
#ifndef ROBOTDEVICES
#define ROBOTDEVICES
#include "vex.h"
using namespace vex;

brain Brain;

// VEXcode devices
controller Controller1 = controller(primary);
motor LeftMiddle     = motor(PORT12, ratio6_1, true);
motor LeftFront    = motor(PORT13, ratio6_1, true);
motor LeftBack   = motor(PORT11, ratio6_1, true);

motor_group LeftMotorGrp = motor_group(LeftBack,LeftMiddle, LeftFront);

motor RightBack    = motor(PORT5, ratio6_1, false);
motor RightMiddle  = motor(PORT14, ratio6_1, false);
motor RightFront   = motor(PORT15, ratio6_1, false);

motor_group RightMotorGrp = motor_group(RightBack, RightMiddle, RightFront);

motor IntakeS1     = motor(PORT20, ratio6_1, false);
motor IntakeS2     = motor(PORT16, ratio6_1, false);

motor WallStakes    = motor(PORT21, ratio6_1,false);

inertial Inertial  = inertial(PORT3);
rotation rotationSensor = rotation(PORT1);

smartdrive Drivetrn = smartdrive(LeftMotorGrp,RightMotorGrp,Inertial,130,320,320,mm,1.62);

motor_group IntakesGrp = motor_group(IntakeS1, IntakeS2);


pneumatics Mogo    = pneumatics(Brain.ThreeWirePort.C);
pneumatics doinker    = pneumatics(Brain.ThreeWirePort.D);
//limit lswitch;
#endif
