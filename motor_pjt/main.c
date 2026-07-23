#include "device_driver.h"
#include <stdio.h>

volatile unsigned int key_pressed_flag = 0;
volatile unsigned int motor_dir= 0;
unsigned int prv_time = 0;
unsigned int pwm_default = 50;
volatile unsigned int re_flag=1;
volatile int Uart_Data_In=0;
volatile unsigned char Uart_Data=0;


static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
	Key_Poll_Init();
	TIM5_Init();

}



void Main(void)
{
    Sys_Init(115200);
    Macro_Set_Bit(RCC->AHB1ENR, 0);
    Macro_Set_Bit(RCC->AHB1ENR, 2); 
	Uart2_RX_Interrupt_Enable(1);

    printf("PWM Motor Start\n");
    
    for(;;)
    {
		
		
		if(Uart_Data_In)
		{
				
			Motor_CW(Uart_Data-'0');
			printf("Motor gear box = %c\n", Uart_Data);
			Uart_Data_In = 0;
		}	
        
		// Get_Pressed_Check();
    
    }
}
