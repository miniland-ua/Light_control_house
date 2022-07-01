#include "Sketch.h"

Timer_t timer_syst;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(SUM_LEDS, PIN_OUT, NEO_GRB + NEO_KHZ800);

uint16_t LEDs_on_summ;
uint8_t mode;
bool LED_status[SUM_LEDS];
bool LED_status_color[SUM_LEDS][3];



void setup() {
	Serial.begin(19200);
	Serial.println("Light_control_house v1.0 test firmware");

	strip.begin();

	LEDs_on_summ = 0;
	mode = MODE_SETTING;
	for (uint16_t i = 0; i < SUM_LEDS; i++) {
		for (uint16_t j = 0; j < 4; j++) {
			LED_status[i] = true;
			LED_status_color[i][WW] = true;
			LED_status_color[i][NW] = true;
			LED_status_color[i][CW] = true;
		}
	}
	r_mem_LEDs_all();

	Timer_init();

}

void loop() {
	comm_read();	//чтение команд
	if (timer_syst.ready == true) {		//если таймер готов
		timer_syst.cnt++;
		logic_mode();
		r_mem_LEDs_all();

		timer_syst.ready = false;		//отправить таймер на подготовку
	}
}

