#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define SIZE 20


volatile char buffer_in[SIZE];
volatile char buffer_out[SIZE];
volatile int8_t in_start, in_end, out_start, out_end, in_count, out_count;

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

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  cli();
  if(out_count == SIZE){
  	sei();	
  	sleep_mode();	
  }
  cli();
  buffer_out[out_end++] = data;
  out_count++;
  if(out_end == SIZE)out_end = 0;
  sei();
  UCSR0B |= _BV(UDRIE0);
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  while (in_count == 0);
  cli();
  in_count--;
  char c = buffer_in[in_start++];
  if(in_start == SIZE)in_start = 0;
  sei();
  return c;
}

ISR(USART_RX_vect)
{
	char c = UDR0;
	buffer_in[in_end++] = c;
	in_count++;
	if(in_end == SIZE) in_end = 0;
}


ISR(USART_UDRE_vect)
{
	if(out_count != 0){
	char c = buffer_out[out_start++];
	if(out_start == SIZE) out_start = 0;
	out_count--;
	UDR0 = c;	
	}
	else{
	 UCSR0B &= ~_BV(UDRIE0);
	 //UCSR0B |= _BV(TXCIE0);
	}
}
/*
ISR(USART_TX_vect)
{
	UCSR0B &= ~_BV(TXCIE0);
}*/

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  sei();
  
  set_sleep_mode(SLEEP_MODE_IDLE);
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy
  printf("Hello world!\r\n");
  while(1) {
    int16_t a = 1;
    scanf("%"SCNd16, &a);
    printf("Odczytano: %"PRId16"\r\n", a);
  }
}


