///// MIDI PARAMETERS ///////////////
const int channel = 1; // the MIDI channel number to send messages
const int controllerA0 = 100; // the MIDI continuous controller (CC value) we will send to the computer

///// PROGRAM VARIABLES ////////////
int n0 = 0; //variables to store the sensor value
int previousA0 = -1; //variable to store the previous value of the sensor, needed to see if the value has changed
int note;   //the note to be played in the array of notes
int note_ordinal; //position in the array of notes

elapsedMillis msec = 0; //variable to store ellapsed time in the program

///// CHORD DEFINITION /////////////
//Definition of notes in the chords to be played. Each MIDI note is defined by a number (C4 = 60)
//How to defined it: 
//- First declare an array with the note numbers. In the declaration you have 
// to specify the number of notes (change it to your needs)
const int number_of_notes = 11;
int notes[number_of_notes] = {45,57,59,60,62,64,65,66,67,69,71};

bool ledstate = true;  //for led blinking

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}


void loop() {
  
  // only check the analog inputs every 100 mseconds
  // to prevent a flood of MIDI messages

  if (msec >= 100) {

    msec = 0;
    ledstate = !ledstate;
    digitalWrite(13,ledstate);  //make a led blink!
    
    n0 = analogRead(A0); // sensor read -> theoretically values from 0 to 1023
    
    usbMIDI.sendControlChange(controllerA0, n0/8, channel); //we send the value to cc 100 as well (not needed)
    
    Serial.println(" ");
    Serial.print("Sensor values: "); 
    Serial.println(n0);   //print it in the serial monitor, check the values for mapping calibration
    
    
    //as we can only read a range of values from the sensor (for example 950 to 1000) 
    //we have to map input range to the actual number of notes minus 1, as the first note
    //in the array has the ordinal 0, not 1. 
    //Here you have to calibrate these numbers (950 -> 1000) to map your sensor input
    note_ordinal = map(n0,950,1000,0,number_of_notes - 1); 

    //find the note number in the array
    note = notes[note_ordinal];
    
    Serial.print("MIDI note played: "); 
    Serial.println(note);   //print it in the serial monitor
    
    // only transmit MIDI notes if analog input changed
     if (n0 != previousA0) {
      
      usbMIDI.sendNoteOff(previousA0, 0, channel); 

      usbMIDI.sendNoteOn(note, 99, channel);

      previousA0 = note;

    }
     
  }


  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash   
  while (usbMIDI.read()) {

    // ignore incoming messages
  }
}
