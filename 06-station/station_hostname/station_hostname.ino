/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"

char* ssid = "sand";
char* passwd = "12345678";
char *host = "ESP8266_TEST1";

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("connecting......");
  }
  Serial.println("Connect to router successfully!");
  Serial.println(String("mac address is ")+WiFi.macAddress());
  Serial.println(String("hostname is ")+WiFi.hostname());
  WiFi.hostname(host);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Connect to router success");
    Serial.println(String("hostname is ")+WiFi.hostname());
  }else
  {
    Serial.println("Connect to router failed");  
  }
  // Wait a bit before scanning again
  delay(1000);
}

