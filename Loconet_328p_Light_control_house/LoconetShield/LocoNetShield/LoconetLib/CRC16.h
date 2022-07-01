/*
#ifndef CRC16_H_
#define CRC16_H_

#include "main.h"

#define CRC16_KEY 0xA001	// �������

uint16_t CRC16_Table[256];	// ������� CRC

void CRC16_CalcTable();													// ���������� � ��������� ������� CRC
uint16_t CRC16_Calc(uint8_t* databyte_ptr, uint8_t length);				// ���������� CRC ����� ������
uint8_t CheckCRC(uint8_t* databytes_ptr, uint8_t index, uint8_t lenth); // ���������� CRC ����� ������ � ��������� ������ � �������� � �������� CRC

#endif / * CRC16_H_ * /*/