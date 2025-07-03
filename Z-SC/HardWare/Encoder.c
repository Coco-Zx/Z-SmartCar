#include "zf_common_headfile.h"
#include "Menu.h" 
#include "pid.h"
#define ENCODER_QUADDEC1                (TIM3_ENCODER)                          // ������������Ӧʹ�õı������ӿ� ����ʹ�� TIM3 �ı���������
#define ENCODER_QUADDEC1_A               (TIM3_ENCODER_CH1_B4)                   // A ���Ӧ������
#define ENCODER_QUADDEC1_B               (TIM3_ENCODER_CH2_B5)                   // B ���Ӧ������
 
#define ENCODER_QUADDEC2                 (TIM4_ENCODER)                          //������������Ӧʹ�õı������ӿ� ����ʹ�� TIM3 �ı���������
#define ENCODER_QUADDEC2_A               (TIM4_ENCODER_CH1_B6)                   // A ���Ӧ������
#define ENCODER_QUADDEC2_B               (TIM4_ENCODER_CH2_B7)                   // B ���Ӧ������
int E_Num1;
int E_Num2;
void Encoder_Init(){
	encoder_quad_init(TIM3_ENCODER, TIM3_ENCODER_CH1_B4, TIM3_ENCODER_CH2_B5);
	encoder_quad_init(TIM4_ENCODER, TIM4_ENCODER_CH1_B6, TIM4_ENCODER_CH2_B7);
	
	pit_ms_init(TIM6_PIT, 80);                                                      // ��ʼ�� PIT Ϊ�����ж� 100ms ����

    interrupt_set_priority(TIM6_IRQn, 0);                                    // ���� PIT �������жϵ��ж����ȼ�Ϊ 0
}
void pit6_handler(){
    E_Num1= -encoder_get_count(ENCODER_QUADDEC1);                  // ��ȡ����������
    E_Num2= encoder_get_count(ENCODER_QUADDEC2);                          // ��ȡ����������
    encoder_clear_count(ENCODER_QUADDEC1);                                       // ��ձ���������
    encoder_clear_count(ENCODER_QUADDEC2);                                           // ��ձ���������
	pid();
	if(C_Num==3){  //����Ϊ2
		//ips200_show_int (70, 164,E_Num1,5);
		//ips200_show_int (70, 180,E_Num2,5);
		ips200_show_float (70, 250,E_Num1,4,2);
	    ips200_show_float (70, 270,E_Num2,4,2);
		ips200_show_float (70, 290,Out,4,2);
	}
}
