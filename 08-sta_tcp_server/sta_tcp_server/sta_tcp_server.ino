#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <WiFiServer.h>

#define CLIENTS_MAX_NUMS  4
/* Set these to your desired credentials. */
const char *ssid = "lxy2305";
const char *password = "123456789a";
WiFiServer server(8089);
WiFiClient serverClients[CLIENTS_MAX_NUMS];

void setup() {
   Serial.begin(115200);
   WiFi.begin(ssid, password);
   Serial.println("\r\nconnecting to router... ");
      //等待wifi连接成功
   while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
   }
   Serial.println("");
   Serial.print("WiFi connected, local IP address:");
   Serial.println(WiFi.localIP());

   delay(500);
   Serial.println("Start tcp server...");
   server.begin();
   server.setNoDelay(true);
}

void loop() {
   int i = 0;
   if (server.hasClient())
   {
      for (i = 0; i < CLIENTS_MAX_NUMS; i++)
      {
         if (!serverClients[i] || !serverClients[i].connected())
         {
            if (serverClients[i])
            {
               serverClients[i].stop();
            }
            serverClients[i] = server.available();
            continue;
         }
      }
   }
   for (i = 0; i < CLIENTS_MAX_NUMS; i++)
   {
      if (serverClients[i] && serverClients[i].connected())
      {
         if (serverClients[i].available())
         {
            while (serverClients[i].available()) 
            {
               String recv_data = serverClients[i].readStringUntil('\r');
               Serial.println("recv data from tcp server:");
               Serial.println(recv_data);
                                 // send back
               serverClients[i].println(recv_data);
            }
         }
      }
   }
   delay(50);
}