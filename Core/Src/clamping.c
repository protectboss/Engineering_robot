#include "clamping.h"
#include "remote_control.h"
#include "tim.h"

//void Clamping_Control(void)
//{
//if(Remote_Control.Mouse.L|Remote_Control.Mouse.R)
//{	
// 	if(Remote_Control.Mouse.L) Clamping_On();
//	else Clamping_Off();
//}
//else Clamping_Stop();
//}


void Clamping_Control(void)
{
if(Remote_Control.Key.F|Remote_Control.Key.G)
{	
 	if(Remote_Control.Key.F) Clamping_On();
	else Clamping_Off();
}
else Clamping_Stop();
}


void Clamping_On(void)
{
  HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET);
}


void Clamping_Off(void)
{
  HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET);
}


void Clamping_Stop(void)
{
 HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET);
}


void rotate(void)
{
if(Remote_Control.Key.Q|Remote_Control.Key.E)
 {
 if(Remote_Control.Key.Q) MotoData.moto_8.Tx.target_speed=-700;
 else MotoData.moto_8.Tx.target_speed=700;
 }
 else MotoData.moto_8.Tx.target_speed=0;
}


void rotate_limit(void)
{
if(MotoData.moto_8.Rx.angle_change>294912)
{
if(MotoData.moto_8.Tx.target_speed>0) MotoData.moto_8.Tx.target_speed=0;
}
if(MotoData.moto_8.Rx.angle_change<-294912)
{
if(MotoData.moto_8.Tx.target_speed<0) MotoData.moto_8.Tx.target_speed=0;
}
}

