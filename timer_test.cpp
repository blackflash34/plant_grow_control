#include <GyverDS3231.h>
GyverDS3231 ds;

int water_t_last_millis = miilis();
int water_t_interval_setup = 1 * 60 * 1000;
int water_t_duration_setup = 10 * 1000;

int start_l_time = 12
int stop_l_time = 18

void water_timer() {
	current_millis = millis();
	if (current_millis - water_t_last_millis > water_t_interval_setup) {
		digitalWrite(pin, 1);
		if (current_millis - water_t_last_millis > water_t_interval_setup + water_t_duration_setup) {
			digitalWrite(pin, 0);
			water_t_last_millis = millis();
		}
	}
}

void light_timer() {
	if (ds.hours() == start_l_time) {
		digitalWrite(pin2, 1);
	}
	if (ds.hours() == stop_l_time) {
		digitalWrite(pin2, 0);
	}

}