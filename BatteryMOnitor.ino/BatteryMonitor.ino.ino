/* This is my first attempt to make a program for the Arduino that i can use in the
 *  real world.  It will monitor 9 x 1.4 volt lead acid batteries that are wired in 
 *  series for an off grid application. They are charged with a 140w solar panel.
 *  
 *  This application will monitor the individual cells, give a total voltage and
 *  will also measure the current draw on the batteries with a shunt.
 *  
 *  Using Arduino MEGA 2560
 *  
 *  To do:
 *  - Solar Tracker
 *  - Add additional 12v gel batteries / bank to monitor
 *  - Add program to compare gel vs/ lead acid banks and charge/discharge based on levels
 */

// START heartbeat LED (just so I know its doing something)
long heartBeatArray[] = {
    50, 100, 15, 1200};
int hbeatIndex = 1;   // initialization
long prevMillis;
int LEDpin = 13;
// END Heartbeat LED

// include the LCD library code
#include <LiquidCrystal.h>

// initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Set up the eight custom Glyphs, found this in Arduino Cookbook and modified
byte eightGlyph[8] = {B11111, B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};
byte sevenGlyph[8] = {B00000, B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};
byte sixGlyph[8] = {B00000, B00000,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};
byte fiveGlyph[8] = {B00000, B00000,  B00000,  B11111,  B11111,  B11111,  B11111,  B11111};
byte fourGlyph[8] = {B00000, B00000,  B00000,  B00000,  B11111,  B11111,  B11111,  B11111};
byte threeGlyph[8] = {B00000, B00000,  B00000,  B00000,  B00000,  B11111,  B11111,  B11111};
byte twoGlyph[8] = {B00000, B00000,  B00000,  B00000,  B00000,  B00000,  B11111,  B11111};
byte oneGlyph[8] = {B00000, B00000,  B00000,  B00000,  B00000,  B00000,  B00000,  B11111};

void setup() {
    // setup the heartbeat LED output
  pinMode(LEDpin, OUTPUT);
  
    // setup serial communications from Arduino at 9600bps if required to debug
  // Serial.begin(9600);

    // set up the battery monitor glyphs
  lcd.createChar(8, eightGlyph);
  lcd.createChar(7, sevenGlyph);
  lcd.createChar(6, sixGlyph);
  lcd.createChar(5, fiveGlyph);
  lcd.createChar(4, fourGlyph);
  lcd.createChar(3, threeGlyph);
  lcd.createChar(2, twoGlyph);
  lcd.createChar(1, oneGlyph);
  lcd.begin(16, 2); 
  lcd.clear();
  delay(1000);  // for testing
}

// Function to write the custom glyphs to the LCD. Values sent to this fuction is the battery
// voltage and the position on the LCD screen. LCD character is is 5x8, we are using one
// stacked on top of the other for a total of 16x5. 
// Battery voltage is X 10 to move the decimal.
void displayLevel(int batval, int batpos){
  if(batval >= 8){
    lcd.setCursor(batpos,1);
    lcd.write(byte(8));    
    lcd.setCursor(batpos,0);
    int math = (batval - 8);
      if(math == 0){
        lcd.write("");
      }
      else{
        lcd.write(byte(math));        
      }
  }
  else{
      if(batval > 0){
        lcd.setCursor(batpos,1);
        lcd.write(byte(batval));    
        lcd.setCursor(batpos,0);
        lcd.write("");    
      }
      else{
        lcd.setCursor(batpos,1);
        lcd.write("");    
        lcd.setCursor(batpos,0);
        lcd.write("");
      }
  }
}

void loop() {
    // Heartbeat variable for speed
  heartBeat(2.0);

    // Battery reads and sending values to fuction
    // Battery level #1
  int bat1val = 0;  // will be an analog input when ready to test inputs, static value for programming
  int bat1pos = 7;  // where to dispay bar on LCD
  displayLevel(bat1val,bat1pos);  // values passed to the displayLevel function
  
    // Battery level #2
  int bat2val = 1; 
  int bat2pos = 8;
  displayLevel(bat2val,bat2pos);
    // Battery level #3
  int bat3val = 16; 
  int bat3pos = 9;
  displayLevel(bat3val,bat3pos);
    // Battery level #4
  int bat4val = 0; 
  int bat4pos = 10;
  displayLevel(bat4val,bat4pos);
    // Battery level #5
  int bat5val = 7; 
  int bat5pos = 11;
  displayLevel(bat5val,bat5pos);
    // Battery level #6
  int bat6val = 8; 
  int bat6pos = 12;
  displayLevel(bat6val,bat6pos);
    // Battery level #7
  int bat7val = 9; 
  int bat7pos = 13;
  displayLevel(bat7val,bat7pos);
    // Battery level #8
  int bat8val = 16; 
  int bat8pos = 14;
  displayLevel(bat8val,bat8pos);
    // Battery level #9
  int bat9val = 15; 
  int bat9pos = 15;
  displayLevel(bat9val,bat9pos);

  //float batTotal = 12.2;  // for testing
  float batTotal = ((bat1val+bat2val+bat3val+bat4val+bat5val+bat6val+bat7val+bat8val+bat9val) * 0.1);
  lcd.setCursor(0,0);
  lcd.print("2.50 A");   // static value for testing
  lcd.setCursor(0,1);
  lcd.print(batTotal,2);   // display voltage total for the 9 cells
  lcd.setCursor(5,1);
  lcd.print("v");

  // Send data THEN start a new line
  // Serial.println(batTotal);
  
  delay(250);
}


// Heartbeat function found online... somewhere
void heartBeat(float tempo){
    if ((millis() - prevMillis) > (long)(heartBeatArray[hbeatIndex] * tempo)){
        hbeatIndex++;
        if (hbeatIndex > 3) hbeatIndex = 0;

        if ((hbeatIndex % 2) == 0){ 
            digitalWrite(LEDpin, HIGH); 
            delay((int)heartBeatArray[hbeatIndex]) ;   
            digitalWrite(LEDpin, LOW); 
        }
        hbeatIndex++;
        // Serial.println(hbeatIndex);
        prevMillis = millis();
    }
}
