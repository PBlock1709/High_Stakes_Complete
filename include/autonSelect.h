#include "vex.h"
#include "ButtonClass.h"

using namespace vex;


int xplace = 70;
int xplace2 = 380;
int ColorChosen = 1;

lcdButton redButton(120, 22, 230, 35, "RED", "#252525","#FF2525",2);
lcdButton blueButton(480-120, 22, 230, 35, "BLUE", "#252525", "#2525FF", 2);

lcdButton confirm(230,150,100,60, "CONFIRM","#14c40e", "#0f990b", 4);
lcdButton none(xplace,90,120,40, "None", "#252525");

lcdButton redNeg(xplace,135,120,40, "Red Negative", "#FF2525", "#FFFFFF", 2);//, color(255, 33, 33));
lcdButton redPos(xplace,180,120,40, "Red Positive", "#FF2525", "#FFFFFF", 2);//, color(255, 33, 33));
lcdButton blueNeg(1000,135,120,40, "Blue Negative", "#2525FF", "#FFFFFF", 2); //figure out color scheme
lcdButton bluePos(1000,180,120,40, "Blue Positive", "#2525FF", "#FFFFFF", 2);

lcdButton redNegElims(xplace2,135,150,40, "Red Neg Elims", "FF2525", "#FFFFFF", 2);
lcdButton redPosElims(xplace2,180,150,40, "Red Pos Elims", "FF2525", "#FFFFFF", 2);
lcdButton blueNegElims(1000,135,150,40, "Blue Neg Elims", "2525FF", "#FFFFFF", 2);
lcdButton bluePosElims(1000,180,150,40, "Blue Pos Elims", "2525FF", "#FFFFFF", 2);

lcdButton skills(xplace,225,120,40, "Skills", "#252525");


void drawTonomous(){
  Brain.Screen.clearScreen("black");
  Brain.Screen.setPenColor(white);
  Brain.Screen.setPenWidth(2);
  Brain.Screen.drawLine(0,60,500,60);
  redButton.draw();
  blueButton.draw();
  confirm.draw();
  none.draw();
  redNeg.draw();
  redPos.draw();
  blueNeg.draw();
  bluePos.draw();
  redNegElims.draw();
  redPosElims.draw();
  blueNegElims.draw();
  bluePosElims.draw();
  skills.draw();
}

