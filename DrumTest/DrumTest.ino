
#include <AccelStepper.h>
#include <LiquidCrystal.h>

#define STEP_PIN 3  // Step pin
#define DIR_PIN 11  // Direction pin

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

boolean top_ready = false;  // Whether top position is set
boolean bottom_ready = false;  // Whether bottom position is set
boolean started = false;
int bottom_position = 100;  // Step position of bottom limit
int cycle_count = 0;  // Cycle counter
int bump_distance = 200;  // Steps for the incremental move

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Define a stepper and the pins it will use
AccelStepper stepper(1, STEP_PIN, DIR_PIN);

// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  // For V1.0 comment the other threshold and use the one below:
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;

  return btnNONE;  // when all others fail, return this...
}

void bump_down() { // Move a small increment during setup
  stepper.move(bump_distance);
  stepper.run();
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

void bump_up() { // Move a small increment up during setup
  stepper.move(-bump_distance);
  stepper.run();
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

void setup() {
  lcd.begin(16, 2);              // start the library

  stepper.setPinsInverted(true);
  stepper.setMaxSpeed(400);
  stepper.setAcceleration(200);
  stepper.setCurrentPosition(0);
}

void loop() {
  if (!top_ready) { // Test has not been started yet (after a reset)
    lcd.setCursor(0, 0);
    lcd.print("MOVE TO TOP");

    while (!top_ready) {
      lcd.setCursor(0, 1);
      lcd_key = read_LCD_buttons();
      switch (lcd_key) {
        case btnUP:
          {
            lcd.print("UP");
            bump_up();
            break;
          }
        case btnDOWN:
          {
            lcd.print("DOWN");
            bump_down();
            break;
          }
        case btnSELECT:
          {
            lcd.print("READY");
            stepper.setCurrentPosition(0);
            top_ready = true;
            lcd.clear();
            delay(500);  // fake debounce
            break;
          }
        case btnNONE:
          {
            lcd.print("            ");
            break;
          }
      }
    }
  }
  if (!bottom_ready) {
    lcd.setCursor(0, 0);
    lcd.print("MOVE TO BOTTOM");

    while (!bottom_ready) {
      lcd.setCursor(0, 1);
      lcd_key = read_LCD_buttons();
      switch (lcd_key) {
        case btnUP:
          {
            lcd.print("UP");
            bump_up();
            break;
          }
        case btnDOWN:
          {
            lcd.print("DOWN");
            bump_down();
            break;
          }
        case btnSELECT:
          {
            lcd.print("READY");
            bottom_position = stepper.currentPosition();
            bottom_ready = true;
            lcd.clear();
            lcd.setCursor(8, 1);
            lcd.print(bottom_position);
            delay(500);  // fake debounce
            break;
          }
        case btnNONE:
          {
            lcd.print("            ");
            break;
          }
      }
    }
  }
  if ((top_ready && bottom_ready) && !started) {
    lcd.setCursor(0, 0);
    lcd.print("SELECT TO START");

    while (!started) {
      lcd_key = read_LCD_buttons();
      switch (lcd_key) {
        case btnUP:
          {
            stepper.moveTo(0);
            while (stepper.distanceToGo() != 0) {
              stepper.run();
            }
            break;
          }
        case btnDOWN:
          {
            stepper.moveTo(bottom_position);
            while (stepper.distanceToGo() != 0) {
              stepper.run();
            }
            break;
          }
        case btnSELECT:
          {
            lcd.setCursor(0, 1);
            lcd.print("GO");
            started = true;
            lcd.clear();
            break;
          }
        case btnNONE:
          {
            break;
          }
      }
    }
  }

  if (started) {  // All setup completed
    while (cycle_count <= 4000) {
      delay(50);
      lcd.setCursor(0, 0);
      lcd.print("CYCLE COUNT:");

      lcd.setCursor(0, 1);
      lcd.print(cycle_count);

      /* Send up */
      lcd.setCursor(12, 1);
      lcd.print("UP  ");
      stepper.moveTo(0);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }

      /* Dwell up */
      lcd.setCursor(12, 1);
      lcd.print("WAIT");
      delay(5000);

      /* Send down */
      lcd.setCursor(12, 1);
      lcd.print("DOWN");
      delay(50);
      stepper.moveTo(bottom_position);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }

      /* Dwell down */
      lcd.setCursor(12, 1);
      lcd.print("WAIT");
      delay(5000);

      cycle_count++;
      lcd.setCursor(0, 1);
      lcd.print(cycle_count);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("COMPLETE");

  }
}

