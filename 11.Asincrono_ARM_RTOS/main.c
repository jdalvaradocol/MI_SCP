
/* Librerias del FreeRTOS */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

/* Librerias del usuario */

#include "keys.h"
#include "board.h"
#include "stdint.h"

/* Prototipo de las funciones */
void tarea1 (void *taskParmPtr);
void tarea2 (void *taskParmPtr);

const static uint8_t leds[4] = { LED0, LED1, LED2, LED3};

int main ( void)
{
	
	/* 	board_Init();
			PORTF 4 bits como entrada.
			PORTB 4 bits como salida.
	*/
	
	board_init();
	keys_init(4);
	
	uint8_t i = 0;
	
	xTaskCreate(
	                	  tarea1, // Funcion de la tarea a ejecutar
    ( const char * )"tarea1", // Nombre de la tarea como String amigable para el usuario
  configMINIMAL_STACK_SIZE*2, // Cantidad de stack de la tarea
                           i, // Parametros de tarea
          tskIDLE_PRIORITY+1, // Prioridad de la tarea
                           0  // Puntero a la tarea creada en el sistema	
	);

	i++;	
		
 	xTaskCreate(
	                	 tarea2, // Funcion de la tarea a ejecutar
    ( const char * )"tarea2", // Nombre de la tarea como String amigable para el usuario
  configMINIMAL_STACK_SIZE*2, // Cantidad de stack de la tarea
                           i, // Parametros de tarea
          tskIDLE_PRIORITY+1, // Prioridad de la tarea
                           0  // Puntero a la tarea creada en el sistema	
	);

		 
	vTaskStartScheduler();	 
	
}
 

void tarea1 (void *taskParmPtr)
{
	uint8_t index = (uint8_t)taskParmPtr;
	
	uint32_t estado;
	int time = 2000;
	
	while(TRUE)
	{
		estado = keys_update(index);
		
		if(estado == KEYS_EVENT_KEY_UP)
		{
			gpioWrite(leds[index], ON);
			vTaskDelay(pdMS_TO_TICKS(time));
			gpioWrite(leds[index], OFF);
			vTaskDelay(pdMS_TO_TICKS(time));
		}	
	}
	
}

void tarea2 (void *taskParmPtr)
{
	uint8_t index = (uint8_t)taskParmPtr;
	
	uint32_t estado;
	int time = 2000;
	
	while(TRUE)
	{
		estado = keys_update(index);
		
		if(estado == KEYS_EVENT_KEY_UP)
		{
			gpioWrite(leds[index], ON);
			vTaskDelay(pdMS_TO_TICKS(time));
			gpioWrite(leds[index], OFF);
			vTaskDelay(pdMS_TO_TICKS(time));
		}	
	}
	
}

 
 
 
