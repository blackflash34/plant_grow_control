#include <Arduino.h>
#include <GyverDS3231.h>
GyverDS3231 ds;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    ds.begin();
    //Datime dt;
    //dt.year = 2025;
    //dt.month = 1;
    //dt.day = 18;
    //dt.hour = 18;
    //dt.minute = 49;
    //dt.second = 0;
    //ds.setTime(dt);
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