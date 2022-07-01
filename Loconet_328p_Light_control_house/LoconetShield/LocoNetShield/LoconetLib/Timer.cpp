#include "Sketch.h"


extern Timer_t timer_syst;
static uint8_t cnt_timer = 0;	//счетчик таймера (увел при прерывании)


//инициализаци€ счетчика
void Timer_init(void) {
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);	// clk/1024
	TIMSK2 |= (1 << TOIE2);		//enable interrupt
	sei();
}

// „астота обновлени€ "cnt_timer":			20 ћ√ц / (1024 * 256) = 76 √ц,
// „астота обновлени€ "timer_global.cnt":	76 √ц/38 = 2 √ц (на практике - 1 секунда)
ISR(TIMER2_OVF_vect) {
	TIMSK2 &= ~(1 << TOIE2);			//disable interrupt

	if (timer_syst.ready == false) {	//если логика таймера окончена
		if (cnt_timer > 38) {			//если прошла 1 секунда
			timer_syst.ready = true;	//разрешение на выполнение логики
			cnt_timer = 0;				//обнуление таймера прерывани€
		} else {
			cnt_timer++;				//добавление таймера дл€ прерываний
		}
	}

	TIMSK2 |= (1 << TOIE2);				//enable interrupt
}

