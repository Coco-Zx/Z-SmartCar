#include "zf_common_headfile.h"
#include "YUdeal.h"
#include "buzzer.h"
#include "key.h"                                                                 
#include "Motor.h"        
#define JD_Search_Line  S_MT9V03X_H   //基点搜寻起始行
#define BX_Search_Start S_MT9V03X_H   //边线搜寻起始行
#define BX_Search_End   20 			  //边线搜寻终止行
#define DX_Search_Start S_MT9V03X_H-10   //边线搜寻起始行
#define DX_Search_End   20 			  //边线搜寻终止行
#define BX_L_R          10            //左边线-右搜寻
#define BX_L_L          5			  //左边线-左搜寻
#define BX_R_R          5			  //右边线-右搜寻
#define BX_R_L          10            //右边线-左搜寻
#define M_M             93			  //中间行
#define ZX_Limit        5
#define GD_Change_Min   5
#define GD_Change_Max   7

#define array_size  (DX_Search_Start - DX_Search_End) / 2
uint8               QZ_L=0;
uint8   BX_L_List[S_MT9V03X_H];//左边线
uint8   BX_R_List[S_MT9V03X_H];//右边线
uint8   M_M_List[S_MT9V03X_H];//中线

uint8 JD_L,JD_R;//左右基点
void find_JD(uint8 index[S_MT9V03X_H][S_MT9V03X_W]){
	//1/2处找基点
	if(index[JD_Search_Line-1][S_MT9V03X_W/2]==255&&index[JD_Search_Line-1][S_MT9V03X_W/2+1]==255&&index[JD_Search_Line-1][S_MT9V03X_W/2-1]==255){
		for(uint8 i=S_MT9V03X_W/2;i>0;i--){
			if(index[JD_Search_Line-1][i-1]==0&&index[JD_Search_Line-1][i]==255&&index[JD_Search_Line-1][i+1]==255){
				JD_L=i;
				break;
			}
			if(i-1==1){
				JD_L=1;
				break;
			}
		}
		for(uint8 i=S_MT9V03X_W/2;i<S_MT9V03X_W-2;i++){
			if(index[JD_Search_Line-1][i-1]==255&&index[JD_Search_Line-1][i]==255&&index[JD_Search_Line-1][i+1]==0){
				JD_R=i;
				break;
			}
			if(i+1==S_MT9V03X_W-2){
				JD_R=S_MT9V03X_W-2;
				break;
			}
		}
	}
	//3/4找基点
	else if(index[JD_Search_Line-1][S_MT9V03X_W*3/4]==255&&index[JD_Search_Line-1][S_MT9V03X_W*3/4+1]==255&&index[JD_Search_Line-1][S_MT9V03X_W*3/4-1]==255){
		for(uint8 i=S_MT9V03X_W*3/4;i>0;i--){
			if(index[JD_Search_Line-1][i-1]==0&&index[JD_Search_Line-1][i]==255&&index[JD_Search_Line-1][i+1]==255){
				JD_L=i;
				break;
			}
			if(i-1==1){
				JD_L=1;
				break;
			}
		}
		for(uint8 i=S_MT9V03X_W*3/4;i<S_MT9V03X_W-2;i++){
			if(index[JD_Search_Line-1][i-1]==255&&index[JD_Search_Line-1][i]==255&&index[JD_Search_Line-1][i+1]==0){
				JD_R=i;
				break;
			}
			if(i+1==S_MT9V03X_W-2){
				JD_R=S_MT9V03X_W-2;
				break;
			}
		}
	}
	//1/4找基点
	else if(index[JD_Search_Line-1][S_MT9V03X_W*1/4]==255&&index[JD_Search_Line-1][S_MT9V03X_W*1/4+1]==255&&index[JD_Search_Line-1][S_MT9V03X_W*1/4-1]==255){
		for(uint8 i=S_MT9V03X_W*1/4;i>0;i--){
			if(index[JD_Search_Line-1][i-1]==0&&index[JD_Search_Line-1][i]==255&&index[JD_Search_Line-1][i+1]==255){
				JD_L=i;
				break;
			}
			if(i-1==1){
				JD_L=1;
				break;
			}
		}
		for(uint8 i=S_MT9V03X_W*1/4;i<S_MT9V03X_W-2;i++){
			if(index[JD_Search_Line-1][i-1]==255&&index[JD_Search_Line-1][i]==255&&index[JD_Search_Line-1][i+1]==0){
				JD_R=i;
				break;
			}
			if(i+1==S_MT9V03X_W-2){
				JD_R=S_MT9V03X_W-2;
				break;
			}
		}
	}
}
//限制函数
uint8 Limit(uint8 a,uint8 b,uint8 c){
	if(b>=a&&b<=c){
		return b;
	}
	else if(b<a){
		return a;
	}
	else if(b>c){
		return c;
	}
	return a;
}
//边线寻找
void find_BX(uint8 index[S_MT9V03X_H][S_MT9V03X_W]){
	uint8 Point_L=JD_L;
	uint8 Point_R=JD_R;
	//左边线寻找
	for(uint8 i=BX_Search_Start-1;i>BX_Search_End;i--){
		
		uint8 L_Search_Flag=0;//往左寻找标志位
		uint8 ML_Search_Flag=0;//中左寻找标志位
		//左边线往右找
		for(uint8 j=Point_L;j<Point_L+BX_L_R;j++){
			if(index[i][j-1]==0&&index[i][j]==255&&index[i][j+1]==255){
				Point_L=j;
				break;
			}
			else if(j==S_MT9V03X_W-2){
				Point_L=S_MT9V03X_W-5;
				break;
			}
			else if(j==Point_L+BX_L_R-1){
				L_Search_Flag=1;
				break;
			}
		}
		//左边线往左找
		if(L_Search_Flag==1){
			for(uint8 j=Point_L;j>Point_L-BX_L_L;j--){
				if(index[i][j-1]==0&&index[i][j]==255&&index[i][j+1]==255&&j<S_MT9V03X_W-5){
					Point_L=j;
					break;
			    }
			    else if(j==1){
					Point_L =1;
					ML_Search_Flag=1;
					break;
				}
				else if(j==Point_L-BX_L_L+1){
					ML_Search_Flag=1;
					break;
				}
		   }
			
	    }
		//中间开始找左边线
		if(ML_Search_Flag==1){
			for(uint8 j=M_M;j>0;j--){
				if(index[i][j-1]==0&&index[i][j]==255&&index[i][j+1]==255){
					Point_L=j;
					break;
			    }
			    else if(j==1){
					Point_L =1;
					break;
				}
		   }
	   }
		uint8 R_Search_Flag=0;//往右寻找标志位
		uint8 MR_Search_Flag=0;//中右寻找标志位;
	   //右边线往左找
		for(uint8 j=Point_R;j>Point_R-BX_R_L;j--){
			if(index[i][j-1]==255&&index[i][j]==255&&index[i][j+1]==0){
				Point_R=j;
				break;
			}
			else if(j==1){
				Point_R=4;
				break;
			}
			else if(j==Point_R-BX_R_L+1){
				R_Search_Flag=1;
				break;
			}
		}
		//右边线往右找
		if(R_Search_Flag==1){
			for(uint8 j=Point_R;j<Point_R+BX_R_R;j++){
				if(index[i][j-1]==255&&index[i][j]==255&&index[i][j+1]==0&&j>4){
					Point_R=j;
					break;
			    }
			    else if(j==S_MT9V03X_W-2){
					Point_R=S_MT9V03X_W-2;
					MR_Search_Flag=1;
					break;
				}
				else if(j==Point_R+BX_R_R-1){
					MR_Search_Flag=1;
					break;
				}
		   }
			
	    }
		//中间开始找右边线
		if(MR_Search_Flag==1){
			for(uint8 j=M_M;j<S_MT9V03X_W-1;j++){
				if(index[i][j-1]==255&&index[i][j]==255&&index[i][j+1]==0){
					Point_R=j;
					break;
			    }
			    else if(j==S_MT9V03X_W-2){
					Point_R =S_MT9V03X_W-2;
					break;
				}
		   }
	   }
	   
		//猪肺画线显示边线和中线
	   BX_L_List[i]=Limit(1,Point_L,S_MT9V03X_W-2);
	   BX_R_List[i]=Limit(1,Point_R,S_MT9V03X_W-2);
	  
	   
	   
	}
}

uint8 DX_L_Count;
uint8 DX_R_Count;
uint8 DX_M_Count;
	
uint8 DX_L_Start;
uint8 DX_R_Start;
uint8 DX_M_Start;
void Deal_DX(){
	DX_L_Count=0;
	DX_R_Count=0;
	DX_M_Count=0;
	
	DX_L_Start=0;
	DX_R_Start=0;
	DX_M_Start=0;

    // 计算实际需要的数组大小（考虑步长2）
  
    uint8 DX_L_Flag=0;
    uint8 DX_R_Flag=0;

    // 使用转换后的索引进行遍历
    for (uint8 i = DX_Search_Start-1; i > DX_Search_End; i -= 2) {
        // 左线检测
        if (BX_L_List[i] == 1) {
            DX_L_Flag= 1;
            DX_L_Count++;
            if (DX_L_Start == 0) {
                DX_L_Start = i;
            }
			ips200_show_int (180, 260,DX_L_Start,3);
        }
		if(BX_R_List[i]==S_MT9V03X_W-2){
			DX_R_Flag=1;
			DX_R_Count++;
			if(DX_R_Start==0){
				DX_R_Start=i;
			}
			ips200_show_int (180, 280,DX_R_Start,3);
		}
		if(DX_L_Flag==1&&DX_R_Flag==1){
			DX_M_Count++;
			if(DX_M_Start==0){
				DX_M_Start=i;
				ips200_show_int (180, 300,DX_M_Start,3);
			}
		}
		DX_L_Flag=0;
		DX_R_Flag=0;
	}
}
uint8 GD_L_H;
uint8 GD_R_H;
uint8 GD_L_L=DX_Search_Start-1;
uint8 GD_R_L=DX_Search_Start-1;

void Deal_GD(){
	GD_L_H=0;
	GD_R_H=0;
	GD_L_L=0;
	GD_R_L=0;
	
	for(uint8 i=DX_L_Start;i+3<DX_Search_Start;i++){
		if(BX_L_List[i+1]-BX_L_List[i]>GD_Change_Max){
			if(BX_L_List[i+2]-BX_L_List[i+1]<GD_Change_Min){
				if(BX_L_List[i+3]-BX_L_List[i+2]<GD_Change_Min){
					GD_L_L=i+1;
				
					break;
				}
			}
		}
	}
	for(uint8 i=DX_R_Start;i+3<DX_Search_Start;i++){
		if(abs(BX_R_List[i+1]-BX_R_List[i])>GD_Change_Max){
			if(abs(BX_R_List[i+2]-BX_R_List[i+1])<GD_Change_Min){
				if(abs(BX_R_List[i+3]-BX_R_List[i+2])<GD_Change_Min){
					GD_R_L=i+1;
					break;
				}
			}
		}
	}
	for(uint8 i=DX_L_Start;i-3>DX_Search_End;i--){
		if(BX_L_List[i-1]-BX_L_List[i]>GD_Change_Max){
			if(BX_L_List[i-2]-BX_L_List[i-1]<GD_Change_Min){
				if(BX_L_List[i-3]-BX_L_List[i-2]<GD_Change_Min){
					GD_L_H=i-1;
				
					break;
				}
			}
		}
	}
	for(uint8 i=DX_R_Start;i-3>DX_Search_End;i--){
		if(abs(BX_R_List[i-1]-BX_R_List[i])>GD_Change_Max){
			if(abs(BX_R_List[i-2]-BX_R_List[i-1])<GD_Change_Min){
				if(abs(BX_R_List[i-3]-BX_R_List[i-2])<GD_Change_Min){
					GD_R_H=i-1;
				
					break;
				}
			}
		}
	}
}


void BX_L(uint8 BX_Start_X,uint8 BX_End_X,uint8 BX_Start_Y,uint8 BX_End_Y){
	float K_L=(float)(BX_End_Y - BX_Start_Y) / (BX_End_X - BX_Start_X);
	for(uint8 i=BX_Start_X;i<=BX_End_X;i++){
		BX_L_List[i]=BX_L_List[BX_Start_X]+(int)(K_L*(i-BX_Start_X));
	}
}

void BX_R(uint8 BX_Start_X,uint8 BX_End_X,uint8 BX_Start_Y,uint8 BX_End_Y){
	float K_R=(float)(BX_End_Y - BX_Start_Y) / (BX_End_X - BX_Start_X);
	for(uint8 i=BX_Start_X;i<=BX_End_X;i++){
		BX_R_List[i]=BX_R_List[BX_Start_X]+(int)(K_R*(i-BX_Start_X));
	}
}

int QZ=60;
int Cross_Flag=0;
void Deal_Cross(){
	
		Cross_Flag=0;
		if(DX_M_Count>4
			&&image[DX_M_Start][S_MT9V03X_W/2]==255&&image[DX_M_Start][S_MT9V03X_W/2+1]==255&&image[DX_M_Start][S_MT9V03X_W/2-1]==255
			&&image[DX_M_Start-4][S_MT9V03X_W/2]==255&&image[DX_M_Start-4][S_MT9V03X_W/2+1]==255&&image[DX_M_Start-4][S_MT9V03X_W/2-1]==255){
			Deal_GD();
			
			DX_M_Count=0;
//			ips200_show_int (180,180 ,GD_L_L,3);
//			ips200_show_int (180,200 ,GD_R_L,3);
//			ips200_show_int (180,220 ,GD_L_H,3);
//			ips200_show_int (180,240 ,GD_R_H,3);
//			Buzzer_On();
			
		}
		if(GD_L_H>0&&GD_R_H>0){
			Cross_Flag=1;
			Buzzer_On();
			if(GD_L_L&&GD_R_L){
				BX_L(GD_L_H,GD_L_L,BX_L_List[GD_L_H],BX_L_List[GD_L_L]);
				BX_R(GD_R_H,GD_R_L,BX_R_List[GD_R_H],BX_R_List[GD_R_L]);
			}
			if(GD_L_L&&!GD_R_L){
				BX_L(GD_L_H,GD_L_L,BX_L_List[GD_L_H],BX_L_List[GD_L_L]);
				BX_R(GD_R_H,S_MT9V03X_H-1,BX_R_List[GD_R_H],BX_R_List[S_MT9V03X_H-1]);
			}
			if(!GD_L_L&&GD_R_L){
				BX_L(GD_L_H,S_MT9V03X_H-1,BX_L_List[GD_L_H],BX_L_List[S_MT9V03X_H-1]);
				BX_R(GD_R_H,GD_R_L,BX_R_List[GD_R_H],BX_R_List[GD_R_L]);
			}
			if(!GD_L_L&&!GD_R_L){
				BX_R(GD_R_H,S_MT9V03X_H-1,BX_R_List[GD_R_H],BX_R_List[S_MT9V03X_H-1]);
				BX_L(GD_L_H,S_MT9V03X_H-1,BX_L_List[GD_L_H],BX_L_List[S_MT9V03X_H-1]);
			}
		}
		GD_L_H=0;
		GD_R_H=0;
		GD_L_L=0;
	    GD_R_L=0;
}	
void find_ZX(){
	for(uint8 i=BX_Search_Start-1;i>BX_Search_End;i--){
		M_M_List[i]=Limit(1,(BX_L_List[i]+BX_R_List[i])/2,S_MT9V03X_W-2);
	}
}

void QZ_Limit(){
	for(uint8 i=BX_Search_Start-6;i>BX_Search_End;i--){
		if(abs(M_M_List[i+1]-M_M_List[i])>ZX_Limit){
			QZ_L = i+1+4;
			break;
		}
	}
}
//画中线和边线函数
void Draw_Line(){
	for(uint8 i=S_MT9V03X_H-1;i>BX_Search_End;i--){
		ips200_draw_point (BX_L_List[i],i,RGB565_RED);
		ips200_draw_point (BX_L_List[i]+1,i,RGB565_RED);
		ips200_draw_point (BX_R_List[i],i,RGB565_RED);
		ips200_draw_point (BX_R_List[i]-1,i,RGB565_RED);
		ips200_draw_point (M_M_List[i]+1,i,RGB565_GREEN);
		ips200_draw_point (M_M_List[i]-1,i,RGB565_GREEN);
		ips200_draw_point (M_M_List[i],i,RGB565_GREEN);
	}

}
//中线权重数组
uint8 M_W_List[120]=
{
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	6,6,6,6,6,6,6,6,6,6,
	7,8,9,10,11,12,13,14,15,16,
	17,18,19,20,20,20,20,19,18,17,
	16,15,14,13,12,11,10,9,8,7,
	6,6,6,6,6,6,6,6,6,6,
	1,1,1,1,1,1,1,1,1,1,
};
uint8 Last_M_Out=97;//中线权重上一次输出
uint8 M_W_Finally;

//中线权重计算


void Protect(){
	uint8 Counter=0;
	for(uint8 i=118;i>110;i--){
		if(image[i][S_MT9V03X_W/2]==0){
			Counter++;
		}
	}
	if(Counter>5){
		Car_Flag=0;
		ips200_show_string(0, 300, " ST!");
		Motor_Stop();
	}
}

void Stop(){
	uint8 Counter=0;
	uint8 flag=0;
	for(uint8 i=1;i<187;i++){
		if(image[S_MT9V03X_H/2][i]==255&&flag==0){
			flag=1;
		}
		if(image[S_MT9V03X_H/2][i]==0&&flag==1){
			Counter++;
			flag=0;
		}
	}
	if(Counter>5){
		Car_Flag=0;
		ips200_show_string(0, 300, " ST!");
		Motor_Stop();
	}
}
float M_Weight(){
	float M_Out;
	int temp=QZ;
	uint32 M_W_Sum=0;
	if(QZ<QZ_L){
		QZ=QZ_L;
	}
	ips200_show_int (180,240 ,QZ,3);
	for(uint8 i=QZ;i>QZ-5;i--){
		M_W_Sum+=M_M_List[i];
	}
	QZ=temp;
	QZ_L=QZ;
	M_Out=M_W_Sum/5;
	return M_Out;
}
//float M_Weight(){
//	uint8 M_Out;
//	uint8 M_Value;
//	uint32 M_W_Sum=0;
//	uint32 W_Sum=0;
//	for(uint8 i=S_MT9V03X_H-1;i>BX_Search_End;i--){
//		M_W_Sum+=M_M_List[i]*M_W_List[i];
//		W_Sum+=M_W_List[i];
//	}
//	M_Value=(uint8)(M_W_Sum/W_Sum);
//	M_Out=Last_M_Out*0.2+M_Value*0.8;
//	Last_M_Out=M_Out;
//	return M_Out;
//}