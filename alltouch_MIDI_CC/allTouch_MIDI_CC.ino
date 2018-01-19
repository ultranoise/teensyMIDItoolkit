//
//Reads from capacitive pins and outputs MIDI CC values
//implementing a simple calibration routine.
//
//Teensy LC offers 11 capacitive touch input pins.
//Touch inputs are 0, 1, 5, 6, 15, 16,17, 18, 19, 22, 23
//
//Written by uktranoise based on Teensy MIDI examples provided by teensy prjc


#include <Bounce.h>

// the MIDI channel number to send messages
const int channel = 1;

// the MIDI continuous controller for each analog input
const int controllerA0 = 11; // 10 = pan position
const int controllerA1 = 1; // 11 = volume/expression
const int controllerA2 = 2; // 91 = reverb level
const int controllerA3 = 3; // 93 = chorus level
const int controllerA4 = 4; // 10 = pan position
const int controllerA5 = 5; // 11 = volume/expression
const int controllerA6 = 6; // 91 = reverb level
const int controllerA7 = 7; // 93 = chorus level
const int controllerA8 = 8; // 10 = pan position
const int controllerA9 = 9; // 11 = volume/expression
const int controllerA10 = 10; // 91 = reverb level


int sensorValue = 0;         // the sensor value

// fix some maximums and minimums to init
int sensorMin1 = 100023;        // minimum sensor value
int sensorMin2 = 100023;        // minimum sensor value
int sensorMin3 = 100203;        // minimum sensor value
int sensorMin4 = 100023;        // minimum sensor value
int sensorMin5 = 100023;        // minimum sensor value
int sensorMin6 = 100023;        // minimum sensor value
int sensorMin7 = 100023;        // minimum sensor value
int sensorMin8 = 100023;        // minimum sensor value
int sensorMin9 = 100023;        // minimum sensor value
int sensorMin10 = 100023;        // minimum sensor value
int sensorMin0 = 100023;        // minimum sensor value

int sensorMax1 = 0;           // maximum sensor value
int sensorMax2 = 0;           // maximum sensor value
int sensorMax3 = 0;           // maximum sensor value
int sensorMax4 = 0;           // maximum sensor value
int sensorMax5 = 0;           // maximum sensor value
int sensorMax6 = 0;           // maximum sensor value
int sensorMax7 = 0;           // maximum sensor value
int sensorMax8 = 0;           // maximum sensor value
int sensorMax9 = 0;           // maximum sensor value
int sensorMax10 = 0;           // maximum sensor value
int sensorMax0 = 0;           // maximum sensor value

int th1 = 0;           // thresholds
int th2 = 0;           
int th3 = 0;           
int th4 = 0;           
int th5 = 0;           
int th6 = 0;           
int th7 = 0;          
int th8 = 0;           
int th9 = 0;           
int th10 = 0;          
int th0 = 0;           

int amountTh = 800;  //amount to add to minimum to calculate threshold

int note0=0;
int note1=0;
int note2=0;
int note3=0;
int note4=0;
int note5=0;
int note6=0;
int note7=0;
int note8=0;
int note9=0;
int note10=0;

void setup() {

  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  

  // calibrate during the first five seconds
  delay(3000);
  // turn off LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.println("////////////////////////////");
  Serial.println("WELCOME TO THE PROGRAM");
  Serial.println("////////////////////////////");
  Serial.println("STARTING CALIBRATION: TOUCH ALL ELECTRODES");
  Serial.println("DURING 20 SECONDS");
  while (millis() < 20000) {

      /////
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

    sensorValue = touchRead(16);

    // record the maximum sensor value
    if (sensorValue > sensorMax5) {
      sensorMax5 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin5) {
      sensorMin5 = sensorValue;
    }

    sensorValue = touchRead(17);

    // record the maximum sensor value
    if (sensorValue > sensorMax6) {
      sensorMax6 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin6) {
      sensorMin6 = sensorValue;
    }

    sensorValue = touchRead(18);

    // record the maximum sensor value
    if (sensorValue > sensorMax7) {
      sensorMax7 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin7) {
      sensorMin7 = sensorValue;
    }

    sensorValue = touchRead(19);

    // record the maximum sensor value
    if (sensorValue > sensorMax8) {
      sensorMax8 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin8) {
      sensorMin8 = sensorValue;
    }

    sensorValue = touchRead(22);

    // record the maximum sensor value
    if (sensorValue > sensorMax9) {
      sensorMax9 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin9) {
      sensorMin9 = sensorValue;
    }

    sensorValue = touchRead(23);

    // record the maximum sensor value
    if (sensorValue > sensorMax10) {
      sensorMax10 = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin10) {
      sensorMin10 = sensorValue;
    }
    
  } //end while

  Serial.println("END OF CALIBRATION");
  Serial.println("////////////////////////////");
  
  //calculate thresholds
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
  th5= sensorMin5 + amountTh;
  Serial.println(th5);
  th6= sensorMin6 + amountTh;
  Serial.println(th6);
  th7= sensorMin7 + amountTh;
  Serial.println(th7);
  th8= sensorMin8 + amountTh;
  Serial.println(th8);
  th9= sensorMin9 + amountTh;
  Serial.println(th9);
  th10= sensorMin10 + amountTh;
  Serial.println(th10);
  Serial.println("XXXXXXXX");
  

  // signal the end of the calibration period
  digitalWrite(13, HIGH);
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
int previousA10 = -1;

bool downThreshold0= false;
bool downThreshold1= false;
bool downThreshold2= false;
bool downThreshold3= false;
bool downThreshold4= false;
bool downThreshold5= false;
bool downThreshold6= false;
bool downThreshold7= false;
bool downThreshold8= false;
bool downThreshold9= false;
bool downThreshold10= false;

bool fxSwitch = false;
bool fxChange = false;

elapsedMillis msec = 0;

void loop() {

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
    int n5 = touchRead(16);
    //Serial.println(n5);
    int n6 = touchRead(17);
    //Serial.println(n6);
    int n7 = touchRead(18);
    //Serial.println(n7);
    int n8 = touchRead(19);
    //Serial.println(n8);
    int n9 = touchRead(22);
    //Serial.println(n9);
    int n10 = touchRead(23);
    //Serial.println(n10);
    //delay(10);
  
  
  // only check the analog inputs 50 times per second,
  // to prevent a flood of MIDI messages
  //if (msec >= 20) {
    //msec = 0;
    
    Serial.println("");
    
    // only transmit MIDI messages if analog input changed
    /*
    if (n0 != previousA0) {
      if(n0<th0) {          //under threshold do not do anything       
        previousA0 = n0;
        fxChange = true;
        delay(20); //to avoid bouncing
        //Serial.println("ELECTRODE 0 DOWN");
        
      } else  {             //over threshold change fx switch status
        if(fxChange){
          if(!fxSwitch){    
              usbMIDI.sendNoteOn(60, 127, channel);  // trigger FX on
              Serial.println("NOTE ELECTRODE 0");
              Serial.println("ON");
              //downThreshold0=true;
              fxSwitch = true;
                        
          } 
          else {
              usbMIDI.sendNoteOff(60, 0, channel);  // trigger FX on
              Serial.println("NOTE ELECTRODE 0");
              Serial.println("OFF");
              //downThreshold0=true;
              fxSwitch = false;
          }
           delay(20); //to avoid bouncing 
           fxChange = false;  
        } 
          previousA0 = n0;
          
      }
    }

    */
    if (n0 != previousA0) {
      if(n0<th0) {
        if(!downThreshold0){
          usbMIDI.sendControlChange(controllerA0, 0, channel);
          Serial.println("CC ELECTRODE 0");
          Serial.println("0");
          downThreshold0=true;
        }
        
        previousA0 = n0;
      } else  {
          note0=map(n0,th0,sensorMax0,0,127);
          Serial.println("CC ELECTRODE 0");
          Serial.println(note0);
          usbMIDI.sendControlChange(controllerA0, note0, channel);
          previousA0 = n0;
          downThreshold0=false;
      }
      
    }
    if (n1 != previousA1) {
      if(n1<th1) {
        if(!downThreshold1){
          usbMIDI.sendControlChange(controllerA1, 0, channel);
          Serial.println("CC ELECTRODE 1");
          Serial.println("0");
          downThreshold1=true;
        }
        
        previousA1 = n1;
      } else  {
          note1=map(n1,th1,sensorMax1,0,127);
          Serial.println("CC ELECTRODE 1");
          Serial.println(note1);
          usbMIDI.sendControlChange(controllerA1, note1, channel);
          previousA1 = n1;
          downThreshold1=false;
      }
      
    }
    if (n2 != previousA2) {
      if(n2<th2) {
        if(!downThreshold2){
          usbMIDI.sendControlChange(controllerA2, 0, channel);
          Serial.println("CC ELECTRODE 2");
          Serial.println("0");
          downThreshold2=true;
        }
        previousA2 = n2;
      } else  {
          note2=map(n2,th2,sensorMax2,0,127);
          Serial.println("CC ELECTRODE 2");
          Serial.println(note2);
          usbMIDI.sendControlChange(controllerA2, note2, channel);
          previousA2 = n2;
          downThreshold2=false;
      }
    }
    if (n3 != previousA3) {
      if(n3<th3) {
        if(!downThreshold3){
          usbMIDI.sendControlChange(controllerA3, 0, channel);
          Serial.println("CC ELECTRODE 3");
          Serial.println("0");
          downThreshold3=true;
        }
        previousA3 = n3;
      } else  {
          note3=map(n3,th3,sensorMax3,0,127);
          Serial.println("CC ELECTRODE 3");
          Serial.println(note3);
          usbMIDI.sendControlChange(controllerA3, note3, channel);
          previousA3 = n3;
          downThreshold3=false;
      }
    }
    if (n4 != previousA4) {
      if(n4<th4) {
        if(!downThreshold4){
          usbMIDI.sendControlChange(controllerA4, 0, channel);
          Serial.println("CC ELECTRODE 4");
          Serial.println("0");
          downThreshold4=true;
        }
        previousA4 = n4;
      } else  {
          note4=map(n4,th4,sensorMax4,0,127);
          Serial.println("CC ELECTRODE 4");
          Serial.println(note4);
          usbMIDI.sendControlChange(controllerA4, note4, channel);
          previousA4 = n4;
          downThreshold4=false;
      }
    }
    if (n5 != previousA5) {
      if(n5<th5) {
        if(!downThreshold5){
          usbMIDI.sendControlChange(controllerA5, 0, channel);
          Serial.println("CC ELECTRODE 5");
          Serial.println("0");
          downThreshold5=true;
        }
        previousA5 = n5;
      } else  {
          note5=map(n5,th5,sensorMax5,0,127);
          Serial.println("CC ELECTRODE 5");
          Serial.println(note5);
          usbMIDI.sendControlChange(controllerA5, note5, channel);
          previousA5 = n5;
          downThreshold5=false;
      }
    }
    if (n6 != previousA6) {
      if(n6<th6) {
        if(!downThreshold6){
          usbMIDI.sendControlChange(controllerA6, 0, channel);
          Serial.println("CC ELECTRODE 6");
          Serial.println("0");
          downThreshold6=true;
        }
        previousA6 = n6;
      } else  {
          note6=map(n6,th6,sensorMax6,0,127);
          Serial.println("CC ELECTRODE 6");
          Serial.println(note6);
          usbMIDI.sendControlChange(controllerA6, note6, channel);
          previousA6 = n6;
          downThreshold6=false;
      }
    }
    if (n7 != previousA7) {
      if(n7<th7) {
        if(!downThreshold7){
          usbMIDI.sendControlChange(controllerA7, 0, channel);
          Serial.println("CC ELECTRODE 7");
          Serial.println("0");
          downThreshold7=true;
        }
        previousA7 = n7;
      } else  {
          note7=map(n7,th7,sensorMax7,0,127);
          Serial.println("CC ELECTRODE 7");
          Serial.println(note7);
          usbMIDI.sendControlChange(controllerA7, note7, channel);
          previousA7 = n7;
          downThreshold7=false;
      }
    }
    if (n8 != previousA8) {
      if(n8<th8) {
        if(!downThreshold8){
          usbMIDI.sendControlChange(controllerA8, 0, channel);
          Serial.println("CC ELECTRODE 8");
          Serial.println("0");
          downThreshold8=true;
        }
        previousA8 = n8;
      } else  {
          note8=map(n8,th8,sensorMax8,0,127);
          Serial.println("CC ELECTRODE 8");
          Serial.println(note8);
          usbMIDI.sendControlChange(controllerA8, note8, channel);
          previousA8 = n8;
          downThreshold8=false;
      }
    }
    if (n9 != previousA9) {
      if(n9<th9) {
        if(!downThreshold9){
          usbMIDI.sendControlChange(controllerA9, 0, channel);
          Serial.println("CC ELECTRODE 9");
          Serial.println("0");
          downThreshold9=true;
        }
        previousA9 = n9;
      } else  {
          note9=map(n9,th9,sensorMax9,0,127);
          Serial.println("CC ELECTRODE 9");
          Serial.println(note9);
          usbMIDI.sendControlChange(controllerA9, note9, channel);
          previousA9 = n9;
          downThreshold9=false;
      }
    }
    if (n10 != previousA10) {
      if(n10<th10) {
        if(!downThreshold10){
          usbMIDI.sendControlChange(controllerA10, 0, channel);
          Serial.println("CC ELECTRODE 10");
          Serial.println("0");
          downThreshold10=true;
        }
        previousA10 = n10;
      } else  {
          note10=map(n10,th10,sensorMax10,0,127);
          Serial.println("CC ELECTRODE 10");
          Serial.println(note10);
          usbMIDI.sendControlChange(controllerA10, note10, channel);
          previousA10 = n10;
          downThreshold10=false;
      }
    }

    delay(20);
  //} //end of msec

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  //while (usbMIDI.read()) {
    // ignore incoming messages
  //}
}

