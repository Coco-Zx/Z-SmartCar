#include "zf_common_headfile.h"
#include "YUdeal.h" 

void filter(){//图像处理滤波
	uint8 (*ptr)[S_MT9V03X_H][S_MT9V03X_W]=&image_copy;
	uint16 i;
	uint16 j;
	uint8 gray;
	for(i=1;i<=S_MT9V03X_H-1;i++){
		for(j=1;j<=S_MT9V03X_W-1;j++){
			gray=(*ptr)[i][j]*4+(*ptr)[i+1][j]+(*ptr)[i][j]*2+(*ptr)[i-1][j]*2+(*ptr)[i][j+1]*2
			+(*ptr)[i][j-1]*2+(*ptr)[i-1][j-1]+(*ptr)[i+1][j+1]+(*ptr)[i+1][j-1]+(*ptr)[i-1][j+1];
			(*ptr)[i][j]=gray;
		}		
	}
}

//uint8 DJthreshold(uint8 index[S_MT9V03X_H][S_MT9V03X_W]){//大津法处理阈值
//	uint16 histogram[Gray]={0};
//	uint32 Gray_Sum[Gray]={0};
//	uint8 threshold=0;
//	int sum=0;
//	uint32 S_P_Sum=S_MT9V03X_H*S_MT9V03X_W;
//	uint16 i;
//	uint16 j;
//	uint8 gray;
//	for(i=0;i<S_MT9V03X_H;i++){
//		for(j=0;j<S_MT9V03X_W;j++){
//			gray=index[i][j];
//			histogram[gray]++;
//		}		
//	}
//	for(i=0;i<Gray;i++){
//		Gray_Sum[i]=i*histogram[i];
//		sum+=Gray_Sum[i];
//	}
//	uint16 MinV,MaxV;
//	
//	for(MinV=5;MinV<Gray&&histogram[MinV]==0;MinV++);
//	for(MaxV=Gray-6;MaxV>MinV&&histogram[MaxV]==0;MaxV--);
//	ips200_show_int (100,190,MinV,3);
//	ips200_show_int (100,210,MaxV,3);
//	if(MinV==MaxV){
//		return (uint8)MinV;
//	}
//	if(MinV+1==MaxV){
//		return (uint8)MaxV;
//	}
//	
//	uint16 b_back=0,b_front=0;
//	uint32 u_back_sum=0,u_front_sum=0;
//	float a_back=0,a_front=0;
//	float deltaTmp=0,deltaMax=0;
//	
//	for(i=MinV;i<MaxV;i++){
//		b_back+=histogram[i];
//		b_front=S_P_Sum-b_back;
//		u_back_sum+=Gray_Sum[i];
//		u_front_sum =sum-u_back_sum;
//		
//		a_back=u_back_sum/(float)b_back;
//		a_front=u_front_sum/(float)b_front;
//		deltaTmp=b_back*b_front*(a_back-a_front)*(a_back-a_front)/(float)S_P_Sum;
//		
//		if(deltaTmp>deltaMax){
//			deltaMax=deltaTmp;
//			threshold=(uint8)i;
//		}
//		
//	}
//	ips200_show_int (100,230,threshold,3);
//	return threshold;
//}
//大津法
uint8 DJthreshold(uint8 index[S_MT9V03X_H][S_MT9V03X_W]){
	uint8 threshold;
	uint8 gray_value;
	uint32 S_P_Sum=S_MT9V03X_H*S_MT9V03X_W;
	float SumPK=0;
	float SumMK=0;
	float Var=0;
	float Vartmp=0;
	
	uint16 Hist[Gray]={0};
	float P[Gray]={0};
	float PK[Gray]={0};
	float MK[Gray]={0};
	
	for(uint8 i=0;i<S_MT9V03X_H;i++){
		for(uint8 j=0;j<S_MT9V03X_W;j++){
			gray_value=index[i][j];
			Hist[gray_value]++;
		}
	}
	
	for(uint16 i=0;i<Gray;i++){
		P[i]=(float)Hist[i]/S_P_Sum;
		PK[i]=SumPK+P[i];
		SumPK=PK[i];
		MK[i]=SumMK+i*P[i];
		SumMK=MK[i];
	}
	
	for(uint8 i=5;i<245;i++){
		Vartmp=((MK[Gray-1]*PK[i]-MK[i])*(MK[Gray-1]*PK[i]-MK[i]))/(PK[i]*(1-PK[i]));
		if(Vartmp>Var){
			Var=Vartmp;
			threshold=i;
		}
	}
	return threshold;
}
//大津法
uint8 GetOTSU (uint8 index[S_MT9V03X_H][S_MT9V03X_W])
{
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned short HistoGram[256];     //原先为unsigned char ，但是同一个灰度值的像素点可能会超过255个，因此造成溢出，扩大数据范围，感谢评论区指正。

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < S_MT9V03X_H; j++)
    {
        for (i = 0; i < S_MT9V03X_W; i++)
        {
            HistoGram[index[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MaxValue] == 0; MaxValue--); //获取最大灰度的值
//	ips200_show_int (150, 200, MinValue,3);
//	ips200_show_int (150, 220, MaxValue,3);
    if (MaxValue == MinValue)
        return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue)
        return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  像素总数

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
        PixelFore = Amount - PixelBack;           //背景像素点数
        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}
int OTSU=0;
void Set_image_T(uint8 value){//二值化转换
	uint8 temp_value;
	uint16 i;
	uint16 j;
	value+=OTSU;
	for(i=0;i<S_MT9V03X_H;i++){
		for(j=0;j<S_MT9V03X_W;j++){
			temp_value=image[i][j];
			if(temp_value<value){
				image[i][j]=0;
			}
			else{
				image[i][j]=255;
			}
		}		
	}
}