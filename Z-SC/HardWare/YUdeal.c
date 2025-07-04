#include "zf_common_headfile.h"
#define Gray 255
#define P_Sum MT9V03X_H*MT9V03X_W

uint8 DJthreshold(){
	uint16 histogram[Gray]={0};
	uint32 Gray_Sum[Gray]={0};
	uint8 threshold;
	int sum;
	
	uint8 (*ptr)[120][188]=&image_copy;
	uint16 i;
	uint16 j;
	uint8 gray;
	for(i=0;i<=MT9V03X_H;i++){
		for(j=0;j<=MT9V03X_W;j++){
			gray=(*ptr)[i][j];
			histogram[gray]++;
		}		
	}
	for(i=0;i<Gray;i++){
		Gray_Sum[i]=i*histogram[i];
		sum+=Gray_Sum[i];
	}
	uint16 MinV,MaxV;
	
	for(MinV=0;MinV<Gray&&histogram[MinV]==0;MinV++);
	for(MaxV=Gray;MaxV>MinV&&histogram[MaxV]==0;MinV--);
	
	uint16 b_back=0,b_front=0;
	uint32 u_back_sum=0,u_front_sum=0;
	float a_back=0,a_front=0;
	float deltaTmp=0,deltaMax=0;
	
	for(i=MinV;i<MaxV;i++){
		b_back+=histogram[i];
		b_front=P_Sum-b_back;
		u_back_sum+=Gray_Sum[i];
		u_front_sum =sum-u_back_sum;
		
		a_back=u_back_sum/(float)b_back;
		a_front=u_front_sum/(float)b_front;
		deltaTmp=b_back*b_front*(a_back-a_front)*(a_back-a_front)/(float)P_Sum;
		
		if(deltaTmp>deltaMax){
			deltaMax=deltaTmp;
			threshold=(uint8)i;
		}
		
	}
	
	return threshold;
}