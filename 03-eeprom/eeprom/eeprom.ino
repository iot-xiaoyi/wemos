#include <Arduino.h>
#include <EEPROM.h>

int address = 3000;
byte value;
byte value_write = 0;
int len = 4096;

void setup() {
   // put your setup code here, to run once:
   Serial.begin(9600);

   EEPROM.begin(len);
}

void loop() {
  // put your main code here, to run repeatedly:

   value = EEPROM.read(address);
   Serial.print(address);
   Serial.print("\t");
   Serial.print(value, DEC);
   Serial.println();

   EEPROM.write(address, value_write);
   value_write ++;

   if (address == 3025)
   {
      EEPROM.commit();
   }
   address = address + 1;
   if (address == 4096)
      address = 0;

   delay(2000);
}
