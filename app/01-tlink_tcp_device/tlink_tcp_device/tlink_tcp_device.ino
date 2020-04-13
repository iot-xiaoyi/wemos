/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Ticker.h>

#define DEVICE_ID "V36625K243D8ROR1"
#define DEVICE_DATA  "#25,1#"

char* ssid = "lxy2305";
char* passwd = "123456789a";

const uint16_t port = 8647;
const char * host = "tcp.tlink.io"; // ip or dns
WiFiClient client;//创建一个tcp client连接
int  heartbeart_flag = 0;

Ticker tk;

void time_coming_cicyle_cb(void)
{
  heartbeart_flag = 1;
}

// 复位或上电后运行一次:
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
    delay(500);
    Serial.print("connecting to ");
    Serial.println(host);
    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }else
    {
        Serial.println("connect to tcp server success.");
        Serial.println("Send this data to tcp server");
        client.print(DEVICE_ID);
        delay(500);
        client.print(DEVICE_DATA);
         // call time_coming_cicyle_cb every 30s
         tk.attach(5, time_coming_cicyle_cb);
    }
}
 
void loop() {

    if (1 == heartbeart_flag)
    {
      client.print("Q");
      heartbeart_flag = 0;
    }
    
    String recv_data = client.readString(); //   client.readStringUntil('\r');
    if (recv_data != NULL)
    {
      Serial.print("Receive data : ");
      Serial.println(recv_data);
    }
    delay(20);
}
