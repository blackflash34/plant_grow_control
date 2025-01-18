#include <Arduino.h>
#include <GyverDS3231.h>
GyverDS3231 ds;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    if (!ds.begin()) ds.setBuildTime();
    Datime dt;
    
    dt.year = 2025;
    dt.month = 1;
    dt.day = 18;
    dt.hour = 17;
    dt.minute = 1;
    dt.second = 40;
    ds.setTime(dt);
}

void loop() {
    if (ds.tick()) {
        Serial.println(ds.toString());

        Datime dt(ds);
        Serial.println(dt.second);
        Serial.println(dt.minute);
        // ...
    }
}