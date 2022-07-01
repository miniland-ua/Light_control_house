#ifndef TIMER_H_
#define TIMER_H_

#include "Sketch.h"

typedef struct Timer_t {
	bool ready;			//флаг на готовность выполнения логики
	uint8_t cnt;
} Timer_t;

void Timer_init(void);	//инициализация счетчика

#endif /*TIMER_H_*/

