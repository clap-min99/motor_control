#include "device_driver.h"
#include <stdio.h>

unsigned int prv_time = 0;
unsigned int pwm_default = 50;

volatile int Uart_Data_In=0;
volatile unsigned int Key_Pressed = 0;
volatile unsigned int re_flag=1;
volatile unsigned char Uart_Data=0;
volatile unsigned int motor_dir= 0;
volatile int TIM2_Expired = 0; 
volatile int TIM4_Expired = 0; 
volatile unsigned int key_3sec_flag = 0; 
volatile motor_state = 2;
volatile int gear = 1;  


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
	Key_ISR_Enable(1);
    
	printf("PWM Motor Start\n");
    
    for(;;)
    {
		
		
		if(Uart_Data_In)
        {
            printf("UART state=%d\n", motor_state);
            if(motor_state == 0)
            {
                Motor_CW(Uart_Data-'0');
               }
            else if(motor_state == 1)
            {
                Motor_CCW(Uart_Data-'0');
               }
               else if(motor_state == 2)
            {
                   Motor_Stop();
            }
            printf("Motor gear box = %c\n", Uart_Data);
            Uart_Data_In = 0;

        }
		
		if(Key_Pressed)
        {

            TIM4_ISR_Enable(1,500);
            Key_Pressed=0;

        }

        if(TIM4_Expired)
        {
            TIM4_Expired = 0;

            if(click_wait)
            {
                click_wait = 0;

                motor_state = (motor_state + 1) % 2;

                if(motor_state == 0)
                    Motor_CW(Uart_Data-'0');
                else
                    Motor_CCW(Uart_Data-'0');
            }
        }
		
		if (key_3sec_flag)
		{
			Motor_Stop();
			TIM5_Out_Stop();
		}
    }
}
