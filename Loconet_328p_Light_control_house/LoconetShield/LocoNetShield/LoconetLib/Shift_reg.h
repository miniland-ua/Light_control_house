#ifndef SHIFT_REG_H_
#define SHIFT_REG_H_

#include "Sketch.h"

#define SIZE_BUF_SHIFT 15	//������ ������ ��� ������ ������� (n^2-1)

typedef struct Shift_t {
	uint16_t input;						//������� ������
	uint16_t buff[SIZE_BUF_SHIFT + 1];	//����� � ����������� ���������� ��������
	uint8_t buf_cnt_w;					//������� ������ ��� ������
	uint8_t buf_cnt_r;					//������� ������ ��� ������
} Shift_t;

// ************************** ������� ���� ************************** //

void ShiftIN_init(void);	//������������ ������� �����
void ShiftData_in(void);	//���������� ������� �����

// ************************** ��������� ************************** //

void detect_D(void);		//����������� ��������� �����


#endif /*SHIFT_REG_H_*/

