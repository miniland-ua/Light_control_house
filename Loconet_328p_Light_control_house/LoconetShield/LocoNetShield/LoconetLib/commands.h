#ifndef COMMAND_H_
#define COMMAND_H_

#include "Sketch.h"

// ["led"][num][ww][nw][cw] - запись яркости портов WW + NW + CW
// ["ww"][num][ww] - запись значения яркости порта WW
// ["nw"][num][nw] - запись значения яркости порта NW
// ["cw"][num][cw] - запись значения яркости порта CW

// ["clear_on"][num] - очистка значения порта в значения 255
// ["clear_off"][num] - очистка значения порта в значения 0
// ["clear_on_all"] - очистка значений портов в значения 255
// ["clear_off_all"] - очистка значений портов в значения 0

// ["on_all"] - вкючение отбражение всех цветов для всех LED
// ["off_all"] - отключение отбражение всех цветов для всех LED
// ["on_all_ww"] - включение отбражение цвета для всех LED цвета WW
// ["on_all_nw"] - включение отбражение цвета для всех LED цвета NW
// ["on_all_cw"] - включение отбражение цвета для всех LED цвета CW

// ["on"][num] - включение отбражение всех цветов для LED
// ["off"][num] - отключение отбражение всех цветов для LED
// ["on_ww"] - включение отбражение цвета для LED цвета WW
// ["off_ww"] - отключение отбражение цвета для LED цвета WW
// ["on_nw"] - включение отбражение цвета для LED цвета NW
// ["off_nw"] - отключение отбражение цвета для LED цвета NW
// ["on_cw"] - включение отбражение цвета для LED цвета CW
// ["off_cw"] - отключение отбражение цвета для LED цвета CW

// ["setting"] - режим SETTING
// ["dinner"] - режим DINNER
// ["night_on"] - режим NIGHT_ON
// ["night_main"] - режим NIGHT_MAIN
// ["night_off"] - режим NIGHT_OFF

#define SIZE_COMMANDS 64

typedef struct Command_t {
	char buff[SIZE_COMMANDS];
	uint8_t cnt_write;
	uint8_t cnt_read;
} Command_t;

//struct: [name] [num1] [num2] ... [num_n]
void comm_read();	//read commands

void comm_clean_buff();
static bool check_name(char str[]);
static uint16_t pow10(uint8_t x);
static uint16_t read_number();
static bool comm_logic_name();

#endif /*COMMAND_H_*/

