#include "Sketch.h"

extern Adafruit_NeoPixel strip;
extern bool LED_status[SUM_LEDS];
extern bool LED_status_color[SUM_LEDS][3];
extern uint8_t mode;

static Command_t comm = {{0}, 0, 0};

void comm_read() {
	if (Serial.available() > 0) {
		char data = Serial.read();

		if (comm.cnt_write > SIZE_COMMANDS) {	//buffer overflow
			if (data == 10) {
				Serial.println("Comm: buffer overflow");
				comm_clean_buff();
			}
		} else if (data == 10) {				//finish read (enter)
			Serial.print("Comm: ");
			for (uint8_t i = 0; i < comm.cnt_write; i++) {
				Serial.print(comm.buff[i]);
			}
			Serial.println("");
			
			if (comm_logic_name() == false) {
				Serial.println("undefined command");
			}
			comm_clean_buff();
		} else {								//reading
			comm.buff[comm.cnt_write] = data;
			comm.cnt_write++;
		}
	}
}

void comm_clean_buff() {
	for (uint8_t i = 0; i < SIZE_COMMANDS; i++) {
		comm.buff[i] = 0;
	}
	comm.cnt_write = 0;
	comm.cnt_read = 0;
}

static bool check_name(char str[]) {
	comm.cnt_read = 0;
	if (strlen((str)) > comm.cnt_write) {
		return 0;
	} else {
		for (uint8_t i = 0; i < strlen(str); i++, comm.cnt_read++) {
			if (comm.buff[i] != str[i]) {
				return 0;
			}
		}
		if (comm.buff[comm.cnt_read] == 32) {	//space
			comm.cnt_read++;
			return 1;
		} else if (comm.cnt_read >= comm.cnt_write) {
			return 1;
		} else {
			return 0;
		}
	}
}

static uint16_t pow10(uint8_t x) {
	if (x == 0) {
		return 1;
	} else {
		uint16_t res = 1;
		for (uint8_t i = 0; i < x; i++) {
			res *= 10;
		}
		return res;
	}
}

static uint16_t read_number() {
	if (comm.cnt_write == comm.cnt_read) {
		return 256 * 256 - 1;
	}

	uint8_t start = comm.cnt_read;
	for (uint8_t i = comm.cnt_read; i < comm.cnt_write; i++) {
		if (comm.buff[comm.cnt_read] == 32) {
			break;
		}
		comm.cnt_read++;
	}

	uint16_t num = 0;
	for (uint8_t i = start; i < comm.cnt_read; i++) {
		num += pow10(comm.cnt_read - i - 1) * (comm.buff[i] - 48);
	}
	comm.cnt_read++;
	return num;
}

static bool comm_logic_name() {
	if (check_name("led") == true) {
		uint16_t num = read_number();
		uint8_t ww = (uint8_t)read_number();
		uint8_t nw = (uint8_t)read_number();
		uint8_t cw = (uint8_t)read_number();
		change_color(num, ww, nw, cw);
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("ww") == true) {
		uint16_t num = read_number();
		uint8_t ww = (uint8_t)read_number();
		LED_status_color[num][WW] = true;
		change_color(num, ww, r_mem_LED(num, NW), r_mem_LED(num, CW));
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("nw") == true) {			
		uint16_t num = read_number();
		uint8_t nw = (uint8_t)read_number();
		LED_status_color[num][NW] = true;
		change_color(num, r_mem_LED(num, WW), nw, r_mem_LED(num, CW));
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("cw") == true) {			
		uint16_t num = read_number();
		uint8_t cw = (uint8_t)read_number();
		LED_status_color[num][CW] = true;
		change_color(num, r_mem_LED(num, WW), r_mem_LED(num, NW), cw);
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("clear_on") == true) {	
		uint16_t num = read_number();
		change_color(num, 255, 255, 255);
		r_mem_LEDs_all();
	return 1;

	} else if (check_name("clear_off") == true) {	
		uint16_t num = read_number();
		change_color(num, 0, 0, 0);
		r_mem_LEDs_all();
	return 1;

	} else if (check_name("clear_on_all") == true) {	
		for(uint16_t i = 0; i < SUM_LEDS; i++) {
			change_color(i, 255, 255, 255);
		}
		r_mem_LEDs_all();
	return 1;

	} else if (check_name("clear_off_all") == true) {	
		for(uint16_t i = 0; i < SUM_LEDS; i++) {
			change_color(i, 0, 0, 0);
		}
		r_mem_LEDs_all();
	return 1;

	} else if (check_name("on_all") == true) {
		for (uint16_t i = 0; i < SUM_LEDS; i++) {
			LED_status_color[i][WW] = true;
			LED_status_color[i][NW] = true;
			LED_status_color[i][CW] = true;
		}
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("off_all") == true) {
		for (uint16_t i = 0; i < SUM_LEDS; i++) {
			LED_status_color[i][WW] = false;
			LED_status_color[i][NW] = false;
			LED_status_color[i][CW] = false;
		}
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("on_all_ww") == true) {	
		for (uint16_t i = 0; i < SUM_LEDS; i++) {
			LED_status_color[i][WW] = true;
		}
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("on_all_nw") == true) {
		for (uint16_t i = 0; i < SUM_LEDS; i++) {
			LED_status_color[i][NW] = true;
		}
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("on_all_cw") == true) {
		for (uint16_t i = 0; i < SUM_LEDS; i++) {
			LED_status_color[i][CW] = true;
		}
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("on") == true) {			
		uint16_t num = read_number();
		LED_status_color[num][WW] = true;
		LED_status_color[num][NW] = true;
		LED_status_color[num][CW] = true;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("off") == true) {				
		uint16_t num = read_number();
		LED_status_color[num][WW] = false;
		LED_status_color[num][NW] = false;
		LED_status_color[num][CW] = false;
		r_mem_LEDs_all();
		return 1;


	} else if (check_name("on_ww") == true) {	
		uint16_t num = read_number();
		LED_status_color[num][WW] = true;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("off_ww") == true) {	
		uint16_t num = read_number();
		LED_status_color[num][WW] = false;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("on_nw") == true) {	
		uint16_t num = read_number();
		LED_status_color[num][NW] = true;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("off_nw") == true) {	
		uint16_t num = read_number();
		LED_status_color[num][NW] = false;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("on_cw") == true) {	
		uint16_t num = read_number();
		LED_status_color[num][CW] = true;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("off_cw") == true) {	
		uint16_t num = read_number();
		LED_status_color[num][CW] = false;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("setting") == true) {	
		mode = MODE_SETTING;
		for (uint16_t i = 0; i < SUM_LEDS; i++) {
			LED_on(i);
		}
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("dinner") == true) {
		mode = MODE_DINNER;
		for (uint16_t i = 0; i < SUM_LEDS; i++) {
			LED_off(i);
		}
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("night_on") == true) {	
		mode = MODE_NIGHT_ON;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("night_main") == true) {	
		mode = MODE_NIGHT_MAIN;
		r_mem_LEDs_all();
		return 1;

	} else if (check_name("night_off") == true) {	
		mode = MODE_NIGHT_OFF;
		r_mem_LEDs_all();
		return 1;

	} else {
		return 0;
	}
}
