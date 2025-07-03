/*********************************************************************************************************************
* MM32F327X-G8P Opensourec Library 即（MM32F327X-G8P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F327X-G8P 开源库的一部分
* 
* MM32F327X-G8P 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.37
* 适用平台          MM32F327X_G8P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完


// *************************** 例程硬件连接说明 ***************************
// 核心板正常供电即可 无需额外连接
// 如果使用主板测试 主板必须要用电池供电


// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程 完成上电
// 
// 2.可以看到核心板上两个 LED 呈流水灯状闪烁
// 
// 3.将 SWITCH1 / SWITCH2 两个宏定义对应的引脚分别按照 00 01 10 11 的组合接到 1-VCC 0-GND 或者波动对应主板的拨码开关
// 
// 3.不同的组合下 两个 LED 流水灯状闪烁的频率会发生变化
// 
// 4.将 KEY1 / KEY2 / KEY3 / KEY4 两个宏定义对应的引脚接到 1-VCC 0-GND 或者 按对应按键
// 
// 5.任意引脚接 GND 或者 按键按下会使得两个 LED 一起闪烁 松开后恢复流水灯
// 
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查


// **************************** 代码区域 ****************************
#define LED1                    (H2 )
#define LED2                    (B13)

#define KEY1                    (E2 )
#define KEY2                    (E3 )
#define KEY3                    (E4 )
#define KEY4                    (E5 )

#define SWITCH1                 (D3 )
#define SWITCH2                 (D4 )

int8 offset=0;
uint8_t T_Counter=0;//定时器计数
int G_Num=1;//光标位置
char C_Num=0;//菜单页码
char CS_GB=0;//光标参数
char CS_Change_Flag=0;//参数改变标志位

//参数声明
int Kp=50;
int Ki=40;
int Kd=30;
int Speed=20;

//函数声明
void All_Init();
void Scan_Key();
void Dis_CD0();
void Dis_CD1();
void Dis_CD2();
void Dis_CD3();
void Dis_GB();

int main (void)
{
	All_Init();
    Dis_CD0();
	pit_ms_init(TIM2_PIT,20);
    while(1)
    {
        Scan_Key();
		if(mt9v03x_finish_flag)
		{
			memcpy(image_copy, mt9v03x_image, MT9V03X_H*MT9V03X_W);
			ips200_show_gray_image(0, 0, (const uint8 *)image_copy, MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
			mt9v03x_finish_flag=0;
		}
		
    }
}

void All_Init(){
	clock_init(SYSTEM_CLOCK_120M);                                              // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART
	system_delay_ms(300);
	ips200_init(IPS200_TYPE_SPI);                                               //ips初始化
	//摄像头初始化
	while(1)
    {
        if(mt9v03x_init())
        {
            ips200_show_string(0, 16, "mt9v03x reinit.");
        }
        else
        {
            break;
        }
        system_delay_ms(500);                                                   // 短延时快速闪灯表示异常
    }
        system_delay_ms(500);
	ips200_show_string(0, 16, "init success.");
	system_delay_ms(1000);  
	gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);                               // 初始化 KEY1 输入 默认高电平 上拉输入
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);                               // 初始化 KEY2 输入 默认高电平 上拉输入
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);                               // 初始化 KEY3 输入 默认高电平 上拉输入
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);                               // 初始化 KEY4 输入 默认高电平 上拉输入
	
	gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // 初始化 LED1 输出 默认高电平 推挽输出模式
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // 初始化 LED2 输出 默认高电平 推挽输出模式
	
	encoder_quad_init(TIM3_ENCODER, TIM3_ENCODER_CH1_B4, TIM3_ENCODER_CH2_B5);
	encoder_quad_init(TIM4_ENCODER, TIM4_ENCODER_CH1_B6, TIM4_ENCODER_CH2_B7);
	
	ips200_clear();
	
	//编码器，中断初始化
}


void TIM2_IRQHandler (void)
{
    T_Counter++;
	if(T_Counter%5==0){
		Dis_GB();
	}
    TIM2->SR &= ~TIM2->SR;                                                      // 清空中断状态
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
			C_Num=0;
			ips200_clear();
			Dis_CD0();
			G_Num=1;
		}
	}
	if(!gpio_get_level(KEY3)) {
		system_delay_ms(100);
		if(!gpio_get_level(KEY3)) {
			switch(C_Num){
				case 0:
				{
					switch(G_Num){
						case 1:ips200_show_string(0, 300, " GO!");break;
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

// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 
// 问题1：LED 不闪烁
//      如果使用主板测试，主板必须要用电池供电
//      查看程序是否正常烧录，是否下载报错，确认正常按下复位按键
//      万用表测量对应 LED 引脚电压是否变化，如果不变化证明程序未运行，如果变化证明 LED 灯珠损坏
// 
// 问题2：SWITCH1 / SWITCH2 更改组合流水灯频率无变化
//      如果使用主板测试，主板必须要用电池供电
//      查看程序是否正常烧录，是否下载报错，确认正常按下复位按键
//      万用表测量对应 LED 引脚电压是否变化，如果不变化证明程序未运行，如果变化证明 LED 灯珠损坏
//      万用表检查对应 SWITCH1 / SWITCH2 引脚电压是否正常变化，是否跟接入信号不符，引脚是否接错
// 
// 问题3：KEY1 / KEY2 / KEY3 / KEY4 接GND或者按键按下无变化
//      如果使用主板测试，主板必须要用电池供电
//      查看程序是否正常烧录，是否下载报错，确认正常按下复位按键
//      万用表测量对应 LED 引脚电压是否变化，如果不变化证明程序未运行，如果变化证明 LED 灯珠损坏
//      万用表检查对应 KEY1 / KEY2 / KEY3 / KEY4 引脚电压是否正常变化，是否跟接入信号不符，引脚是否接错
