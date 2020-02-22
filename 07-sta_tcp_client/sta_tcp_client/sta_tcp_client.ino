/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */

#include <ESP8266WiFi.h>
 
char* ssid = "lxy2305";
char* passwd = "123456789a";

const uint16_t port = 8089;
const char * host = "192.168.1.7"; // ip or dns
WiFiClient client;//创建一个tcp client连接
 
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
        client.println(String("hello tcp server"));
    }
}
 
void loop() {

    //读取从server返回到响应数据
    String recv_data = client.readStringUntil('\r');
    Serial.println(recv_data);
    
    if (0 == recv_data.compareTo("exit"))
    {
        Serial.println("closing connection");
        client.stop();
    }
    delay(200);
}
