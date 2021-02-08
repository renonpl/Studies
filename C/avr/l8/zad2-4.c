/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
#define wtime 100
/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vUartRead(void* pvParameters);
static void vBlinkLed(void* pvParameters);


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
 
QueueHandle_t queue;
 
int main(void)
{
    // Create task.
    xTaskHandle uart_handle;
    xTaskHandle blink_handle;
    
    queue = xQueueCreate(100, sizeof(int16_t));

    if(queue != NULL){
    		xTaskCreate
		(
		 vUartRead,
		 "uart",
		 configMINIMAL_STACK_SIZE,
		 NULL,
		 1,
		 &uart_handle
		);
    
    
	    xTaskCreate
		(
		 vBlinkLed,
		 "blink",
		 configMINIMAL_STACK_SIZE,
		 NULL,
		 2,
		 &blink_handle
		);
	}
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
 * \fn static void vUartRead(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vUartRead(void* pvParameters)
{
    uart_init();
    stdin = stdout = stderr = &uart_file;
    int16_t in;
    while(1)
    {
      printf("Wczytaj: \r\n");
      scanf("%"PRId16, &in);
      printf("Wczytano: %"PRId16"\r\n", in);
      xQueueSendToBack(queue, &in, 0 );
    }

}


/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vBlinkLed(void* pvParameters)
{
  LED_DDR |= _BV(LED);
  int16_t time;    
  while(1){
	  if(xQueueReceive(queue, &time, pdMS_TO_TICKS( 100 ) ) == pdTRUE){
		LED_PORT |= _BV(LED);
		vTaskDelay(time / portTICK_PERIOD_MS);
        	LED_PORT &= ~_BV(LED);
        	vTaskDelay(wtime / portTICK_PERIOD_MS);
		}
	}
}
