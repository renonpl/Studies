/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/
#define mainLED_TASK_PRIORITY   2

#define mainSERIAL_TASK_PRIORITY 1

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
#define wtime 10

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define EYE_wtime 100
#define EYE_DDR DDRD
#define EYE_PORT PORTD



/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/


static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/
int main(void)
{
     // Create task.
    xTaskHandle blink_handle;
    xTaskHandle serial_handle;

    xTaskCreate
        (
         vBlinkLed,
         "blink",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_TASK_PRIORITY,
         &blink_handle
        );

    xTaskCreate
        (
         vSerial,
         "serial",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &serial_handle
        );
    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

/**************************************************************************//**
 * \fn static vApplicationIdleHook(void)
 *
 * \brief
 ******************************************************************************/
void vApplicationIdleHook(void)
{

}

/******************************************************************************
 * Private function definitions.
 ******************************************************************************/

/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vBlinkLed(void* pvParameters)
{
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  uint8_t tab[100] = {};
  uint8_t i = 0;
  uint8_t j = 1;
  while (1) {
    if (BTN_PIN & _BV(BTN))
	tab[i++] = 0;
    else
	tab[i++] = 1;
    if(i == 100) 
	i = 0;
    if(tab[j++])
	LED_PORT &= ~_BV(LED);
    else
	LED_PORT |= _BV(LED);
    if(j == 100)
	j = 0;
    vTaskDelay(wtime / portTICK_PERIOD_MS);
  }
}


/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vSerial(void* pvParameters)
{
	UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
	EYE_DDR |= _BV(8)-1;
	EYE_PORT |= _BV(PD0);
	while(1){
		for(int i = 0; i < 7; i++){
           		 vTaskDelay(EYE_wtime / portTICK_PERIOD_MS);
	    		EYE_PORT <<=1;
	 	}
		for(int i = 0; i < 7; i++){
           		 vTaskDelay(EYE_wtime / portTICK_PERIOD_MS);
	    		EYE_PORT >>=1;
	 	}
	}
}
