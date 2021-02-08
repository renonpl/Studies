#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
#define wtime 10

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

int main() {
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  uint8_t tab[100] = {};
  uint8_t i = 0;
  uint8_t j = 1;
  while (1) {
    if (BTN_PIN & _BV(BTN))
	tab[i++] = 0;
    else
	tab[i++] = 1;
    if(i == 100) 
	i = 0;
    if(tab[j++])
	LED_PORT &= ~_BV(LED);
    else
	LED_PORT |= _BV(LED);
    if(j == 100)
	j = 0;
    _delay_ms(wtime);
  }
}
