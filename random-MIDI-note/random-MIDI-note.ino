/* Buttons to USB MIDI Example

   You must select MIDI from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

// the MIDI channel number to send messages
const int channel = 1;

elapsedMillis msec = 0; //counter for creating notes periodically 

int notePitch = 0;  //variable for MIDI note

void setup() {

}

void loop() {
  if (msec >= 2000) {  //create a note every 2000 mseconds
      msec = 0;

      //mute previous notes
      usbMIDI.sendNoteOff(notePitch, 0, channel);  // 60 = C4
      delay(100);

      //create a new note
      notePitch = random(40) + 40; //range 40 - 79
      usbMIDI.sendNoteOn(notePitch, 99, channel);  // velocity fixed to 99
  }

}
