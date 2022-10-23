#include "quick_clamping.h"
#include "usart.h"
#include <math.h>
#include "remote_control.h"
#include "gyroscope.h"
#include "moto.h"
#include "usart.h"
#include "output_data.h"

int16_t coordinate_x,coordinate_y;
int16_t real_x,real_y;


/**
* @brief  机械臂第一关节解算函数
* @param  x轴目标值，y轴目标值，一号机械臂陀螺仪实时反馈角，误差角比例调节系数
* @return 第一关节电机输出电流值
*/
int16_t Arm_Out1(int16_t x,int16_t y,float angle,float p)
{
	int16_t Moto_out,Le;//电机输出值，目标坐标相较原点直线距离
	float Lf,all,exp_angle;
	
	/*坐标向量长度*/
	Lf = x * x + y * y;

	Le = sqrt(Lf);

	
	/*将反余弦函数的总值先计算好*/
	all = (L1f + Lf - L2f)/(2 * L1 * Le);

	
	/*计算第一关节机械臂的目标角度，并将计算出来的弧度转换为角度*/
	exp_angle = (acos(all) + atan2(y,x))*180.0/Pi;
	
	/*目标角度 - 实时角度 获得机械臂角度误差值*/
	Moto_out = (int16_t)((exp_angle - angle) * p);
	
	return Moto_out;
}


/**
* @brief  机械臂第二关节解算函数
* @param  x轴目标值，y轴目标值，二号机械臂陀螺仪实时反馈角，误差角比例调节系数
* @return 第二关节电机输出电流值
*/
int16_t Arm_Out2(int16_t x,int16_t y,float angle,float p)
{
	int16_t Moto_out,Le;//电机输出值，目标坐标相较原点直线距离
	float Lf,all1,all2,arm_angle1,exp_angle;
	

	Lf = x * x + y * y;
	
	Le = sqrt(Lf);
	
	all1 = (L1f + Lf - L2f)/(2 * L1 * Le);
	
	all2 = (L1f + L2f - Lf)/(2 * L1 * L2);
	
	arm_angle1 = acos(all1) + atan2(y,x);

	
	exp_angle = (arm_angle1 + acos(all2))*180.0/Pi - 180;
	
	Moto_out = (int16_t)((exp_angle - angle) * p);
	
	
	return Moto_out;
}


void Quick_Joint_Move(float x,float y,float P1, float P2)
{
MotoData.moto_5.Tx.target_speed=Arm_Out1(x,y,-angle1[1],P1);
MotoData.moto_6.Tx.target_speed=Arm_Out2(x,y,-angle2[1],P2);
MotoData.moto_7.Tx.target_speed=-Arm_Out2(x,y,-angle2[1],P2)+speed7_error;
}


void Quick_Joint_Remote_control(void)
{
// if(Remote_Control.Key.F|Remote_Control.Key.G|Remote_Control.Key.R)
//  {
//   if(Remote_Control.Key.F|Remote_Control.Key.G) 
//	 {
//	 if(Remote_Control.Key.F) Quick_Joint_Move(55,0,400,150);//F键
//   else Quick_Joint_Move(50,0,400,150);//G键
//	 }
//   else Quick_Joint_Move(60,20,400,150);//R键
//  }
	 if(Remote_Control.Key.R|Remote_Control.Key.Board)
  {
   if(Remote_Control.Key.R) Quick_Joint_Move(55,0,400,150);//R键
   else Quick_Joint_Move(50,0,400,150);//空格键
	 }
}

