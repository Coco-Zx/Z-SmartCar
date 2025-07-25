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
#include "Menu.h"
#include "Key.h"
#include "Motor.h"
#include "Encoder.h"
#include "YUdeal.h" 
#include "pid.h"
#include "image.h"
#include "buzzer.h"
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

uint8_t T_Counter=0;//定时器计数

//函数声明
void All_Init();

int main (void)
{
	All_Init();//全部初始化
    Dis_CD0();//主页面菜单显示
	pit_ms_init(TIM2_PIT,15);//控制环刷新
	pit_ms_init(TIM7_PIT,50);//按键刷新
	Mode=1;
	ips200_show_int (100, 150,Mode,1);
	Outer.Target=0;
	
    Z_Kp=30;//pid分段
	Z_Kd=400;
	W_Kp=65;
	W_Kd=620;
	
	while(1)
    {                    
		ips200_show_int (180,132,stage_R,3);//左右圆环状态位
		ips200_show_int (200,132,stage_L,3);
//		if(DX_M_Start!=0){
//			Buzzer_On();
//		}
		//Buzzer_On();
			memcpy(image_copy, mt9v03x_image, MT9V03X_H*MT9V03X_W);//图像复制
			memcpy(image, mt9v03x_image, MT9V03X_H*MT9V03X_W);
//			filter();
			uint8 threshold=GetOTSU(image_copy);//大津法
//			ips200_show_int (150, 290, threshold,3);
//			uint8 threshold=DJthreshold(image_copy);
			Set_image_T(threshold);
			Protect();//保护
			Stop();//斑马线停车
			find_JD(image);//找边线基点
			find_BX(image);//爬边线
			Deal_DX();//丢线
			Deal_Cross();//十字
			
			Deal_Circle_R();//右环岛
			//Deal_Circle_L();//左环岛
			
			Cross_Flag=0;//十字标志位清0
			
			Circle_Flag=0;//环岛标志位清0
			find_ZX();//中线
			QZ_Limit();//动态前瞻
			M_W_Finally=M_Weight();
			Outer.Actual=97-M_W_Finally;//中线误差
			pid_update();//分段pid
			ips200_show_float (150, 160,Outer.Actual,4,2);
			ips200_show_int (150, 240,S_stage,1);//停车标志位
			
		if(mt9v03x_finish_flag&&Car_Flag ==0)
		{
			if(C_Num==2){
				
			
//				ips200_show_float (70, 230,Inner_R.Actual,4,2);
//				ips200_show_float (70, 250,Inner_L.Actual,4,2);//实际速度输出
//				ips200_show_float (70, 270,Inner_R.Out,4,2);
//				ips200_show_float (70, 290,Inner_L.Out,4,2);
				
	
				ips200_show_gray_image(0, 0, (const uint8 *)image_copy, MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H,0);
		
			}
			if(C_Num==0){
				
				Draw_Line();//画线
				ips200_show_gray_image(0, 0, (const uint8 *)image, MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H,0);
			
		}

			mt9v03x_finish_flag=0;
		}

		Buzzer();//蜂鸣器
	

//       printf("%f %f %f\r\n",Inner_L.Target,Inner_L.Actual,Inner_L.Out );
		
    }
}

void All_Init(){
	clock_init(SYSTEM_CLOCK_120M);                                              // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                                                               // 初始化默认 Debug UART 方便调pid
	system_delay_ms(300);
	ips200_init(IPS200_TYPE_SPI);   	//ips初始化
	key_init(5);
	Key_Init();
	Motor_Init();
	Encoder_Init();
	Buzzer_Init();
	
	
	
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
	//ips200_show_string(0, 16, "init success.");
	system_delay_ms(1000);  
	
	ips200_clear();
	
	
}
//按键中断
void pit7_handler(){
	if(Car_Flag ==0){
	 T_Counter++;
	//ips200_show_float (120, 290, M_W_Finally,4,2);
    key_scanner();
	Scan_Key();
	if(T_Counter%5==0){
		Dis_GB();
		}
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
