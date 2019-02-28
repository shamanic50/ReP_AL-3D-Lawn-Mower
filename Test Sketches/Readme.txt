
Description of the test sketches and what they do.
==================================================


Relay_Test:
If the relay is correctly wired to the MEGA the sketch turns the relay on and off at 1 second intervals.
If the relay is not working check that pin24 is really being used.  The pins are labeled so that its easily done to use the wrong pin.


Test Coms MEGA NANO:
Checks that the serial communication between the MEGA and the NANO is working.
Open the sketch in 2 seperate ARDUINO IDE editors.  then run the serial mointor of the MEGA (Baud 115200) and the NANO (Baud 9600)
If all is working well you should see the same Amps and Volts reading on each serial monitor.
