# Create a basic step sequencer

In this practice you will experiment with the simplest possible step sequencer for MIDI (probably a bit jitterish...)

1) Upload the following code. It is a monophonic 16-steps sequencer without any control. Compare three options:

Option 1: play the notes using delay() -> blocks the rest of loop()
```

int channel = 1;  //MIDI channels

int NUM_STEPS = 16;
int pitches[NUM_STEPS]={60, 62, 63, 65, 67, 68, 70, 72, 73, 72, 70, 68, 67, 65, 63, 62};  //init pitches for each step
int velocity = 100;   //same velocity to all them

int seq_time = 100;  //the sequencer step rhythm

void setup() {  //nothing to do here by the moment

}

void loop() {

  //loop all the steps at the rhythm, get the pitches, and play them
  for(int i = 0; i<NUM_STEPS; i++) {
    usbMIDI.sendNoteOn(pitches[i], velocity, channel);
    delay(seq_time/2);
    usbMIDI.sendNoteOff(pitch, 0, channel);
    delay(seq_time/2);
  }

}
```
Option 2: measure the ellapsed time without blocking loop() but without releasing MIDI notes (only noteOn)

```
int channel = 1;  //MIDI channels

int NUM_STEPS = 16;
int pitches[NUM_STEPS]={60, 62, 63, 65, 67, 68, 70, 72, 73, 72, 70, 68, 67, 65, 63, 62};  //init pitches for each step
int velocity = 100;   //same velocity to all them

int seq_time = 100;  //the sequencer step rhythm
int current_step = 0;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated


void setup() {  //nothing to do here by the moment

}

void loop() {

  // check to see if it's time to send the note; that is, if the difference
  // between the current time and last time you sent a note is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= seq_time) {  //time to play the note
    // save the last time you sent a note
    previousMillis = currentMillis;
    
    //play note 
    usbMIDI.sendNoteOn(pitches[current_step], velocity, channel);
    
    //update current step
    current_step = current_step + 1;
    if(current_step == NUM_STEPS) current_step = 0;  //if it ends the sequence go to the beginning  
  } else {  //time between notes
    //you could do something here (update displays, reading sensors, etc)
  }
}

```
Option 3: measure the ellapsed time without blocking loop() and releasing the MIDI note (noteOff) at a particular time

```
int channel = 1;  //MIDI channels

int NUM_STEPS = 16;
int pitches[NUM_STEPS]={60, 62, 63, 65, 67, 68, 70, 72, 73, 72, 70, 68, 67, 65, 63, 62};  //init pitches for each step
int velocity = 100;   //same velocity to all them

int seq_time = 100;  //the sequencer step rhythm
int current_step = 0;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated


void setup() {  //nothing to do here by the moment

}

void loop() {

  // check to see if it's time to send the note; that is, if the difference
  // between the current time and last time you sent a note is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= seq_time) {  //time to play the note
    // save the last time you sent a note
    previousMillis = currentMillis;
    
    //play note 
    usbMIDI.sendNoteOn(pitches[current_step], velocity, channel);
    
    //update current step
    current_step = current_step + 1;
    if(current_step == NUM_STEPS) current_step = 0;  //if it ends the sequence go to the beginning  
  } else if(currentMillis - previousMillis >= seq_time/2){
      usbMIDI.sendNoteOff(pitches[current_step], 0, channel);
  }
}

```

2) Test it with your favourite synth. 
  
3) Add controls to this monophonic sequencer with the circuit of the previous practices (LDR, button, touch) for controlling speed, play/stop, frequencies, etc. 

4) Test it with your favourite synth

5) Show it to the class

6) Add another voice or voices....

7) Show it to the class
