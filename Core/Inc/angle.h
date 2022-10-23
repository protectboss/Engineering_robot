#ifndef __ANGLE_H_
#define __ANGLE_H_


#include "moto.h"


typedef struct
{
 int16_t compare1,compare2;
 int16_t angle,angle_old;
 int16_t err;
 int16_t err_real;
 int8_t cnt;
}AngleData_TypeDef;

typedef struct
{
 AngleData_TypeDef No5;
 AngleData_TypeDef No6;
 AngleData_TypeDef No7;
 AngleData_TypeDef No8;
}Angle_TypeDef;


int16_t ABS(int16_t number);
void Angle_Turn(MotoData_RxTypeDef *moto,AngleData_TypeDef *angle,int T);
void No8_Angle_Turn(MotoData_RxTypeDef *moto,AngleData_TypeDef *angle,int T);
extern Angle_TypeDef Angle;


#endif

