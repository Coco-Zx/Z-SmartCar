#include "zf_common_headfile.h"
#include "image.h"
#include "Menu.h" 
#include "pid.h"
#include "Motor.h" 
#include "Key.h"
#define ENCODER_QUADDEC1                (TIM3_ENCODER)                      
#define ENCODER_QUADDEC1_A               (TIM3_ENCODER_CH1_B4)              
#define ENCODER_QUADDEC1_B               (TIM3_ENCODER_CH2_B5)              
 
#define ENCODER_QUADDEC2                 (TIM4_ENCODER)                     
#define ENCODER_QUADDEC2_A               (TIM4_ENCODER_CH1_B6)              
#define ENCODER_QUADDEC2_B               (TIM4_ENCODER_CH2_B7)    
int Count=0;
int E_Num1;
int E_Num2;//编码器数值
int M_M;
//编码器初始化
void Encoder_Init(){
	encoder_quad_init(TIM3_ENCODER, TIM3_ENCODER_CH1_B4, TIM3_ENCODER_CH2_B5);
	encoder_quad_init(TIM4_ENCODER, TIM4_ENCODER_CH1_B6, TIM4_ENCODER_CH2_B7);
	
	pit_ms_init(TIM6_PIT,10);                                            

    interrupt_set_priority(TIM6_IRQn, 0);                                 
}
void pit6_handler(){
	Count++;
	E_Num1= -encoder_get_count(ENCODER_QUADDEC1);                  
    E_Num2= encoder_get_count(ENCODER_QUADDEC2);     //读取数值              
    encoder_clear_count(ENCODER_QUADDEC1);                         
    encoder_clear_count(ENCODER_QUADDEC2);            //清空计数   
	Inner_L.Actual=E_Num2;
	Inner_R.Actual=E_Num1;   //实际调速赋值	
	if(Car_Flag!=0){
           
	
		M_M=94;
		if(Count%1==0){
			Outer.Actual= M_M-M_W_Finally;
			PID_UpdateZ(&Outer);
		}
		
		Inner_L.Target=Speed;
		Inner_R.Target=Speed;
		PID_Update(&Inner_L);    //PID
		PID_Update(&Inner_R); 
		MotorL_SetSpeed(Inner_L.Out+Outer.Out);//左轮PID
		MotorR_SetSpeed(Inner_R.Out-Outer.Out);
	
	//ips200_show_float (70, 270,Inner_R.Out,4,2);
	//ips200_show_float (70, 290,Inner_L.Out,4,2);
	}
	
	
//	
}

