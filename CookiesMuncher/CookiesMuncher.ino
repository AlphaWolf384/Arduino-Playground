//Libraries
#include <LiquidCrystal.h>
#include <HX711.h>

/*******************************************************

This program will test the output from HX711.

A2 = SCK (Black)
A3 = DT (White)

********************************************************/

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
HX711 scale(A3,A2); // A2 and A3 pins used on LCD Keypad

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  Serial.println("HX711 Cookies");

  Serial.println("Initializing the scale");
  Serial.print("Read: \t\t");
  Serial.println(scale.read()); // Print raw reading

  Serial.print("Average: \t");
  Serial.println(scale.read_average(20)); // Average of 20 readings 

  Serial.print("Units: \t\t");
  Serial.println(scale.get_units(5), 1);  // Correct reading after initials

  scale.set_scale(2280.f);  // Set to gram calibration scale
  scale.tare(); // Set scale to zero

  Serial.println("Setup is completed");
  Serial.print("Read: \t\t");
  Serial.println(scale.read()); // Print raw reading

  Serial.print("Average: \t");
  Serial.println(scale.read_average(20)); // Average of 20 readings 

  Serial.print("Units: \t\t");
  Serial.println(scale.get_units(5), 1);  // Correct reading after initials

  Serial.println(" ==== Reading begins below ==== ");
  
}
 
void loop()
{
  
  Serial.print("Unit: \t"); // One unit each in Grams
  Serial.print(abs(scale.get_units()), 1);
  Serial.print("\t | Average: \t"); // 10 units averagely
  Serial.println(abs(scale.get_units(10)), 1);

  lcd.setCursor(0,0);
  lcd.print("Unit = ");
  lcd.print(abs(scale.get_units()), 1); // Same as above

  lcd.setCursor(0,1);
  lcd.print("Avg. = ");
  lcd.print(abs(scale.get_units(10)), 1); // Same as above

}






