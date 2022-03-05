# Read capacitive input, calibrate it and transmit it as MIDI CC

1) In this example we will read one capacitive (touch) pin of the Teensy LC. Add a jumper cable (in the püicture below it is blue) to the pin 1. You can also physically connect a electrolytic object to the cable (fruits, wood, some plastics, etc)

![alt text](teensy-onetouch-calibrated.png)

2) Use the code from this example alone: https://github.com/ultranoise/teensyMIDItoolkit/blob/master/oneTouch-calibrated/teenys-onetouch-calibrated.ino

3) Integrate it in the previous code (LDR + button) so that now you have it all using two CC values and a chord trigger. 

4) Map it with your favourite synth.

5) Show it to the class
