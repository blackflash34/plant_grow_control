#include <Arduino.h>
#include <GyverDS3231.h>
GyverDS3231 ds;

int water_t_last_millis = millis();
int water_t_interval_setup = 5  * 1000;
int water_t_duration_setup = 10 * 1000;

uint8_t start_l_time = 1;
uint8_t stop_l_time = 30;
int current_millis;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    ds.begin();
}

void loop() {
  
  ds.tick();
  Serial.println(ds.toString()); 
  water_timer();
  light_timer();
  Serial.println(ds.second());




}

void water_timer() {
	current_millis = millis();
	if (current_millis - water_t_last_millis > water_t_interval_setup) {
		//digitalWrite(pin, 1);
    Serial.println("Water timer +");
		if (current_millis - water_t_last_millis > water_t_interval_setup + water_t_duration_setup) {
			//digitalWrite(pin, 0);
      Serial.println("Water timer -");
			water_t_last_millis = millis();
		}
	}
  delay(1000);
}

void light_timer() {
  Datime dt(ds);
	if (dt.second == start_l_time) {
		//digitalWrite(pin2, 1);
    Serial.println("Light timer +");
	}
	if (dt.second == stop_l_time) {
		//digitalWrite(pin2, 0);
    Serial.println("Light timer -");
	}

}