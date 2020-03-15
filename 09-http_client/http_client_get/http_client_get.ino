/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

char* ssid = "sand";
char* passwd = "12345678";

const uint16_t port = 80;
const char * host = "http://t.weather.sojson.com/api/weather/city/101021300";
 HTTPClient http;

void setup() {
   //在这里加入初始化相关代码，只运行一次:
   Serial.begin(115200);

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, passwd);

   Serial.println("connecting to router... ");
   //等待wifi连接成功
   while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
   }
   Serial.println("");

   Serial.print("WiFi connected, local IP address:");
   Serial.println(WiFi.localIP());

   Serial.print("[HTTP] begin...\n");

   http.begin(host); //HTTP

    delay(500);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED)
  {
      // start connection and send HTTP header
      int httpCode = http.GET();
      if(httpCode) {
         // HTTP header has been send and Server response header has been handled
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
         // file found at server
         if(httpCode == 200) {
               String payload = http.getString();
               Serial.println(payload);
         }
      } else {
         Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
      }
    }

    delay(5000);
}

