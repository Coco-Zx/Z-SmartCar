#include "zf_common_headfile.h"
#include "pid.h"
#include "Menu.h" 
#include "Encoder.h"
#include "Motor.h"
float Target,Actual,Out;
float Kp=0,Ki=0,Kd=0;
float Err0,Err1,ErrI,Err2;

PID Inner={
	.Kp=0,
	.Ki=0,
	.Kd=0,
	.OutMax=4000,
	.OutMin=-4000,
};
PID Outer={
	.Kp=0,
	.Ki=0,
	.Kd=0,
	.OutMax=4000,
	.OutMin=-4000,
};
void PID_Update(PID *p){
	p->Err1=p->Err0;
	p->Err0=p->Target - p->Actual;
	
	if(p->ErrI!=0){
		p->ErrI+=p->Err0;
	}
	else{
		p->ErrI=0;
	}
	p->Out =p->Kp*p->Err0 
		   +p->Ki*p->ErrI
		   +p->Kd*(p->Err0-p->Err1);
	
	if(p->Out>p->OutMax){
		p->Out=p->OutMax;
	}
	if(p->Out<p->OutMin){
		p->Out=p->OutMin;
	}
}
void pid_W(){
	
	
	Actual=E_Num1;
	
	Err1=Err0;
	Err0=Target -Actual;
	if(Ki!=0){
		ErrI+=Err0;
	}
	else {
		ErrI=0;
	}
	
//	if(ErrI>  ){
//		ErrI=
//	}
//	if(ErrI<   ){
//		ErrI=
//	}
	
	Out=Kp*Err0+Ki*ErrI+Kd*(Err0-Err1);
	
	if(Out>4000){
		Out=4000;
	}
	if(Out<-4000){
		Out=-4000;
	}
	
	MotorR_SetSpeed(Out);
}

void pid_Z(){
	
	
	Actual=E_Num1;
	
	Err2=Err1;
	Err1=Err0;
	Err0=Target -Actual;
	
	
	Out+=Kp*(Err0-Err1)+Ki*Err0+Kd*(Err0-2*Err1+Err2);
	
	if(Out>4000){
		Out=4000;
	}
	if(Out<-4000){
		Out=-4000;
	}
	
	MotorR_SetSpeed(Out);
}