# Add one button for triggering a MIDI note

1) Add a button in PULL-UP configuration to the circuit
![alt text](teensy-ldr-button.png)

2) First try the code for the button alone: https://github.com/ultranoise/teensyMIDItoolkit/blob/master/note-oneButton/teensy-one-button.ino It will trigger a MIDI note when you press the button. It also releases the note when releasing the button. 

3) Then add this code to the previous of the LDR so that you have a Control Change for the LDR and a MIDI note triggered with the Button

4) Try a sonic mapping with your favourite digital synth

5) Show it to the class
