#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <modem.h>

#include "lcd.h"

void on_receive_msg(const char *msg, uint8_t size) {
	lcd_gotoxy(0, 1);
	lcd_puts("                ");
	lcd_gotoxy(0, 1);
	char message[size + 1];
	for(uint8_t i = 0; i < size; i++)
		message[i] = msg[i];
	message[size] = 0;
	lcd_puts(message);

	modem_snd_async(message, size);
}

int main(void) {

//	char s[16];

//	char* p_tester;
//	p_tester = (char*) malloc(0 * sizeof(char));
//	free(p_tester);
//	uint16_t i;

//	char t[16];
//	uint8_t p = 0b00000000;
//	p ^= 0b00000000;

	sei();

	lcd_init(LCD_DISP_ON_CURSOR_BLINK);
	lcd_clrscr();

	lcd_puts("R:");

	modem_lsn(on_receive_msg);

	char information[16];

	while (1) {

//		lcd_gotoxy(0, 1);
//		lcd_puts(s);

//		sprintf(t, "%X", p);
//		lcd_gotoxy(0, 1);
//		lcd_puts(t);

//		free(p_tester);
//		p_tester = (char*) malloc(16 * sizeof(char));
//		sprintf(s, "%u", p_tester);
//		lcd_gotoxy(0, 1);
//		lcd_puts(s);
//		modem_snd_async("U", 1);

		const char *bit_rep[16] = {
		    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
		    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
		    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
		    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
		};
		sprintf(information, "%s%s = %03u", bit_rep[info() >> 4], bit_rep[info() & 0x0F],info());
		lcd_gotoxy(2, 0);
		lcd_puts(information);

		_delay_ms(50);
		PORTD &= ~(1 << 7);
		_delay_ms(50);
		PORTD |= (1 << 7);
	}
}
