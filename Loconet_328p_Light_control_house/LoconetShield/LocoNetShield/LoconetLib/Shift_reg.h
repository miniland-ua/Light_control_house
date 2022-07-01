#ifndef SHIFT_REG_H_
#define SHIFT_REG_H_

#include "Sketch.h"

#define SIZE_BUF_SHIFT 15	//размер буфера дл€ чтени€ датчика (n^2-1)

typedef struct Shift_t {
	uint16_t input;						//входные данные
	uint16_t buff[SIZE_BUF_SHIFT + 1];	//буфер с измененными значени€ми датчиков
	uint8_t buf_cnt_w;					//счетчик чтени€ дл€ буфера
	uint8_t buf_cnt_r;					//счетчик записи дл€ буфера
} Shift_t;

// ************************** ¬ходные пины ************************** //

void ShiftIN_init(void);	//инициализац€ входных пинов
void ShiftData_in(void);	//обновление входных пинов

// ************************** ќбработка ************************** //

void detect_D(void);		//обнаружение изменений пинов


#endif /*SHIFT_REG_H_*/

