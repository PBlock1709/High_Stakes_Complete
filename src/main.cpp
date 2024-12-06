/*
PORTS:
  Drivetrain left: 12, 13, 14
  Drivetrain right: 4, 5, 8 
  Lady brown: 19
  Intake/conveyor: 18
THREE WIRE CONNECTIONS:
  Mobile goal mechanism: A
  Doinker: B
*/

#include "vex.h"
#include <cmath>
#include "robot-config.h"
#include "autonomous.h"
#include "autonSelect.h"

using namespace vex;


//define variables
int liftMacroVar = 1;
int doinkCount = 0;
int intakeLiftCount = 0;
int colorSort = 1;
int aselection = -1;


//joystick curve math
int turningCurve = 20;
bool turningRed = true;

int forwardCurve = 20;
bool forwardRed = true;

//graph of red and blue lines here
//https://www.desmos.com/calculator/sdcgzah5ya
int curveJoystick(bool red, int input, double t){
  int val = 0;
  if(red){
    val = (std::exp(-t/10)+std::exp((std::abs(input)-100)/10)*(1-std::exp(-t/10))) * input;
  }else{
    //blue
    val = std::exp(((std::abs(input)-100)*t)/1000) * input;
  }
  return val;
}

//define some macros
void printTeamLogo() {
  if (aselection == 0) {
    Brain.Screen.setPenColor(red);
    Brain.Screen.setFillColor(black);
  } else if (aselection == 1) {
    Brain.Screen.setPenColor(red);
    Brain.Screen.setFillColor(black);
  } else if (aselection == 2) {
    Brain.Screen.setPenColor(blue);
    Brain.Screen.setFillColor(black);
  } else if (aselection == 3) {
    Brain.Screen.setPenColor(red);
    Brain.Screen.setFillColor(black);
  } else if (aselection == 4) {
    Brain.Screen.setPenColor(blue);
    Brain.Screen.setFillColor(black);
  } else if (aselection == 5) {
    Brain.Screen.setPenColor(yellow);
    Brain.Screen.setFillColor(black);
  }

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("   .d8888b.   d888   .d8888b.    888       888   "); Brain.Screen.newLine();
  Brain.Screen.print("  d88P  Y88b d8888  d88P  Y88b   888   o   888   "); Brain.Screen.newLine();
  Brain.Screen.print("       .d88P   888  888          888  d8b  888   "); Brain.Screen.newLine();
  Brain.Screen.print("      8888     888  d888888b.    888 d888b 888   "); Brain.Screen.newLine();
  Brain.Screen.print("        Y8b.   888  888P  Y88b   888d88888b888   "); Brain.Screen.newLine();
  Brain.Screen.print("  888    888   888  888    888   88888P Y88888   "); Brain.Screen.newLine();
  Brain.Screen.print("  Y88b  d88P   888  Y88b. d88P   8888P   Y8888   "); Brain.Screen.newLine();
  Brain.Screen.print("   'Y8888P'  8888888 'Y8888P'    888P     Y888   "); Brain.Screen.newLine();
}

void liftMacro() {
  if (liftMacroVar == 1) {
      liftMacroVar = 2;
      LBMech.spinTo(-57, degrees);
  } else if (liftMacroVar == 2) {
    liftMacroVar = 3;
    LBMech.spinTo(-285, degrees);
  } else if (liftMacroVar == 3) {
    liftMacroVar = 1;
    LBMech.spinTo(0, degrees);
  }
}

void MogoCode() {
  if (MogoClamp.value() == false) {
    MogoClamp.set(true);
  } else if (MogoClamp.value() == true) {
    MogoClamp.set(false);
  } else {
    
  }
}

void doinkCode() {
  if (Doinker.value() == false) {
    Doinker.set(true);
  } else {
    Doinker.set(false);
  }
}

/*void specialDoinkCode() {
  if (Doinker.value() == false) {
    if (doinkCount < 4) {
      Doinker.set(true);
      doinkCount = doinkCount + 1;
    } else {

    }
  } else if (Doinker.value() == true) {
    Doinker.set(false);
  } else {

  }
}*/

/*
void IntakeLiftCode() {
  if (IntakeLift.value() == false) {
    if (intakeLiftCount < 4) {
      IntakeLift.set(true);
      intakeLiftCount = intakeLiftCount + 1;
    } else {

    }
  } else if (IntakeLift.value() == true) {
    IntakeLift.set(false);
  } else {

  }
}
*/

/*void colorSortToggle() {
  if (colorSort == 1) {
    colorSort = 0;
  } else if (colorSort == 0) {
    colorSort = 1;
  } else {
    colorSort = 1;
  }
}*/




//AUTON CODE//
void autonCode(void) {
  printTeamLogo();
  LBMech.setStopping(hold);
  IntakeMotor.setVelocity(100, percent);
  LBMech.setVelocity(75, percent);
  Drivetrain.setDriveVelocity(25, percent);
  Drivetrain.setTurnVelocity(20, percent);
  MogoClamp.set(false);


  if (aselection == 0) {
    //do nothing
  } else if (aselection == 1) { //red negative auton
    redNegativeAuton();
  } else if (aselection == 2) { //blue negative auton
    blueNegativeAuton();
  } else if (aselection == 3) { //red positive auton
    redPositiveAuton();
  } else if (aselection == 4) { //blue positive auton
    bluePositiveAuton();
  } else if (aselection == 5) { //skills auton
    skillsAuton();
  }
}


///DRIVER CONTROL///
void driverControl(void) {
  //simple stuff really
  printTeamLogo();
  Controller.ButtonL2.pressed(liftMacro);
  Controller.ButtonY.pressed(doinkCode);
  Controller.ButtonL1.pressed(MogoCode);
  //Controller.ButtonY.pressed(IntakeLiftCode);
  //Controller.ButtonDown.pressed(colorSortToggle);
  Drivetrain.setStopping(brake);
  LBMech.setStopping(hold);
  IntakeMotor.setVelocity(100, percent);
  LBMech.setVelocity(75, percent);
  //Optical1.setLight(ledState::on);
  
  
  while(1){ //use this section to continually look for conditions (check if controller button is pressed, check state of motor, etc)
    double turnVal = curveJoystick(false, Controller.Axis1.position(percent), turningCurve); //Get curvature according to settings [-100,100]
    double forwardVal = curveJoystick(false, Controller.Axis3.position(percent), forwardCurve); //Get curvature according to settings [-100,100]

    double turnVolts = turnVal * 0.12; //Converts to voltage
    double forwardVolts = forwardVal * 0.12; //Converts to voltage

    LeftDriveSmart.spin(forward, forwardVolts + turnVolts, voltageUnits::volt); //Apply Via Voltage
    RightDriveSmart.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);


    if (Controller.ButtonR1.pressing()) {
      IntakeMotor.spin(forward);
    } else if (Controller.ButtonR2.pressing()) {
      IntakeMotor.spin(reverse);
    } else {
      IntakeMotor.stop();
    }


    /*
    //USE THIS IF LADYBROWN MACRO ISNT WORKING
    if (Controller.ButtonY.pressing()) {
      LBMech.spin(reverse);
    } else if (Controller.ButtonRight.pressing()) {
      LBMech.spin(forward);
    } else {
      LBMech.stop();
    }*/
    

    /*
    //THIS SECTION OF CODE USES TOO MUCH RAM
    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("Left:%.1f", leftMotorA.temperature(fahrenheit),",", leftMotorB.temperature(fahrenheit), ",", leftMotorC.temperature(fahrenheit) );
    Controller.Screen.newLine();
    Controller.Screen.print("Right:%.1f", rightMotorA.temperature(fahrenheit),",", rightMotorB.temperature(fahrenheit), ",", rightMotorC.temperature(fahrenheit) );
    Controller.Screen.newLine();
    Controller.Screen.print("Intake:%.1f", IntakeMotor.temperature(fahrenheit));*/



    this_thread::sleep_for(20);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


  bool unconfirmed = true;

  Brain.Screen.clearScreen("black");
  confirm.setPenColor("#0f990b");
  drawTonomous();

  //use coordinate presser for exact spacing
  while(unconfirmed){
    if(Brain.Screen.pressing()){
      if(redButton.pressing()){
        ColorChosen = 1;
        redNeg.moveTo(xplace,redNeg.yPos);
        redPos.moveTo(xplace,redPos.yPos);
        blueNeg.moveTo(1000,blueNeg.yPos);
        bluePos.moveTo(1000,bluePos.yPos);
        drawTonomous();
      }
      else if (blueButton.pressing()){
        ColorChosen = 2;
        redNeg.moveTo(1000,redNeg.yPos);
        redPos.moveTo(1000,redPos.yPos);
        blueNeg.moveTo(xplace,blueNeg.yPos);
        bluePos.moveTo(xplace,bluePos.yPos);
        drawTonomous();
      }
      else if (ColorChosen == 1){
        if(redNeg.pressing()){
          aselection = 1;
          drawTonomous();
        }
        else if (redPos.pressing()){
          aselection = 3;
          drawTonomous();
        }
      }
      else if (ColorChosen == 2){
        if(blueNeg.pressing()){
          aselection = 2;
          drawTonomous();
        }
        else if (bluePos.pressing()){
          aselection = 4;
          drawTonomous();
        }
      }
      if (skills.pressing()){
        aselection = 5;
        drawTonomous();
      }
      if (none.pressing()){
        aselection = 0;
        drawTonomous();
      }
    }


    if(aselection >-1){  
      switch(aselection){
        case 0: Brain.Screen.printAt(200, 200, "none");
          break;
        case 1: Brain.Screen.printAt(200, 200, "Red Neg");
          break;
        case 2: Brain.Screen.printAt(200, 200, "Blue Neg");
         break;
        case 3: Brain.Screen.printAt(200, 200, "Red Pos");
         break;
        case 4: Brain.Screen.printAt(200, 200, "Blue Pos");
          break;
        case 5: Brain.Screen.printAt(200, 200, "skills auton");
          break;
      }
      if(confirm.pressing()){
        unconfirmed = false;
      }
    }
    else{
      if(confirm.pressing()){
        Brain.Screen.printAt(150, 220, "Please select an option");
      }
    }
    this_thread::sleep_for(50);
  }
  Brain.Screen.clearScreen();
  
  

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  //competition setup
  competition Competition;
  Competition.autonomous(autonCode);
  Competition.drivercontrol(driverControl);
}