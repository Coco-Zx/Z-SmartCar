#ifndef __IMAGE_H
#define __IMAGE_H
#define S_MT9V03X_H  120
#define S_MT9V03X_W  188
extern uint8 M_W_Finally;
extern uint8 DX_M_Start;
extern int Cross_Flag;
void find_JD(uint8 index[S_MT9V03X_H][S_MT9V03X_W]);
void find_BX(uint8 index[S_MT9V03X_H][S_MT9V03X_W]);
void find_ZX();
void Deal_DX();
void Deal_GD();
void Deal_Cross();
void Draw_Line();
uint8 M_Weight();
#endif