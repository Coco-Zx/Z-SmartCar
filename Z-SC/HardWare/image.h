#ifndef __IMAGE_H
#define __IMAGE_H
#define S_MT9V03X_H  120
#define S_MT9V03X_W  188
extern uint8 M_W_Finally;
void find_JD(uint8 index[S_MT9V03X_H][S_MT9V03X_W]);
void find_BX(uint8 index[S_MT9V03X_H][S_MT9V03X_W]);
void Draw_Line();
uint8 M_Weight();
#endif