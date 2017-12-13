//Libraries
#include <LiquidCrystal.h>
#include <Stepper.h>

/*******************************************************

This program will test the stepper motor direction and speed.
Dominic Ricchio, November 2017

********************************************************/

int STEPS = 1000;

int lcd_key     = 0;
int adc_key_in  = 0;
int SPEED = 150;        // 150 RPM for default setting
int directionCYCLE = 0;        // Right direction for default
int CYCLE = 50;        // 50 Cycles
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Stepper myStepper(STEPS, 10, 11, 12, 13);

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   



 return btnNONE;  // when all others fail, return this...
}

void setup()
{
 Serial.print("Initializing setup");
 Serial.begin(9600);
 lcd.begin(16, 2);              
 Serial.print("Setup is complete");
}

void loop(){
  setupDisplay(); // Update Display per cycle
  btnControl();   // Control Stepper motor
}

void setupDisplay(){
 lcd.setCursor(0,0);            
 lcd.print(millis()/1000);  
 lcd.print("|");
 lcd.print("RPM: ");
 lcd.print(STEPS);
}

void btnControl(){
 
 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("Clockwise  ");
     myStepper.setSpeed(SPEED); // Control Motor rotation speed
     myStepper.step(STEPS);     // Control Motor cycles to start and end
     break;
     }
   case btnLEFT:
     {
     lcd.print("C-Clockwise");
     myStepper.setSpeed(SPEED);
     myStepper.step(-STEPS);
     break;
     }
   case btnUP:
     {
     lcd.print("RPM++10    ");
     STEPS = STEPS + 1000; // Feature to add more RPM for STEPS
     delay(200);          // For convienent to input between delays to add numbers
     break;
     }
   case btnDOWN:
     {
     lcd.print("RPM--10    ");
     STEPS = STEPS - 1000;
     delay(200);
     break;
     }
   case btnSELECT:
     {
      lcd.print("STOP");      // Feature to shut down but this doesn't work if motor is already running
      myStepper.setSpeed(0);  // WIP
      myStepper.step(0);
     break;
     }
   case btnNONE:
     {
      lcd.print("NONE       "); // Default message on LCD screen
      break;
     }
 }
}






