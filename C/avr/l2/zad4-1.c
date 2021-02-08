#include <avr/io.h>
#include <util/delay.h>

#define wtime 10
#define LED_DDR DDRD
#define LED_PORT PORTD

#define TRAN_DDR DDRC
#define TRAN_PORT PORTC

int main() {
	UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
	LED_DDR |= _BV(8)-1;
	TRAN_DDR = 3;
	TRAN_PORT = 0;
	LED_PORT = 0;
	int numbers[10] = {0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0xFD,0x07,0x7F,0xEF};

	while(1)
	{
		for(int j = 0; j < 60; j++)
		{
			for(int i = 0; i < 1000/(2*wtime); i++){
			    	_delay_ms(wtime);
			    	LED_PORT = ~numbers[j%10];
				TRAN_PORT = 1;
				_delay_ms(wtime);
				LED_PORT = ~numbers[j/10];
				TRAN_PORT = 2;
			}
		}
	}
}

