#include "Sketch.h"

extern Shift_t shift;

// ************************** ������� ���� ************************** //

//������������ ��� ������� �����
void ShiftIN_init(void)	{
	PORTB &= ~(1 << 3);	// INPUT_165 (PB3) - PB3
	PORTB |= (1 << 4);	// LOCK_165 (PC4) - PB4
	DDRB &= ~(1 << 3);	// INPUT_165 (PB3) - PB3
	DDRD |= (1 << 7);	// CLK (PD7) - PD7
	DDRB |= (1 << 4);	// LOCK_165 (PC4) - PB4
}

//���������� ������� �����
void ShiftData_in(void) {
	PORTB |= (1 << 3);	// INPUT_165 (PB3) - PB3
	PORTB &= ~(1 << 4);	// LOCK_165 (PC4) - PB4
	PORTB |= (1 << 4);	// LOCK_165 (PC4) - PB4
	PORTB &= ~(1 << 3); // INPUT_165 (PB3) - PB3
	uint16_t tmp = 0;	//�������� ������� ����� (��������, ���� �� ����� ������� ��� ������)
	bool state;			//��������� �������� ����
	for (uint8_t b = 0; b < 16 ; b++) {	//������� ������� �����
		state = PINB & (1 << 3);		// INPUT_165 (PB3) - PB3
		tmp = (tmp << 1) + state;		//������ ������ � tmp
		PORTD |= (1 << 7);				// CLK (PD7) - PD7
		PORTD &= ~(1 << 7);				// CLK (PD7) - PD7
	}
	shift.input = tmp;	//���������� �������� ������� �����

	_delay_ms(20);		//���������� ������ 20��
}

// ************************** ��������� ************************** //

//����������� ��������� �����
void detect_D(void) {
	ShiftData_in();
	uint16_t change = shift.buff[shift.buf_cnt_w] ^ shift.input;	//������ ������� �������� ��� ��������
	if (change > 0) {												//���� �� ����� ��������� ���������
		shift.buf_cnt_w++; shift.buf_cnt_w &= SIZE_BUF_SHIFT;		//���������� �������� �� ��������� �������
		shift.buff[shift.buf_cnt_w] = shift.input;					//���������� ������ � ������
	}
}

