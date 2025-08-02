#include "zf_common_headfile.h"
#include "image.h"
#include "Menu.h" 
#include "pid.h"
#include "Motor.h" 
#include "Key.h"
#include "auto_menu.h" 
#define ENCODER_QUADDEC1                (TIM3_ENCODER)                      
#define ENCODER_QUADDEC1_A               (TIM3_ENCODER_CH1_B4)              
#define ENCODER_QUADDEC1_B               (TIM3_ENCODER_CH2_B5)              
 
#define ENCODER_QUADDEC2                 (TIM4_ENCODER)                     
#define ENCODER_QUADDEC2_A               (TIM4_ENCODER_CH1_B6)              
#define ENCODER_QUADDEC2_B               (TIM4_ENCODER_CH2_B7)    
int E_NumR;
int E_NumL;//编码器数值
int M_M;
int Counter=0;
//编码器初始化
void Encoder_Init(){
	encoder_quad_init(TIM3_ENCODER, TIM3_ENCODER_CH1_B4, TIM3_ENCODER_CH2_B5);
	encoder_dir_init(TIM4_ENCODER, TIM4_ENCODER_CH1_B6, TIM4_ENCODER_CH2_B7);
	                          
}
float GKD=0;
//编码器读取与pid控制
void pit2_handler(){
	Counter++;
	imu660ra_get_gyro();
	
	
		E_NumR= -encoder_get_count(ENCODER_QUADDEC1);                  
		E_NumL= encoder_get_count(ENCODER_QUADDEC2);     //读取数值              
		encoder_clear_count(ENCODER_QUADDEC1);                         
		encoder_clear_count(ENCODER_QUADDEC2);            //清空计数   
		Inner_L.Actual=(E_NumL+E_NumR)/2;
		Inner_R.Actual=(E_NumL+E_NumR)/2;   //实际调速赋值	
		Outer.Actual=97-M_W_Finally;//中线误差
		if(Car_Flag!=0){
			
			PID_UpdateImage(&Outer);
			Inner_L.Target=Speed;
			Inner_R.Target=Speed;
			PID_Update(&Inner_L);    
			PID_Update(&Inner_R); //PID
//			MotorL_SetSpeed(Inner_L.Out+Outer.Out);//左轮PID
//			MotorR_SetSpeed(Inner_R.Out-Outer.Out);
		}
	
	if(Car_Flag!=0){
		MotorL_SetSpeed(Inner_L.Out+Outer.Out+GKD*imu660ra_gyro_z);//左轮PID
		MotorR_SetSpeed(Inner_R.Out-Outer.Out-GKD*imu660ra_gyro_z);
	}
}

