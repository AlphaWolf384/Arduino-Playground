#include <LiquidCrystal.h>
#include <HX711.h>

/*******************************************************

This program will output data from HX711 modular and addition of set to Zero is added.

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
HX711 scale(A3, A2);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
int peak1 = 0;
int peak2 = 0;
int array[] = {};

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
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
 lcd.begin(16, 2);              // start the library

 scale.set_scale(696.0);       // Calibration scale with user input
 scale.tare();                  // Set it to 0
}

// NOTE: 696.0 is calibration factor for 5kg strain gauge and Calibration code is used in HX711_ADC
 
void loop() 
{
 float unit = scale.get_units();
 // Update Peaks for both sides
 if (peak1 < unit)
 {
  peak1 = unit;
 }
 if (peak2 > unit)
 {
  peak2 = unit;
 }
  
 lcd.setCursor(0,0); // Peak1 for left(positive)
 lcd.print(peak1);
 
 lcd.setCursor(8,0);
 lcd.print("|"); // Split Peaks to both side, left is Positive and right is Negative

 lcd.setCursor(9,0);  // Peak2 for right(negative)
 lcd.print(peak2);

 lcd.setCursor(15,1);
 lcd.print("g"); 
 lcd.setCursor(8,1);            
 lcd.print(abs(unit));     

 // Helps to clear up any numbers that are left behind
 delay(300);
 lcd.print("        ");
 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("RIGHT ");
     break;
     }
   case btnLEFT:
     {
     lcd.print("LEFT   ");
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("Set 0 ");  // Calibrate to Zero
     scale.set_scale(2280.f);
     scale.tare();
     
     lcd.setCursor(0,0);  // Set peak1 to 0
     lcd.print("        ");
     peak1 = 0;
     
     lcd.setCursor(9,0);  // Set peak2 to 0
     lcd.print("        ");
     peak2 = 0;
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
 }

}

