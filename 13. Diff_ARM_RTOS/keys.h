/*=============================================================================
 * Copyright (c) 2021, Franco Bucafusco <franco_bucafusco@yahoo.com.ar>
 * 					   Martin N. Menendez <mmenendez@fi.uba.ar>
 * All rights reserved.
 * License: Free
 * Date: 2021/10/03
 * Version: v1.0
 *===========================================================================*/

/*==================[ Inclusions ]============================================*/
#ifndef keys_H_
#define keys_H_

#include "FreeRTOS.h"
#include "stdint.h"

/* public macros ================================================================= */
#define KEYS_INVALID_TIME   -1
#define DEBOUNCE_TIME       40
#define KEYS_EVENT_NONE     0
#define KEYS_EVENT_KEY_DOWN 1
#define KEYS_EVENT_KEY_UP   2

#define 	TEC0       0x01
#define 	TEC1       0x02
#define 	TEC2       0x04
#define 	TEC3       0x08

#define 	LED0       0x01
#define 	LED1       0x02
#define 	LED2       0x04
#define 	LED3       0x08


/* types ================================================================= */

typedef enum {
	STATE_OFF,
	STATE_ON
} led_state_t;

typedef enum
{
    STATE_BUTTON_UP,
    STATE_BUTTON_DOWN,
    STATE_BUTTON_FALLING,
    STATE_BUTTON_RISING
} keys_ButtonState_t;



/* methods ================================================================= */

int keys_get_diff(int i);
void keys_clear_diff(int i);
void keys_init(int KEYS);
uint32_t  keys_update(int i);

#endif /* PDM_ANTIRREBOTE_MEF_INC_DEBOUNCE_H_ */
