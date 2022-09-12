




#include"board.h"
#include"tm4c123gh6pm.h"

// PORTF 
// BIT4 - BIT3 - BIT2 - BIT1 - BIT0
//   IN -  OUT -  OUT -  OUT -   IN

#define ENTRADA	GPIO_PORTF_DATA_R 
#define  SALIDA  GPIO_PORTF_DATA_R

#define ESTADO1	0
#define ESTADO2	1
#define ESTADO3	2
#define ESTADO4	3

#define LED_E1	0x02
#define LED_E2	0x04
#define LED_E3	0x08
#define LED_E4	0x0A

void delay_ms(int delay);
int  lectura(void);

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06

// Fosc = 16MHz T = (1/Fosc) * 4 = 250ns 
// 1ms / 250ns = 4000

void delay_ms(int delay)
{
	volatile int i , j;
	
		for( i = 0;i < delay;i++)
		{
			for( j = 0;j < 3200;j++)
			{}
		}
}

int lectura(void)
{
	int dato_salida;
	
	/* 	Opcion 1 de lectura
			Se realiza la lectura en dos variables 
			Bit0 y Bit4, se reliza el desplazamiento   
			de Bit4 en 3 posiciones a la >> derecha.
			Por ultimo se dumar y se realiza una negacion 
			de la salida.
	*/

	/*

	int Bit0;
	int Bit4;
	
	Bit0 = Entrada & 0x01;
	Bit4 = (Entrada & 0x10) >> 3;
	
	dato_salida = (~(Bit4 + Bit0))&0x03;
	
	*/
	
		/* 	Opcion 2 de lectura
				Se realiza la lectura de la entrada 
				y se evalua cada caso, el resultado de almacena 
				en una variable.	
	*/
	
	dato_salida = ENTRADA&0x11;
	
	if(dato_salida == 0)
	{
		dato_salida = 3;
	}
	else if (dato_salida == 1)
	{
		dato_salida = 2;	
	}
	else if (dato_salida == 16)
	{
		dato_salida = 1;	
	}
	else if (dato_salida == 17)
	{
		dato_salida = 0;	
	}
	
	return dato_salida;
}

int main()
{
	
	int estado = ESTADO1;
	int in = 0;
	
	board_Init();
	
	while(TRUE)
	{
		if(estado == ESTADO1)
		{
			SALIDA = LED_E1;
			
			in = lectura();
			
			if((in == 2) || (in == 3))
			{
				estado = ESTADO1;
			}
			else if(in == 0)
			{
				estado = ESTADO2;	
			}
			else if(in == 1)
			{
				estado = ESTADO4;
			}
			
		}
		
		else if(estado == ESTADO2)
		{
			SALIDA = LED_E2;
			
			in = lectura();
			
			if((in == 2) || (in == 3))
			{
				estado = ESTADO2;
			}
			else if(in == 0)
			{
				estado = ESTADO3;	
			}
			else if(in == 1)
			{
				estado = ESTADO1;
			}
			
		}
		
		else if(estado == ESTADO3)
		{
			SALIDA = LED_E3;
			
			in = lectura();
			
			if((in == 2) || (in == 3))
			{
				estado = ESTADO3;
			}
			else if(in == 0)
			{
				estado = ESTADO4;	
			}
			else if(in == 1)
			{
				estado = ESTADO2;
			}
			
		}
		
		else if(estado == ESTADO4)
		{
			SALIDA = LED_E4;
			
			in = lectura();
			
			if((in == 2) || (in == 3))
			{
				estado = ESTADO4;
			}
			else if(in == 0)
			{
				estado = ESTADO1;	
			}
			else if(in == 1)
			{
				estado = ESTADO3;
			}
			
		}
		
		
		
		delay_ms(500);
		
	}


}

