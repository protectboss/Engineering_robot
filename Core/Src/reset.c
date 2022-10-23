#include "reset.h"
#include "moto.h"
#include "remote_control.h"


int moto5_limit;


void Reset_Init(void)	
{
 if(Remote_Control.Key.Ctrl)
 {
  MotoData.moto_5.Tx.target_speed=400;
 }
}


void Limit_Moto_No5(void)
{
 if(moto5_limit==0)
 {
  if(MotoData.moto_5.Tx.target_speed>0) MotoData.moto_5.Tx.target_speed=0;
	MotoData.moto_5.Rx.angle_change=0;
 }
 if(MotoData.moto_5.Rx.angle_change<-2300000)
 {
 if(MotoData.moto_5.Tx.target_speed<0) MotoData.moto_5.Tx.target_speed=0;
 }	 
}


void Moto5_Limit(void)
{
moto5_limit=HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_10);
}
