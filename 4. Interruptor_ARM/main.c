

#include"board.h"
#include"tm4c123gh6pm.h"

// PORTF 
// BIT4 - BIT3 - BIT2 - BIT1 - BIT0
//   IN -  OUT -  OUT -  OUT -   IN

#define ENTRADA	GPIO_PORTF_DATA_R 
#define  SALIDA  GPIO_PORTF_DATA_R

#define ESTADO_0	0
#define ESTADO_1	1

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
		for(int i = 0;i < delay;i++)
		{
			for(int j = 0;j < 4000;j++)
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



int main ()
{
	
	int dato_in = 0; 	//  Variable para el guardar el dato de entrada.
	int  estado = 0;	//  Varaible para el estado actual.
	int       x = 0;	//  Contador de la variable de estado.
	
	board_Init();			//	Inicializa la placa.
	
	// unidada de tiempo es de 150ms
	
	while(TRUE)				// Se ejecuta un bucle infinito 
	{

		dato_in =  lectura();		// se realiza la lectura de los sw
		
		if(estado == ESTADO_0)
		{
			SALIDA = 0x00;

			if(dato_in == ON)
			{	
				estado = ESTADO_1;
				
				while(dato_in == ON)
				{
					dato_in =  lectura();
				}


				
			}		
		
		}
		else if(estado == ESTADO_1)
		{
			
			SALIDA = 0x08;
			
			if(dato_in == ON || x >= 10)
			{	
				estado = ESTADO_0;
				x = 0;
			
				while(dato_in == ON)
				{
					dato_in =  lectura();
				}
				
			}		
			
			x++;
			
		}
		
		delay_ms(500);
		
	}
		
}
