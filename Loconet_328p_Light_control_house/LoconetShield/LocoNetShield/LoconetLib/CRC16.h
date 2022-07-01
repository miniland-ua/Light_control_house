/*
#ifndef CRC16_H_
#define CRC16_H_

#include "main.h"

#define CRC16_KEY 0xA001	// Полином

uint16_t CRC16_Table[256];	// Таблица CRC

void CRC16_CalcTable();													// Рассчитать и заполнить таблицу CRC
uint16_t CRC16_Calc(uint8_t* databyte_ptr, uint8_t length);				// Рассчитать CRC блока данных
uint8_t CheckCRC(uint8_t* databytes_ptr, uint8_t index, uint8_t lenth); // Рассчитать CRC блока данных в кольцевом буфере и сравнить с принятым CRC

#endif / * CRC16_H_ * /*/