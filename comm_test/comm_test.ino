#include  <ctype.h>
char ibyte;
bool m;
void setup()
{
  Serial.begin(9600);
  delay(2500);
}

void loop()
{
  if(Serial.available()>0)
  {
    ibyte=Serial.read();
    unsigned long number = strtoul( ibyte, NULL, 10 );
    m = isdigit(number);
//    Serial.print(number);
//    Serial.print(m);
    Serial.print(m);
  }
}
  long stringToLong(String value) {
  long outLong=0;
      long inLong=1;
      int c = 0;
      int idx=value.length()-1;
      for(int i=0;i<=idx;i++){

          c=(int)value[idx-i];
          outLong+=inLong*(c-48);
          inLong*=10;
      }
      return outLong;
  }
