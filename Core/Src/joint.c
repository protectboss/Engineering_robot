#include "joint.h"
#include "tim.h"
#include "remote_control.h"


#define Joint3_Sent 1.5


int16_t speed7_error;

/*关节二速度角偏差计算*/
void synchronization(void)
{
 if(MotoData.moto_6.Rx.temperature&MotoData.moto_7.Rx.temperature)
  {
	  speed7_error=(int16_t)((-MotoData.moto_6.Rx.angle_change-MotoData.moto_7.Rx.angle_change)/500);
  }
}


/*键盘关节一、关节二控制*/
void JointData_processing(void)
{
	if(Remote_Control.Key.Z|Remote_Control.Key.X)
	{
  if(Remote_Control.Key.Z) MotoData.moto_5.Tx.target_speed=-4800;
  else MotoData.moto_5.Tx.target_speed=4800;
	}
	else MotoData.moto_5.Tx.target_speed=0;
	
	
	if(Remote_Control.Mouse.L|Remote_Control.Mouse.R)
	{
   if(Remote_Control.Mouse.L)
	 {
	  MotoData.moto_6.Tx.target_speed=-1600;
    MotoData.moto_7.Tx.target_speed=(1600+speed7_error);
	 }
   else    
	 {
	  MotoData.moto_6.Tx.target_speed=1600;
    MotoData.moto_7.Tx.target_speed=(-1600+speed7_error);
	 }
	}
	else   
	{	
	 MotoData.moto_6.Tx.target_speed=0; 
	 MotoData.moto_7.Tx.target_speed=0+speed7_error;
	}
}


void Joint_Init(void)//关节3直流电机初始化
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET);
}


void Joint_Control(void)
{
if(Remote_Control.Key.C|Remote_Control.Key.V)
{
if(Remote_Control.Key.C) Joint_Direction(-950);
else Joint_Direction(950);
}
else Joint_Stop();
}



void Joint_Direction(int PWM)
{
if(PWM>0) Joint_Up(PWM);
if(PWM<0) Joint_Down(-PWM);
if(PWM==0) Joint_Stop();	
}


void Joint_Down(int PWM)
{
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_2,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_5,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_6,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,PWM);
 __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,PWM);
} 


void Joint_Up(int PWM)
{
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_2,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_5,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_6,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,PWM);
 __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,PWM);
}


void Joint_Stop(void)
{
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_2,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_6,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOI,GPIO_PIN_5,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);
 __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,0);
}

