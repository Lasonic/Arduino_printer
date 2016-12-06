#include  <ctype.h>
//// DEFINE Pressure Pin
char matlab_data;
const int pressurePin = 8;
int m;
void setup() {
  // put your setup code here, to run once:
    //// PRESSURE SETUP ////
  Serial.begin(9600);
  pinMode(pressurePin, OUTPUT);
  delay(2500);

}

void loop() {
  // put your main code here, to run repeatedly:
   if(Serial.available() > 0)  {  // if ther is data to read
    matlab_data = Serial.read();
    unsigned long number = strtoul( input, NULL, 10 );
//    m = isdigit(number);
    Serial.print(matlab_data);
    pressureWrite(number);
  }     
 
  
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

