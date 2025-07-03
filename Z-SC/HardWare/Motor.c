#include "zf_common_headfile.h"
#include "Menu.h"
#define MotorR_PWM   TIM5_PWM_CH2_A1 
#define MotorR_Turn  A0
#define MotorL_PWM   TIM5_PWM_CH4_A3 
#define MotorL_Turn  A2

int pwmL;
int pwmR;
void Motor_Init(){
	gpio_init(MotorL_Turn,GPO,0,GPO_PUSH_PULL);
	gpio_init(MotorR_Turn,GPO,0,GPO_PUSH_PULL);
	pwm_init (MotorL_PWM,5000,0);
	pwm_init (MotorR_PWM,5000,0);
}
void MotorR_SetSpeed(int pwm){
	if(pwm>0){
		gpio_set_level (MotorR_Turn,0);
		pwm_set_duty (MotorR_PWM,pwm);
	}
	if(pwm<0){
		gpio_set_level (MotorR_Turn,1);
		pwm_set_duty (MotorR_PWM,-pwm);
	}
}
void MotorL_SetSpeed(int pwm){//10000
	if(pwm>0){
		gpio_set_level (MotorL_Turn,0);
		pwm_set_duty (MotorL_PWM,pwm);
	}
	if(pwm<0){
		gpio_set_level (MotorL_Turn,1);
		pwm_set_duty (MotorL_PWM,-pwm);
	}
}

void Motor_SetSpeed(int pwmL,int pwmR){//10000
	MotorL_SetSpeed(pwmL);
	MotorR_SetSpeed(pwmR);
}
int PWM_change(int x){
	int pwm;
	pwm=10000*0.8*x/100;
	return pwm;
}
void Motor_Stop(void){
	pwm_set_duty (MotorR_PWM,0);
	pwm_set_duty (MotorL_PWM,0);
}