#include "PCF8574.h"    //Include the HCPCF8574 library

PCF8574 Port1(0x20);  //Create an instance of the library
PCF8574 Port2(0x21);  //Create an instance of the library


void setup() 
{
  Port1.begin();            //Initiliase the PCF8574 (all pins are set to high)
  Port2.begin();            //Initiliase the PCF8574 (all pins are set to high)

  for (int i=0; i<8; i++){
    //Port.pinMode(i, OUTPUT); //Set digital pin 0 to an ouput
    Port1.shiftRight();
    Port2.shiftRight();
  }
  
}


void loop() 
{
  int relay1=0;int relay2=1;int relay3=2; int relay4=3;int relay5=4;int relay6=5;int relay7=6;int relay8=7;
  int relay9=0;int relay10=1; int relay11=2;int relay12=3;int relay13=4;int relay14=5;int relay15=6;int relay16=7;
  
    Port1.write(relay1, HIGH); //Set digital pin 0 high
    Port2.write(relay9, HIGH); //Set digital pin 0 high
    delay(1000);
    Port1.write(relay1, LOW); //Set digital pin 0 high
    Port2.write(relay9, LOW); //Set digital pin 0 high
    delay(1000);
    
}
