#include "zf_common_headfile.h"
#include "YUdeal.h"

#define JD_Search_Line  S_MT9V03X_H
#define BX_Search_Start S_MT9V03X_H
#define BX_Search_End   30
#define BX_L_R          10
#define BX_L_L          5
#define BX_R_R          5
#define BX_R_L          10
#define M_M             93

uint8   BX_L_List[S_MT9V03X_H];
uint8   BX_R_List[S_MT9V03X_H];
uint8   M_M_List[S_MT9V03X_H];

uint8 JD_L,JD_R;
void find_JD(uint8 index[S_MT9V03X_H][S_MT9V03X_W]){
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
			if(i-1==1){
				JD_L=S_MT9V03X_W-2;
				break;
			}
		}
	}
	if(index[JD_Search_Line-1][S_MT9V03X_W*3/4]==255&&index[JD_Search_Line-1][S_MT9V03X_W*3/4+1]==255&&index[JD_Search_Line-1][S_MT9V03X_W*3/4-1]==255){
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
			if(i-1==1){
				JD_L=S_MT9V03X_W-2;
				break;
			}
		}
	}
	if(index[JD_Search_Line-1][S_MT9V03X_W*1/4]==255&&index[JD_Search_Line-1][S_MT9V03X_W*1/4+1]==255&&index[JD_Search_Line-1][S_MT9V03X_W*1/4-1]==255){
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
			if(i-1==1){
				JD_L=S_MT9V03X_W-2;
				break;
			}
		}
	}
}
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
void find_BX(uint8 index[S_MT9V03X_H][S_MT9V03X_W]){
	uint8 Point_L=JD_L;
	uint8 Point_R=JD_R;
	for(uint8 i=BX_Search_Start-1;i>BX_Search_End;i--){
		
		uint8 L_Search_Flag=0;
		uint8 ML_Search_Flag=0;
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
		if(L_Search_Flag==1){
			for(uint8 j=Point_L;j>Point_L-BX_L_L;j--){
				if(index[i][j-1]==0&&index[i][j]==255&&index[i][j+1]==255){
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
		uint8 R_Search_Flag=0;
		uint8 MR_Search_Flag=0;
		for(uint8 j=Point_R;j>Point_R-BX_R_L;j--){
			if(index[i][j-1]==255&&index[i][j]==255&&index[i][j+1]==0){
				Point_R=j;
				break;
			}
			else if(j==1){
				Point_L=4;
				break;
			}
			else if(j==Point_R-BX_R_L+1){
				R_Search_Flag=1;
				break;
			}
		}
		if(R_Search_Flag==1){
			for(uint8 j=Point_R;j<Point_L+BX_R_R;j++){
				if(index[i][j-1]==255&&index[i][j]==255&&index[i][j+1]==0){
					Point_R=j;
					break;
			    }
			    else if(j==S_MT9V03X_W-2){
					Point_R=S_MT9V03X_W-2;
					MR_Search_Flag=1;
					break;
				}
				else if(j==Point_L+BX_R_R-1){
					MR_Search_Flag=1;
					break;
				}
		   }
			
	    }
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
	   
	 //
	   BX_L_List[i]=Limit(1,Point_L,S_MT9V03X_W-2);
	   BX_R_List[i]=Limit(1,Point_R,S_MT9V03X_W-2);
	   M_M_List[i]=Limit(1,(BX_L_List[i]+BX_R_List[i])/2,S_MT9V03X_W-2);
	   
	   //猪肺画线显示边线和中线
	}
}


void Draw_Line(){
	for(uint8 i=S_MT9V03X_H-1;i>BX_Search_End;i--){
		ips200_draw_point (BX_L_List[i],i,RGB565_YELLOW);
		ips200_draw_point (BX_R_List[i],i,RGB565_GREEN);
		ips200_draw_point (M_M_List[i],i,RGB565_RED);
	}

}