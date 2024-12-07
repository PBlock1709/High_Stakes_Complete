#include "robot-config.h"

//create variables and stuff
double driveError = 162.5; //set to 90% for 10% overshoot and 110% for 10% undershoot
double turnError = 162.5; //same as this ^^^

double moveActual;
double turnActual;

//error control
void driveForward (double moveDistance) {
  moveActual=(((moveDistance) / 100) * driveError);
  Drivetrain.driveFor(forward, (moveActual), inches);
}
void driveReverse (double moveDistance) {
  moveActual=(((moveDistance) / 100) * driveError);
  Drivetrain.driveFor(reverse, (moveActual), inches);
}
void turnRight (double turnDistance) {
  turnActual=(((turnDistance) / 100) * turnError);
  Drivetrain.turnFor(right, (turnActual), degrees);
}
void turnLeft (double turnDistance) {
  turnActual=(((turnDistance) / 100) * turnError);
  Drivetrain.turnFor(left, (turnActual), degrees);
}



///////AUTON PATHS///////

void skillsAuton() {
  Drivetrain.driveFor(reverse, 8, inches, false);
  wait(1000, msec);
  IntakeMotor.spinFor(forward, 1, seconds);
  wait(2, msec);
  driveForward(16);
  wait(2, msec);

  turnLeft(90);
  wait(2, msec);
  driveReverse(24);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  turnLeft(90);
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(24);
  wait(2, msec);

  turnRight(60);
  wait(2, msec);
  driveForward(36);
  wait(2, msec);

  turnLeft(80);
  wait(2, msec);
  driveForward(24);
  wait(500, msec);
  IntakeMotor.stop();
  wait(2, msec);

  turnRight(30);
  wait(2, msec);
  driveReverse(24);
  wait(2, msec);
  turnLeft(90);
  wait(2, msec);
  Drivetrain.drive(forward);
  wait(1500, msec);
  Drivetrain.stop();
  wait(2, msec);
  LBMech.spinFor(forward, 1.5, seconds);
  wait(2, msec);

  driveReverse(16);
  wait(2, msec);
  turnRight(90);
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(48);
  wait(1000, msec);

  driveForward(8);
  wait(2, msec);
  driveReverse(16);
  wait(2, msec);
  
  turnLeft(45);
  wait(2, msec);
  driveForward(10);
  wait(2, msec);

  turnLeft(180);
  wait(2, msec);
  Drivetrain.drive(reverse);
  wait(1500, msec);
  Drivetrain.stop();
  wait(2, msec);
  MogoClamp.set(false);
  wait(2, msec);
  driveReverse(16);
  wait(2, msec);

  turnLeft(45); //allign with wall
  wait(2, msec);
  Drivetrain.drive(forward);
  wait(1500, msec);
  Drivetrain.stop();
  wait(2, msec);
  driveForward(16);
  wait(2, msec);

  //START GREEN PATH//

  turnRight(45);
  wait(2, msec);
  driveForward(67);
  wait(2, msec);
  IntakeMotor.spinFor(forward, 0.5, seconds);
  wait(2, msec);

  turnLeft(90);
  wait(2, msec);
  driveForward(36);
  wait(2, msec);
  IntakeMotor.spinFor(forward, 0.75, seconds);
  wait(2, msec);

  turnRight(135);
  wait(2, msec);
  driveReverse(24);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  turnLeft(45);
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(32);
  wait(2, msec);
  
  turnLeft(135); //grab 4th green ring
}

void redNegativeAuton() {
  driveReverse(24); //grabs mogo
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);
  
  turnRight(135); // scores preload and first ring
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(22);
  wait(500, msec);
  driveReverse(12);
  wait(2, msec);

  turnLeft(90); //scores second ring
  wait(2, msec);
  driveForward(14);
  wait(500, msec);
  driveReverse(6);
  wait(2, msec);

  turnRight(90); //scores third ring
  wait(2, msec);
  driveForward(8);
  wait(500, msec);
  driveReverse(8);
  wait(2, msec);

  IntakeMotor.stop(); //drives to touch ladder
  wait(2, msec);
  turnLeft(45);
  wait(2, msec);
  driveReverse(36);
}

void blueNegativeAuton() {
  driveReverse(24); //grabs mogo
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);
  
  turnLeft(135); // scores preload and first ring
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(22);
  wait(500, msec);
  driveReverse(12);
  wait(2, msec);

  turnRight(90); //scores second ring
  wait(2, msec);
  driveForward(14);
  wait(500, msec);
  driveReverse(6);
  wait(2, msec);

  turnLeft(90); //scores third ring
  wait(2, msec);
  driveForward(8);
  wait(500, msec);
  driveReverse(8);
  wait(2, msec);

  IntakeMotor.stop(); //drives to touch ladder
  wait(2, msec);
  turnRight(45);
  wait(2, msec);
  driveReverse(36);
}

void redPositiveAuton() {
  driveForward(36); //drives forward for mogo rush
  wait(2, msec);
  turnLeft(40);
  wait(2, msec);
  driveForward(6);
  wait(2, msec);

  Doinker.set(true); //grabs contested mogo with doinker then pulls it back and releases it
  wait(2, msec);
  driveReverse(14);
  wait(2, msec);
  Doinker.set(false);
  wait(2, msec);

  turnLeft(180); //turns around and grabs mogo
  wait(2, msec);
  driveReverse(8);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  turnRight(90); //turns and drives forward to grab ring and score preload
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(30);
  wait(2, msec);
  IntakeMotor.stop();
  wait(2, msec);

  turnRight(180); //drops off mogo
  wait(2, msec);
  driveReverse(24);
  wait(2, msec);
  MogoClamp.set(false);
  wait(2, msec);
  driveForward(24);
  wait(2, msec);

  turnRight(90); //grabs second mogo
  wait(2, msec);
  driveReverse(14);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  driveReverse(12); //drives to touch ladder
}

void bluePositiveAuton() {
  driveForward(36); //drives forward for mogo rush
  wait(2, msec);
  turnRight(40);
  wait(2, msec);
  driveForward(6);
  wait(2, msec);

  Doinker.set(true); //grabs contested mogo with doinker then pulls it back and releases it
  wait(2, msec);
  driveReverse(14);
  wait(2, msec);
  Doinker.set(false);
  wait(2, msec);

  turnRight(180); //turns around and grabs mogo
  wait(2, msec);
  driveReverse(8);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  turnLeft(90); //turns and drives forward to grab ring and score preload
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(30);
  wait(2, msec);
  IntakeMotor.stop();
  wait(2, msec);

  turnLeft(180); //drops off mogo
  wait(2, msec);
  driveReverse(24);
  wait(2, msec);
  MogoClamp.set(false);
  wait(2, msec);
  driveForward(24);
  wait(2, msec);

  turnLeft(90); //grabs second mogo
  wait(2, msec);
  driveReverse(14);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  driveReverse(12); //drives to touch ladder
}

void redNegativeElimsAuto() {
  driveReverse(24); //grabs mogo
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);
  
  turnRight(135); // scores preload and first ring
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(22);
  wait(500, msec);
  driveReverse(12);
  wait(2, msec);

  turnLeft(90); //scores second ring
  wait(2, msec);
  driveForward(14);
  wait(500, msec);
  driveReverse(6);
  wait(2, msec);

  turnRight(75); //scores third ring
  wait(2, msec);
  driveForward(8);
  wait(500, msec);
  driveReverse(8);
  wait(2, msec);

  turnLeft(135); //scores fourth ring
  wait(2, msec);
  driveForward(46);
  wait(500, msec);
  driveReverse(16);
  wait(2, msec);

  turnLeft(135); //drives to ending position
  wait(2, msec);
  driveForward(48);
  wait(2, msec);
  IntakeMotor.stop();
}

void blueNegativeElimsAuto() {
  driveReverse(24); //grabs mogo
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);
  
  turnLeft(135); // scores preload and first ring
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(22);
  wait(500, msec);
  driveReverse(12);
  wait(2, msec);

  turnRight(90); //scores second ring
  wait(2, msec);
  driveForward(14);
  wait(500, msec);
  driveReverse(6);
  wait(2, msec);

  turnLeft(75); //scores third ring
  wait(2, msec);
  driveForward(8);
  wait(500, msec);
  driveReverse(8);
  wait(2, msec);

  turnRight(135); //scores fourth ring
  wait(2, msec);
  driveForward(46);
  wait(500, msec);
  driveReverse(16);
  wait(2, msec);

  turnRight(135); //drives to ending position
  wait(2, msec);
  driveForward(48);
  wait(2, msec);
  IntakeMotor.stop();
}

void redPositiveElimsAuto() {
  driveForward(36); //drives forward for mogo rush
  wait(2, msec);
  turnLeft(40);
  wait(2, msec);
  driveForward(6);
  wait(2, msec);

  Doinker.set(true); //grabs contested mogo with doinker then pulls it back and releases it
  wait(2, msec);
  driveReverse(14);
  wait(2, msec);
  Doinker.set(false);
  wait(2, msec);

  turnLeft(180); //turns around and grabs mogo
  wait(2, msec);
  driveReverse(8);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  turnRight(90); //turns and drives forward to grab ring and score preload
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(30);
  wait(2, msec);
  IntakeMotor.stop();
  wait(2, msec);

  turnRight(180); //drops off mogo
  wait(2, msec);
  driveReverse(24);
  wait(2, msec);
  MogoClamp.set(false);
  wait(2, msec);
  driveForward(24);
  wait(2, msec);

  turnRight(90); //grabs second mogo
  wait(2, msec);
  driveReverse(14);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  driveForward(14); //grabs ring in pos corner
  wait(2, msec);
  turnRight(25);
  wait(2, msec);
  driveForward(20);
  wait(2, msec);
  turnLeft(60);
  wait(2, msec);
  driveForward(16);
}

void bluePositiveElimsAuto() {
  driveForward(36); //drives forward for mogo rush
  wait(2, msec);
  turnRight(40);
  wait(2, msec);
  driveForward(6);
  wait(2, msec);

  Doinker.set(true); //grabs contested mogo with doinker then pulls it back and releases it
  wait(2, msec);
  driveReverse(14);
  wait(2, msec);
  Doinker.set(false);
  wait(2, msec);

  turnRight(180); //turns around and grabs mogo
  wait(2, msec);
  driveReverse(8);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  turnLeft(90); //turns and drives forward to grab ring and score preload
  wait(2, msec);
  IntakeMotor.spin(forward);
  wait(2, msec);
  driveForward(30);
  wait(2, msec);
  IntakeMotor.stop();
  wait(2, msec);

  turnLeft(180); //drops off mogo
  wait(2, msec);
  driveReverse(24);
  wait(2, msec);
  MogoClamp.set(false);
  wait(2, msec);
  driveForward(24);
  wait(2, msec);

  turnLeft(90); //grabs second mogo
  wait(2, msec);
  driveReverse(14);
  wait(2, msec);
  MogoClamp.set(true);
  wait(2, msec);

  driveForward(14); //grabs ring in pos corner
  wait(2, msec);
  turnLeft(25);
  wait(2, msec);
  driveForward(20);
  wait(2, msec);
  turnRight(60);
  wait(2, msec);
  driveForward(16);
}