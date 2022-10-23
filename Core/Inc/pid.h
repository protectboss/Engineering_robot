#ifndef __PID_H_
#define __PID_H_


#include "tim.h"
#include "moto.h"
#include "remote_control.h"


typedef struct 
{
 float Kp,Ki,Kd;
 float error,error_last;
 float limit;
 float integral,integral_max;
 float output,output_max;
}WZPID_TypeDef;


typedef struct
{
 float Kp,Ki,Kd;
 float error,error_last,error_last_last;
 float outputI,outputI_max;
 float output,output_max;
}ZLPID_TypeDef;


typedef struct
{
 ZLPID_TypeDef No1;
 ZLPID_TypeDef No2;
 ZLPID_TypeDef No3;
 ZLPID_TypeDef No4;
 ZLPID_TypeDef No5;
 ZLPID_TypeDef No6;
 ZLPID_TypeDef No7;
 ZLPID_TypeDef No8;
}ZLPID_NumberTypeDef;


typedef struct
{
 WZPID_TypeDef No6;
 WZPID_TypeDef No7;
 WZPID_TypeDef No8;
}WZPID_NumberTypeDef;


typedef struct
{
ZLPID_NumberTypeDef ZL;
WZPID_NumberTypeDef WZ;
}PID_TypeDef;

void All_Pid_Init(void);
void ZLPid_Init(ZLPID_TypeDef *ZLpid,float p,float i,float d,float Intergral_max,float Out_max);
void ZLPid(ZLPID_TypeDef *ZLpid,float target,float real);
void WZPid_Init(WZPID_TypeDef *WZpid,float p,float i,float d,float Integral_max,float Out_max,float limit);
void WZPid(WZPID_TypeDef *WZpid,float target,float real);


extern PID_TypeDef Pid;






#endif

