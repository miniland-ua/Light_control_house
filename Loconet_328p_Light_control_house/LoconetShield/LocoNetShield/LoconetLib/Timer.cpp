#include "Sketch.h"


extern Timer_t timer_syst;
static uint8_t cnt_timer = 0;	//������� ������� (���� ��� ����������)


//������������� ��������
void Timer_init(void) {
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);	// clk/1024
	TIMSK2 |= (1 << TOIE2);		//enable interrupt
	sei();
}

// ������� ���������� "cnt_timer":			20 ��� / (1024 * 256) = 76 ��,
// ������� ���������� "timer_global.cnt":	76 ��/38 = 2 �� (�� �������� - 1 �������)
ISR(TIMER2_OVF_vect) {
	TIMSK2 &= ~(1 << TOIE2);			//disable interrupt

	if (timer_syst.ready == false) {	//���� ������ ������� ��������
		if (cnt_timer > 38) {			//���� ������ 1 �������
			timer_syst.ready = true;	//���������� �� ���������� ������
			cnt_timer = 0;				//��������� ������� ����������
		} else {
			cnt_timer++;				//���������� ������� ��� ����������
		}
	}

	TIMSK2 |= (1 << TOIE2);				//enable interrupt
}

