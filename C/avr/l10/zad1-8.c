#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

volatile int16_t adc_value;

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

/* Calculating the PWM frequency for fast PWM mode is easy. Take the CPU clock frequency,
divide it by a prescaler value if applicable, and then divide by the number of steps per cycle.
For example, I’ve set the prescaler at 8, using an 8-bit timer with 256 steps, and a 1 MHz CPU
clock; therefore, the fast PWM frequency is 1,000,000 Hz / 8 / 256 = 488 Hz. */
//Arduino nano 16MHZ
// 16 000 000 / 8 / 2000 = 1000Hz

static int top = 2000;
void timer1_init()
{
  // ustaw tryb licznika
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = 10  -- prescaler 8
  ICR1 = top;
  TCCR1A =  _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS11);
  // ustaw pin OC1A (PB1) jako wyjście
 DDRB |= _BV(PB1);
}



// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

int16_t adc_read() 
{
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  return ADC; // zwroc wartosc ADC
}

FILE uart_file;
int main() 
{

  uart_init();
  timer1_init();
  adc_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;


  DDRB |= _BV(PB1);
  OCR1A = 0;

  while(1) 
  {
    adc_value = adc_read();
    OCR1A =  adc_value*2;
  //  printf("Odczytano: %"PRIu16"\r\n", adc_value);
    printf("Value: %"PRIu16"\r\n", OCR1A);
  }
}
