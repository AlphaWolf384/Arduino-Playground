//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
#include <Stepper.h>

/*******************************************************

This program will test the stepper motor direction and speed.

********************************************************/

const int STEPS = 400;

int lcd_key     = 0;
int adc_key_in  = 0;
int SPEED = 60;        // 60 RPM for default setting
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define ADCwidth 12
#define ADCCsteps pow(2, ADCwidth)
#define maxSpeed 256 // RPM

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
 Serial.begin(9600);
 lcd.begin(16, 2);              // start the library
}
 
void loop()
{
 lcd.setCursor(0,0);            
 lcd.print("Rt ");
 lcd.print(millis()/1000);      // display seconds elapsed since power-up
 lcd.print(" | ");
 lcd.print(SPEED);
 lcd.print(" RPM");


 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("Clockwise ");
     myStepper.setSpeed(SPEED);
     myStepper.step(STEPS);
     break;
     }
   case btnLEFT:
     {
     lcd.print("C-Clockwise   ");
     myStepper.setSpeed(SPEED);
     myStepper.step(-STEPS);
     break;
     }
   case btnUP:
     {
     lcd.print("Speed++10    ");
     SPEED = SPEED + 10;
     delay(200);
     break;
     }
   case btnDOWN:
     {
     lcd.print("Speed--10  ");
     SPEED = SPEED - 10;
     delay(200);
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     break;
     }
     case btnNONE:
     {
     lcd.print("      NONE      ");
     break;
     }
 }

}

