#include "z_ESP8266ConnectToWifi.h"
#include "z_ESP8266ReadFeederStatus.h"
#include "z_ESP8266ControlStepper.h"

void setup()
{
	Serial.begin(115200);
	esp8266ConnectToWifi("VNPT_2.4G", "nguyen12345");
}

void loop()
{
	String status = esp8266ReadFeederStatus("managefoodofparrot.000webhostapp.com", "/feeder-status.json");
	esp8266ControlStepper(status, 5, 4, 13, 14);
	ESP.deepSleep(15*60000000);
}
