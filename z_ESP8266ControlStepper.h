#include <ArduinoJson.h>
#include <Stepper_28BYJ_48.h>
#include <EEPROM.h>

void esp8266ControlStepper(String status, int stepper1, int stepper2, int stepper3, int stepper4)
{
    EEPROM.begin(10);
    int size = 1024;
    char json[size];
    Stepper_28BYJ_48 keoStepper(stepper1, stepper2, stepper3, stepper4);
    // Ép kiểu từ String sang Array
    status.toCharArray(json, size);
    DynamicJsonDocument jsonBuffer(size);
    DeserializationError error = deserializeJson(jsonBuffer, json);
    if (error)
    {
        Serial.println("Parse JSON failed!");
    }
    // atoi - hàm chuyển một chuỗi số sang kiểu int
    int keoSteps = atoi(jsonBuffer["keoSet"]);
    // strcmp - string compare - so sánh 2 chuỗi, nếu bằng nhau thì trả về 0
    if (strcmp(jsonBuffer["keo"], "on") == 0)
    {
        if (EEPROM.read(0) != 1)
        {
            EEPROM.write(0, 1);
            //Mỗi lần write phải commit xem đã write được hay chưa
            if (EEPROM.commit())
            {
                Serial.print("Feeder ");
                Serial.println("ON!");
                keoStepper.step(keoSteps);
            }
        }
        else
        {
            Serial.print("Feeder ");
            Serial.println("ON!!");
        }
    }
    else
    {
        if (EEPROM.read(0) != 0)
        {
            EEPROM.write(0, 0);
            if (EEPROM.commit())
            {
                Serial.print("Feeder ");
                Serial.println("OFF!");
                keoStepper.step(0 - keoSteps);
            }
        }
        else
        {
            Serial.print("Feeder ");
            Serial.println("OFF!!");
        }
    }
}