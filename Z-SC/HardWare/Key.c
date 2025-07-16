#include "zf_common_headfile.h"
#include "Menu.h"
#include "Motor.h" 
#include "pid.h"
#include "image.h" 
#define KEY1                    (E2 )
#define KEY2                    (E3 )
#define KEY3                    (E4 )
#define KEY4                    (E5 )
//发车标志位
char Car_Flag=0;
int Final_Speed=0;
//按键初始化
void Key_Init(){
	gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);                               // ??? KEY1 ?? ????? ????
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);                               // ??? KEY2 ?? ????? ????
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);                               // ??? KEY3 ?? ????? ????
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);                               // ??? KEY4 ?? ????? ????
}
//按键代码执行
void Scan_Key(){
	int Max;
	switch(C_Num){
		case 0:Max=4;break;
		case 1:Max=3;break;
		case 2:Max=4;break;
		case 3:Max=4;break;
	}
	if(key_get_state(KEY_2)==KEY_SHORT_PRESS) {
		key_clear_state(KEY_2); 
		if(CS_Change_Flag==0){//不调参情况下上下页翻动
				G_Num++;
				if(G_Num > Max)
				{
					G_Num=1;
				}
			}
			else if(CS_Change_Flag==1){//调参情况下参数增减
				switch(G_Num){
					case 1:Outer.Kp-=1;ips200_show_float (70, 164,Outer.Kp,2,2);break;
					case 2:QZ-=1;ips200_show_int (70, 180,QZ,3);break;
					case 3:Outer.Kd-=10;ips200_show_float (70, 196,Outer.Kd,4,2);break;
					case 4:Speed-=50;ips200_show_float (70, 212,Speed,4,2);break;
				}
			}
		
	}
	if(key_get_state(KEY_1)==KEY_SHORT_PRESS) {//与上按键相同
		key_clear_state(KEY_1);
			if(CS_Change_Flag==0){
				G_Num--;
				if(G_Num <1)
				{
					G_Num=Max;
				}
			}
			else if(CS_Change_Flag==1){
				switch(G_Num){
					case 1:Outer.Kp+=1;ips200_show_float (70, 164,Outer.Kp,2,2);;break;
					case 2:QZ+=1;ips200_show_int (70, 180,QZ,3);;break;
					case 3:Outer.Kd+=10;ips200_show_float (70, 196,Outer.Kd,4,2);;break;
					case 4:Speed+=50;ips200_show_float (70, 212,Speed,4,2);break;
				}
			}
		
	}
	if(!gpio_get_level(KEY4)) {//退出按键。返回主菜单，阻塞式
		system_delay_ms(100);
		if(!gpio_get_level(KEY4)){
//	if(key_get_state(KEY_4)==KEY_SHORT_PRESS) {
//		key_clear_state(KEY_4);
			if(CS_Change_Flag==0){
			C_Num=0;
			ips200_clear();
			Dis_CD0();
			G_Num=1;
			}
		}
	}
	if(key_get_state(KEY_3)==KEY_SHORT_PRESS) {//确定按键
		key_clear_state(KEY_3);
			switch(C_Num){
				case 0:
				{
					switch(G_Num){
						case 1:
								if(Car_Flag==0){//发车确认
									ips200_show_string(0, 300, " GO!");
									Car_Flag=1;
							//		Final_Speed=Speed;
									break;
								}
								else{
									ips200_show_string(0, 300, "    ");
									Car_Flag=0;
									MotorL_SetSpeed(Speed);
									MotorR_SetSpeed(Speed);
									system_delay_ms(1000);
									Motor_Stop();
								}break;
						case 2:C_Num=1;Dis_CD1();G_Num=1;break;
						case 3:C_Num=2;Dis_CD2();G_Num=1;break;
						case 4:C_Num=3;Dis_CD3();G_Num=1;break;
					}
				}break;
				case 3:
				{//调参确认
					
					if(CS_Change_Flag==0){
						
					switch(G_Num){
						case 1:CS_Change_Flag=1;break;
						case 2:CS_Change_Flag=1;break;
						case 3:CS_Change_Flag=1;break;
						case 4:CS_Change_Flag=1;break;
					}
				}
					else{
						CS_Change_Flag=0;
						Inner_L.Target=Speed;
						Inner_R.Target=Speed;
						
					}
				}break;
				
			
			}
			
		}
	
}