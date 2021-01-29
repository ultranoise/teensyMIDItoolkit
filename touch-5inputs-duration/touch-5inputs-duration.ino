//
//Reads from capacitive pins and outputs MIDI CC values
//implementing a simple calibration routine.
//
//Teensy LC offers 11 capacitive touch input pins.
//Touch inputs are 0, 1, 3, 4, 15, 16,17, 18, 19, 22, 23
//
// CODE FOR KRISTINA FOR THE FOLLOWING TOUCH PINS: 0,1,3,4,15
//
//Written by ultranoise based on Teensy MIDI examples provided by teensy prjc


//triggers note the first time the threshold is surpassed
//the note off is triggered when the touch value crosses again the threshold.

// the MIDI channel number to send messages
const int channel = 1;

// the MIDI continuous controller for each analog input -> IDENTIFY EACH OF THE TOUCH lines in the computer
const int controllerA0 = 10; // 10 = pan position
const int controllerA1 = 11; // 11 = volume/expression
const int controllerA2 = 12; // 91 = reverb level
const int controllerA3 = 13; // 93 = chorus level
const int controllerA4 = 14; // 10 = pan position


int sensorValue = 0;         // the sensor value

// fix some maximums and minimums to init the calibration
int sensorMin0 = 100023;        // minimum sensor value
int sensorMin1 = 100023;        // minimum sensor value
int sensorMin2 = 100023;        // minimum sensor value
int sensorMin3 = 100203;        // minimum sensor value
int sensorMin4 = 100023;        // minimum sensor value

int sensorMax0 = 0;           // maximum sensor value
int sensorMax1 = 0;           // maximum sensor value
int sensorMax2 = 0;           // maximum sensor value
int sensorMax3 = 0;           // maximum sensor value
int sensorMax4 = 0;           // maximum sensor value

int th0 = 0; 
int th1 = 0;           // thresholds for calibration (init value to be replaced at calibration)
int th2 = 0;           
int th3 = 0;           
int th4 = 0;                   
          

int amountTh = 800;  //amount to add to minimum to calculate threshold

//what we send to the computer , not really notes, but CC values
int note0=0;
int note1=0;
int note2=0;
int note3=0;
int note4=0;

//status of the touch for each of the inputs. Also the previous touch value. 
bool on0 = false; 
bool on0_old = false;
bool on1 = false; 
bool on1_old = false;
bool on2 = false;
bool on2_old = false; 
bool on3 = false;
bool on3_old = false; 
bool on4 = false;
bool on4_old = false; 

//HERE WE DO THE CALIBRATION!!!
void setup() {

  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);  //SWITCH ON ONBOARD LED IN THE TEENSY TO BEGIN

  // calibrate during the first 20 seconds
  delay(3000);

  
  // TURN OFF LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  //Print some message in the terminal to announce calibration
  Serial.println("////////////////////////////");
  Serial.println("WELCOME TO THE PROGRAM");
  Serial.println("////////////////////////////");
  Serial.println("STARTING CALIBRATION: TOUCH ALL ELECTRODES");
  Serial.println("DURING 20 SECONDS");

  //BEGIN THE CALIBRATION FOR 20 SECONDS-> touch all touch terminals with the rubber at least once!!
  while (millis() < 20000) {

      ///// first read values many times to see maximum and minimum when touching or not
    sensorValue = touchRead(0);

    // record the maximum sensor value
    if (sensorValue > sensorMax0) {
      sensorMax0 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin0) {
      sensorMin0 = sensorValue;
    }


    /////
    sensorValue = touchRead(1);

    // record the maximum sensor value
    if (sensorValue > sensorMax1) {
      sensorMax1 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin1) {
      sensorMin1 = sensorValue;
    }
    /////////

    /////
    sensorValue = touchRead(3);

    // record the maximum sensor value
    if (sensorValue > sensorMax2) {
      sensorMax2 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin2) {
      sensorMin2 = sensorValue;
    }
    /////////

/////
    sensorValue = touchRead(4);

    // record the maximum sensor value
    if (sensorValue > sensorMax3) {
      sensorMax3 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin3) {
      sensorMin3 = sensorValue;
    }
    /////////
    sensorValue = touchRead(15);

    // record the maximum sensor value
    if (sensorValue > sensorMax4) {
      sensorMax4 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin4) {
      sensorMin4 = sensorValue;
    }

    
  } //end while

  Serial.println("END OF CALIBRATION");
  Serial.println("////////////////////////////");
  
  //calculate thresholds from the previous readings
  th0= sensorMin0 + amountTh;
  Serial.println("thresholds calculated values");
  Serial.println(th0);
  th1= sensorMin1 + amountTh;
  Serial.println(th1);
  th2= sensorMin2 + amountTh;
  Serial.println(th2);
  th3= sensorMin3 + amountTh;
  Serial.println(th3);
  th4= sensorMin4 + amountTh;
  Serial.println(th4);

  Serial.println("XXXXXXXX THRESHOLDS CALCULATED XXXX");
  
  // signal the end of the calibration period switching on the led
  digitalWrite(13, HIGH);
}

//SOME VARIABLES DECLARED HEREs

// store previously sent values, to detect changes
int previousA0 = -1;
int previousA1 = -1;
int previousA2 = -1;
int previousA3 = -1;
int previousA4 = -1;


bool downThreshold0= false;
bool downThreshold1= false;
bool downThreshold2= false;
bool downThreshold3= false;
bool downThreshold4= false;



void loop() {

    //Read the touch inputs (only five here)
    
    //Serial.println("XXXXXXX");
    int n0 = touchRead(0);
    //Serial.println(n0);
    int n1 = touchRead(1);
    //Serial.println(n1);
    int n2 = touchRead(3);
    //Serial.println(n2);
    int n3 = touchRead(4);
    //Serial.println(n3);
    int n4 = touchRead(15);
    //Serial.println(n4);
 
    
    Serial.println("");

    // for each of the pins
    // only transmit MIDI messages if touch input changed
    // then send the value of the input if the value is bigger than the calculated threshold
    // this will send CC messages to the computer if you touch the terminals.

    if (n0 != previousA0) {
      if(n0<th0) {          //under the threshold -> do not trigger note, set noteOff
        if(on0_old == true) {  //if we come from touching
          
          if(!downThreshold0){
            on0_old = false;
            usbMIDI.sendNoteOff(60, 0, 1);

            ////uncomment if you want to send a CC message
            /*
            usbMIDI.sendControlChange(controllerA0, 0, channel);
            Serial.println("CC ELECTRODE 0");
            Serial.println("0");
            */
            
            downThreshold0=true;
          }
        }      
        
        previousA0 = n0;
      } else  {           //over the threshold -> do not trigger note, set noteOff

          //ok, we are over the threshold, but is it the first time?
          if(on0_old == false) {  //if there is a change of status, from false (no touch) to true, touch
            on0_old = true;
            usbMIDI.sendNoteOn(60, 99, 1);

            //uncomment if you want to send a CC message
            /*
            note0=map(n0,th0,sensorMax0,0,127);
            Serial.println("CC ELECTRODE 0");
            Serial.println(note0);
            usbMIDI.sendControlChange(controllerA0, note0, channel);
            */
                
            previousA0 = n0;
            downThreshold0=false; 
          }     
      }
    }

    if (n1 != previousA1) {
      if(n1<th1) {          //under the threshold -> do not trigger note, set noteOff
        if(on1_old == true) {  //if we come from touching
          
          if(!downThreshold1){
            on1_old = false;
            usbMIDI.sendNoteOff(62, 0, 2);

            ////uncomment if you want to send a CC message
            /*
            usbMIDI.sendControlChange(controllerA0, 0, channel);
            Serial.println("CC ELECTRODE 0");
            Serial.println("0");
            */
            
            downThreshold1=true;
          }
        }      
        
        previousA1 = n1;
      } else  {           //over the threshold -> do not trigger note, set noteOff

          //ok, we are over the threshold, but is it the first time?
          if(on1_old == false) {  //if there is a change of status, from false (no touch) to true, touch
            on1_old = true;
            usbMIDI.sendNoteOn(62, 99, 2);

            //uncomment if you want to send a CC message
            /*
            note0=map(n0,th0,sensorMax0,0,127);
            Serial.println("CC ELECTRODE 0");
            Serial.println(note0);
            usbMIDI.sendControlChange(controllerA0, note0, channel);
            */
                
            previousA1 = n1;
            downThreshold1=false; 
          }     
      }
    }

    if (n2 != previousA2) {
      if(n2<th2) {          //under the threshold -> do not trigger note, set noteOff
        if(on2_old == true) {  //if we come from touching
          
          if(!downThreshold2){
            on2_old = false;

            usbMIDI.sendNoteOff(64, 0, 3);

            ////uncomment if you want to send a CC message
            /*
            usbMIDI.sendControlChange(controllerA0, 0, channel);
            Serial.println("CC ELECTRODE 0");
            Serial.println("0");
            */
            
            downThreshold2=true;
          }
        }      
        
        previousA2 = n2;
      } else  {           //over the threshold -> do not trigger note, set noteOff

          //ok, we are over the threshold, but is it the first time?
          if(on2_old == false) {  //if there is a change of status, from false (no touch) to true, touch
            on2_old = true;
            usbMIDI.sendNoteOn(64, 99, 3);

            //uncomment if you want to send a CC message
            /*
            note0=map(n0,th0,sensorMax0,0,127);
            Serial.println("CC ELECTRODE 0");
            Serial.println(note0);
            usbMIDI.sendControlChange(controllerA0, note0, channel);
            */
                
            previousA2 = n2;
            downThreshold2=false; 
          }     
      }
    }

    if (n3 != previousA3) {
      if(n3<th3) {          //under the threshold -> do not trigger note, set noteOff
        if(on3_old == true) {  //if we come from touching
          
          if(!downThreshold3){
            on3_old = false;

            usbMIDI.sendNoteOff(65, 0, 4);

            ////uncomment if you want to send a CC message
            /*
            usbMIDI.sendControlChange(controllerA0, 0, channel);
            Serial.println("CC ELECTRODE 0");
            Serial.println("0");
            */
            
            downThreshold3=true;
          }
        }      
        
        previousA3 = n3;
      } else  {           //over the threshold -> do not trigger note, set noteOff

          //ok, we are over the threshold, but is it the first time?
          if(on3_old == false) {  //if there is a change of status, from false (no touch) to true, touch
            on3_old = true;
            usbMIDI.sendNoteOn(65, 99, 4);

            //uncomment if you want to send a CC message
            /*
            note0=map(n0,th0,sensorMax0,0,127);
            Serial.println("CC ELECTRODE 0");
            Serial.println(note0);
            usbMIDI.sendControlChange(controllerA0, note0, channel);
            */
                
            previousA3 = n3;
            downThreshold3=false; 
          }     
      }
    }


    if (n4 != previousA4) {
      if(n4<th4) {          //under the threshold -> do not trigger note, set noteOff
        if(on4_old == true) {  //if we come from touching
          
          if(!downThreshold4){
            on4_old = false;

            usbMIDI.sendNoteOff(67, 0, 5);

            ////uncomment if you want to send a CC message
            /*
            usbMIDI.sendControlChange(controllerA0, 0, channel);
            Serial.println("CC ELECTRODE 0");
            Serial.println("0");
            */
            
            downThreshold4=true;
          }
        }      
        
        previousA4 = n4;
      } else  {           //over the threshold -> do not trigger note, set noteOff

          //ok, we are over the threshold, but is it the first time?
          if(on4_old == false) {  //if there is a change of status, from false (no touch) to true, touch
            on4_old = true;
            usbMIDI.sendNoteOn(67, 99, 5);

            //uncomment if you want to send a CC message
            /*
            note0=map(n0,th0,sensorMax0,0,127);
            Serial.println("CC ELECTRODE 0");
            Serial.println(note0);
            usbMIDI.sendControlChange(controllerA0, note0, channel);
            */
                
            previousA4 = n4;
            downThreshold4=false; 
          }     
      }
    }
   
    

    delay(10);
  //} //end of msec

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  //while (usbMIDI.read()) {
    // ignore incoming messages
  //}
}
