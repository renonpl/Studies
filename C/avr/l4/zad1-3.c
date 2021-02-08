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

void timer1_init()
{
  // ustaw tryb licznika
  // WGM1  = 0000 -- normal
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
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
  timer1_init();
  while(1) {
    uint16_t t1, t2;
     int8_t a;
     int8_t b;
    volatile int8_t res;
    scanf("%"SCNd8, &a);
    printf("Odczytano: %"PRId8"\r\n", a);
    scanf("%"SCNd8, &b);
    printf("Odczytano: %"PRId8"\r\n", b);
    t1 = TCNT1; // wartość licznika przed czekaniem
    res = a + b;
    t2 = TCNT1;
    printf("Dodano: %"PRId8"\r\n", res);
    printf("Zmierzony czas dodawania 8t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res = a - b;
    t2 = TCNT1;
    printf("Odjeto: %"PRId8"\r\n", res);
    printf("Zmierzony czas odejmowania 8t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res = a * b;
    t2 = TCNT1;
    printf("Pomnozono: %"PRId8"\r\n", res);
    printf("Zmierzony czas mnozenia 8t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res = a/b;
    t2 = TCNT1;
    printf("Podzielono: %"PRId8"\r\n", res);
    printf("Zmierzony czas dzielenia 8t: %"PRIu16" cykli\r\n", t2 - t1);
    
     int16_t a1 ;
     int16_t b1 ;
    volatile int16_t res1;
    scanf("%"SCNd16, &a1);
    printf("Odczytano: %"PRId16"\r\n", a1);
    scanf("%"SCNd16, &b1);
    printf("Odczytano: %"PRId16"\r\n", b1);
    
    t1 = TCNT1;
    res1 = a1 + b1;
    t2 = TCNT1;
    printf("Dodano: %"PRId16"\r\n", res1);
    printf("Zmierzony czas dodawania 16t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res1 = a1 - b1;
    t2 = TCNT1;
    printf("Odjeto: %"PRId16"\r\n", res1);
    printf("Zmierzony czas odejmowania 16t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res1 = a1 * b1;
    t2 = TCNT1;
    printf("Pomnozono: %"PRId16"\r\n", res1);
    printf("Zmierzony czas mnozenia 16t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res1 = a1 / b1;
    t2 = TCNT1;
    printf("Podzielono: %"PRId16"\r\n", res1);
    printf("Zmierzony czas dzielenia 16t: %"PRIu16" cykli\r\n", t2 - t1);
    
     int32_t a2;
     int32_t b2;
    volatile int32_t res2;
    scanf("%"SCNd32, &a2);
    printf("Odczytano: %"PRId32"\r\n", a2);
    scanf("%"SCNd32, &b2);
    printf("Odczytano: %"PRId32"\r\n", b2);
    t1 = TCNT1;
    res2 = a2 + b2;
    t2 = TCNT1;
    printf("Dodano: %"PRId32"\r\n", res2);
    printf("Zmierzony czas dodawania 32t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res2 = a2 - b2;
    t2 = TCNT1;
    printf("Odjeto: %"PRId32"\r\n", res2);
    printf("Zmierzony czas odejmowania 32t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res2 = a2 * b2;
    t2 = TCNT1;
    printf("Pomnozono: %"PRId32"\r\n", res2);
    printf("Zmierzony czas mnozenia 32t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res2 = a2 / b2;
    t2 = TCNT1;
    printf("Podzielono: %"PRId32"\r\n", res2);
    printf("Zmierzony czas dzielenia 32t: %"PRIu16" cykli\r\n", t2 - t1);
    
    
    int64_t a3;
    int64_t b3;
    volatile int64_t res3;
    scanf("%"SCNd32, &a3);
    printf("Odczytano: %"PRId32"\r\n", a3);
    scanf("%"SCNd32, &b3);
    printf("Odczytano: %"PRId32"\r\n", b3);
    t1 = TCNT1;
    res3 = a3 + b3;
    t2 = TCNT1;
    printf("Dodano: %"PRId32"\r\n", res3);
    printf("Zmierzony czas dodawania 64t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res3 = a3 - b3;
    t2 = TCNT1;
    printf("Odjeto: %"PRId32"\r\n", res3);
    printf("Zmierzony czas odejmowania 64t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res3 = a3 * b3;
    t2 = TCNT1;
    printf("Pomnozono: %"PRId32"\r\n", res3);
    printf("Zmierzony czas mnozenia 64t: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res3 = a3 / b3;
    t2 = TCNT1;
    printf("Podzielono: %"PRId32"\r\n", res3);
    printf("Zmierzony czas dzielenia 64t: %"PRIu16" cykli\r\n", t2 - t1);

     float a4;
     float b4;
    volatile float res4;
    scanf("%f", &a4);
    printf("Odczytano: %f\r\n", a4);
    scanf("%f", &b4);
    printf("Odczytano: %f\r\n", b4);
    t1 = TCNT1;
    res4 = a4 + b4;
    t2 = TCNT1;
    printf("Dodano: %f\r\n", res4);
    printf("Zmierzony czas dodawania float: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res4 = a4- b4;
    t2 = TCNT1;
    printf("Odjeto: %f\r\n", res4);
    printf("Zmierzony czas odejmowania float: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res4 = a4 * b4;
    t2 = TCNT1;
    printf("Pomnozono: %f\r\n", res4);
    printf("Zmierzony czas mnozenia float: %"PRIu16" cykli\r\n", t2 - t1);
    t1 = TCNT1;
    res4 = a4 / b4;
    t2 = TCNT1;
    printf("Podzielono: %f\r\n", res4);
    printf("Zmierzony czas dzielenia float: %"PRIu16" cykli\r\n", t2 - t1);

  }
}


