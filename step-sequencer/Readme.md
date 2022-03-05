# Create a basic step sequencer

In this practice you will experiment with the simplest possible step sequencer for MIDI (probably a bit jitterish...)

1) Upload the following code. It is a monophonic 16-steps sequencer without any control.
```

int channel = 1;  //MIDI channels

int NUM_STEPS = 16;
int pitches[NUM_STEPS]={60, 62, 63, 65, 67, 68, 70, 72, 73, 72, 70, 68, 67, 65, 63, 62};  //init pitches for each step
int velocity = 100;   //same velocity to all them

int delay_time = 100;  //the sequencer step rhythm

void setup() {  //nothing to do here by the moment

}

void loop() {

  //loop all the steps at the rhythm, get the pitches, and play them
  for(int i = 0; i<NUM_STEPS; i++) {
    usbMIDI.sendNoteOn(pitches[i], velocity, channel);
    delay(delay_time/2);
    usbMIDI.sendNoteOff(pitch, 0, channel);
    delay(delay_time/2);
  }

}
```

  
2) Test it with your favourite synth. 
  
3) Add controls to this monophonic sequencer with the circuit of the previous practices (LDR, button, touch) for controlling speed, play/stop, frequencies, etc. 

4) Test it with your favourite synth

5) Show it to the class

6) Add another voice or voices....

7) Show it to the class
