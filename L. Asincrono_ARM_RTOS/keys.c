/*=============================================================================
 * Copyright (c) 2021, Franco Bucafusco <franco_bucafusco@yahoo.com.ar>
 * 					   Martin N. Menendez <mmenendez@fi.uba.ar>
 * All rights reserved.
 * License: Free
 * Date: 2021/10/03
 * Version: v1.0
 *===========================================================================*/

/*==================[ Inclusions ]============================================*/

#include "FreeRTOS.h"
#include "keys.h"

/*=====[ Definitions of private data types ]===================================*/


/*=====[Definition macros of private constants]==============================*/

/*=====[Prototypes (declarations) of private functions]======================*/


/*=====[Definitions of private global variables]=============================*/

/*=====[Definitions of public global variables]==============================*/
static keys_ButtonState_t state[4];   	// state of the key
static int time_down[4];								// timestamp of the last High to Low transition of the key
static int time_up[4];		    					// timestamp of the last Low to High transition of the key
static int time_diff[4];	   						// las time difference

const static int tecla[4] = { TEC0, TEC1, TEC2, TEC3};

/*=====[prototype of private functions]=================================*/


/*=====[Implementations of public functions]=================================*/

/**
   @brief Obtiene el tiempo de la ultima pulsacion de la tecla indicada.

   @param index
   @return TickType_t
 */
int keys_get_diff(int i)
{
	return time_diff[i];
}

/**
   @brief Borra el tiempo de la ultima pulsacion de la tecla indicada.

   @param index
 */
void keys_clear_diff(int i)
{
    time_diff[i] = KEYS_INVALID_TIME;

}

/**
   @brief Inicializa el driver

 */

void keys_init(int KEYS)
{

	for(int i=0;i < KEYS;i++)
	{
		state[i]     = STATE_BUTTON_UP;  			// Set initial state
		time_down[i] = KEYS_INVALID_TIME;
		time_up[i]   = KEYS_INVALID_TIME;
		time_diff[i] = KEYS_INVALID_TIME;
	}

}

// keys_ Update State Function
/**
   @brief Keys SM for polled operation

 */
uint32_t  keys_update(int i)
{
    uint32_t event = KEYS_EVENT_NONE ;
	
		int current_tick_count;

    switch(state[i])
    {
        case STATE_BUTTON_UP:
            /* CHECK TRANSITION CONDITIONS */
            if( !gpioRead( tecla[i] ) )
            {
                state[i] = STATE_BUTTON_FALLING;
            }
            break;

        case STATE_BUTTON_FALLING:
            /* ENTRY */

            /* CHECK TRANSITION CONDITIONS */
            if( !gpioRead( tecla[i] ) )
            {
                state[i] = STATE_BUTTON_DOWN;

                /* ACCION DEL EVENTO !*/
                event = KEYS_EVENT_KEY_DOWN;

                time_down[i] =  (TickType_t)xTaskGetTickCount();
            }
            else
            {
                state[i] = STATE_BUTTON_UP;
            }

            /* LEAVE */
            break;

        case STATE_BUTTON_DOWN:
            /* CHECK TRANSITION CONDITIONS */
            if( gpioRead( tecla[i] ) )
            {
                state[i] = STATE_BUTTON_RISING;
            }
            break;

        case STATE_BUTTON_RISING:
            /* ENTRY */

            /* CHECK TRANSITION CONDITIONS */

            if( gpioRead( tecla[i] ) )
            {
                state[i] = STATE_BUTTON_UP;

                /* ACCION DEL EVENTO ! */
                event = KEYS_EVENT_KEY_UP;

                current_tick_count =  (TickType_t)xTaskGetTickCount();

                /* calculo el tiempo de pulsacion */
                if( time_down[i] < current_tick_count )
                {
                    time_diff[i]  = current_tick_count - time_down[i];
                }
                else
                {
                    time_diff[i]  = current_tick_count - time_down[i] + 0xFFFFFFFF;
                }
            }
            else
            {
                state[i] = STATE_BUTTON_DOWN;
            }

            /* LEAVE */
            break;
    }

    return event;

}

/*=====[Implementations of private functions]================================*/

/*=====[Implementations of private functions]=================================*/

