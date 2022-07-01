#include "Sketch.h"

extern Adafruit_NeoPixel strip;
extern bool LED_status[SUM_LEDS];
extern bool LED_status_color[SUM_LEDS][3];
extern uint16_t LEDs_on_summ;

//очистка памяти в EEPROM
void eeprom_clear_memory(void) {
	Serial.println("Memory clearing");

	for (uint16_t i = 0; i < 2048; i++) {
		eeprom_write_byte((uint8_t*)i, (uint8_t)0xFF);	//очистка памяти
	}

	Serial.println("Memory cleared");
}

//отображение памяти EEPROM
void eeprom_show_memory(void) {
	for (uint16_t i = 0; i < 2048; i++) {
		Serial.print(i);
		Serial.print(": ");
		Serial.println(eeprom_read_byte((uint8_t*)i));
	}
}

uint8_t r_mem_LED(uint16_t num, uint8_t color) {
	switch (color) {
		case WW:
			return eeprom_read_byte((uint8_t*)(3 * num));
			break;
		case NW:
			return eeprom_read_byte((uint8_t*)(3 * num + 1));
			break;
		case CW:
			return eeprom_read_byte((uint8_t*)(3 * num + 2));
			break;
	}
	return 255;
}

void w_mem_LED(uint16_t num, uint8_t ww, uint8_t nw, uint8_t cw) {
	eeprom_write_byte((uint8_t*)(3 * num), (uint8_t)ww);
	eeprom_write_byte((uint8_t*)(3 * num + 1), (uint8_t)nw);
	eeprom_write_byte((uint8_t*)(3 * num + 2), (uint8_t)cw);
}

void w_mem_LED_ww(uint16_t num, uint8_t ww) {
	eeprom_write_byte((uint8_t*)(3 * num), (uint8_t)ww);
}

void w_mem_LED_nw(uint16_t num, uint8_t nw) {
	eeprom_write_byte((uint8_t*)(3 * num + 1), (uint8_t)nw);
}

void w_mem_LED_cw(uint16_t num, uint8_t cw) {
	eeprom_write_byte((uint8_t*)(3 * num + 2), (uint8_t)cw);
}

