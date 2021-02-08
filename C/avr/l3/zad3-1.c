#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>


#define LED PD3
#define LED_DDR DDRD
#define LED_PORT PORTD

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}


void delay_us(int count)
{

	while(count){
		_delay_us(1);
		count--;
	}
}
 

int main()
{
	
   LED_DDR |= _BV(LED);
   LED_PORT |= _BV(LED);
  // zainicjalizuj ADC
  adc_init();
  // mierz napięcie
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    LED_PORT |= _BV(LED);
    delay_us(_BV(ADC/128));
    LED_PORT &= ~_BV(LED);
    delay_us(100);

  }
}

