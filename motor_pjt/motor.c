#include "device_driver.h"

void Motor_CW(int gear)
{
    #if 0
    Motor_Stop();
    if(Macro_Check_Bit_Set(TIM4->SR,0)){
        TIM5_CW();   
        Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 2);
	    Macro_Clear_Bit(GPIOA->ODR, 1);
        TIM5_Out_PWM(10000, pwm_default);
    }
    #endif

    #if 1
    TIM5_CW();   
    Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 2);
	Macro_Clear_Bit(GPIOA->ODR, 1);
    TIM5_Out_PWM(10000, pwm_default+(gear-1)*5);
    #endif
    
}

void Motor_CCW(int gear)
{
    #if 0
    Motor_Stop();
    if(Macro_Check_Bit_Set(TIM4->SR,0)){
        TIM5_CCW();
        Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 0);
        Macro_Clear_Bit(GPIOA->ODR, 0);   
	    TIM5_Out_PWM(10000, pwm_default);
    }
    #endif
    #if 1
    Motor_Stop();
    TIM2_Delay(1000);
    TIM5_CCW();
    Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 0);
    Macro_Clear_Bit(GPIOA->ODR, 0);   
	TIM5_Out_PWM(10000, pwm_default+(gear-1)*5);
    #endif
    
}


void Motor_Stop(void)
{
    Macro_Write_Block(GPIOA->MODER,0xf,0x5,0);
    Macro_Clear_Area(GPIOA->ODR, 0x3,0);
}
