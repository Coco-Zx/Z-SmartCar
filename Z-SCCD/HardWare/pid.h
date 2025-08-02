#ifndef __PID_H
#define __PID_H
extern float Kp,Ki,Kd;
extern float Target,Actual,Out;
extern float limit;
extern int Final_Speed;
extern int Z_Kp;
extern int Z_Kd;
extern int W_Kp;
extern int W_Kd;
typedef struct{
	float Target;//目标输出
	float Actual;//实际输出
	float Out;//PWM装载值
	
	float Kp;
	float Ki;
	float Kd;
	
	float Err0;//本次误差
	float Err1;//上次误差
	float Err2;
	float ErrI;//积分误差累加
	
	float offset;
		
	float OutMax;
	float OutMin;//限幅
}PID;
typedef struct{
	float Target;//目标输出
	float Actual;//实际输出
	float Out;//PWM装载值
	
	float Kp;
	float Kp2;
	float Kd;
	
	float Err0;//本次误差
	float Err1;//上次误差
	float Err2;
	float ErrI;//积分误差累加
	
	float offset;
		
	float OutMax;
	float OutMin;//限幅
}PIDImage;
extern PID Inner_L,Inner_R;
extern PIDImage Outer;

void Kp_Change(float k);
void PID_Update(PID *p);
void PID_UpdateZ(PID *p);
void PID_UpdateImage(PIDImage *p);
void pid_update();

void pid_W();
void pid_Z();
#endif