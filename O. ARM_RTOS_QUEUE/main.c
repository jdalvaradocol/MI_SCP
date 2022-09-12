
/* Librerias del FreeRTOS */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"

/* Librerias del usuario */

#include "keys.h"
#include "board.h"
#include "stdint.h"

/* Prototipo de las funciones */
void tarea_leds (void *taskParmPtr);
void tarea_teclas (void *taskParmPtr);

const static uint8_t leds[4] = { LED0, LED1, LED2, LED3};

#define TAREAS 	4

QueueHandle_t xdiffQueue[TAREAS];


int main ( void)
{
	
	/* 	board_Init();
			PORTF 4 bits como entrada.
			PORTB 4 bits como salida.
	*/
	
	board_init();
	keys_init(4);
	
	int i;

	for(i = 0;i < TAREAS;i++)
	{
		xTaskCreate(
				  				  tarea_leds, // Funcion de la tarea a ejecutar
			  ( const char * )"leds", // Nombre de la tarea como String amigable para el usuario
		  configMINIMAL_STACK_SIZE, // Cantidad de stack de la tarea
											(void*)i, // Parametros de tarea
						tskIDLE_PRIORITY+1, // Prioridad de la tarea
														 0  // Puntero a la tarea creada en el sistema	
		);
		
		xTaskCreate(
								  tarea_teclas, // Funcion de la tarea a ejecutar
			( const char * )"teclas", // Nombre de la tarea como String amigable para el usuario
		  configMINIMAL_STACK_SIZE, // Cantidad de stack de la tarea
														 i, // Parametros de tarea
						tskIDLE_PRIORITY+1, // Prioridad de la tarea
														 0  // Puntero a la tarea creada en el sistema	
		);	 
			 
		xdiffQueue[i] = xQueueCreate( 10, sizeof( int ) );		
			 
	}
			 
	vTaskStartScheduler();	 
	
}
 
void tarea_leds (void *taskParmPtr)
{
	uint8_t index = (uint8_t)taskParmPtr;
	
 int time = 0;

	while(TRUE)
	{
		
		xQueueReceive( xdiffQueue[index], &time, portMAX_DELAY );
    
		gpioWrite(leds[index], ON);
		vTaskDelay(pdMS_TO_TICKS(time));
		gpioWrite(leds[index], OFF);
		vTaskDelay(pdMS_TO_TICKS(100));
		keys_clear_diff(index);
	}	
}
	
void tarea_teclas (void *taskParmPtr)
{
	uint8_t index = (uint8_t)taskParmPtr;
	
	int time = 0;
	
	while(TRUE)
	{
		keys_update(index);
		time = keys_get_diff(index);
		
		if(time != KEYS_INVALID_TIME)
		{
			xQueueSend( xdiffQueue[index], (void*) &time, 0 );
			keys_clear_diff(index);
		}	
	}
	
}


