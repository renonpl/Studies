#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define BUFFER_SIZE 16

  char buffer[BUFFER_SIZE] = {};
  int8_t c;
  uint8_t len = 0;


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


int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}

FILE hd44780_file;
FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  //fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_NOBLINK);
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, uart_receive, _FDEV_SETUP_RW);
  //stdin = &uart_file;
  stdin = stdout = stderr = &hd44780_file;
  LCD_GoTo(0,1);
  while(1) {
    c = getchar();
    if(c == 0xD){
    	LCD_Clear();
    	LCD_GoTo(0,0);
    	for(uint8_t i = 0; i < BUFFER_SIZE; i++){
    		if(buffer[i] != 0){
    			putchar(buffer[i]);
    		}
    		buffer[i] = 0;
    	}
    	len = 0;
    	LCD_GoTo(0,1);
    	getchar();
    }
    else{
    	buffer[len] = c;
    	//LCD_GoTo(len,1);
    	putchar(c);
    	len++;
    	if(len == BUFFER_SIZE){
    		len = 0;
    		LCD_GoTo(len,1);
    	}
    }
  }
}

