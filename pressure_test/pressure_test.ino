//// DEFINE Pressure Pin
const int pressurePin = 8;

void setup() {
  // put your setup code here, to run once:
  //// PRESSURE SETUP ////
  pinMode(pressurePin, OUTPUT);
  double pressure;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pressureWrite(128);
}

void pressureWrite(int value) {
  analogWrite(pressurePin,value);
  /*
  Serial.print("pressure:");
  Serial.print("\n");
  Serial.print(value);
  Serial.print("\n");
  */
}
