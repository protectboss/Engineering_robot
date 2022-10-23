#include "angle.h"

Angle_TypeDef Angle;


int16_t ABS(int16_t number)
{
 if(number<0)
 {
  number=-number;
 }
 return number;
}


/*变化角度计算*/
void Angle_Turn(MotoData_RxTypeDef *moto,AngleData_TypeDef *angle,int T)
{
 if(moto->temperature)
 {
	if(angle->cnt==0)
	{
	 angle->angle_old=moto->angle;
	 angle->cnt=1;
	}
	angle->angle=moto->angle;
	angle->err=angle->angle-angle->angle_old;
  
  if(angle->err>0)
	{
	 angle->compare1=angle->err-T;
	 angle->compare2=angle->err;
	}
	else
	{
	 angle->compare1=angle->err+T;
	 angle->compare2=angle->err;
	}
	if(ABS(angle->compare1)<ABS(angle->compare2))
	{
	 angle->err_real=angle->compare1;
	}
	else
	{
	 angle->err_real=angle->compare2;
	}
	moto->angle_change+=angle->err_real;
	angle->angle_old=angle->angle;
 }
}


void No8_Angle_Turn(MotoData_RxTypeDef *moto,AngleData_TypeDef *angle,int T)
{
 if(moto->current) moto->temperature=1;
 if(moto->temperature)
 {
	if(angle->cnt==0)
	{
	 angle->angle_old=moto->angle;
	 angle->cnt=1;
	}
	angle->angle=moto->angle;
	angle->err=angle->angle-angle->angle_old;
  
  if(angle->err>0)
	{
	 angle->compare1=angle->err-T;
	 angle->compare2=angle->err;
	}
	else
	{
	 angle->compare1=angle->err+T;
	 angle->compare2=angle->err;
	}
	if(ABS(angle->compare1)<ABS(angle->compare2))
	{
	 angle->err_real=angle->compare1;
	}
	else
	{
	 angle->err_real=angle->compare2;
	}
	moto->angle_change+=angle->err_real;
	angle->angle_old=angle->angle;
 }
}
