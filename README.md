# Arduino-Playground
Arduino is where the Fire Nation attack occurs
========

Arduino is used for developing Stepper Motor working with Strain gauge for blind testing.  
This is still in development phase for project.
The devices that I used for Arduino is HX711 (Green Board), Stepper Motor (24HS34-3504D), and
DM1182 Digital Microstep Drive.  DM1182 or other Digital Microstep Drive is recommeneded to use
to drive Stepper motor with more voltage and current. Pulse and Direction is only used for this.
Fault and Enable can be used for safety feature.


Features
--------
- AKL
- CookiesMuncher
- DrumTest
- HX711_AKL
- LCDKeypadTest

Installation
------------

Stepper library is already included.
The libraries would be needed to install: AccelStepper and HX711

HX711: https://github.com/bogde/HX711

AccelStepper: https://github.com/adafruit/AccelStepper

I have included Libraries in 'Library' with other Saves.  Also, you can change Arduino IDE's theme
to dark as I included 'DarkArduinoTheme'.

Content
-------

> AKL

AKL is initial code project to test the stepper motor direction and speed.  AKL is code named to 
Arduino Koolness Lab. Right and left buttons control direction which motor will go.  Up and Down
buttons control RPM of motor to spin duration of times.  This can be modified for speed as well.
This is used as base for HX711_AKL to attempt to add HX711 to Arduino and run it same time as
Stepper motor is connected to same Arduino.  This attempt works but it is horribly slow like putting
coffee in car tank and expect to run it.  Therefore Arduino is not good multitasking barebone computer.

> CookiesMuncher

CookiesMuncher is code named for taking data from HX711 just like Computer is eating cookies from
HX711 module.  Ironic name is nice pun for code project as they could use spruce up.  
CookiesMuncher connect to HX711 as it connects to Arduino using A2 and A3 pins.  Then HX711 uses
Strain Gauge 5kg to obtain data results.  Data result will be formatted to grams prior to my
knowledge.

> DrumTest

Old test code with Stepper Motor using AccelStepper library provided by Mike Graybar.  I did not
modify anything on this code and still not able to connect it to Stepper motor.  Will fix this if
I have time but my focus is moved to different focus.

> HX711_AKL

HX711_AKL is additional feature to get output of data result from HX711 and ability to calibrate
it to zero.  So far, it is working but still WIP.  It is currently paused as same thing with
DrumTest and AKL.

> LCDKeypadTest

This used to be testing LCDKeypad functionality but I replaced it with AKL code.  Only difference is
that I modified Up and Down button to change speed of Stepper motor speeds.  It still works but
I do not recommended to change Stepper motor's speed over 300 or 500 unless you like rocky boat.

License
-------

The project is licensed under the BSD license.
