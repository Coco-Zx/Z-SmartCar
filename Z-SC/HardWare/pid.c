#include "zf_common_headfile.h"
#include "pid.h"
#include "Menu.h" 
#include "Encoder.h"
#include "Motor.h"
#include "image.h" 
#include "key.h" 
float Target,Actual,Out;
float Kp=0,Ki=0,Kd=0;
float Err0,Err1,ErrI,Err2;
float Z_Kp;
float Z_Kd;
float W_Kp;
float W_Kd;

//右轮pid结构体定义
PID Inner_R={
	.ErrI=0,
	.Err1=0,
	.Err0=0,
	.Kp=3.68,//0.88
	.Ki=0.11,//0.29,
	.Kd=0,
	.OutMax=4000,//限幅
	.OutMin=-4000,
};
//左轮pid结构体定义
PID Inner_L={
	.ErrI=0,
	.Err1=0,
	.Err0=0,
	.Kp=3.68,//0.60
	.Ki=0.11,//0.32
	.Kd=0,
	.OutMax=4000,
	.OutMin=-4000,
};
//中线外环pid定义
PID Outer={
	.Kp=63,//49//4.89
	.Ki=0,
	.Kd=630,//580
	.OutMax=4000,
	.OutMin=-4000,
};

//分段pid
void pid_update(){
	if(Outer.Actual<10&&Outer.Actual>-10){
		Final_Speed=Speed+25;
		Outer.Kp=Z_Kp;
		Outer.Kd=Z_Kd;
	}
	else {
		Final_Speed=Speed-15;
		Outer.Kp=W_Kp;
		Outer.Kd=W_Kd;
	}
}
//pid封装
void PID_Update(PID *p){
	p->Err1=p->Err0;
	p->Err0=p->Target - p->Actual;//数据读取
	
//	if(p->ErrI!=0){
		p->ErrI+=p->Err0;//积分项累加
//	}
//	else{
//		p->ErrI=0;
//	}
	p->Out =p->Kp*p->Err0 
		   +p->Ki*p->ErrI
		   +p->Kd*(p->Err0-p->Err1);//输出
	
	
	
	
	
	if(p->Out>p->OutMax){
		p->Out=p->OutMax;
	}
	if(p->Out<p->OutMin){
		p->Out=p->OutMin;//限幅
	}
}

void PID_UpdateZ(PID *p){
	p->Err2=Err1;
	p->Err1=p->Err0;
	p->Err0=p->Target - p->Actual;//数据读取
	
//	if(p->ErrI!=0){
//		p->ErrI+=p->Err0;//积分项累加
//	}
//	else{
//		p->ErrI=0;
//	}
	p->Out +=p->Kp*(p->Err0 -p->Err1)
		   +p->Ki*p->Err0
		   +p->Kd*(p->Err0-p->Err1*2+Err2);//输出
	
	if(p->Out>p->OutMax){
		p->Out=p->OutMax;
	}
	if(p->Out<p->OutMin){
		p->Out=p->OutMin;//限幅
	}
}



int Kp_base=30;
void Kp_Change(float k){
	Outer.Kp=Kp_base+(M_M-M_W_Finally)*k;
}



//以下未封装

//位置式PID
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
//增量式PID
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
