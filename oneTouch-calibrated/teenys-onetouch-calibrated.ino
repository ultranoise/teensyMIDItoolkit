//
//Reads a capacitive pin and outputs MIDI CC values
//implementing first a simple calibration routine.
//
//Teensy LC offers 11 capacitive touch input pins.
//Touch inputs are 0, 1, 5, 6, 15, 16,17, 18, 19, 22, 23
//We are using here pin nr 1. 
//
//Written by ultranoise based on Teensy MIDI examples provided by teensy prjc


#include <Bounce.h>

// the MIDI channel number to send messages
const int channel = 1;

// the MIDI CC we will use
const int controllerA0 = 11;

// a variable to calibrate    
int capacitiveValue = 0;

// variables init to some maximums and minimums to calibrate
int sensorMin0 = 100000;      // fix an extreme minimum sensor value to be updated during calibration
int sensorMax0 = 0;           // fix an extreme maximum sensor value to be updated during calibration

// store previously sent values, to detect changes
int previousA0 = -1;

//this is a variable of type elapsedMillis (only in Teensy to measure time between loop iterations)
elapsedMillis msec = 0;



/*
 * In setup() we will calibrate the capacitive readings. If we want to map the capacitive input 
 * to MIDI CC values (0-127), we have to know the input range because it will be different every time 
 * you connect the usb cable. 
 * This means that we will first read the maximum and minimum value of the capacitive pin when we touch 
 * the cable or the object connected to it. We will run this cablibration during 10 seconds. 
 * We will use the on board LED (pin 13) to signal the beginning (LED OFF) and end (LED ON) of the calibration routine. 
 */
void setup() {

  Serial.begin(9600);

  //Switch the LED on at the very beginning of the program 
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  // Take 5 seconds before you begin the calibration routine
  delay(5000);
  

  // 1) Turn off LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  Serial.println("////////////////////////////");
  Serial.println("WELCOME TO THE PROGRAM");
  Serial.println("////////////////////////////");
  Serial.println("STARTING CALIBRATION: TOUCH ALL ELECTRODES");
  Serial.println("DURING 10 SECONDS");


  // 2) Calibrate during ten seconds. 
  //From this loop we obtain the maximum (sensorMax0) and minimum (sensorMin0) readings.  
  
  while (millis() < 10000) {

    //read the capacitive input nr 1
    capacitiveValue = touchRead(1);

    // record the maximum sensor value (sensorMax0 was initialized to 0)
    if (capacitiveValue > sensorMax0) {
      sensorMax0 = capacitiveValue;
    }

    // record the minimum sensor value (sensorMin0 was initialized to 100000)
    if (capacitiveValue < sensorMin0) {
      sensorMin0 = capacitiveValue;
    }
    
  }
  
  // signal the end of the calibration period switching ON the LED
  digitalWrite(13, HIGH);
  
  Serial.println("END OF CALIBRATION");
  Serial.println("////////////////////////////");
 
}

/*
 * in loop() we read the capacitive pin and send the CC value 
 */
void loop() {

  // only check the analog inputs 50 times per second,
  // to prevent a flood of MIDI messages
  // This time control is made with the variable msec, 
  // every time msec is bigger than 20 ms we read and try to send MIDI.
  if (msec >= 20) {
    msec = 0;     //reset msec to measure 20 ms from now on
    
    //Read capacitive pin
    int n0 = touchRead(1);
    
    // only transmit MIDI messages if analog input changed
    if (n0 != previousA0) {
      //send CC value mapping actual value with calibrated minimum and maximum
      usbMIDI.sendControlChange(controllerA0, map(n0,sensorMin0,sensorMax0,0,127), channel);
      previousA0 = n0;
    }

  }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }

}
