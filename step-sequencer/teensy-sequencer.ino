

// sequence parameters
#define NUM_STEPS 16
#define VELOCITY 100
#define CHANNEL 1

// define the step sequencer core with a Struct
struct Step {
  int note;
  int vel;
};

// and an array of Step for a number of steps
struct Step sequencer[NUM_STEPS];

//function to write the values of each of the steps in the array
void set_step(int i, int note, int vel) {
  sequencer[i].note = note;
  sequencer[i].vel = vel;
}

//function to set the steps of the sequencer
void set_sequence() {
  // preset sequence  (step number, MIDI note, MIDI velocity)
  set_step(0, 60, VELOCITY);
  set_step(1, 64, VELOCITY);
  set_step(2, 67, VELOCITY);
  set_step(3, 71, VELOCITY);
  set_step(4, 60, VELOCITY);
  set_step(5, 64, VELOCITY);
  set_step(6, 67, VELOCITY);
  set_step(7, 71, VELOCITY);
  set_step(8, 60, VELOCITY);
  set_step(9, 64, VELOCITY);
  set_step(10, 65, VELOCITY);
  set_step(11, 67, VELOCITY);
  set_step(12, 60, VELOCITY);
  set_step(13, 64, VELOCITY);
  set_step(14, 65, VELOCITY);
  set_step(15, 67, VELOCITY);
}

//function to update the actual sequence step
void step_ahead() {
  // step ahead one place every time we call it
    current_step++;
    if (current_step >= NUM_STEPS)  //if we are at the end go to the beginning
      current_step = 0;
}

//function to send the adequate MIDI note On
void step_on(){
  usbMIDI.sendNoteOn(sequencer[current_step].note, VELOCITY, CHANNEL);
}

//function to send the adequate MIDI note Off
void step_off(){
  usbMIDI.sendNoteOff(sequencer[current_step].note, VELOCITY, CHANNEL);
}

//In setup() we init a few control variables
void setup() {
  step_delay = 100; // step delay in ms
  
  lastStepTime = millis();  //init the step sequencer timer
  current_step = 0;         //init the sequencer step
  
}

void loop() {

    //we calculate the delay since last iteration
    //if it is the moment to send the note, update the step and send a note On
    if(millis() > lastStepTime + step_delay){
      lastStepTime = millis();
      step_ahead();
      step_on();
    }
    // wait until the middle of the step to send the MIDI note Off (the envelope could be modified)
    else if(millis() > lastStepTime + (step_delay / 2)){
      step_off();
    }
  
  
  while(usbMIDI.read()) {} // ignore incoming MIDI messages
  
}
