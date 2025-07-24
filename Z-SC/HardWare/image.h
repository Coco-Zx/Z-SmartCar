#ifndef __IMAGE_H
#define __IMAGE_H
#define S_MT9V03X_H  120
#define S_MT9V03X_W  188
extern uint8 M_W_Finally;
extern uint8 DX_M_Start;
extern int Cross_Flag;
extern int S_stage;
extern int QZ;
extern int Circle_Flag;
extern uint8 stage_L;
void find_JD(uint8 index[S_MT9V03X_H][S_MT9V03X_W]);
void find_BX(uint8 index[S_MT9V03X_H][S_MT9V03X_W]);
void find_ZX();
void Deal_DX();
void Deal_GD();
void Deal_Cross();
uint8 Find_A();
uint8 Find_B();
uint8 Find_C();
void Deal_Circle_R();
void Draw_Line();
void Protect();
void Stop();
void QZ_Limit();
float M_Weight();
#endif