/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"

char* ssid = "sand";
char* passwd = "12345678";
IPAddress local_static_ip(192, 168, 43, 10);
IPAddress local_gateway(192, 168, 43, 1);
IPAddress local_subnet(255, 255, 255, 0);
IPAddress local_dns_ip(192, 168, 43, 1);

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  WiFi.config(local_static_ip, local_gateway, local_subnet, local_dns_ip);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("connecting......");
  }
  Serial.println("Connect to router successfully!");
  Serial.println(String("mac address is ")+WiFi.macAddress());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Connect to router success");
    Serial.println(String("IP address is ")+WiFi.localIP().toString());
    Serial.println(String("Subnet mask is ")+WiFi.subnetMask().toString());
    Serial.println(String("gatewayIP address is ")+WiFi.gatewayIP().toString());
    Serial.println(String("dnsIP address is ")+WiFi.dnsIP().toString());
    Serial.println(String("SSID is ") + WiFi.SSID());
    Serial.println(String("PSK is ") + WiFi.psk());
    Serial.println(String("BSSID is ") + WiFi.BSSIDstr());
    Serial.println(String("RSSI is ") + WiFi.RSSI());
  }else
  {
    Serial.println("Connect to router failed");  
  }
  // Wait a bit before scanning again
  delay(1000);
}

