#ifndef __PID_H
#define __PID_H
extern float Kp,Ki,Kd;
extern float Target,Actual,Out;

typedef struct{
	float Target;
	float Actual;
	float Out;
	
	float Kp;
	float Ki;
	float Kd;
	
	float Err0;
	float Err1;
	float ErrI;
	
	float OutMax;
	float OutMin;
}PID;
extern PID Inner;

void PID_Update(PID *p);
void pid_W();
void pid_Z();
#endif