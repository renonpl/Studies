#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

#define BUFFER_SIZE 16
#define wtime 200

int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}


uint8_t char_template[5] = {
	0x10,0x18,0x1C,0x1E,0x1F
};

void save_new_char(uint8_t index){
	LCD_WriteCommand(0x40 | (index << 3));
	for(int8_t i = 0; i < 8; i++)
		LCD_WriteData(char_template[index]);
}


FILE hd44780_file;

int main()
{
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;
  // program testowy
  
  for(uint8_t i = 0; i < 5; i++)
  	save_new_char(i);
  while(1){
    LCD_Clear();
    LCD_GoTo(0,0);
    printf("Loading");
    int8_t prog = 0;
    _delay_ms(wtime);
	  while(prog != 80) {
			LCD_GoTo(prog / 5, 1);	
			putchar(prog % 5);
			prog++;
			_delay_ms(wtime);
	  }
	  _delay_ms(10*wtime);
  }
}

