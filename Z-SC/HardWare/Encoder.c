#include "zf_common_headfile.h"
#include "Menu.h" 
#include "pid.h"
#define ENCODER_QUADDEC1                (TIM3_ENCODER)                          // 正交编码器对应使用的编码器接口 这里使用 TIM3 的编码器功能
#define ENCODER_QUADDEC1_A               (TIM3_ENCODER_CH1_B4)                   // A 相对应的引脚
#define ENCODER_QUADDEC1_B               (TIM3_ENCODER_CH2_B5)                   // B 相对应的引脚
 
#define ENCODER_QUADDEC2                 (TIM4_ENCODER)                          //正交编码器对应使用的编码器接口 这里使用 TIM3 的编码器功能
#define ENCODER_QUADDEC2_A               (TIM4_ENCODER_CH1_B6)                   // A 相对应的引脚
#define ENCODER_QUADDEC2_B               (TIM4_ENCODER_CH2_B7)                   // B 相对应的引脚
int E_Num1;
int E_Num2;
void Encoder_Init(){
	encoder_quad_init(TIM3_ENCODER, TIM3_ENCODER_CH1_B4, TIM3_ENCODER_CH2_B5);
	encoder_quad_init(TIM4_ENCODER, TIM4_ENCODER_CH1_B6, TIM4_ENCODER_CH2_B7);
	
	pit_ms_init(TIM6_PIT, 80);                                                      // 初始化 PIT 为周期中断 100ms 周期

    interrupt_set_priority(TIM6_IRQn, 0);                                    // 设置 PIT 对周期中断的中断优先级为 0
}
void pit6_handler(){
    E_Num1= -encoder_get_count(ENCODER_QUADDEC1);                  // 获取编码器计数
    E_Num2= encoder_get_count(ENCODER_QUADDEC2);                          // 获取编码器计数
    encoder_clear_count(ENCODER_QUADDEC1);                                       // 清空编码器计数
    encoder_clear_count(ENCODER_QUADDEC2);                                           // 清空编码器计数
	pid();
	if(C_Num==3){  //正常为2
		//ips200_show_int (70, 164,E_Num1,5);
		//ips200_show_int (70, 180,E_Num2,5);
		ips200_show_float (70, 250,E_Num1,4,2);
	    ips200_show_float (70, 270,E_Num2,4,2);
		ips200_show_float (70, 290,Out,4,2);
	}
}
