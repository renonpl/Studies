#include <avr/io.h>
#include <util/delay.h>

#define wtime 100
#define LED_DDR DDRD
#define LED_PORT PORTD

int main() {
	UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
	LED_DDR |= _BV(8)-1;
	LED_PORT |= _BV(PD0);
	while(1){
		for(int i = 0; i < 7; i++){
	    		_delay_ms(wtime);
	    		LED_PORT <<=1;
	 	}
		for(int i = 0; i < 7; i++){
	    		_delay_ms(wtime);
	    		LED_PORT >>=1;
	 	}
	}
}

