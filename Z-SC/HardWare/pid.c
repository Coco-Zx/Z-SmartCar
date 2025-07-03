#include "zf_common_headfile.h"
#include "Menu.h" 
#include "Encoder.h"
#include "Motor.h"
float Target,Actual,Out;
float Kp=0,Ki=0,Kd=0;
float Err0,Err1,ErrI;


void pid(){
	
	
	Actual=E_Num1;
	
	Err1=Err0;
	Err0=Target -Actual;
	if(Ki!=0){
		ErrI+=Err0;
	}
	else {
		ErrI=0;
	}
	
	Out=Kp*Err0+Ki*ErrI+Kd*(Err0-Err1);
	
	if(Out>4000){
		Out=4000;
	}
	if(Out<-4000){
		Out=-4000;
	}
	
	MotorR_SetSpeed(Out);
}