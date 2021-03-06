
#include <UTFT.h> 
#include <URTouch.h>
#include <SD.h>
#include <SPI.h>

//==== Creating Objects
UTFT    myGLCD(ILI9341_16,38,39,40,41); //Parameters should be adjusted to your Display/Shield model
URTouch  myTouch( 6, 5, 4, 3, 2);

//==== Defining Variables
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

int x, y;
char currentPage, selectedUnit;

void setup() {
// Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  drawHomeScreen();  // Draws the Home Screen
  currentPage = '0'; // Indicates that we are at Home Screen
  selectedUnit = '0'; // Indicates the selected unit for the first example, cms or inches
}

void loop() { 

  // Home Screen
  if (currentPage == '0') {
    
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x=myTouch.getX(); // X coordinate where the screen has been pressed
      y=myTouch.getY(); // Y coordinates where the screen has been pressed

      // If we press the Live Temp Display Button
      if ((x>=35) && (x<=285) && (y>=90) && (y<=130)) {
        drawFrame(35, 90, 285, 130); // Custom Function -Highlighs the buttons when it's pressed
        currentPage = '1'; // Indicates that we are the first example
        myGLCD.clrScr(); // Clears the screen
        liveTemps(); // It is called only once, because in the next iteration of the loop, this above if statement will be false so this funtion won't be called. This function will draw the graphics of the first example.
        }
      }
    }
  
  // Live Temp Display
  if (currentPage == '1') {    
      //tempDisplay(); // Gets distance from the sensor and this function is repeatedly called while we are at the first example in order to print the lasest results from the distance sensor
      if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
      }  
    // If we press the Back Button
        if ((x>=10) && (x<=60) &&(y>=10) && (y<=36)) {
          drawFrame(10, 10, 60, 36);
          currentPage = '0'; // Indicates we are at home screen
          myGLCD.clrScr();
          drawHomeScreen(); // Draws the home screen
        }
    }
}

void drawHomeScreen() {
  // Title
  myGLCD.setBackColor(0,0,0); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.print("Tire Temp Sense", CENTER, 10); // Prints the string on the screen
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0,32,319,32); // Draws the red line
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setFont(SmallFont); // Sets the font to small
  myGLCD.print("Racecars suck, dont bother", CENTER, 61); // Prints the string

  // Button - Live Tire Temps
  myGLCD.setColor(16, 167, 103); // Sets green color
  myGLCD.fillRoundRect (35, 90, 285, 130); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (35, 90, 285, 130); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("Live Tire Temps", CENTER, 102); // Prints the string
  
  // Button - Data Logging
  myGLCD.setColor(16, 167, 103);
  myGLCD.fillRoundRect (35, 140, 285, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (35, 140, 285, 180);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(16, 167, 103);
  myGLCD.print("Start Logger", CENTER, 152);

}
// Highlights the button when pressed
void drawFrame(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (x1, y1, x2, y2);
}
//====================================================
void liveTemps() {
  myGLCD.setColor(100, 155, 203);
  myGLCD.fillRoundRect (10, 10, 60, 36);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 10, 60, 36);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(100, 155, 203);
  myGLCD.print("<-", 18, 15);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 70, 18);
  myGLCD.setFont(BigFont);
  myGLCD.print("Tire Temperatures", CENTER, 45);




//=== Wheel Labels ===
  myGLCD.setFont(SmallFont);
  myGLCD.print("LF", 10, 110);
  myGLCD.print("RF", 240, 110);
  myGLCD.print("LR", 10, 180);
  myGLCD.print("RR", 240, 180);
  
//=== LEFT WHEELS ===
  for(double i = 30; i <= 100; i+=31){ //start at x = 30, add 31 up to 92 (3 iterations)
      for (double j = 70; j <= 165; j+=71){ //start at y = 75, add 71 up to 170 
        j = j+8; //spaces front and rear wheel sections
      myGLCD.setColor(223, 77, 55);
      myGLCD.fillRoundRect (i, j, i+31, j+71); //+31 adds equal section width, +71 adds equal section height
      myGLCD.setColor(255, 255, 255);
      myGLCD.drawRoundRect (i, j, i+31, j+71);
      myGLCD.setBackColor(223, 77, 55);
      myGLCD.setColor(255, 255, 255);
      }
  }

//=== RIGHT WHEELS ===
  for(double g = 140; g <= 210; g+=31){
      for (double z = 70; z <= 165; z+=71){
          z = z+8; 
      myGLCD.setColor(223, 77, 55);
      myGLCD.fillRoundRect (g, z, g+31, z+71); 
      myGLCD.setColor(255, 255, 255);
      myGLCD.drawRoundRect (g, z, g+31, z+71);
      myGLCD.setBackColor(223, 77, 55);
      myGLCD.setColor(255, 255, 255);
      }
  }
 
}
