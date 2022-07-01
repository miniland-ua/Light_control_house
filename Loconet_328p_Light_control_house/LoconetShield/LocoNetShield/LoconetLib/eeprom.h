#ifndef MY_EEPROM_H_
#define MY_EEPROM_H_

#include "Sketch.h"

#define WW	0
#define NW	1
#define CW	2

void eeprom_clear_memory(void);		//очистка памяти в EEPROM
void eeprom_show_memory(void);		//отображение памяти EEPROM

uint8_t r_mem_LED(uint16_t num, uint8_t color);
void r_mem_LEDs_all(void);

void w_mem_LED(uint16_t num, uint8_t ww, uint8_t nw, uint8_t cw);
void w_mem_LED_ww(uint16_t num, uint8_t ww);
void w_mem_LED_nw(uint16_t num, uint8_t nw);
void w_mem_LED_cw(uint16_t num, uint8_t cw);

#endif /*MY_EEPROM_H_*/
