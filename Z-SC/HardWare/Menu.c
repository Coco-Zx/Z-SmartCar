#include "zf_common_headfile.h"
#include "Motor.h" 
#include "Encoder.h"
#include "pid.h"
#include "image.h" 
int G_Num=1;//光标序号
char C_Num=0;//菜单序号
char CS_Change_Flag=0;//参数改变标志位



float Speed=0.0;
//主菜单显示
void Dis_CD0(){
	
			ips200_show_string(10, 132, "MainMenu  ");
			ips200_show_string(0, 164, ">");
			ips200_show_string(10, 164, "Cargo     ");
			ips200_show_string(10, 180, "Mode      ");
			ips200_show_string(10, 196, "View      ");
			ips200_show_string(10, 212, "Setting   ");
		
}
//模式菜单显示
void Dis_CD1(){
	
			ips200_show_string(10, 132, "MODE      ");
			ips200_show_string(0, 164, ">");
			ips200_show_string(10, 164, "Mode1     ");
			ips200_show_string(10, 180, "Mode2     ");
			ips200_show_string(10, 196, "Mode3     ");
			ips200_show_string(10, 212, "          ");
}
//试图菜单显示
void Dis_CD2(){
			
			ips200_show_string(10, 132, "View      ");
			ips200_show_string(0, 164, ">");
			ips200_show_string(10, 164, "E1=       ");
			ips200_show_string(10, 180, "E2=       ");
			ips200_show_string(10, 196, "          ");
			ips200_show_string(10, 212, "          ");
	
			ips200_show_int (70, 164,E_Num1,5);
			ips200_show_int (70, 180,E_Num2,5);
			
		
}
//设置菜单显示
void Dis_CD3(){
	
			ips200_show_string(10, 132, "Setting   ");
			ips200_show_string(0, 164, ">");
			ips200_show_string(10, 164, "Kp=       ");
			ips200_show_string(10, 180, "QZ=    ");
			ips200_show_string(10, 196, "Kd=       ");
			ips200_show_string(10, 212, "Speed=    ");
	
	        ips200_show_string(10, 230, "ActualR=   ");
			ips200_show_string(10, 250, "ActualL=   ");
			ips200_show_string(10, 270, "OutR=      ");
			ips200_show_string(10, 290, "OutL=      ");
			
		
			ips200_show_float (70, 164,Outer.Kp,2,2);
			ips200_show_int (70, 180,QZ,3);
			ips200_show_float (70, 196,Outer.Kd,2,2);
			ips200_show_float (70, 212,Speed,4,2);
	
	        ips200_show_float (70, 250,Inner_L.Actual,4,2);
	
			ips200_show_float (70, 230,Inner_R.Actual,4,2);
			
			ips200_show_float (70, 270,Inner_R.Out,4,2);
	        ips200_show_float (70, 290,Inner_L.Out,4,2);
			
		
}
//光标显示
void Dis_GB(){
	switch(C_Num){
		case 0:
		{
			ips200_show_string(0, 164, " ");
			ips200_show_string(0, 180, " ");
			ips200_show_string(0, 196, " ");
			ips200_show_string(0, 212, " ");
			ips200_show_string(0, 148+16*G_Num, ">");
		}break;
		case 1:
		{
			
				
				ips200_show_string(0, 164, " ");
				ips200_show_string(0, 180, " ");
				ips200_show_string(0, 196, " ");
				ips200_show_string(0, 148+16*G_Num, ">");
		
		}break;
		case 2:
		{
			ips200_show_string(0, 164, " ");
			ips200_show_string(0, 180, " ");
			ips200_show_string(0, 196, " ");
			ips200_show_string(0, 212, " ");
			ips200_show_string(0, 148+16*G_Num, ">");
		}break;
		case 3:
		{
			ips200_show_string(0, 164, " ");
			ips200_show_string(0, 180, " ");
			ips200_show_string(0, 196, " ");
			ips200_show_string(0, 212, " ");
			if(CS_Change_Flag==1){
				ips200_show_string(0, 148+16*G_Num, "!");
			}
			else{
				ips200_show_string(0, 148+16*G_Num, ">");
			}
		}break;
	}
}