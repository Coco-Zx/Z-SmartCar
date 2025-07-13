#include "zf_common_headfile.h"
#define BEEP                (D7 )
uint16 count_buzzer=0;
void Buzzer_Init(){
	gpio_init(BEEP, GPO, GPIO_LOW, GPO_PUSH_PULL);
}
void Buzzer_On(){
	count_buzzer=25;

}
void Buzzer(){
	 if(count_buzzer)
    {
        gpio_set_level(BEEP,GPIO_HIGH);
        count_buzzer--;
    }
    else
    {
        gpio_set_level(BEEP, GPIO_LOW);
    }

}