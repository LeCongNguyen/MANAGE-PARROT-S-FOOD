#include <ESP8266WiFi.h>

void esp8266ConnectToWifi(const char *ssid, const char *password)
{
    pinMode(LED_BUILTIN, OUTPUT);
    WiFi.begin(ssid, password);
    Serial.print("Connecting...");
    delay(250);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        digitalWrite(LED_BUILTIN, LOW);
        delay(250);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
    }
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}