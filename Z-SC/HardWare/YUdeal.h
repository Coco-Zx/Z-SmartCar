#ifndef __YUDEAL_H
#define __YUDEAL_H

#define Gray 255
#define P_Sum    MT9V03X_H*MT9V03X_W
#define S_MT9V03X_H  120   //实际高度
#define S_MT9V03X_W  188   //实际宽度
uint8 DJthreshold(uint8 index[S_MT9V03X_H][S_MT9V03X_W]);
uint8 GetOTSU (uint8 index[S_MT9V03X_H][S_MT9V03X_W]);
void Set_image_T(uint8 value);
void filter();
#endif