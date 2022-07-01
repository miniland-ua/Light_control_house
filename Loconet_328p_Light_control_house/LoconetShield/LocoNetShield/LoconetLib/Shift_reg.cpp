#include "Sketch.h"

extern Shift_t shift;

// ************************** ¬ходные пины ************************** //

//инициализац€ дл€ входных пинов
void ShiftIN_init(void)	{
	PORTB &= ~(1 << 3);	// INPUT_165 (PB3) - PB3
	PORTB |= (1 << 4);	// LOCK_165 (PC4) - PB4
	DDRB &= ~(1 << 3);	// INPUT_165 (PB3) - PB3
	DDRD |= (1 << 7);	// CLK (PD7) - PD7
	DDRB |= (1 << 4);	// LOCK_165 (PC4) - PB4
}

//обновление входных пинов
void ShiftData_in(void) {
	PORTB |= (1 << 3);	// INPUT_165 (PB3) - PB3
	PORTB &= ~(1 << 4);	// LOCK_165 (PC4) - PB4
	PORTB |= (1 << 4);	// LOCK_165 (PC4) - PB4
	PORTB &= ~(1 << 3); // INPUT_165 (PB3) - PB3
	uint16_t tmp = 0;	//значени€ входных пинов (временно, пока не будут собраны все данные)
	bool state;			//состо€ние входного пина
	for (uint8_t b = 0; b < 16 ; b++) {	//перебор входных пинов
		state = PINB & (1 << 3);		// INPUT_165 (PB3) - PB3
		tmp = (tmp << 1) + state;		//запись входов в tmp
		PORTD |= (1 << 7);				// CLK (PD7) - PD7
		PORTD &= ~(1 << 7);				// CLK (PD7) - PD7
	}
	shift.input = tmp;	//сохранение значений входных пинов

	_delay_ms(20);		//выполнение каждые 20мс
}

// ************************** ќбработка ************************** //

//обнаружение изменений пинов
void detect_D(void) {
	ShiftData_in();
	uint16_t change = shift.buff[shift.buf_cnt_w] ^ shift.input;	//запись входных значений дл€ проверки
	if (change > 0) {												//если на входе произошло изменение
		shift.buf_cnt_w++; shift.buf_cnt_w &= SIZE_BUF_SHIFT;		//добавление счетчика на обработку буффера
		shift.buff[shift.buf_cnt_w] = shift.input;					//сохранение входов в буффер
	}
}

