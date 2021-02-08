#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include<util/delay.h>

#define LA PB1
#define OE PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

int numbers[10] = {0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0xFD,0x07,0x7F,0xEF};


// inicjalizacja SPI
void spi_init()
{
    // ustaw piny MOSI, SCK jako wyjścia
    DDRB |= _BV(DDB3) | _BV(DDB5);	
    DDRB |= _BV(LA) | _BV(OE);
    // włącz SPI w trybie master z zegarem 250 kHz
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

// transfer jednego bajtu
uint8_t spi_transfer(uint8_t data)
{
    // rozpocznij transmisję
    SPDR = data;
    // czekaj na ukończenie transmisji
    while (!(SPSR & _BV(SPIF)));
    // wyczyść flagę przerwania
    SPSR |= _BV(SPIF);
    // zwróć otrzymane dane
    return SPDR;
}

int main()
{
  LED_DDR |= _BV(OE) | _BV(LA);
  // zainicjalizuj SPI
  spi_init();
  // program testujący połączenie
  while(1) {
  	for(uint8_t v = 0; v < 10; v++){
		LED_PORT |= _BV(OE);
		spi_transfer(numbers[v]);
		LED_PORT |= _BV(LA);
		LED_PORT &= ~_BV(LA);
		LED_PORT &= ~_BV(OE);				
		_delay_ms(1000);
	}
  }
}

