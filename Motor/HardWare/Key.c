#include "zf_common_headfile.h"
#include "Menu.h"
#include "Motor.h" 
#define KEY1                    (E2 )
#define KEY2                    (E3 )
#define KEY3                    (E4 )
#define KEY4                    (E5 )
char Car_Flag=0;
void Key_Init(){
	gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);                               // ??? KEY1 ?? ????? ????
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);                               // ??? KEY2 ?? ????? ????
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);                               // ??? KEY3 ?? ????? ????
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);                               // ??? KEY4 ?? ????? ????
}
void Scan_Key(){
	int Max;
	switch(C_Num){
		case 0:Max=4;break;
		case 1:Max=3;break;
		case 2:Max=4;break;
		case 3:Max=4;break;
	}
	if(!gpio_get_level(KEY2)) {
		system_delay_ms(100);
		if(!gpio_get_level(KEY2)) {
			if(CS_Change_Flag==0){
				G_Num++;
				if(G_Num > Max)
				{
					G_Num=1;
				}
			}
			else if(CS_Change_Flag==1){
				switch(G_Num){
					case 1:Kp--;ips200_show_int (70, 164,Kp,2);break;
					case 2:Ki--;ips200_show_int (70, 180,Ki,2);break;
					case 3:Kd--;ips200_show_int (70, 196,Kd,2);break;
					case 4:Speed--;ips200_show_int (70, 212,Speed,2);break;
				}
			}
		}
	}
	if(!gpio_get_level(KEY1)) {
		system_delay_ms(100);
		if(!gpio_get_level(KEY1)) {
			if(CS_Change_Flag==0){
				G_Num--;
				if(G_Num <1)
				{
					G_Num=Max;
				}
			}
			else if(CS_Change_Flag==1){
				switch(G_Num){
					case 1:Kp++;ips200_show_int (70, 164,Kp,2);break;
					case 2:Ki++;ips200_show_int (70, 180,Ki,2);break;
					case 3:Kd++;ips200_show_int (70, 196,Kd,2);break;
					case 4:Speed++;ips200_show_int (70, 212,Speed,2);break;
				}
			}
		}
	}
	if(!gpio_get_level(KEY4)) {
		system_delay_ms(100);
		if(!gpio_get_level(KEY4)) {
			if(CS_Change_Flag==0){
			C_Num=0;
			ips200_clear();
			Dis_CD0();
			G_Num=1;
			}
		}
	}
	if(!gpio_get_level(KEY3)) {
		system_delay_ms(100);
		if(!gpio_get_level(KEY3)) {
			switch(C_Num){
				case 0:
				{
					switch(G_Num){
						case 1:
								if(Car_Flag==0){
									ips200_show_string(0, 300, " GO!");
									Car_Flag=1;
									Motor_SetSpeed(PWM_change(Speed),PWM_change(Speed));
									break;
								}
								else{
									ips200_show_string(0, 300, "    ");
									Car_Flag=0;
									Motor_Stop();
								}break;
						case 2:C_Num=1;ips200_full(RGB565_WHITE);Dis_CD1();G_Num=1;break;
						case 3:C_Num=2;ips200_full(RGB565_WHITE);Dis_CD2();G_Num=1;break;
						case 4:C_Num=3;ips200_full(RGB565_WHITE);Dis_CD3();G_Num=1;break;
					}
				}break;
				case 3:
				{
					
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
						
					}
				}break;
				
			
			}
			
		}
	}
}