/*
#include "main.h"

uint16_t CRC16_Table[256];

void CRC16_CalcTable()
{
	uint16_t val, crc;

	for(uint16_t i = 0; i < 256; i++) {
		crc = 0;
		val = i;
		for(uint16_t j = 0; j < 8; j++) {
			if( (val ^ crc) & 0x0001) {
				crc = (crc >> 1) ^ CRC16_KEY;
				} else {
				crc >>= 1;
			}
			val >>= 1;
		}
		CRC16_Table[i] = crc;
	}
}

uint16_t CRC16_Calc(uint8_t* databyte_ptr, uint8_t length)
{
	uint16_t result_crc = 0x0000; // 0xFFFF
	while(length--) {
		result_crc = (result_crc >> 8) ^ CRC16_Table[(result_crc & 0xFF) ^ *databyte_ptr++];
	}
	
	return result_crc;
}

uint8_t CheckCRC(uint8_t* databytes_ptr, uint8_t index, uint8_t lenth)
{
	// Вычисление CRC блока данных:
	// databytes_ptr - указатель на первый элемент данных в массиве
	// index - индекс первого элемента данных в массиве
	// lenth - количество байтов данных для вычисления CRC
	uint16_t calc_crc16 = 0x0000; // 0xFFFF
	while(lenth--) {
		calc_crc16 = (calc_crc16 >> 8) ^ CRC16_Table[(calc_crc16 & 0xFF) ^ *databytes_ptr];
		
		index++;
		index &= 15;			// Маска на индекс(чтобы не вышел за пределы кольцевого буфера)
		if (index == 0)			// Если произошел переход в начало кольцевого буфера
		databytes_ptr -= 15;	// Переместить указатель на начало буфера
		else
		databytes_ptr++;		// Следующий байт в буфере
	}
	
	// Склеивание принятого CRC (следующие 2 байта после блока данных [low][high]):
	uint16_t rcv_crc16 = 0;
	uint8_t rcv_crc_low = *databytes_ptr;
	
	index++;
	index &= 15;
	if (index == 0) {
		databytes_ptr -= 15;
		} else {
		databytes_ptr++;
	}
	
	rcv_crc16 = *databytes_ptr; // high
	rcv_crc16 <<= 8;
	rcv_crc16 |= rcv_crc_low;	// low
	
	// Сравнение:
	if (calc_crc16 == rcv_crc16) {
		return 1;
		} else {
		return 0;
	}
}
*/
