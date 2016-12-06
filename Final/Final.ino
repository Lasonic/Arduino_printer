#include <SPI.h>
#include "High_Temp.h"
#include "FastLED.h"
#include <PID_v1.h>


char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

//// DEFINE variables from MATLAB GUI ////

//Data from MATLAB GUI
double para;
double matlab_data;
double matlab_value;  

//// DEFINE Pressure Pin
const int pressurePin = 8;

//// DEFINE FastLED MOSFET
#define NUM_LEDS 1
#define DATA_PIN 26
CRGB leds[NUM_LEDS];

//// DEFINE RELAY PIN ////
//#define RelayPin 22

//// DEFINE STEPPER PIN
const int DirPin = 22;
const int PulsePin = 24;

//// DEFINTE TEMP SENSORS ht( pinRoomTmp, pinThermocouple)
// on the sensor A0 = thermocouple, A1 = roomTmp
HighTemp ht_head(A4, A5);
HighTemp ht_ring(A2, A3);

//// DEFINE Variables we'll be connecting to
double Setpoint_head, Input_head, Output_head;
double Setpoint_ring, Input_ring, Output_ring;

//// DEFINE Slave Pin for DIGIPOT
const int slaveSelectPin = 53;

//// DEFINE PID variables

int WindowSize = 3000; // 3 seconds
unsigned long windowStartTime;
//Specify the links and initial tuning parameters
//  myPID(&Input, &Output, &Setpoint,Kp,Ki,Kd,Direction); 
PID myPID_head(&Input_head, &Output_head, &Setpoint_head,5,5,1,DIRECT);
PID myPID_ring(&Input_ring, &Output_ring, &Setpoint_ring,5,5,1,DIRECT);

void setup() {
  //// TESTING LED PIN 13 SETUP ////
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  //// DIGIPOT SETUP ////
  pinMode(slaveSelectPin, OUTPUT);
  double voltage;
  
  //// PRESSURE SETUP ////
  pinMode(pressurePin, OUTPUT);
  double pressure;
  
  //// STEPPER SETUP ////
  pinMode(DirPin, OUTPUT);
  pinMode(PulsePin, OUTPUT);
  double motor_speed;

  // Start Serial
  Serial.begin(115200);
  // High temperature start
  ht_head.begin();
  ht_ring.begin();
  // SPI voltage control start
  SPI.begin();
    
  //// MOSFETS + PID + TEMPERATURE ////
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  windowStartTime = millis();

  //tell the PID to range between 0 and the full window size
  myPID_head.SetOutputLimits(0, WindowSize);
  myPID_ring.SetOutputLimits(0, WindowSize);
  //turn the PID on
  myPID_head.SetMode(AUTOMATIC);
  myPID_ring.SetMode(AUTOMATIC);
  
  //// TEST RUN ////
  // High voltage( 0 - max, 255 - min)
  digitalPotWrite(0);
  // StepperWrite( frequency, direction: 0 or 255)
  stepperWrite(2000,255);
  // Pressure ( 0 - min, 255 - max)
  pressureWrite(0);
  // Temperature setpoint in degrees celcius
  Setpoint_head = 20;
  Setpoint_ring = 20;
 /*
  Serial.print("head temp setpoint:");
  Serial.print("\n");
  Serial.print(Setpoint_head);
  Serial.print("\n");
  Serial.print("ring temp setpoint:");
  Serial.print(Setpoint_ring);
  Serial.print("\n");
  */
  
}


void loop() {

  if(Serial.available() > 0)  {  // if ther is data to read
    matlab_data = Serial.parseInt();
//    matlab_value = Serial.parseInt();
//    digitalWrite(13,HIGH);
//    delay(500);
//    digitalWrite(13,LOW);
//    delay(500);
//    digitalWrite(13,HIGH);
//    delay(500);
//    digitalWrite(13,LOW);
//    delay(500);
      digitalWrite(13,HIGH);
      delay(matlab_data*1000);
      digitalWrite(13,LOW);
      pressureWrite(matlab_data);
// /*
  }     
//    
//    
//    if(matlab_data == 1)  { // pressure
//      Serial.println("PRESSURE:");
//      Serial.println(matlab_data);
//      Serial.println(matlab_value);
//      digitalWrite(13,HIGH);
//      delay(1000);
//      digitalWrite(13,LOW);
//      pressureWrite(matlab_
//      
//    }
//    if(matlab_data == 2)  { // voltage
//      digitalWrite(13,HIGH);
//      delay(2000);
//      digitalWrite(13,LOW);
//    }
//    if(matlab_data == 3)  { // motor_speed
//      digitalWrite(13,HIGH);
//      delay(3000);
//      digitalWrite(13,LOW);
//    }
//    if(matlab_data == 4)  { // Setpoint_head
//      digitalWrite(13,HIGH);
//      delay(4000);
//      digitalWrite(13,LOW);
//    }      
//    if(matlab_data == 5)  { // Setpoint_ring
//      digitalWrite(13,HIGH);
//      delay(5000);
//      digitalWrite(13,LOW);
//    }
//    */
//  }
//  
//  /*
//  Serial.print("MATLAB:");
//  Serial.print("\n");
//  Serial.print(matlab_data);
//  Serial.print("\n");
//  */
//  //// TEMPERATURE SERIAL ////
//  /*
//  Serial.print("head temp:");
//  Serial.print("\n");
//  Serial.print(ht_head.getThmc());
//  Serial.print("\n");
//  Serial.print("ring temp:");
//  Serial.print("\n");
//  Serial.print(ht_ring.getThmc());
//  Serial.print("\n");
//  
//  delay(500);
//
//  //// PID HEAD ////
//  Input_head = ht_head.getThmc();
//  myPID_head.Compute();
//  /*
//  Serial.print("head output:");
//  Serial.print("\n");
//  Serial.print(Output_head);
//  Serial.print("\n");
//  */
//  unsigned long now_head = millis();
//  if(now_head - windowStartTime>WindowSize)  {
//    //time to shift the Relay Window
//    windowStartTime += WindowSize;
//  }
//  if(Output_head > now_head - windowStartTime)  {
//    setHeadRelayOn();  
//  }
//  else  {
//  setHeadRelayOff();
//  }
//  
//  //// PID RING ////
//  Input_ring = ht_ring.getThmc();
//  myPID_ring.Compute();
//  /*
//  Serial.print("ring output:");
//  Serial.print("\n");
//  Serial.print(Output_ring);
//  Serial.print("\n");
//  */
//  unsigned long now_ring = millis();
//  if(now_ring - windowStartTime>WindowSize)  {
//    //time to shift the Relay Window
//    windowStartTime += WindowSize;
//  }
//  if(Output_ring > now_ring - windowStartTime)  {
//    setRingRelayOn();  
//  }
//  else  {
//  setRingRelayOff();
//  }
//  
}


void digitalPotWrite(int value)  {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(value);
  
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
  /*
  Serial.print("voltage:");
  Serial.print("\n");
  Serial.print(value);
  Serial.print("\n");
  */
}
void pressureWrite(double value) {
  analogWrite(pressurePin,value);
  /*
  Serial.print("pressure:");
  Serial.print("\n");
  Serial.print(value);
  Serial.print("\n");
  */
}
void stepperWrite(int speed_val, int direction_val) {
  // tone() function interferes with PWM on pins 3 and 11
  // DON'T USE PINS 3 & 11 WHEN USING TONE()
  digitalWrite(DirPin, direction_val);
  tone(PulsePin, speed_val);
  /*
  Serial.print("stepper speed:");
  Serial.print("\n");
  Serial.print(speed_val);
  Serial.print("\n");
  */
  
}
void setHeadRelayOn() {
  leds[0] = CRGB::Red;
  FastLED.show();
}
void setHeadRelayOff()  {
  leds[0] = CRGB::Black;
  FastLED.show();
}
void setRingRelayOn() {
  leds[1] = CRGB::Red;
  FastLED.show();
}
void setRingRelayOff()  {
  leds[1] = CRGB::Black;
  FastLED.show();
}





