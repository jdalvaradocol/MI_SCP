

#include"board.h"
#include"tm4c123gh6pm.h"

# define Entrada	GPIO_PORTF_DATA_R 
# define  Salida  GPIO_PORTF_DATA_R

void delay_ms(int delay);

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06

void delay_ms(int delay)
{
		for(int i = 0;i < delay;i++)
		{
			for(int j = 0;j < 2500;j++)
			{
		
			}
		}
}


int main ()
{
	
	board_Init();
	
	while(TRUE)
	{
		Salida = 0x0C;
		delay_ms(300);
		Salida = 0x00;
		delay_ms(300);
	}
		
}
