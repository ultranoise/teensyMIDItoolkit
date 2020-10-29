/* USB MIDI AnalogControlChange Example

   You must select MIDI from the "Tools > USB Type" menu
   http://www.pjrc.com/teensy/td_midi.html

   This example code is in the public domain.
*/

// the MIDI channel number to send messages
const int channel = 1;

void setup() {
}

// store previously sent values, to detect changes
int previousA0 = -1;

elapsedMillis msec = 0;

void loop() {
  // only check the analog inputs 50 times per second,
  // to prevent a flood of MIDI messages
  if (msec >= 20) {
    msec = 0;
    int n0 = analogRead(A0) / 8;

    // only transmit MIDI messages if analog input changed
    if (n0 != previousA0) {
      usbMIDI.sendNoteOn(map(n0, 0, 127, 40, 127), 99, channel);  // velocity fixed to 99
      previousA0 = n0;
    }

  }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}
