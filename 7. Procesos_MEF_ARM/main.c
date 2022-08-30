
#include"board.h"
#include"tm4c123gh6pm.h"

// PORTF 
// BIT4 - BIT3 - BIT2 - BIT1 - BIT0
//   IN -  OUT -  OUT -  OUT -   IN

#define ENTRADA	GPIO_PORTF_DATA_R 
#define  SALIDA  GPIO_PORTF_DATA_R

#define EST_1		0
#define EST_2		1
#define EST_3		2
#define EST_4		3

#define LED_E1	0x02
#define LED_E2	0x04
#define LED_E3	0x08
#define LED_E4	0x0A

#define DELAY		500

struct estados 
{	
	int salida;
	int delay;
	int Estados[4];
};

typedef const struct estados state_t;

static state_t MEF[4] = 
{
/* Salida, Delay,in= 00	   01    10    11  */     
	{LED_E1, DELAY, {EST_2, EST_4,EST_1,EST_1} },
	{LED_E2, DELAY, {EST_3, EST_1,EST_2,EST_2} },
	{LED_E3, DELAY, {EST_4, EST_2,EST_3,EST_3} },
	{LED_E4, DELAY, {EST_1, EST_3,EST_4,EST_4} }

};
	

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
	
	int estado = EST_1;
	int in = 0;
	
	board_Init();
	
	while(TRUE)
	{	
		SALIDA = (volatile unsigned long)	MEF[estado].salida;
		delay_ms(MEF[estado].delay);
		
		in = lectura();
		
		estado = MEF[estado].Estados[in];
		
	}


}

