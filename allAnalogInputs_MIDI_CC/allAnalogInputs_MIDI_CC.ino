//
//Reads from all analog pins and outputs MIDI CC values
//
//Teensy LC offers 10 analog input pins.
//Touch inputs are 15, 16,17, 18, 19, 20, 21, 22, 23, 24
//
//Written by ultranoise based on Teensy MIDI examples provided by teensy prjc


// the MIDI channel number to send messages
const int channel = 1;

// the MIDI continuous controller for each analog input
const int controllerA0 = 10; // 10 = pan position
const int controllerA1 = 11; // 11 = volume/expression
const int controllerA2 = 12; // 91 = reverb level
const int controllerA3 = 13; // 93 = chorus level
const int controllerA4 = 14; // 10 = pan position
const int controllerA5 = 15; // 11 = volume/expression
const int controllerA6 = 16; // 91 = reverb level
const int controllerA7 = 17; // 93 = chorus level
const int controllerA8 = 18; // 91 = reverb level
const int controllerA9 = 19; // 93 = chorus level


void setup() {

}

// store previously sent values, to detect changes
int previousA0 = -1;
int previousA1 = -1;
int previousA2 = -1;
int previousA3 = -1;
int previousA4 = -1;
int previousA5 = -1;
int previousA6 = -1;
int previousA7 = -1;
int previousA8 = -1;
int previousA9 = -1;


elapsedMillis msec = 0;

void loop() {
  
  // only! check the analog inputs 200 times per second,
  // 
  if (msec >= 5) {
    msec = 0;
    int n0 = analogRead(A0) / 8;
    int n1 = analogRead(A1) / 8;
    int n2 = analogRead(A2) / 8;
    int n3 = analogRead(A3) / 8;
    int n4 = analogRead(A4) / 8;
    int n5 = analogRead(A5) / 8;
    int n6 = analogRead(A6) / 8;
    int n7 = analogRead(A7) / 8;
    int n8 = analogRead(A8) / 8;
    int n9 = analogRead(A9) / 8;
    
    // only transmit MIDI messages if analog input changed
    if (n0 != previousA0) {
      usbMIDI.sendControlChange(controllerA0, n0, 10);
      previousA0 = n0;
    }
    if (n1 != previousA1) {
      usbMIDI.sendControlChange(controllerA1, n1, 1);
      previousA1 = n1;
    }
    if (n2 != previousA2) {
      usbMIDI.sendControlChange(controllerA2, n2, 2);
      previousA2 = n2;
    }
    if (n3 != previousA3) {
      usbMIDI.sendControlChange(controllerA3, n3, 3);
      previousA3 = n3;
    }
    if (n4 != previousA4) {
      usbMIDI.sendControlChange(controllerA4, n4, 4);
      previousA4 = n4;
    }
    if (n5 != previousA5) {
      usbMIDI.sendControlChange(controllerA5, n5, 5);
      previousA5 = n5;
    }
    if (n6 != previousA6) {
      usbMIDI.sendControlChange(controllerA6, n6, 6);
      previousA6 = n6;
    }
    if (n7 != previousA7) {
      usbMIDI.sendControlChange(controllerA7, n7, 7);
      previousA7 = n7;
    }
    if (n8 != previousA8) {
      usbMIDI.sendControlChange(controllerA8, n8, 8);
      previousA8 = n8;
    }
    if (n9 != previousA9) {
      usbMIDI.sendControlChange(controllerA9, n9, 9);
      previousA9 = n9;
    }
  }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

