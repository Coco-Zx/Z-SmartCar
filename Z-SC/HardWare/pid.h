#ifndef __PID_H
#define __PID_H
extern float Kp,Ki,Kd;
extern float Target,Actual,Out;

typedef struct{
	float Target;//目标输出
	float Actual;//实际输出
	float Out;//PWM装载值
	
	float Kp;
	float Ki;
	float Kd;
	
	float Err0;//本次误差
	float Err1;//上次误差
	float ErrI;//积分误差累加
	
	float OutMax;
	float OutMin;//限幅
}PID;
extern PID Inner_L,Inner_R,Outer;

void PID_Update(PID *p);
void pid_W();
void pid_Z();
#endif