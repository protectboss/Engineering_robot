#include "protect.h"


#include "remote_control.h"
#include "joint.h"
#include "clamping.h"
#include "pid.h"
#include "gpio.h"

int32_t Protect_Cnt;
extern uint32_t Remote_Control_Normal;
extern uint32_t Protect_Number6;
extern uint32_t Protect_Number7;
int16_t Protect2_No6;
int16_t Protect2_No7;
/*Ò£¿ØÆ÷¶ÏÁ¬±£»¤*/
void Protect_RemoteControl(void)
{
 if(Remote_Control_Normal>50)
 {
  MotoData.moto_1.Tx.target_speed=0;
  MotoData.moto_2.Tx.target_speed=0;
  MotoData.moto_3.Tx.target_speed=0;
  MotoData.moto_4.Tx.target_speed=0;
  MotoData.moto_5.Tx.target_speed=0;
  MotoData.moto_6.Tx.target_speed=0;
  MotoData.moto_7.Tx.target_speed=0;
	MotoData.moto_8.Tx.target_speed=0;
	Remote_Control.Key.F=0;
	Remote_Control.Key.G=0;
	Remote_Control.Key.C=0;
	Remote_Control.Key.V=0;
  Joint_Stop();
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
 }
 else
 {
 	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
 }
}


void Protect_Joint1(void)
{
  if((Protect_Number6<1000&Protect_Number6>30)|(Protect_Number7<1000&Protect_Number7>30))
  {
	 HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET);	
  }
	else
	{
	 HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET);	
	}
}


void Protect_Joint2(void)
{
 if((MotoData.moto_6.Rx.temperature==0)|(MotoData.moto_7.Rx.temperature==0))
 {
  MotoData.moto_6.Tx.target_speed=0;
	MotoData.moto_7.Tx.target_speed=0;
 }
 if((Protect2_No6==MotoData.moto_6.Rx.current)|(Protect2_No7==MotoData.moto_7.Rx.current)) Protect_Cnt++;
 else Protect_Cnt=1;
 Protect2_No6=MotoData.moto_6.Rx.current;
 Protect2_No7=MotoData.moto_7.Rx.current;
 if(Protect_Cnt>50)
 {
  MotoData.moto_6.Tx.target_speed=0;
	MotoData.moto_7.Tx.target_speed=0;
 }
}

