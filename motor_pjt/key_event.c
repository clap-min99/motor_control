#include "device_driver.h"
#include <stdio.h>

void Get_Pressed_Check(void) 
{
    if (!key_pressed_flag)
    {
        if (Key_Get_Pressed())
        // 3초 세기
        {
            printf("버튼\n");
            // TIM2_SW_Start(3000);
            // TIM4_SW_Stop();
            key_pressed_flag = 1;
        }
    }

    else 
    {
        if (!Key_Get_Pressed())
        {
            Macro_Clear_Bit(TIM4->SR, 0);
            // TIM2_SW_Stop();
            //TIM4_SW_Start(1000);
            key_pressed_flag = 0;
            Motor_Stop();
            //정지
            re_flag = 1;

             printf("버튼\n");
            if(!motor_dir)
            {
                LED_On();
                printf("정회전\n");
                Motor_CW();
                motor_dir=1;
            }
            else
            {
                LED_Off(); 
                printf("역회전\n");
                Motor_CCW();
                motor_dir=0;
            }
        }
    }
}