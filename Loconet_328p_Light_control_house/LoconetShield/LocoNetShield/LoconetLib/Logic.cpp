#include "Sketch.h"

extern Adafruit_NeoPixel strip;
extern Timer_t timer_syst;
extern bool LED_status[SUM_LEDS];
extern bool LED_status_color[SUM_LEDS][3];
extern uint8_t mode;
uint8_t interval_t;
extern uint16_t LEDs_on_summ;

void change_color(uint16_t num, uint8_t ww, uint8_t nw, uint8_t cw) {
	if (num < SUM_LEDS) {
		w_mem_LED(num, ww, nw, cw);
	}
}

void LED_off(uint16_t num) {
	if (LED_status[num] == true) {
		LEDs_on_summ--;
		LED_status[num] = false;
		strip.setPixelColor(num, COLOR_BLACK);
		strip.show();
		Serial.print("LED[");
		Serial.print(num);
		Serial.print("] - off (");
		Serial.print(LEDs_on_summ);
		Serial.print("/");
		Serial.print(SUM_LEDS);
		Serial.print("=");
		Serial.print(LEDs_on_summ * 100 / SUM_LEDS);
		Serial.println("%)");
	}
}

void LED_on(uint16_t num) {
	if (LED_status[num] == false) {
		LEDs_on_summ++;
		LED_status[num] = true;
		strip.setPixelColor(num, strip.Color(read_LED_color(num, WW), read_LED_color(num, NW), read_LED_color(num, CW)) );
		strip.show();
		Serial.print("LED[");
		Serial.print(num);
		Serial.print("] - off (");
		Serial.print(LEDs_on_summ);
		Serial.print("/");
		Serial.print(SUM_LEDS);
		Serial.print("=");
		Serial.print(LEDs_on_summ * 100 / SUM_LEDS);
		Serial.println("%)");
	}
}

void LED_color_status(uint16_t num, uint8_t color, bool status) {
	LED_status_color[num][color] = status;
}

uint8_t read_LED_color(uint16_t num, uint8_t color) {
	if (LED_status_color[num][color] == true) {
		return r_mem_LED(num, color);
	} else {
		return 0;
	}
}

void r_mem_LEDs_all(void) {
	uint16_t tmp_LEDs_on_summ = 0;
	for (uint16_t i = 0; i < SUM_LEDS; i++) {
		if (LED_status[i] == true) {
			strip.setPixelColor(i, strip.Color(read_LED_color(i, WW), read_LED_color(i, NW), read_LED_color(i, CW)));
			tmp_LEDs_on_summ++;
		} else {
			strip.setPixelColor(i, COLOR_BLACK);
		}
	}
	strip.show();
	LEDs_on_summ = tmp_LEDs_on_summ;
}


uint16_t param_night_on_limit_h = 80;
uint16_t param_night_main_limit_l = 70;
uint16_t param_night_main_limit_h = 90;


void logic_mode() {
	switch (mode) {
		case MODE_SETTING:
			
			break;
		case MODE_DINNER:
			logic_mode_dinner();
			break;
		case MODE_NIGHT_ON:
			if ( (uint32_t)(LEDs_on_summ * 100 / SUM_LEDS ) < param_night_on_limit_h ) {	//если включено более 80% LEDs
				logic_mode_night(90, 5, 3);
			} else {
				mode = MODE_NIGHT_MAIN;
			}
			break;
		case MODE_NIGHT_MAIN:
			if ( (uint32_t)(LEDs_on_summ * 100 / SUM_LEDS ) < param_night_main_limit_l ) {	//если включено менее 70% LEDs
				logic_mode_night(80, 2, 3);
			} else if ( (uint32_t)(LEDs_on_summ * 100 / SUM_LEDS ) > param_night_main_limit_h ) {	//если включено более 90% LEDs
				logic_mode_night(20, 2, 3);
			} else {
				logic_mode_night(50, 2, 3);
			}
			break;
		case MODE_NIGHT_OFF:
			if (LEDs_on_summ == 0) {	//если включено более 80% LEDs
				mode = MODE_DINNER;
			} else {
				logic_mode_night(10, 5, 3);
			}
			break;
	}
}

void logic_mode_dinner() {

}

//chance_on: веро€тность включени€/отключение освещени€, %
//max_num: максимальное количество включенных  LEDs за раз
//max_interval:максимальный интервал времени между включени€ми LEDs
void logic_mode_night(uint8_t chance_on, uint8_t max_num, uint8_t max_interval) {
	if (timer_syst.cnt > interval_t) {
		max_num = 1 + rand() % max_num;		//количество мен€ющих LED
		bool status;
		uint16_t num;
	
		for (uint16_t i = 0; i < max_num; i++) {
			if ( (rand() % 100) < chance_on) {
				status = true;
				num = rand() % (SUM_LEDS - LEDs_on_summ);
			} else {
				status = false;
				num = rand() % (LEDs_on_summ);
			}

			uint16_t n = 0;
			for (uint16_t i = 0; i < SUM_LEDS; i++) {
				if ( (LED_status[i] == false) && (status == true) ) {
					n++;
					if (n == num) {
						LED_on(i);
						break;
					}
				} else if ( (LED_status[i] == true) && (status == false) ) {
					n++;
					if (n == num) {
						LED_off(i);
						break;
					}
				}
			}
		}
		interval_t =  rand() % max_interval;
		timer_syst.cnt = 0;
	}
}

