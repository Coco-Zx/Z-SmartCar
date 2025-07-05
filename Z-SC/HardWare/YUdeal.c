#include "zf_common_headfile.h"
#include "YUdeal.h" 

void filter(){
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

uint8 DJthreshold(uint8 index[S_MT9V03X_H][S_MT9V03X_W]){
	uint16 histogram[Gray]={0};
	uint32 Gray_Sum[Gray]={0};
	uint8 threshold=0;
	int sum=0;
	uint32 S_P_Sum=S_MT9V03X_H*S_MT9V03X_W;
	uint16 i;
	uint16 j;
	uint8 gray;
	for(i=0;i<S_MT9V03X_H;i++){
		for(j=0;j<S_MT9V03X_W;j++){
			gray=index[i][j];
			histogram[gray]++;
		}		
	}
	for(i=0;i<Gray;i++){
		Gray_Sum[i]=i*histogram[i];
		sum+=Gray_Sum[i];
	}
	uint16 MinV,MaxV;
	
	for(MinV=5;MinV<Gray&&histogram[MinV]==0;MinV++);
	for(MaxV=Gray-6;MaxV>MinV&&histogram[MaxV]==0;MaxV--);
	ips200_show_int (100,190,MinV,3);
	ips200_show_int (100,210,MaxV,3);
	if(MinV==MaxV){
		return (uint8)MinV;
	}
	if(MinV+1==MaxV){
		return (uint8)MaxV;
	}
	
	uint16 b_back=0,b_front=0;
	uint32 u_back_sum=0,u_front_sum=0;
	float a_back=0,a_front=0;
	float deltaTmp=0,deltaMax=0;
	
	for(i=MinV;i<MaxV;i++){
		b_back+=histogram[i];
		b_front=S_P_Sum-b_back;
		u_back_sum+=Gray_Sum[i];
		u_front_sum =sum-u_back_sum;
		
		a_back=u_back_sum/(float)b_back;
		a_front=u_front_sum/(float)b_front;
		deltaTmp=b_back*b_front*(a_back-a_front)*(a_back-a_front)/(float)S_P_Sum;
		
		if(deltaTmp>deltaMax){
			deltaMax=deltaTmp;
			threshold=(uint8)i;
		}
		
	}
	ips200_show_int (100,230,threshold,3);
	return threshold;
}

//uint8 DJthreshold(uint8 index[S_MT9V03X_H][S_MT9V03X_W]){
//	uint8 threshold;
//	uint8 gray_value;
//	
//	float SumPK=0;
//	float SumMK=0;
//	float Var=0;
//	float Vartmp=0;
//	
//	uint16 Hist[Gray]={0};
//	float P[Gray]={0};
//	float PK[Gray]={0};
//	float MK[Gray]={0};
//	
//	for(uint8 i=0;i<S_MT9V03X_H;i++){
//		for(uint8 j=0;j<S_MT9V03X_W;j++){
//			gray_value=index[i][j];
//			Hist[gray_value]++;
//		}
//	}
//	
//	for(uint16 i=0;i<Gray;i++){
//		P[i]=(float)Hist[i]/S_P_Sum;
//		PK[i]=SumPK+P[i];
//		SumPK=PK[i];
//		MK[i]=SumMK+i*P[i];
//		SumMK=MK[i];
//	}
//	
//	for(uint8 i=5;i<245;i++){
//		Vartmp=((MK[Gray-1]*PK[i]-MK[i])*(MK[Gray-1]*PK[i]-MK[i]))/(PK[i]*(1-PK[i]));
//		if(Vartmp>Var){
//			Var=Vartmp;
//			threshold=i;
//		}
//	}
//	return threshold;
//}


void Set_image_T(uint8 value){
	uint8 temp_value;
	uint8 (*ptr)[S_MT9V03X_H][S_MT9V03X_W]=&image_copy;
	uint16 i;
	uint16 j;
	for(i=0;i<=S_MT9V03X_H;i++){
		for(j=0;j<=S_MT9V03X_W;j++){
			temp_value=(*ptr)[i][j];
			if(temp_value<value){
				(*ptr)[i][j]=0;
			}
			else{
				(*ptr)[i][j]=255;
			}
		}		
	}
}