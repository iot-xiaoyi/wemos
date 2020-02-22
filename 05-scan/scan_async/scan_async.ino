/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"
#include <Ticker.h>

Ticker tk;

int timer_flag = 0;
int scan_res = 0;

void time_coming_cicyle_cb(void)
{
  timer_flag = 1;
}

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  tk.attach(5, time_coming_cicyle_cb);
  Serial.println("Setup done");
}

void loop() {

  if (1 == timer_flag)
  {
    Serial.println("scan start");
    timer_flag = 0;
    WiFi.scanNetworks(true);
  }

  scan_res = WiFi.scanComplete();
  if (-1 == scan_res)
  {
  Serial.println("scan not finish");
  }
  else if(-2 == scan_res)
  {
    Serial.println("scan not triggered");
  }
  else if(scan_res >= 0)
  {
    Serial.println("scan done");
    if (scan_res == 0)
      Serial.println("no networks found");
    else
    {
      Serial.print(scan_res);
      Serial.println(" networks found");
      for (int i = 0; i < scan_res; ++i)
      {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
        delay(10);
      }
    }
    Serial.println("");
  }

  // Wait a bit before scanning again
  delay(500);
}

