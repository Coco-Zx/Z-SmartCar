#ifndef __MOTOR_H
#define __MOTOR_H
extern int pwmL;
extern int pwmR;
void Motor_Init();
void MotorR_SetSpeed(int pwm);
void MotorL_SetSpeed(int pwm);
void Motor_SetSpeed(int pwmL,int pwmR);
void Motor_Stop(void);
int PWM_change(int x);
#endif