
#include <UTFT.h> 
#include <URTouch.h>

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
        drawDistanceSensor(); // It is called only once, because in the next iteration of the loop, this above if statement will be false so this funtion won't be called. This function will draw the graphics of the first example.
        }
  
      }
    }
  
  // Distance Sensor Example
  if (currentPage == '1') {    
      tempDisplay(); // Gets distance from the sensor and this function is repeatedly called while we are at the first example in order to print the lasest results from the distance sensor
      if (myTouch.dataAvailable()) {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
      }
  }
}
// ====== Custom Funtions ======
// drawHomeScreen - Custom Function
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
  
  // Button - RGB LED Control
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
void drawDistanceSensor() {
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
  
 

  //LR Wheel Outer
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (30, 140, 60, 200);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (30, 140, 60, 200);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  
  //LR Wheel Inner
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (61, 140, 91, 200);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (61, 140, 91, 200);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  
  //RR Wheel Outer
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (100, 140, 130, 200);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (100, 140, 130, 200);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  
  //RR Wheel Inner
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (131, 140, 161, 200);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (131, 140, 161, 200);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  
//----------------------------------------------------------------------------------------------------
   //LF Wheel Outer
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (30, 130, 60, 70);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (30, 130, 60, 70);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  
  //LF Wheel Inner
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (61, 130, 91, 70);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (61, 130, 91, 70);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  
  //RF Wheel Outer
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (100, 130, 130, 70);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (100, 130, 130, 70);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
  
  //RF Wheel Inner
  myGLCD.setColor(223, 77, 55);
  myGLCD.fillRoundRect (131, 130, 161, 70);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (131, 130, 161, 70);
  myGLCD.setBackColor(223, 77, 55);
  myGLCD.setColor(255, 255, 255);
 
}
void tempDisplay(){

}

/*
//====================================================
//===== getDistance - Custom Function

 * void getDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distanceCm= duration*0.034/2;
  distanceInch= distanceCm/2.53;
  // Prints the distance in centimeters
  if (selectedUnit == '0' && distanceCm <=400) {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceCm,130, 145, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("cm  ", 235, 178);
  
  }
  // Prints the distance in inches
  if (selectedUnit == '1' && distanceCm <=160) {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(0, 255, 0);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.printNumI(distanceInch,130, 145, 3,'0');
    myGLCD.setFont(BigFont);
    myGLCD.print("inch", 235, 178);
  } 
  delay(10);
}
*/
//====================================================

  // Maps the values of the X - Axis from 38 to 0 and 310 to 255, because we need values from 0 to 255 for turning on the led
