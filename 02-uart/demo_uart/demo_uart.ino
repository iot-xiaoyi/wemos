#include <Arduino.h>

char byte_recv = 0;
String data_recv = "";
int flag_recv_str = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUILTIN_LED, OUTPUT); 
  digitalWrite(BUILTIN_LED, LOW);
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  while (Serial.available() > 0) {
     byte_recv = Serial.read();
     Serial1.print("recv_byte:");
     Serial1.println(byte_recv, HEX);
     Serial.print("recv_byte:");
     Serial.println(byte_recv, DEC);

     flag_recv_str = 1;
    data_recv += byte_recv;
    delay(10);
   }

   if (1 == flag_recv_str){
      flag_recv_str = 0;
      Serial.print("recv_str:");    
      Serial.println(data_recv);
      Serial1.print("recv_str:");    
      Serial1.println(data_recv);
      data_recv = "";
   }
}
