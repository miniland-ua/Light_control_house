#ifndef COMMAND_H_
#define COMMAND_H_

#include "Sketch.h"

// ["led"][num][ww][nw][cw] - ������ ������� ������ WW + NW + CW
// ["ww"][num][ww] - ������ �������� ������� ����� WW
// ["nw"][num][nw] - ������ �������� ������� ����� NW
// ["cw"][num][cw] - ������ �������� ������� ����� CW

// ["clear_on"][num] - ������� �������� ����� � �������� 255
// ["clear_off"][num] - ������� �������� ����� � �������� 0
// ["clear_on_all"] - ������� �������� ������ � �������� 255
// ["clear_off_all"] - ������� �������� ������ � �������� 0

// ["on_all"] - �������� ���������� ���� ������ ��� ���� LED
// ["off_all"] - ���������� ���������� ���� ������ ��� ���� LED
// ["on_all_ww"] - ��������� ���������� ����� ��� ���� LED ����� WW
// ["on_all_nw"] - ��������� ���������� ����� ��� ���� LED ����� NW
// ["on_all_cw"] - ��������� ���������� ����� ��� ���� LED ����� CW

// ["on"][num] - ��������� ���������� ���� ������ ��� LED
// ["off"][num] - ���������� ���������� ���� ������ ��� LED
// ["on_ww"] - ��������� ���������� ����� ��� LED ����� WW
// ["off_ww"] - ���������� ���������� ����� ��� LED ����� WW
// ["on_nw"] - ��������� ���������� ����� ��� LED ����� NW
// ["off_nw"] - ���������� ���������� ����� ��� LED ����� NW
// ["on_cw"] - ��������� ���������� ����� ��� LED ����� CW
// ["off_cw"] - ���������� ���������� ����� ��� LED ����� CW

// ["setting"] - ����� SETTING
// ["dinner"] - ����� DINNER
// ["night_on"] - ����� NIGHT_ON
// ["night_main"] - ����� NIGHT_MAIN
// ["night_off"] - ����� NIGHT_OFF

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

