// Read Adafruit LIS3DH accelerometer 
// and transmit x,y,z values as MIDI CC
// (only teensy)
// by ultranoise based on examples by Adafruit

#include <Wire.h>
#include <math.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

// the MIDI channel number to send messages
const int channel = 1;

// the MIDI continuous controller for each accelerometer axis
const int controllerA0 = 10; // 10 = pan position
const int controllerA1 = 11; // 11 = volume/expression
const int controllerA2 = 91; // 91 = reverb level
const int controllerPitch = 101; //
const int controllerRoll = 120; //

// store previously sent values, to detect changes
int previousA0 = -1;
int previousA1 = -1;
int previousA2 = -1;
double previousRoll = -1;
double previousPitch = -1;

elapsedMillis msec = 0;  //to measure time between events


void setup() {
  Serial.begin(115200);
  Serial.println("Trying to read LIS3DH!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

  delay(100);
}

void loop() {
  
  // only check the analog inputs 50 times per second,
  // to prevent a flood of MIDI messages
  if (msec >= 20) {
    msec = 0;
    
    /* get a new sensor event, normalized */ 
    sensors_event_t event; 
    lis.getEvent(&event);

    //transform values to MIDI range ( [+-]9.8 to 0 -> 127)
    int n0 = map(event.acceleration.x, -9.8, 9.8, 0, 127);
    int n1 = map(event.acceleration.y,-9.8, 9.8, 0, 127);
    int n2 = map(event.acceleration.z,-9.8, 9.8, 0, 127);

    // only transmit MIDI messages if analog input changed
    if (n0 != previousA0) {
      usbMIDI.sendControlChange(controllerA0, n0, channel);
      previousA0 = n0;
    }
    if (n1 != previousA1) {
      usbMIDI.sendControlChange(controllerA1, n1, channel);
      previousA1 = n1;
    }
    if (n2 != previousA2) {
      usbMIDI.sendControlChange(controllerA2, n2, channel);
      previousA2 = n2;
    }

    // calculating pitch and roll ind degrees
    // see https://www.dfrobot.com/wiki/index.php/How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing
    double roll = atan2(event.acceleration.y , event.acceleration.z) * 57.3;
    double pitch = atan2((- event.acceleration.x) , sqrt(event.acceleration.y * event.acceleration.y + event.acceleration.z * event.acceleration.z)) * 57.3;

    if (roll != previousRoll) {
      float tempRoll = map(roll, -180, 180, 0, 127);
      usbMIDI.sendControlChange(controllerRoll, tempRoll, channel);
      previousRoll = roll;
    }

    if (pitch != previousPitch) {
      float tempPitch = map(pitch, -90, 90, 0, 127);
      usbMIDI.sendControlChange(controllerPitch, tempPitch, channel);
      previousPitch = pitch;
    }

    Serial.print("\t\troll: ");Serial.println(roll);
    Serial.print("\t\tpitch: ");Serial.println(pitch);
    
    /* Display the results (acceleration is measured in m/s^2) */
    //Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
    //Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
    //Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
    //Serial.println(" m/s^2 ");
    Serial.print("\t\tX: "); Serial.print(n0);Serial.print(" , ");
    Serial.print(event.acceleration.x);
    Serial.print(" \tY: "); Serial.print(n1);Serial.print(" , ");
    Serial.print(event.acceleration.y); 
    Serial.print(" \tZ: "); Serial.print(n2);Serial.print(" , ");
    Serial.print(event.acceleration.z);  
    Serial.println();

  }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}
