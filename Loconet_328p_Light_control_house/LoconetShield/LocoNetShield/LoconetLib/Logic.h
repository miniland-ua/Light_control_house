#ifndef LOGIC_H_
#define LOGIC_H_

#include "Sketch.h"

#define MODE_SETTING	0
#define MODE_DINNER		1
#define MODE_NIGHT_ON	2
#define MODE_NIGHT_MAIN	3
#define MODE_NIGHT_OFF	4

#define COLOR_BLACK strip.Color(0, 0, 0)

void change_color(uint16_t num, uint8_t ww, uint8_t nw, uint8_t cw);

void LED_off(uint16_t num);
void LED_on(uint16_t num);

void LED_color_status(uint16_t num, uint8_t color, bool status);
uint8_t read_LED_color(uint16_t num, uint8_t color);

void logic_mode();
void logic_mode_dinner();
void logic_mode_night(uint8_t chance_on, uint8_t max_num, uint8_t max_interval);

#endif /*LOGIC_H_*/

