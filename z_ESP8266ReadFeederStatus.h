#include <ESP8266WiFi.h>
#include <WiFiClient.h>

String esp8266ReadFeederStatus(String host, String path)
{
    String status;
    pinMode(LED_BUILTIN, OUTPUT);
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        if (!client.connect(host, 80))
        {
            Serial.println("Connect to server fail!");
            return "";
        }
        // ESP sent GET request to host
        client.print(String("GET ") + path + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: keep-alive\r\n\r\n");
        while (client.available() == 0)
        {
        }
        while (client.available())
        {
            // Đọc response được gửi tới ESP từ host
            status = client.readString();
            // Tách ra nội dung file feeder-status.json
            status = status.substring(status.indexOf("{"));
            Serial.print("Feeder Status: ");
            Serial.println(status);
            client.stop();
        }
        return status;
    }
    else
    {
        Serial.println("WiFi Disconnected!");
        return "";
    }
}