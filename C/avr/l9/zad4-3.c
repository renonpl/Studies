#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

#define BUZZ PB1
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#define MELODY_DURATION 102 

#define A	440
#define B	466
#define C	262
#define D	294
#define E	330
#define F	350
#define G	392
#define H	493
#define As	415
#define Des	277
#define Ges	370
#define Es	311
#define nute	2000

static const uint16_t music[] PROGMEM = {A,A,A,F,C,A,F,C,A,E,E,E,F,C,
				As,F,C,A,A,A,A,A,As,G,Ges,F,Ges,B,Es,D,Des,
				C,H,C,F,As,F,As,C,H,C,A};
static const uint8_t time[] PROGMEM  = {4,4,4,8,8,4,8,8,2,4,4,4,8,8,
				4,8,8,2,4,8,8,4,8,8,8,8,8,8,4,8,8,
				8,8,8,8,4,8,8,4,8,8,2};

void delay_us(int count)
{
	while(count > 0){
		_delay_us(10);
		count -= 10;
	}
}

 void tone(unsigned step,unsigned delay){
 	for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) {
 	     	BUZZ_PORT |= _BV(BUZZ);
	      	delay_us(step);
      		BUZZ_PORT &= ~_BV(BUZZ);
      		delay_us(step);
    	}
    	delay_us(delay);
 }
 

int main()
{
  BUZZ_DDR |= _BV(BUZZ);

  while (1) {
	for(int i = 0; i < sizeof(time); i++){
		uint16_t ton = (uint16_t)pgm_read_word(&music[i]);
		uint8_t tim = (uint8_t)pgm_read_byte(&time[i]);
		tone(500000/ton,nute/tim);
	}
	_delay_ms(2000);
  }
}
