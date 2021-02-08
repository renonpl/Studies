#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
  UCSR0B |= _BV(RXCIE0);

}


ISR(USART_RX_vect)
{
	UDR0 = UDR0;
}



int main()
{
  // zainicjalizuj UART
  uart_init();
  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();
  while(1) {
     	    sleep_mode();
  }
}


