#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include<util/delay.h>
#include "i2c.h"

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
  char buff[100]; 
const uint8_t eeprom_addr = 0xa0;

void write(uint16_t addr, int8_t value);
int8_t read(uint16_t addr);
void write_long(char* hex);
void read_long(uint16_t addr, int8_t lenght);


int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj I2C
  i2cInit();
  // program testowy
 // uint16_t addr = 0;

  uint8_t fun;
  uint8_t val = 0;
  int16_t addr = 0;
  #define i2cCheck(code, msg) \
    if ((TWSR & 0xf8) != (code)) { \
      printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      i2cReset(); \
      continue; \
    }
  while(1)
	{
        printf("Wybierz polecenie:\r\n");
	printf("0-read\r\n");
        printf("1-write\r\n");
        printf("2-long read\r\n");
        printf("3-long write\r\n");
	scanf("%"PRIu8, &fun);
        if (fun == 0)
        {
            printf("Odczyt,podaj adres: \r\n");
            scanf("%"PRId16, &addr);
            uint8_t data = read(addr);
            printf("Wartość: %"PRIu8" adres: %"PRId16"\r\n", data, addr);
        }
        else if(fun == 1)
        {  
            printf("Zapis,podaj adres: \r\n");
            scanf("%"PRId16, &addr);
            printf("Podaj wartosc: \r\n");
            scanf("%"PRIu8, &val);
            write(addr, val);
            printf("Wartość: %"PRIu8" adres: %"PRId16"\r\n", val, addr);
        }
        else if(fun==2){
            printf("Długi odczyt,podaj adres: \r\n");
            scanf("%"PRId16, &addr);
            printf("Podaj ilosc: \r\n");
            scanf("%"PRIu8, &val);
            read_long(addr, val);
        }
        if (fun == 3)
        {
            while(1){
		    printf("Długi zapis,podaj ihexa: \r\n");
		    scanf("%s", buff);
		    if(buff[7] == '1'){
		    	printf("Koniec rekordu \r\n");
		    	break;
		    }
		    write_long(buff);
		    printf("Wartość: %s \r\n", buff);
            }
        }
    }

}


void write(uint16_t addr, int8_t value){
	do{
	i2cStart();
	i2cCheck(0x08, "I2C start");
	i2cSend(eeprom_addr | 0x00);
	i2cCheck(0x18, "I2C EEPROM write request")
    	i2cSend(addr);
	i2cCheck(0x28, "I2C EEPROM set address");
	
	i2cSend(value);
   	i2cCheck(0x28, "I2C EEPROM write value")
	i2cStop();   
    	i2cCheck(0xf8, "I2C stop writing")
	}while(0);
	
}

int8_t read(uint16_t addr){
	uint8_t data = 0;
	do{
	i2cStart();
	i2cCheck(0x08, "I2C start");
	i2cSend(eeprom_addr | 0x00);
   	i2cCheck(0x18, "I2C EEPROM write request")
    	i2cSend(addr);
    	i2cCheck(0x28, "I2C EEPROM set address")
	
	i2cStart();
    	i2cCheck(0x10, "I2C second start")
    	i2cSend(eeprom_addr | 0x01);
    	i2cCheck(0x40, "I2C EEPROM read request")
    	data = i2cReadNoAck();
    	i2cCheck(0x58, "I2C EEPROM read")
    	i2cStop();
    	i2cCheck(0xf8, "I2C stop")
    	}while(0);
    	return data;
}

void read_long(uint16_t addr, int8_t length){
	uint8_t c[length];
	uint8_t type = 0;
	if(length == 0) type = 1;
	uint8_t checksum = addr + length + type;
	do{
	i2cStart();
	i2cCheck(0x08, "I2C start");
	i2cSend(eeprom_addr | 0x00);
   	i2cCheck(0x18, "I2C EEPROM write request");
    	i2cSend(addr);
    	i2cCheck(0x28, "I2C EEPROM set address");
	
	i2cStart();
    	i2cCheck(0x10, "I2C second start")
    	i2cSend(eeprom_addr | 0x01);
    	i2cCheck(0x40, "I2C EEPROM read request")
    	for(uint8_t i = 0; i < length-1;i++){
    		c[i] = i2cReadAck();
    		checksum += c[i];
    		i2cCheck(0x50, "I2C EEPROM read")
    	}
    	c[length-1] = i2cReadNoAck();
    	i2cCheck(0x58, "I2C EEPROM read");
    	checksum += c[length-1];
    	checksum = 256 - (uint16_t)checksum;
    	i2cStop();
    	i2cCheck(0xf8, "I2C stop")
    	_delay_ms(10);
    	printf(":%02X" "%04X" "%02X",length,addr,type);
    	for(uint8_t i = 0; i < length;i++){
    		printf("%02X",c[i]);;
    	}
  
    	printf("%X",checksum);;
    	printf("\r\n");    	    	
    	}while(0);
    	return;
}

uint8_t read_hex(char a, char b){
	uint16_t res = 0;
	if (a >= '0' && a <= '9') res = a - '0';
        else if (a >= 'a' && a <='f') res = a - 'a' + 10;
        else if (a >= 'A' && a <='F') res = a - 'A' + 10;
        res = (res << 4);
      	if (b >= '0' && b <= '9') res = res + b - '0';
        else if (b >= 'a' && b <='f') res = res + b - 'a' + 10;
        else if (b >= 'A' && b <='F') res = res + b - 'A' + 10;
        return res;     
}


void write_long(char* hex){
	uint8_t length = read_hex(hex[0],hex[1]);
	if(length > 4){
		printf("Za dużo bajtów \r\n");
		return;
	}
	printf(" lenght = %"PRIu8,length);
	uint16_t addr = (read_hex(hex[2],hex[3]) << 8) + read_hex(hex[4],hex[5]);
	uint8_t type = read_hex(hex[6],hex[7]);
	uint8_t checksum = type +addr + length;
	for(uint8_t i = 0; i < length; i++)
		checksum += read_hex(hex[8+2*i],hex[9+2*i]);
	uint8_t check = read_hex(hex[8+2*length],hex[8+2*length+1]);
	if((checksum + check) & 0xFF != 0){
		printf("Zły checksum \r\n");
		return;
	}
	
	printf(" addr= %"PRIu16,addr);
	do{
	i2cStart();
	i2cCheck(0x08, "I2C start");
	i2cSend(eeprom_addr | 0x00);
	i2cCheck(0x18, "I2C EEPROM write request")
    	i2cSend(addr);
	i2cCheck(0x28, "I2C EEPROM set address");
	for(uint8_t i = 0; i < length; i++)
	{
		i2cSend(read_hex(hex[8+2*i],hex[9+2*i]));
		i2cCheck(0x28, "I2C EEPROM write value")
	}
	i2cStop();   
    	i2cCheck(0xf8, "I2C stop writing")
	}while(0);
}

