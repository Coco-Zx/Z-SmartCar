#include "zf_common_headfile.h"
#include "Motor.h" 
int G_Num=1;//????
char C_Num=0;//????
char CS_GB=0;//????
char CS_Change_Flag=0;//???????


int Kp=50;
int Ki=40;
int Kd=30;
int Speed=20;
void Dis_CD0(){
	
			ips200_show_string(10, 132, "MainMenu  ");
			ips200_show_string(0, 164, ">");
			ips200_show_string(10, 164, "Cargo     ");
			ips200_show_string(10, 180, "Mode      ");
			ips200_show_string(10, 196, "View      ");
			ips200_show_string(10, 212, "Setting   ");
		
}
void Dis_CD1(){
	
			ips200_show_string(10, 132, "MODE      ");
			ips200_show_string(0, 164, ">");
			ips200_show_string(10, 164, "Mode1     ");
			ips200_show_string(10, 180, "Mode2     ");
			ips200_show_string(10, 196, "Mode3     ");
			ips200_show_string(10, 212, "          ");
}
void Dis_CD2(){
			
			ips200_show_string(10, 132, "Setting   ");
			ips200_show_string(0, 164, ">");
			ips200_show_string(10, 164, "Kp=       ");
			ips200_show_string(10, 180, "Ki=       ");
			ips200_show_string(10, 196, "Kd=       ");
			ips200_show_string(10, 212, "Speed=    ");
	
			ips200_show_int (70, 164,Kp,2);
			ips200_show_int (70, 180,Ki,2);
			ips200_show_int (70, 196,Kd,2);
			ips200_show_int (70, 212,Speed,2);
		
}
void Dis_CD3(){
	
			ips200_show_string(10, 132, "Setting   ");
			ips200_show_string(0, 164, ">");
			ips200_show_string(10, 164, "Kp=       ");
			ips200_show_string(10, 180, "Ki=       ");
			ips200_show_string(10, 196, "Kd=       ");
			ips200_show_string(10, 212, "Speed=    ");
		
			ips200_show_int (70, 164,Kp,2);
			ips200_show_int (70, 180,Ki,2);
			ips200_show_int (70, 196,Kd,2);
			ips200_show_int (70, 212,Speed,2);
		
}
void Dis_GB(){
	unsigned char k;
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