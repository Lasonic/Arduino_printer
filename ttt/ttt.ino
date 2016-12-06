
//// DEFINE Pressure Pin

const int pressurePin = 8;

void setup() {
  // put your setup code here, to run once:
    //// PRESSURE SETUP ////

  pinMode(pressurePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pressureWrite(255);
//
     
}
void pressureWrite(int value) {
  analogWrite(pressurePin,value);
}

