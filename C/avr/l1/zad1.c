#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

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

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy
  //printf("Hello world!\r\n");
  while(1) {
    int8_t a = 1;
	int8_t b = 2;
    scanf("%"SCNd8, &a);
	printf("Odczytano: %"PRId8"\r\n", a);
    scanf("%"SCNd8, &b);
    printf("Odczytano: %"PRId8"\r\n", b);
    printf("Dodano: %"PRId8"\r\n", a+b);
    printf("Odjeto: %"PRId8"\r\n", a-b);
    printf("Pomnozono: %"PRId8"\r\n", a*b);
    printf("Podzielono: %"PRId8"\r\n", a/b);
    int16_t a1 = 1;
	int16_t b1 = 2;
    scanf("%"SCNd16, &a1);
	    printf("Odczytano: %"PRId16"\r\n", a1);
    scanf("%"SCNd16, &b1);
    printf("Odczytano: %"PRId16"\r\n", b1);
    printf("Dodano: %"PRId16"\r\n", a1+b1);
    printf("Odjeto: %"PRId16"\r\n", a1-b1);
    printf("Pomnozono: %"PRId16"\r\n", a1*b1);
    printf("Podzielono: %"PRId16"\r\n", a1/b1);
    int32_t a2 = 1;
	int32_t b2 = 2;
    scanf("%"SCNd32, &a2);
	    printf("Odczytano: %"PRId32"\r\n", a2);
    scanf("%"SCNd32, &b2);
    printf("Odczytano: %"PRId32"\r\n", b2);
    printf("Dodano: %"PRId32"\r\n", a2+b2);
    printf("Odjeto: %"PRId32"\r\n", a2-b2);
    printf("Pomnozono: %"PRId32"\r\n", a2*b2);
    printf("Podzielono: %"PRId32"\r\n", a2/b2);
    int64_t a3 = 1;
	int64_t b3 = 2;
    scanf("%"SCNd32, &a3);
	    printf("Odczytano: %"PRId32"\r\n", a3);
    scanf("%"SCNd32, &b3);
    printf("Odczytano: %"PRId32"\r\n", b3);
    printf("Dodano: %"PRId32"\r\n", a3+b3);
    printf("Odjeto: %"PRId32"\r\n", a3-b3);
    printf("Pomnozono: %"PRId32"\r\n", a3*b3);
    printf("Podzielono: %"PRId32"\r\n", a3/b3);
	 float a4 = 1.0;
	float b4 = 2.0;
    scanf("%f", &a4);
	printf("Odczytano: %f\r\n", a4);
    scanf("%f", &b4);
    printf("Odczytano: %f\r\n", b4);
    printf("Dodano: %f\r\n", a4+b4);
    printf("Odjeto: %f\r\n", a4-b4);
    printf("Pomnozono: %f\r\n", a4*b4);
    printf("Podzielono: %f\r\n", a4/b4);
  }
}


